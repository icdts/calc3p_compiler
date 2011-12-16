#ifndef __ASM_H_INCUDED
#define __ASM_H_INCUDED

#include "apm.h"

extern WORD storage[STORAGE];
extern int maxStorage;

static int name2opcode(char *name) {
if(strcasecmp(name,"I_Add") == 0) return I_ADD;
else if(strcasecmp(name,"And") == 0) return I_AND;
else if(strcasecmp(name,"Arrow") == 0) return I_ARROW;
else if(strcasecmp(name,"I_Assign") == 0) return I_ASSIGN;
else if(strcasecmp(name,"Bar") == 0) return I_BAR;
else if(strcasecmp(name,"Call") == 0) return I_CALL;
else if(strcasecmp(name,"I_Constant") == 0) return I_CONSTANT;
else if(strcasecmp(name,"I_Divide") == 0) return I_DIVIDE;
else if(strcasecmp(name,"EndProc") == 0) return I_ENDPROC;
else if(strcasecmp(name,"EndPProc") == 0) return I_ENDPPROC;
else if(strcasecmp(name,"EndProg") == 0) return I_ENDPROG;
else if(strcasecmp(name,"I_Equal") == 0) return I_EQUAL;
else if(strcasecmp(name,"Fi") == 0) return I_FI;
else if(strcasecmp(name,"I_Greater") == 0) return I_GREATER;
else if(strcasecmp(name,"Index") == 0) return I_INDEX;
else if(strcasecmp(name,"I_Less") == 0) return I_LESS;
else if(strcasecmp(name,"I_Minus") == 0) return I_MINUS;
else if(strcasecmp(name,"I_Modulo") == 0) return I_MODULO;
else if(strcasecmp(name,"I_Multiply") == 0) return I_MULTIPLY;
else if(strcasecmp(name,"Not") == 0) return I_NOT;
else if(strcasecmp(name,"Or") == 0) return I_OR;
else if(strcasecmp(name,"Proc") == 0) return I_PROC;
else if(strcasecmp(name,"Prog") == 0) return I_PROG;
else if(strcasecmp(name,"I_Read") == 0) return I_READ;
else if(strcasecmp(name,"C_Read") == 0) return C_READ;
else if(strcasecmp(name,"I_Subtract") == 0) return I_SUBTRACT;
else if(strcasecmp(name,"I_Value") == 0) return I_VALUE;
else if(strcasecmp(name,"I_Variable") == 0) return I_VARIABLE;
else if(strcasecmp(name,"I_Write") == 0) return I_WRITE;
else if(strcasecmp(name,"C_Write") == 0) return C_WRITE;
else if(strcasecmp(name,"I_To_R") == 0) return I_TO_R;
else if(strcasecmp(name,"R_Add") == 0) return R_ADD;
else if(strcasecmp(name,"R_Assign") == 0) return R_ASSIGN;
else if(strcasecmp(name,"R_Constant") == 0) return R_CONSTANT;
else if(strcasecmp(name,"R_Divide") == 0) return R_DIVIDE;
else if(strcasecmp(name,"R_Equal") == 0) return R_EQUAL;
else if(strcasecmp(name,"R_Greater") == 0) return R_GREATER;
else if(strcasecmp(name,"R_Less") == 0) return R_LESS;
else if(strcasecmp(name,"R_Minus") == 0) return R_MINUS;
else if(strcasecmp(name,"R_Multiply") == 0) return R_MULTIPLY;
else if(strcasecmp(name,"R_Read") == 0) return R_READ;
else if(strcasecmp(name,"R_Subtract") == 0) return R_SUBTRACT;
else if(strcasecmp(name,"R_Value") == 0) return R_VALUE;
else if(strcasecmp(name,"R_Variable") == 0) return R_VARIABLE;
else if(strcasecmp(name,"R_Write") == 0) return R_WRITE;
else if(strcasecmp(name,"R_To_I") == 0) return R_TO_I;
else if(strcasecmp(name,"Swap") == 0) return I_SWAP;
else if(strcasecmp(name,"R_Do") == 0) return I_DO;
else if(strcasecmp(name,"Jmp_if_True") == 0) return I_JMP_IF_TRUE;
else if(strcasecmp(name,"Jmp_if_False") == 0) return I_JMP_IF_FALSE;
else if(strcasecmp(name,"Jr_if_True") == 0) return I_JR_IF_TRUE;
else if(strcasecmp(name,"Jr_if_False") == 0) return I_JR_IF_FALSE;
else if(strcasecmp(name,"Jr") == 0) return I_JR;
else if(strcasecmp(name,"Jmp") == 0) return I_JMP;
else return 0;
}
#endif /* __ASM_H_INCLUDED */
