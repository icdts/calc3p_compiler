#include "calc3.h"
#include "compiler.h"
#include "y.tab.h"

int pos = 1;
int inside_prog = 0;
int prog_vars = 0;
int inside_proc = 0;

int proc_params = 0;
int proc_vars = 0;

int first_prog_stmt = 4;
int args = 0;


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

    if (!p) return 0;
    switch(p->type) {
	printTypeStack();
    case typeIntCon:       
		push_asm_statement("I_Constant",1,iargs(p->iCon.value));
		push_type(typeIntCon);	
        break;
	case typeFloatCon:
		push_asm_statement("R_Constant",1,fargs(p->fCon.value));
		push_type(typeFloatCon);
        break;
    case typeIntId:        
		push_asm_statement("I_Variable",2,"0",iargs(p->iId.i + 3));
		push_type(typeIntId);
		break;
	case typeFloatId:
		push_asm_statement("R_Variable",2,"0",iargs(p->fId.i + 3));
		push_type(typeFloatId);
        break;
    case typeOpr:
        switch(p->opr.oper) {
		case PROG:
			start_prog = pos;
			inside_prog = 1;
			push_asm_statement("Prog", 2, "0","4"); //Placeholder

			ex(p->opr.op[0]);
			push_asm_statement("EndProg",0);
			replace_asm_statement(start_prog,"Prog", 2, iargs(prog_vars), iargs(first_prog_stmt));
			break;
		case PROC:
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

				for(i = 0; i < sizeof(new_proc->params); i=i+1){
					new_proc->params[i] = -1;
				}

				inside_proc = 1;
				start_proc = pos;
				push_asm_statement("Proc", 2, "0", "0"); //Placeholder
				if( p->opr.nops == 4 ){
					proc_params = 0;
					ex(p->opr.op[3]);
				}
				ex(p->opr.op[1]);
				push_asm_statement("EndProc",0);
				first_prog_stmt = pos;
				replace_asm_statement(start_proc,"Proc",2,iargs(proc_vars),iargs(start_proc+3));
				
				inside_proc = 0;
				ex(p->opr.op[2]);
			}else{
				fprintf(stderr,"%s\n", "Cannot nest Procedure definitions");
				exit(1);
			}
			break;
		case CALL:
			ex(p->opr.op[1]);
			check_arguments(get_proc(p->opr.op[0]->iId.i));
			push_asm_statement("Call",2,iargs(inside_proc),iargs(get_proc_start(p->opr.op[0]->iId.i)));
			break;
		case DO:
			start_of_loop = pos;
			ex(p->opr.op[0]); //stmts
			ex(p->opr.op[1]); //condition
			push_asm_statement("Jmp_if_True",1,iargs(pos+2));
			break;
		case UNTIL:
			start_of_loop = pos;
			ex(p->opr.op[0]); //stmts
			ex(p->opr.op[1]); //condition
			push_asm_statement("Jmp_if_False",1,iargs(pos+2));
			break;
        case WHILE:
			start_of_loop = pos;
            ex(p->opr.op[0]);

			jmp_pos = pos;
			push_asm_statement("Jmp_if_True",1,"null"); //placeholder

            ex(p->opr.op[1]);
			push_asm_statement("Jmp",1,iargs(start_of_loop));

			replace_asm_statement(jmp_pos,"Jmp_if_True",1,iargs(pos)); //replace placeholder
            break;
		case FOR:
			//initial assignment
			assignment(p->opr.op[0],p->opr.op[1]);

			start_of_loop = pos;
			
			//condition check
			comparison_operator(p->opr.op[0],p->opr.op[3],"Less");
				
			//Create placeholder jump
			jmp_pos = pos;
			push_asm_statement("Jmp_if_True",1,"null");
			
			//execute stmt
            ex(p->opr.op[4]);

			//increment var
            math_assignment(p->opr.op[0],p->opr.op[1],"Add"); 

			//Go back to condition
			push_asm_statement("Jmp",1,iargs(start_of_loop));

			//replace placeholder with right jump position
			replace_asm_statement(jmp_pos,"Jmp_if_True",1,iargs(pos));
			break;
        case IF:
            ex(p->opr.op[0]);
			
			//placeholder jump for skipping if stmt
			jmp_pos = pos;
			push_asm_statement("Jmp_if_True",1,"null");

			//execute if part
			ex(p->opr.op[1]);
			
            
			//if there's an else
			if (p->opr.nops > 2) {
				//placeholder jump for skipping else
				jmp_pos2 = pos;
				push_asm_statement("Jmp",1,"null");

            } 
			
			//replace placeholder
			replace_asm_statement(jmp_pos,"Jmp_if_False",1,iargs(pos));

			//if there's an else
			if (p->opr.nops > 2) {
				//execute else part
				ex(p->opr.op[2]);
				
				//replace placeholder for skipping else
				replace_asm_statement(jmp_pos,"Jmp",1,iargs(pos));
            } 
			break;
        case PRINT:     
            ex(p->opr.op[0]);
			type1 = pop_type();

			if( type1 == typeIntCon || type1 == typeIntId ){
				if( type1 == typeIntId ){
					push_asm_statement("I_Value",0);
				}
				push_asm_statement("I_Write",1,"1");
			}else{
				if( type1 == typeFloatId ){
					push_asm_statement("R_Value",0);
				}
				push_asm_statement("R_Write",1,"1");
			}

            break;
        case UMINUS:    
            ex(p->opr.op[0]);
			type1 = pop_type();

			if(type1 == typeIntId){
			}else if (type1 == typeFloatId){
			}

			if(type1 == typeIntCon){
				push_asm_statement("I_Minus",0);
				push_type(typeIntCon);
			}else if(type1 == typeFloatCon){
				push_asm_statement("R_Minus",0);
				push_type(typeFloatCon);
			}else{
				printf("Can only negate expressions that have a value");
				exit(1);
			}
            break;
		case '=':
			assignment(p->opr.op[0],p->opr.op[1]);
			break;
		case PluE:
			math_assignment(p->opr.op[0],p->opr.op[1],"Add");
			break;
		case MinE:
			math_assignment(p->opr.op[0],p->opr.op[1],"Subtract");
			break;
		case MulE:
			math_assignment(p->opr.op[0],p->opr.op[1],"Multiply");
			break;
		case DivE:
			math_assignment(p->opr.op[0],p->opr.op[1],"Divide");
			break;
		case ModE:
			math_assignment(p->opr.op[0],p->opr.op[1],"Modulo");
			break;
		case '+':  
			math_operator(p->opr.op[0],p->opr.op[1],"Add");
			break;
		case '-':  
			math_operator(p->opr.op[0],p->opr.op[1],"Subtract");
			break; 
		case '*':
			math_operator(p->opr.op[0],p->opr.op[1],"Multiply");
			break;
		case '/':
			math_operator(p->opr.op[0],p->opr.op[1],"Divide");
			break;
		case '%':
			math_operator(p->opr.op[0],p->opr.op[1],"Modulo");
			break;
		case '<':
			comparison_operator(p->opr.op[0],p->opr.op[1],"Less");
			break;
		case '>':
			comparison_operator(p->opr.op[0],p->opr.op[1],"Greater");
			break;
		case NE:
			comparison_operator(p->opr.op[0],p->opr.op[1],"Equal");
			push_asm_statement("I_Minus",0);//negation
			break;
		case EQ:    
			comparison_operator(p->opr.op[0],p->opr.op[1],"Equal");
			break;
		case GE:
			math_operator(p->opr.op[0],p->opr.op[1],"Subtract");
			type1 = pop_type();
			
			if( type1 == typeIntCon ){
				strcpy(tmp_str,"I_");		
			}else{
				strcpy(tmp_str,"R_");
			}

			//check if (op0-op1)+1 > 0
			strcpy(tmp_str2,tmp_str);
			strcat(tmp_str2,"Constant");
			push_asm_statement(tmp_str2,1,"value:1");
			
			strcpy(tmp_str2,tmp_str);
			strcat(tmp_str2,"Add");
			push_asm_statement(tmp_str2,0);

			strcpy(tmp_str2,tmp_str);
			strcat(tmp_str2,"Constant");
			push_asm_statement(tmp_str2,1,"value:0");

			strcpy(tmp_str2,tmp_str);
			strcat(tmp_str2,"Greater");
			push_asm_statement(tmp_str2,0);

			push_type(typeIntCon);

			break;
		case LE:
			math_operator(p->opr.op[0],p->opr.op[1],"Subtract");
			type1 = pop_type();
			
			if( type1 == typeIntCon ){
				strcpy(tmp_str,"I_");		
			}else{
				strcpy(tmp_str,"R_");
			}

			//check if (op0-op1)-1 < 0
			strcpy(tmp_str2,tmp_str);
			strcat(tmp_str2,"Constant");
			push_asm_statement(tmp_str2,1,"value:1");
			
			strcpy(tmp_str2,tmp_str);
			strcat(tmp_str2,"Subtract");
			push_asm_statement(tmp_str2,0);

			strcpy(tmp_str2,tmp_str);
			strcat(tmp_str2,"Constant");
			push_asm_statement(tmp_str2,1,"value:0");

			strcpy(tmp_str2,tmp_str);
			strcat(tmp_str2,"Less");
			push_asm_statement(tmp_str2,0);

			push_type(typeIntCon);

			break;		
		case ';':
			if (p->opr.nops == 2) {
				ex(p->opr.op[0]);
				ex(p->opr.op[1]);
			}
			break;
		case ARGS:
			args += 1;
			ex(p->opr.op[0]);
			ex(p->opr.op[1]);
			break;
		case 'P':
			i = (-1 * proc_vars) + -2;

			if( p->opr.op[1]->iCon.value == typeFloatId ){
				last_proc->params[proc_vars] = typeFloatId;
				push_asm_statement("R_Variable",2,"0",iargs(proc_vars + 3));
				push_asm_statement("R_Variable",2,"0",iargs(i));
				push_asm_statement("R_Value",0);
				push_asm_statement("R_Assign",1,"1");
			}else{
				last_proc->params[proc_vars] = typeIntId;
				push_asm_statement("I_Variable",2,"0",iargs(proc_vars + 3));
				push_asm_statement("I_Variable",2,"0",iargs(i));
				push_asm_statement("I_Value",0);
				push_asm_statement("I_Assign",1,"1");
			}
			proc_vars += 1;
		case 'D':   
			if(inside_proc == 0){
				prog_vars += 1;	
			}else{
				proc_vars += 1;
			}
			break;
		case 'c':
			break;
		default:
			break;
		}
    }
    return 0;
}

