#include "calc3.h"
#include "compiler.h"
#include "y.tab.h"

int pos = 1;
int inside_prog = 0;
int prog_vars = 0;
int inside_proc = 0;

int proc_params = 0;
int proc_vars = 0;

int calling_proc = -1;

int first_prog_stmt = 4;
int args = 0;

int saw_return;



struct type_stack * top_of_stack = NULL;
struct statement * first_statement = NULL;
struct statement * last_statement = NULL;

struct proc * first_proc = NULL;
struct proc * last_proc = NULL;

int ex(nodeType *p) {
    int type1, type2;
	int start_of_loop;
	int jmp_pos;
	int jmp_pos2;
	int start_prog;
	int start_proc;
	char tmp_str[MAX_STMT_LEN];
	char tmp_str2[MAX_STMT_LEN];
	int i;
	///*fprintf(stderr,%d\n,p->type);*/
    if (!p) return 0;
    switch(p->type) {
	printTypeStack();
    case typeIntCon:       
		/*fprintf(stderr,Int constant\n);*/
		push_asm_statement(I_Constant,2,0,p->iCon.value);
		push_type(typeIntCon);	
        break;
	case typeFloatCon:
		/*fprintf(stderr,Float constant\n);*/
		push_asm_statement(R_Constant,2,1,p->fCon.value);
		push_type(typeFloatCon);
        break;
    case typeIntId:        
		/*fprintf(stderr,Int Variable\n);*/
		push_asm_statement(I_Variable,4,0,0,0,p->iId.i + 3);
		push_type(typeIntId);
		break;
	case typeFloatId:
		/*fprintf(stderr,Float Variable\n);*/
		push_asm_statement(R_Variable,4,0,0,0,p->fId.i + 3);
		push_type(typeFloatId);
        break;
    case typeOpr:
        switch(p->opr.oper) {
		case PROG:
			/*fprintf(stderr,Prog Call\n);*/
			start_prog = pos;
			inside_prog = 1;
			push_asm_statement(I_Prog,4,0,0,0,4); //Placeholder
			ex(p->opr.op[0]);
			push_asm_statement(I_EndProg,0);
			replace_asm_statement(start_prog,I_Prog, 4, 0, prog_vars, 0, first_prog_stmt);
			break;
		case PROC:
			/*fprintf(stderr,Proc Def\n);*/
			if(inside_proc == 0 ){
				struct proc * new_proc = (struct proc *)malloc(sizeof(struct proc));
				if(first_proc == NULL){
					first_proc = new_proc;
					last_proc = new_proc;
				}else{
					last_proc->next_proc = new_proc;
					last_proc = new_proc;
				}
				new_proc->position = pos;
				new_proc->id = p->opr.op[0]->iId.i;
				new_proc->return_value = -1;

				for(i = 0; i < sizeof(new_proc->params); i=i+1){
					new_proc->params[i] = -1;
				}

				inside_proc = 1;
				start_proc = pos;
				push_asm_statement(I_Proc, 4, 0,0,0,0); //Placeholder
				if( p->opr.nops == 4 ){
					proc_params = 0;
					ex(p->opr.op[3]);
					new_proc->return_pos = (-1 * proc_vars) + -3;
				}
				ex(p->opr.op[1]);
				push_asm_statement(I_EndProc,0);
				first_prog_stmt = pos;
				replace_asm_statement(start_proc,I_Proc,4,0,proc_vars,0,start_proc+3);
			
				while( pop_type() != -1 );

				inside_proc = 0;
				ex(p->opr.op[2]);
			}else{
				yyerror("Cannot nest Procedure definitions");
				exit(1);
			}
			break;
		case FUNC:
			/*fprintf(stderr,Func Def\n);*/
			if(inside_proc == 0 ){
				saw_return = 0;

				//push a proc onto list
				struct proc * new_proc = (struct proc *)malloc(sizeof(struct proc));
				if(first_proc == NULL){
					first_proc = new_proc;
				}else{
					last_proc->next_proc = new_proc;
				}
				last_proc = new_proc;

				//set its start position and id
				new_proc->position = pos;
				new_proc->id = p->opr.op[1]->iId.i;

				//initialize params to -1
				for(i = 0; i < sizeof(new_proc->params); i=i+1){
					new_proc->params[i] = -1;
				}

				//we're now inside a procedure
				inside_proc = 1;
				start_proc = pos;
				push_asm_statement(I_Proc, 4, 0, 0, 0, 0); //Placeholder

				//if params, take care of them
				if( p->opr.nops == 5 ){
					proc_params = 0;
					ex(p->opr.op[4]);
				}
				new_proc->return_pos = (-1 * proc_vars) + -3;
				new_proc->return_value = p->opr.op[0]->iCon.value;
				if(new_proc->return_value == typeIntId){ 
					new_proc->return_value = typeIntCon;
				}else{
					new_proc->return_value = typeFloatCon;
				}

				//execute function statements
				ex(p->opr.op[2]);
			
				push_asm_statement(I_EndProc,0);
				first_prog_stmt = pos;
				replace_asm_statement(start_proc,I_Proc,4,0,proc_vars,0,start_proc+3);
				
				if(saw_return == 0){
					yyerror("Function without return statement");
					exit(1);
				}

				while( pop_type() != -1 );

				inside_proc = 0;

				ex(p->opr.op[3]);
			}else{
				yyerror("Cannot nest Procedure definitions");
				exit(1);
			}
			break;
		case CALL:
			/*fprintf(stderr,Call of func/proc\n);*/
			calling_proc = p->opr.op[0]->iId.i;
			ex(p->opr.op[1]);
			if(p->opr.op[1] == NULL && get_proc(calling_proc)->params[0] != -1){
				yyerror("Insufficient arguments");
				exit(1);
			}
			push_asm_statement(I_Call,4,0,inside_proc,0,get_proc_start(calling_proc));
			type1 = get_proc(calling_proc)->return_value;
			if( type1 != -1 ){
				push_type(type1);
			}
			break;
		case ARGS:
			/*fprintf(stderr,Parse Arg\n);*/
			ex(p->opr.op[0]);
			type1 = pop_type();
			type2 = get_proc(calling_proc)->params[args];
			//fprintf(stderr,%d =? %d\n, type1, get_proc(calling_proc)->params[args]);
			
			if(type1 == typeFloatId){
				push_asm_statement(R_Value,0);
				type1 = typeFloatCon;
			}else if(type1 == typeIntId){
				push_asm_statement(I_Value,0);
				type1 = typeIntCon;
			}

			if(type2 == typeIntId){
				if(type1 == typeFloatCon){
					push_asm_statement(R_To_I,0);
					type1 = typeIntCon;
				}	
			}else if(type2 == typeFloatId){
				if(type1 == typeIntCon){
					push_asm_statement(I_To_R,0);
					type1 = typeFloatCon;
				}
			}

			if((type1 == typeFloatCon && type2 == typeFloatId) || (type1 == typeIntCon && type2 == typeIntId)){
				if( p->opr.op[1] != NULL ){
					args += 1;
					ex(p->opr.op[1]);
				}
			}else{
				yyerror("Argument error");
				exit(1);
			}
			break;
		case RETURN:
			/*fprintf(stderr,Return\n);*/
			if( inside_proc == 1 ){
				saw_return = 1;
				ex(p->opr.op[0]);
				type1 = pop_type();

				type2 = last_proc->return_value;

				if(type2 == typeIntCon){
					if( type1 == typeFloatCon ){
						push_asm_statement(R_To_I,0);
					}
					push_asm_statement(I_Variable,4,0,0,0,last_proc->return_pos);
					push_asm_statement(I_Write,2,0,1);
				}else{
					if( type1 == typeIntCon ){
						push_asm_statement(I_To_R,0);
					}
					push_asm_statement(R_Variable,4,0,0,0,last_proc->return_pos);
					push_asm_statement(R_Write,2,0,1);
				}
			}
			break;
		case DO:
			/*fprintf(stderr,Do\n);*/
			start_of_loop = pos;
			ex(p->opr.op[0]); //stmts
			ex(p->opr.op[1]); //condition
			push_asm_statement(I_Jmp_If_True,2,0,pos+2);
			break;
		case UNTIL:
			/*fprintf(stderr,Until\n);*/
			start_of_loop = pos;
			ex(p->opr.op[0]); //stmts
			ex(p->opr.op[1]); //condition
			push_asm_statement(I_Jmp_If_False,2,0,pos+2);
			break;
        case WHILE:
			/*fprintf(stderr,While\n);*/
			start_of_loop = pos;
            ex(p->opr.op[0]);

			jmp_pos = pos;
			push_asm_statement(I_Jmp_If_True,2,0,0); //placeholder

            ex(p->opr.op[1]);
			push_asm_statement(I_Jmp,2,0,start_of_loop);

			replace_asm_statement(jmp_pos,I_Jmp_If_True,2,0,pos); //replace placeholder
            break;
		case FOR:
			/*fprintf(stderr,For\n);*/
			//initial assignment
			assignment(p->opr.op[0],p->opr.op[1]);

			start_of_loop = pos;
			
			//condition check
			comparison_operator(p->opr.op[0],p->opr.op[3],"Less");
				
			//Create placeholder jump
			jmp_pos = pos;
			push_asm_statement(I_Jmp_If_True,2,0,0);
			
			//execute stmt
            ex(p->opr.op[4]);

			//increment var
            math_assignment(p->opr.op[0],p->opr.op[1],"Add"); 

			//Go back to condition
			push_asm_statement(I_Jmp,2,0,start_of_loop);

			//replace placeholder with right jump position
			replace_asm_statement(jmp_pos,I_Jmp_If_True,2,0,pos);
			break;
        case IF:
			/*fprintf(stderr,If\n);*/
            ex(p->opr.op[0]);
			
			//placeholder jump for skipping if stmt
			jmp_pos = pos;
			push_asm_statement(I_Jmp_If_True,2,0,0);

			//execute if part
			ex(p->opr.op[1]);
			
            
			//if there's an else
			if (p->opr.nops > 2) {
				//placeholder jump for skipping else
				jmp_pos2 = pos;
				push_asm_statement(I_Jmp,2,0,0);

            } 
			
			//replace placeholder
			replace_asm_statement(jmp_pos,I_Jmp_If_False,2,0,pos);

			//if there's an else
			if (p->opr.nops > 2) {
				//execute else part
				ex(p->opr.op[2]);
				
				//replace placeholder for skipping else
				replace_asm_statement(jmp_pos,I_Jmp,2,0,pos);
            } 
			break;
        case PRINT:     
			/*fprintf(stderr,Print\n);*/
            ex(p->opr.op[0]);
			type1 = pop_type();

			if( type1 == typeIntCon || type1 == typeIntId ){
				if( type1 == typeIntId ){
					push_asm_statement(I_Value,0);
				}
				push_asm_statement(I_Write,2,0,1);
			}else{
				if( type1 == typeFloatId ){
					push_asm_statement(R_Value,0);
				}
				push_asm_statement(R_Write,2,0,1);
			}

            break;
        case UMINUS:    
			/*fprintf(stderr,negation\n);*/
            ex(p->opr.op[0]);
			type1 = pop_type();

			if(type1 == typeIntId){
			}else if (type1 == typeFloatId){
			}

			if(type1 == typeIntCon){
				push_asm_statement(I_Minus,0);
				push_type(typeIntCon);
			}else if(type1 == typeFloatCon){
				push_asm_statement(R_Minus,0);
				push_type(typeFloatCon);
			}else{
				yyerror("Can only negate expressions that have a value");
				exit(1);
			}
            break;
		case '=':
			/*fprintf(stderr,assignment\n);*/
			assignment(p->opr.op[0],p->opr.op[1]);
			break;
		case PluE:
			/*fprintf(stderr,+=\n);*/
			math_assignment(p->opr.op[0],p->opr.op[1],"Add");
			break;
		case MinE:
			/*fprintf(stderr,-=\n);*/
			math_assignment(p->opr.op[0],p->opr.op[1],"Subtract");
			break;
		case MulE:
			/*fprintf(stderr,*=\n);*/
			math_assignment(p->opr.op[0],p->opr.op[1],"Multiply");
			break;
		case DivE:
			/*fprintf(stderr,\\=\n);*/
			math_assignment(p->opr.op[0],p->opr.op[1],"Divide");
			break;
		case ModE:
			/*fprintf(stderr,%=\n);*/
			math_assignment(p->opr.op[0],p->opr.op[1],"Modulo");
			break;
		case '+':  
			/*fprintf(stderr,+\n);*/
			math_operator(p->opr.op[0],p->opr.op[1],"Add");
			break;
		case '-':  
			/*fprintf(stderr,-\n);*/
			math_operator(p->opr.op[0],p->opr.op[1],"Subtract");
			break; 
		case '*':
			/*fprintf(stderr,*\n);*/
			math_operator(p->opr.op[0],p->opr.op[1],"Multiply");
			break;
		case '/':
			/*fprintf(stderr,\\\n);*/
			math_operator(p->opr.op[0],p->opr.op[1],"Divide");
			break;
		case '%':
			/*fprintf(stderr,%\n);*/
			math_operator(p->opr.op[0],p->opr.op[1],"Modulo");
			break;
		case '<':
			/*fprintf(stderr,<\n);*/
			comparison_operator(p->opr.op[0],p->opr.op[1],"Less");
			break;
		case '>':
			/*fprintf(stderr,>\n);*/
			comparison_operator(p->opr.op[0],p->opr.op[1],"Greater");
			break;
		case NE:
			/*fprintf(stderr,!=\n);*/
			comparison_operator(p->opr.op[0],p->opr.op[1],"Equal");
			push_asm_statement(I_Minus,0);//negation
			break;
		case EQ:    
			/*fprintf(stderr,==\n);*/
			comparison_operator(p->opr.op[0],p->opr.op[1],"Equal");
			break;
		case GE:
			/*fprintf(stderr,>=\n);*/
			math_operator(p->opr.op[0],p->opr.op[1],"Subtract");
			type1 = pop_type();

			//check if (op0-op1)+1 > 0
			push_asm_statement(get_op(type1,"Constant"),2,0,1);
			
			push_asm_statement(get_op(type1,"Add"),0);

			push_asm_statement(get_op(type1,"Constant"),2,0,0);

			push_asm_statement(get_op(type1,"Greater"),0);

			push_type(typeIntCon);

			break;
		case LE:
			/*fprintf(stderr,<=\n);*/
			math_operator(p->opr.op[0],p->opr.op[1],"Subtract");
			type1 = pop_type();
			
			//check if (op0-op1)-1 < 0
			push_asm_statement(get_op(type1,"Constant"),2,0,1);
			
			push_asm_statement(get_op(type1,"Subtract"),0);

			push_asm_statement(get_op(type1,"Constant"),2,0,0);

			push_asm_statement(get_op(type1,"Less"),0);

			push_type(typeIntCon);

			break;		
		case ';':
			/*fprintf(stderr,;\n);*/
			if (p->opr.nops == 2) {
				ex(p->opr.op[0]);
				ex(p->opr.op[1]);
			}
			break;
		case 'P':
			/*fprintf(stderr,Param\n);*/
			i = (-1 * proc_vars) + -2;

			if( p->opr.op[1]->iCon.value == typeFloatId ){
				last_proc->params[proc_vars] = typeFloatId;
				push_asm_statement(R_Variable,4,0,0,0,proc_vars + 3);
				push_asm_statement(R_Variable,4,0,0,0,i);
				push_asm_statement(R_Value,0);
				push_asm_statement(R_Assign,2,0,1);
			}else{
				last_proc->params[proc_vars] = typeIntId;
				push_asm_statement(I_Variable,4,0,0,0,proc_vars + 3);
				push_asm_statement(I_Variable,4,0,0,0,i);
				push_asm_statement(I_Value,0);
				push_asm_statement(I_Assign,2,0,1);
			}
			proc_vars += 1;
			break;
		case 'D':   
			/*fprintf(stderr,Definition\n);*/
			if(inside_proc == 0){
				prog_vars += 1;	
			}else{
				proc_vars += 1;
			}

			if( p->opr.op[1] != NULL ){
				/*fprintf(stderr,Definition with assignment\n);*/
				assignment(p->opr.op[0],p->opr.op[1]);
			}
			break;
		case 'c':
			/*fprintf(stderr,Comment\n);*/
			break;
		default:
			/*fprintf(stderr,Throwaway\n);*/
			break;
		}
    }
    return 0;
}

