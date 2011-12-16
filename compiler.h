#include <stdarg.h>
#include <string.h>

#define MAX_STMT_LEN 50

#define I_Add		1
#define I_And		2
#define I_Arrow		3
#define I_Assign	4
#define I_Bar		5
#define I_Call		6
#define I_Constant	7
#define I_Divide	8
#define I_EndProc	9
#define I_EndProg	10
#define I_Equal		11
#define I_Fi		12
#define I_Greater	13
#define I_Index		14
#define I_Less		15
#define I_Minus		16
#define I_Modulo	17
#define I_Multiply	18
#define I_Not		19
#define I_Or		20
#define I_Proc		21
#define I_Prog		22
#define I_Read		23
#define I_Subtract	24
#define I_Value		25
#define I_Variable	26
#define I_Write		27
#define I_To_R		28

#define R_Add		31
#define R_Assign	34
#define R_Constant	37
#define R_Divide	38
#define R_Equal		41
#define R_Greater	43
#define R_Less		45
#define R_Minus		46
#define R_Multiply	48
#define R_Read		53
#define R_Subtract	54
#define R_Value		55
#define R_Variable	56
#define R_Write		57
#define R_To_I		58
#define I_Swap		59

#define I_Do		60
#define I_Jmp_If_True	61
#define I_Jmp_If_False 	62
#define I_Jr_If_True	63
#define I_Jr_If_False	64
#define I_Jmp		65

struct type_stack {
	int type;
	struct type_stack * previous;
};

struct statement {
	int position;
	int cmd;
	int argc;
	int *i_or_f;
	int *iargs;
	float *fargs;
	struct statement * next_statement;
};

struct proc {
	int id;
	int position;
	int params[50];
	int return_value;
	int return_pos;
	struct proc * next_proc;
};

void push_type(int t);
int pop_type();
void printTypeStack();

int get_proc_start(int proc_id);
struct proc * get_proc(int proc_id);

void push_asm_statement(int cmd, int argc, ...);
void replace_asm_statement(int position, int cmd, int argc, ...);
void insert_asm_statement(int position, int cmd, int argc, ...);

void comparison_operator(nodeType* op1, nodeType* op2, char* name);
void math_operator(nodeType* op1, nodeType* op2, char* name);
void math_assignment(nodeType* var, nodeType* expr, char* name);
void assignment(nodeType* var, nodeType* expr);
void get_values_and_convert(int *type1, int *type2, int insert_at);
int is_real_op(int type1, int type2);

void check_arguments(struct proc * p);
