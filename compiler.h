#include <stdarg.h>
#include <string.h>

#define MAX_STMT_LEN 50

struct type_stack {
	int type;
	struct type_stack * previous;
};

struct statement {
	char * string;
	int position;
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

struct statement * push_asm_statement(char* cmd, int argc, ...);
void replace_asm_statement(int position, char* cmd, int argc, ...);
void insert_asm_statement(int position, char* cmd, int argc, ...);
char* iargs(int i);
char* fargs(float f);

void comparison_operator(nodeType* op1, nodeType* op2, char* name);
void math_operator(nodeType* op1, nodeType* op2, char* name);
void math_assignment(nodeType* var, nodeType* expr, char* name);
void assignment(nodeType* var, nodeType* expr);
void get_values_and_convert(int *type1, int *type2, int insert_at);
int is_real_op(int type1, int type2);

void check_arguments(struct proc * p);