void push_type(int t){
	struct type_stack * new = (struct type_stack *)malloc(sizeof(struct type_stack));

	///*fprintf(stderr,Pushing type %d\n, t);*/

	new->type = t;
	new->previous = top_of_stack;
	top_of_stack = new;
}

int pop_type(){
	int ret;
	if( top_of_stack == NULL ){
		ret = -1;
	}else{
		struct type_stack * new_top = top_of_stack->previous;
		ret = top_of_stack->type;
		//free(top_of_stack);
		top_of_stack = new_top;
	}
	///*fprintf(stderr,Popping %d\n, ret);*/
	return ret;
}

struct proc * get_proc(int proc_id){
	struct proc * current = first_proc;
	while( current != NULL ){
		if(current->id == proc_id){ 
			return current;
		}
	}
	return NULL;
}

int get_proc_start(int proc_id){
	struct proc * current = get_proc(proc_id);
	if( current == NULL ){
		return -1;
	}else{
		return current->position;
	}
}

void push_asm_statement(int cmd, int argc, ...){
	va_list args;
	int i;
	int iarg;
	float farg;
	struct statement * new_stmt = (struct statement *)malloc(sizeof(struct statement));
	
	//print cmd
	new_stmt->cmd = cmd;
	new_stmt->argc = argc;
	new_stmt->i_or_f = (int*)malloc(sizeof(int[argc]));
	new_stmt->iargs = (int*)malloc(sizeof(int[argc]));
	new_stmt->fargs = (float*)malloc(sizeof(float[argc]));

	va_start(args, argc);
	for(i = 0; i < argc; i++){
		iarg = va_arg(args , int);
		if( iarg == 0 ){
			iarg = va_arg( args , int);
			i++;
			new_stmt->i_or_f[i] = 0; 
			new_stmt->iargs[i] = iarg;
		}else{
			farg = (float)va_arg(args, double);
			i++;
			new_stmt->i_or_f[i] = 1; 
			new_stmt->fargs[i] = farg;
		}
	}
	va_end(args);
	
	new_stmt->position = pos;
	new_stmt->next_statement = NULL;

	if(last_statement == NULL){
		first_statement = new_stmt;
		last_statement = new_stmt;
	}else{
		last_statement->next_statement = new_stmt;
		last_statement = new_stmt;
	}

	//inc pos
	pos += argc + 1;
	
	/*fprintf(stderr,%s\n,new_stmt->string);*/
}

