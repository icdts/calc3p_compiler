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

void push_type(int t);
int pop_type();
void printTypeStack();

struct statement * push_asm_statement(char* cmd, int argc, ...);
void replace_asm_statement(int position, char* cmd, int argc, ...);
void insert_asm_statement(int position, char* cmd, int argc, ...);
char* iargs(char* str, int i);
char* fargs(char* str, float f);

void comparison_operator(nodeType* op1, nodeType* op2, char* name);
void math_operator(nodeType* op1, nodeType* op2, char* name);
void math_assignment(nodeType* var, nodeType* expr, char* name);
void assignment(nodeType* var, nodeType* expr);
void get_values_and_convert(int *type1, int *type2, int insert_at);
int is_real_op(int type1, int type2);
