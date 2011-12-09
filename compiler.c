#include "calc3.h"
#include "compiler.h"
#include "y.tab.h"

int position = 0;
static int lbl;

void print_asm_statement(char* cmd, int argc, ...){
	va_list args;
	int i;
	char * arg_ptr;

	//print cmd
	printf("%04d\t%s\t",position,cmd);
	va_start(args, argc);
	for(i = 0; i < argc; i++){
		arg_ptr = va_arg( args , char*);
		printf("%s\t",  arg_ptr);
	}
	va_end(args);
	printf("\n");
	
	//inc position
	position += (argc/2) + 1;
}

char* iargs(char* str, int i){
	char * new_str = (char*)malloc(sizeof(char[20]));
	sprintf(new_str,"%s%d",str,i);
	return new_str;
}

char* fargs(char* str, float f){
	char * new_str = (char*)malloc(sizeof(char[20]));
	sprintf(new_str,"%s%f",str,f);
	return new_str;
}
 

int ex(nodeType *p) {
    int lbl1, lbl2, type1, type2;

	//fprintf(stderr,"ex(%d);\n",p->type);

    if (!p) return 0;
    switch(p->type) {
	printTypeStack();
    case typeIntCon:       
		print_asm_statement("I_Constant",1,iargs("value:",p->iCon.value));
		push_type(typeIntCon);	
        break;
	case typeFloatCon:
		print_asm_statement("R_Constant",1,fargs("value:",p->fCon.value));
		push_type(typeFloatCon);
        break;
    case typeIntId:        
		print_asm_statement("I_Variable",2,"lev:0",iargs("disp:",p->iId.i + 3));
		push_type(typeIntId);
		break;
	case typeFloatId:
		print_asm_statement("R_Variable",2,"lev:0",iargs("disp:",p->fId.i + 3));
		push_type(typeFloatId);
        break;
    case typeOpr:
        switch(p->opr.oper) {
        case WHILE:
            printf("L%03d:\n", lbl1 = lbl++);
            ex(p->opr.op[0]);
            printf("\tjz\tL%03d\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
		case FOR:
			printf("FOR\n");
			break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2) {
                /* if else */
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            } else {
                /* if */
                printf("\tjz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:     
            ex(p->opr.op[0]);
			type1 = pop_type();

			if( type1 == typeIntCon || type1 == typeIntId ){
				if( type1 == typeIntId ){
					print_asm_statement("I_Value",0);
				}
				print_asm_statement("I_Write",1,"words:1");
			}else{
				if( type1 == typeFloatId ){
					print_asm_statement("R_Value",0);
				}
				print_asm_statement("R_Write",1,"words:1");
			}

            break;
        case UMINUS:    
            ex(p->opr.op[0]);
            printf("\tneg\n");
            break;
		case 'c':
			break;
		case 'D':   
			break;
		case '=':
			ex(p->opr.op[0]);
			type1 = pop_type();

            ex(p->opr.op[1]);
			type2 = pop_type();

			if( type2 == typeIntId ){
				print_asm_statement("I_Value",0);
				type2 = typeIntCon;
			}else if( type2 == typeFloatId ){
				print_asm_statement("R_Value",0);
				type2 = typeFloatCon;
			}

			if( type1 == typeIntId ){
				if(type2 == typeFloatCon){
					print_asm_statement("R_To_I",0);
				}
				print_asm_statement("I_Assign",1,"words:1");
			}else if( type1 == typeFloatId ){
				if(type2 == typeIntCon){
					print_asm_statement("I_To_R",0);
				}
				print_asm_statement("R_Assign",1,"words:1");
			}else{
				printf("Cannot assign value to constant\n");
				exit(1);
			}
			break;	
        default:
            ex(p->opr.op[0]);
			type1 = pop_type();
            ex(p->opr.op[1]);
			type2 = pop_type();


			if( type1 == typeIntId ){
				print_asm_statement("I_Value",0);
				type1 = typeIntCon;
				if(type2 == typeFloatId || type2 == typeFloatCon){
					print_asm_statement("I_To_R",0);
					type1 = typeFloatCon;
				}
			}else if( type1 == typeFloatId ){
				print_asm_statement("R_Value",0);
				type1 = typeFloatCon;
			}

			if( type2 == typeIntId ){
				print_asm_statement("I_Value",0);
				type2 = typeIntCon;
				if(type1 == typeFloatId || type1 == typeFloatCon){
					print_asm_statement("I_To_R",0);
					type2 = typeFloatCon;
				}
			}else if( type2 == typeFloatId ){
				print_asm_statement("R_Value",0);
				type2 = typeFloatCon;
			}

            int is_real_op;
			if(type1 == typeFloatCon || type2 == typeFloatCon){
				is_real_op = 1;
			}else{
				is_real_op = 0;
			}

			switch(p->opr.oper) {
            case '+':   
				if(is_real_op == 1){
					print_asm_statement("R_Add",0);
					push_type(typeFloatId);
				}else{
					print_asm_statement("I_Add",0);
					push_type(typeIntId);
				}
				break;
            case '-':  
				if(is_real_op == 1){
					print_asm_statement("R_Subtract",0);
					push_type(typeFloatId);
				}else{
					print_asm_statement("I_Subtract",0);
					push_type(typeIntId);
				}
				break; 
            case '*':
				if(is_real_op == 1){
					print_asm_statement("R_Multiply",0);
					push_type(typeFloatId);
				}else{
					print_asm_statement("I_Multiply",0);
					push_type(typeIntId);
				}
				break;
            case '/':
				if(is_real_op == 1){
					print_asm_statement("R_Divide",0);
					push_type(typeFloatId);
				}else{
					print_asm_statement("I_Divide",0);
					push_type(typeIntId);
				}
				break;
            case '<':
				if(is_real_op == 1){
					print_asm_statement("R_Less",0);
				}else{
					print_asm_statement("I_Less",0);
				}
				push_type(typeIntId);
				break;
            case '>':
				if(is_real_op == 1){
					print_asm_statement("R_Greater",0);
				}else{
					print_asm_statement("I_Less",0);
				}
				push_type(typeIntId);
				break;
            case GE:
				print_asm_statement("<Code for GE>",0);
				break;
            case LE:
				print_asm_statement("<Code for LE>",0);
				break;
            case NE:
				if(is_real_op == 1){
					print_asm_statement("R_Equal",0);
				}else{
					print_asm_statement("I_Equal",0);
				}
				print_asm_statement("I_Minus",0);
				push_type(typeIntId);
				break;
            case EQ:    
				if(is_real_op == 1){
					print_asm_statement("R_Equal",0);
				}else{
					print_asm_statement("I_Equal",0);
				}
				push_type(typeIntId);
				break;
            }
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
		printf("Stack error\n");
		exit(1);
	}

	struct type_stack * new_top = top_of_stack->previous;
	int ret = top_of_stack->type;
	free(top_of_stack);
	top_of_stack = new_top;

	//fprintf(stderr,"Popping type %d\n", ret);
	
	return ret;
}

void printTypeStack(){
	struct type_stack * current = top_of_stack;
	while(current != NULL){
		printf("\t%d\n",current->type);
		current = current->previous;
	}
}