void replace_asm_statement(int position, int cmd, int argc, ...){
	va_list args;
	int i;
	int iarg;
	float farg;
	struct statement * current = first_statement;

	while(current->position != position){
		current = current->next_statement;
	}

	//print cmd
	current->argc = argc;
	current->cmd = cmd;
	current->i_or_f = (int*)malloc(sizeof(int[argc]));
	current->iargs = (int*)malloc(sizeof(int[argc]));
	current->fargs = (float*)malloc(sizeof(float[argc]));

	va_start(args, argc);
	for(i = 0; i < argc; i+=2){
		iarg = va_arg( args , int);
		if( iarg == 0 ){
			iarg = va_arg( args , int);
			current->i_or_f[i] = 0; 
			current->iargs[i] = iarg;
		}else{
			farg = (float)va_arg(args, double);
			current->i_or_f[i] = 1; 
			current->fargs[i] = farg;
		}
	}
	va_end(args);
}

//Don't use this if there are Jumps following the position.
void insert_asm_statement(int position, int cmd, int argc, ...){
	va_list args;
	int i;
	int iarg;
	float farg;
	char str[MAX_STMT_LEN];
	struct statement * previous;
	struct statement * current = first_statement;
	struct statement * new_stmt = (struct statement *)malloc(sizeof(struct statement));

	
	while(current->position != position){
		current = current->next_statement;
		///*fprintf(stderr,Current position %d, looking for %d\n,current->position,position);*/
	}

	//inserting after given position
	previous = current;
	current = current->next_statement;
	new_stmt->position = current->position;

	//print cmd
	new_stmt->cmd = cmd;
	new_stmt->argc = argc;
	new_stmt->i_or_f = (int*)malloc(sizeof(int[argc]));
	new_stmt->iargs = (int*)malloc(sizeof(int[argc]));
	new_stmt->fargs = (float*)malloc(sizeof(float[argc]));

	va_start(args, argc);
	for(i = 0; i < argc; i+=2){
		iarg = va_arg( args , int);
		if( iarg == 0 ){
			iarg = va_arg( args , int);
			new_stmt->i_or_f[i] = 0; 
			new_stmt->iargs[i] = iarg;
		}else{
			farg = (float)va_arg( args , double);
			new_stmt->i_or_f[i] = 1; 
			new_stmt->fargs[i] = farg;
		}
	}
	va_end(args);

	previous->next_statement = new_stmt;
	new_stmt->next_statement = current;

	/*
		Increment positions after this.  This is why you shouldn't
		use this if there are any jumps already pointing to positions
		greater than this one.  Their position will get updated,
		but not their args, since that's stored in a string.
	*/
	while(current != NULL){
		current->position += argc + 1;
		current = current->next_statement;
	}

}

