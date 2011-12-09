#include "calc3.h"
#include "y.tab.h"

static int lbl;

int ex(nodeType *p) {
    int lbl1, lbl2, type1, type2;

	//fprintf(stderr,"ex(%d);\n",p->type);

    if (!p) return 0;
    switch(p->type) {
	printTypeStack();
    case typeIntCon:       
        printf("\tI_Constant\tvalue:%d\n", p->iCon.value); 
		push_type(typeIntCon);	
        break;
	case typeFloatCon:
        printf("\tR_Constant\tvalue:%d\n", p->fCon.value); 
		push_type(typeFloatCon);
        break;
    case typeIntId:        
		printf("\tI_Variable\t%d\n", p->iId.i); 
		push_type(typeIntId);
		break;
	case typeFloatId:
		printf("\tR_Variable\t%s\n", p->fId.i); 
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
					printf("\tI_Value");
				}
				printf("\tI_Write\n");	
			}else{
				if( type1 == typeFloatId ){
					printf("\tR_Value");
				}
				printf("\tR_Write\n");
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
            ex(p->opr.op[1]);
			type1 = pop_type();
			type2 = pop_type();

			if( type1 == typeIntId ){
				printf("\tI_Value\n");
			}else if( type1 == typeFloatId ){
				printf("\tR_Value\n");
			}

			if( type2 == typeIntId ){
				if( type1 == typeIntCon || type1 == typeIntId ){
					printf("\tI_Assign\twords:1\n");
				}
			}else if( type2 == typeFloatId ){
				if( type1 == typeFloatCon || type1 == typeFloatId ){
					printf("\tR_Assign\twords:1\n");
				}
			}else{
				printf("Cannot assign value to constant %d %d\n", type1, type2);
				exit(1);
			}
			break;	
        default:
            ex(p->opr.op[0]);
			type1 = pop_type();
			if( type1 == typeIntId ){
				printf("\tI_Value\n");
			}else if( type1 == typeFloatId ){
				printf("\tR_Value\n");
			}

            ex(p->opr.op[1]);
			type2 = pop_type();
			if( type2 == typeIntId ){
				printf("\tI_Value\n");
			}else if( type2 == typeFloatId ){
				printf("\tR_Value\n");
			}

            int is_real_op;
			if(type1 == typeFloatId || type1 == typeFloatId || type2 == typeFloatId || type2 == typeFloatId){
				is_real_op = 1;
			}else{
				is_real_op = 0;
			}

			switch(p->opr.oper) {
            case '+':   
				if(is_real_op == 1){
					printf("\tR_Add\n");
					push_type(typeFloatId);
				}else{
					printf("\tI_Add\n");
					push_type(typeIntId);
				}
				break;
            case '-':  
				if(is_real_op == 1){
					printf("\tR_Subtract\n");
					push_type(typeFloatId);
				}else{
					printf("\tI_Subtract\n");
					push_type(typeIntId);
				}
				break; 
            case '*':
				if(is_real_op == 1){
					printf("\tR_Multiply\n");
					push_type(typeFloatId);
				}else{
					printf("\tI_Multiply\n");
					push_type(typeIntId);
				}
				break;
            case '/':
				if(is_real_op == 1){
					printf("\tR_Divide\n");
					push_type(typeFloatId);
				}else{
					printf("\tI_Divide\n");
					push_type(typeIntId);
				}
				break;
            case '<':
				if(is_real_op == 1){
					printf("\tR_Less\n");
				}else{
					printf("\tI_Less\n");
				}
				push_type(typeIntId);
				break;
            case '>':
				if(is_real_op == 1){
					printf("\tR_Greater\n");
				}else{
					printf("\tI_Less\n");
				}
				push_type(typeIntId);
				break;
            case GE:
				printf("\t<Code for GE>\n");
				break;
            case LE:
				printf("\t<Code for LE>\n");
				break;
            case NE:
				if(is_real_op == 1){
					printf("\tR_Equal\n");
				}else{
					printf("\tI_Equal\n");
				}
				printf("\tI_Minus");
				push_type(typeIntId);
				break;
            case EQ:    
				if(is_real_op == 1){
					printf("\tR_Equal\n");
				}else{
					printf("\tI_Equal\n");
				}
				push_type(typeIntId);
				break;
            }
        }
    }
    return 0;
}