void push_type(int t){
	struct type_stack * new = (struct type_stack *)malloc(sizeof(struct type_stack));

	//fprintf(stderr,"Pushing type %d\n", t);

	new->type = t;
	if( top_of_stack == NULL ){
		top_of_stack = new;
	}else{
		new->previous = top_of_stack;
		top_of_stack = new;
	}
}

int pop_type(){
	if( top_of_stack == NULL ){
		return -1;
	}else{
		struct type_stack * new_top = top_of_stack->previous;
		int ret = top_of_stack->type;
		//free(top_of_stack);
		top_of_stack = new_top;

		
		return ret;
	}
}

void printTypeStack(){
	struct type_stack * current = top_of_stack;
	while(current != NULL){
		printf("\t%d\n",current->type);
		current = current->previous;
	}
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

struct statement * push_asm_statement(char* cmd, int argc, ...){
	va_list args;
	int i;
	char * arg_ptr;
	struct statement * new_stmt = (struct statement *)malloc(sizeof(struct statement));
	char str[MAX_STMT_LEN];


	new_stmt->string = (char *)malloc(sizeof(char[MAX_STMT_LEN]));
	//print cmd
	snprintf(str,MAX_STMT_LEN,"%s\t",cmd);
	va_start(args, argc);
	for(i = 0; i < argc; i++){
		arg_ptr = va_arg( args , char*);
		snprintf(str+strlen(str),MAX_STMT_LEN-strlen(str),"%s\t",  arg_ptr);
		strcat(new_stmt->string,str);
	}
	va_end(args);
	
	strcpy(new_stmt->string,str);
	
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
	
	//fprintf(stderr,"%s\n",new_stmt->string);
}

void replace_asm_statement(int position, char* cmd, int argc, ...){
	va_list args;
	int i;
	char * arg_ptr;
	char str[MAX_STMT_LEN];
	struct statement * current = first_statement;

	while(current->position != position){
		current = current->next_statement;
	}

	//print cmd
	current->string = (char *)malloc(sizeof(char[MAX_STMT_LEN]));
	//print cmd
	snprintf(str,MAX_STMT_LEN,"%s\t",cmd);
	va_start(args, argc);
	for(i = 0; i < argc; i++){
		arg_ptr = va_arg( args , char*);
		snprintf(str+strlen(str),MAX_STMT_LEN-strlen(str),"%s\t",  arg_ptr);
		strcat(current->string,str);
	}
	va_end(args);
	
	strcpy(current->string,str);
}

//Don't use this if there are Jumps following the position.
void insert_asm_statement(int position, char* cmd, int argc, ...){
	va_list args;
	int i;
	char * arg_ptr;
	char str[MAX_STMT_LEN];
	struct statement * previous;
	struct statement * current = first_statement;
	struct statement * new_stmt = (struct statement *)malloc(sizeof(struct statement));

	while(current->position != position){
		current = current->next_statement;
	}

	//inserting after given position
	previous = current;
	current = current->next_statement;
	new_stmt->position = current->position;

	//print cmd
	new_stmt->string = (char *)malloc(sizeof(char[MAX_STMT_LEN]));
	//print cmd
	snprintf(str,MAX_STMT_LEN,"%s\t",cmd);
	va_start(args, argc);
	for(i = 0; i < argc; i++){
		arg_ptr = va_arg( args , char*);
		snprintf(str+strlen(str),MAX_STMT_LEN-strlen(str),"%s\t",  arg_ptr);
		strcat(new_stmt->string,str);
	}
	va_end(args);
	
	strcpy(new_stmt->string,str);

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

char* iargs( int i ){
	char * new_str = (char*)malloc(sizeof(char[20]));
	sprintf(new_str,"%d",i);
	return new_str;
}

char* fargs( float f ){
	char * new_str = (char*)malloc(sizeof(char[20]));
	sprintf(new_str,"%f",f);
	return new_str;
}

void print_all(){
	struct statement * current = first_statement;
	while(current != NULL){
		printf("%04d\t%s\n", current->position,current->string);
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
	
	if(is_real == 1){
		strcpy(prefix,"R_");
	}else{
		strcpy(prefix,"I_");
	}
	strcat(prefix,name);

	push_asm_statement(prefix,0);
	push_type(typeIntCon);
}

void math_operator(nodeType* op1, nodeType* op2, char* name){
	int insert_at = pos;
	ex(op1);
	int type1 = pop_type();

	ex(op2);
	int type2 = pop_type();
	char prefix[30];

	get_values_and_convert(&type1, &type2,insert_at);

	int is_real = is_real_op(type1,type2);

	if(is_real == 1){
		strcpy(prefix,"R_");
		push_type(typeFloatCon);
	}else{
		strcpy(prefix,"I_");
		push_type(typeIntCon);
	}
	strcat(prefix,name);

	push_asm_statement(prefix,0);
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
			push_asm_statement("R_To_I",0);
		}
		push_asm_statement("I_Assign",1,"words:1");
	}else if( type == typeFloatId ){
		if(is_real_type == 0){
			push_asm_statement("I_To_R",0);
		}
		push_asm_statement("R_Assign",1,"words:1");
	}else{
		printf("Cannot assign value to constant\n");
		exit(1);
	}
}

void assignment(nodeType* var, nodeType* expr){
	ex(var);
	int type1 = pop_type();

	ex(expr);
	int type2 = pop_type();

	if( type2 == typeIntId ){
		push_asm_statement("I_Value",0);
		type2 = typeIntCon;
	}else if( type2 == typeFloatId ){
		push_asm_statement("R_Value",0);
		type2 = typeFloatCon;
	}

	if( type1 == typeIntId ){
		if(type2 == typeFloatCon){
			push_asm_statement("R_To_I",0);
		}
		push_asm_statement("I_Assign",1,"words:1");
	}else if( type1 == typeFloatId ){
		if(type2 == typeIntCon){
			push_asm_statement("I_To_R",0);
		}
		push_asm_statement("R_Assign",1,"words:1");
	}else{
		printf("Cannot assign value to constant\n");
		exit(1);
	}
}

void get_values_and_convert(int *type1, int *type2, int insert_at){
	if( *type1 == typeIntId ){
		insert_asm_statement(insert_at,"I_Value",0);
		*type1 = typeIntCon;
		insert_at += 1;

		if(*type2 == typeFloatId || *type2 == typeFloatCon){
			insert_asm_statement(insert_at,"I_To_R",0);
			*type1 = typeFloatCon;
		}
	}else if( *type1 == typeFloatId ){
		push_asm_statement("R_Value",0);
		*type1 = typeFloatCon;
	}

	if( *type2 == typeIntId ){
		push_asm_statement("I_Value",0);
		*type2 = typeIntCon;
		if(*type1 == typeFloatId || *type1 == typeFloatCon){
			push_asm_statement("I_To_R",0);
			*type2 = typeFloatCon;
		}
	}else if( *type2 == typeFloatId ){
		push_asm_statement("R_Value",0);
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

void check_arguments(struct proc * p){
	int i = 0;
	while( args != 0 ){
		int type = pop_type();
		if( p->params[i] != type ){
			if( p->params[i] == typeIntId ){
				if( type == typeFloatId ){
					//convert
				}
			}else if(p->params[i] == typeFloatId){
				if( type == typeIntId ){
					//convert
				}
			}else{
				yyerror("mis matched types");
				exit(1);
			}
		}
		args = args - 1;
		i = i + 1;
	}
}