void print_all(){
	int i;
	struct statement * current = first_statement;
	FILE * output_file;
	output_file = fopen("calc_out.apm","w");

	while(current != NULL){
		fwrite(&(current->cmd),sizeof(int),1,output_file);
		
		for(i = 0; i < current->argc; i++){
			if(current->i_or_f[i] == 0){
				fwrite(&(current->iargs[i]),sizeof(int),1,output_file);
			}else{
				fwrite(&(current->fargs[i]),sizeof(float),1,output_file);
			}
		}

		current = current->next_statement;
	}
}

void comparison_operator(nodeType* op1, nodeType* op2, char* name){
	int insert_at = pos;
	ex(op1);
	int type1 = pop_type();
	ex(op2);
	int type2 = pop_type();
	char prefix[30];

	get_values_and_convert(&type1, &type2,insert_at);

	int is_real = is_real_op(type1,type2);
	push_asm_statement(get_op(is_real,name),0);
	push_type(typeIntCon);
}

void math_operator(nodeType* op1, nodeType* op2, char* name){
	int insert_at = pos;
	///*fprintf(stderr,Insert at %d\n,insert_at);*/
	ex(op1);
	int type1 = pop_type();

	ex(op2);
	int type2 = pop_type();
	char prefix[30];

	get_values_and_convert(&type1, &type2,insert_at);
	
	int is_real = is_real_op(type1,type2);
	push_asm_statement(get_op(is_real,name),0);
}



void math_assignment(nodeType* var, nodeType* expr, char* name){
	//put var on stack
	ex(var);
	int type = pop_type();
	math_operator(var,expr,name);

	int is_real_type = pop_type();
	if(is_real_type == typeFloatCon){
		is_real_type = 1;
	}else{
		is_real_type = 0;
	}
	if( type == typeIntId ){
		if(is_real_type == 1){
			push_asm_statement(R_To_I,0);
		}
		push_asm_statement(I_Assign,2,0,1);
	}else if( type == typeFloatId ){
		if(is_real_type == 0){
			push_asm_statement(I_To_R,0);
		}
		push_asm_statement(R_Assign,2,0,1);
	}else{
		yyerror("Cannot assign value to constant\n");
		exit(1);
	}
}

void assignment(nodeType* var, nodeType* expr){
	ex(var);
	int type1 = pop_type();

	ex(expr);
	int type2 = pop_type();

	if( type2 == typeIntId ){
		push_asm_statement(I_Value,0);
		type2 = typeIntCon;
	}else if( type2 == typeFloatId ){
		push_asm_statement(R_Value,0);
		type2 = typeFloatCon;
	}

	if( type1 == typeIntId ){
		if(type2 == typeFloatCon){
			push_asm_statement(R_To_I,0);
		}
		push_asm_statement(I_Assign,2,0,1);
	}else if( type1 == typeFloatId ){
		if(type2 == typeIntCon){
			push_asm_statement(I_To_R,0);
		}
		push_asm_statement(R_Assign,2,0,1);
	}else{
		yyerror("Cannot assign value to constant\n");
		exit(1);
	}
}

void get_values_and_convert(int *type1, int *type2, int insert_at){
	///*fprintf(stderr,Insert at %d\n,insert_at);*/
	if( *type1 == typeIntId ){
		insert_asm_statement(insert_at,I_Value,0);
		*type1 = typeIntCon;
		insert_at += 3;

		if(*type2 == typeFloatId || *type2 == typeFloatCon){
			insert_asm_statement(insert_at,I_To_R,0);
			*type1 = typeFloatCon;
		}
	}else if( *type1 == typeFloatId ){
		push_asm_statement(R_Value,0);
		*type1 = typeFloatCon;
	}

	if( *type2 == typeIntId ){
		push_asm_statement(I_Value,0);
		*type2 = typeIntCon;
		if(*type1 == typeFloatId || *type1 == typeFloatCon){
			push_asm_statement(I_To_R,0);
			*type2 = typeFloatCon;
		}
	}else if( *type2 == typeFloatId ){
		push_asm_statement(R_Value,0);
		*type2 = typeFloatCon;
	}
}

int is_real_op(int type1, int type2){
	if(type1 == typeFloatCon || type2 == typeFloatCon){
		return 1;
	}else{
		return 0;
	}
}

int get_op(int real, char* name){
	//#define I_Add		1
	//#define R_Add		31
	if(strcmp(name,"Add") == 0){
		if(real == 0){
			return I_Add;
		}else{
			return R_Add;
		}
	}
	//#define I_Assign	4
	//#define R_Assign	34
	if(strcmp(name,"Assign") == 0){
		if(real == 0){
			return I_Assign;
		}else{
			return R_Assign;
		}
	}
	//#define I_Constant	7
	//#define R_Constant	37
	if(strcmp(name,"Constant") == 0){
		if(real == 0){
			return I_Constant;
		}else{
			return R_Constant;
		}
	}
	//#define I_Divide	8
	//#define R_Divide	38
	if(strcmp(name,"Divide") == 0){
		if(real == 0){
			return I_Divide;
		}else{
			return R_Divide;
		}
	}
	//#define I_Equal		11
	//#define R_Equal		41
	if(strcmp(name,"Equal") == 0){
		if(real == 0){
			return I_Equal;
		}else{
			return R_Equal;
		}
	}
	//#define I_Greater	13
	//#define R_Greater	43
	if(strcmp(name,"Greater") == 0){
		if(real == 0){
			return I_Greater;
		}else{
			return R_Greater;
		}
	}
	//#define I_Less		15
	//#define R_Less		45
	if(strcmp(name,"Less") == 0){
		if(real == 0){
			return I_Less;
		}else{
			return R_Less;
		}
	}
	//#define I_Minus		16
	//#define R_Minus		46
	if(strcmp(name,"Minus") == 0){
		if(real == 0){
			return I_Minus;
		}else{
			return R_Minus;
		}
	}
	//#define I_Multiply	18
	//#define R_Multiply	48
	if(strcmp(name,"Multiply") == 0){
		if(real == 0){
			return I_Multiply;
		}else{
			return R_Multiply;
		}
	}
	//#define I_Read		23
	//#define R_Read		53
	if(strcmp(name,"Read") == 0){
		if(real == 0){
			return I_Read;
		}else{
			return R_Read;
		}
	}
	//#define I_Subtract	24
	//#define R_Subtract	54
	if(strcmp(name,"Subtract") == 0){
		if(real == 0){
			return I_Subtract;
		}else{
			return R_Subtract;
		}
	}
	//#define I_Value		25
	//#define R_Value		55
	if(strcmp(name,"Value") == 0){
		if(real == 0){
			return I_Value;
		}else{
			return R_Value;
		}
	}
	//#define I_Variable	26
	//#define R_Variable	56
	if(strcmp(name,"Variable") == 0){
		if(real == 0){
			return I_Variable;
		}else{
			return R_Variable;
		}
	}
	//#define I_Write		27
	//#define R_Write		57
	if(strcmp(name,"Write") == 0){
		if(real == 0){
			return I_Write;
		}else{
			return R_Write;
		}
	}
}
