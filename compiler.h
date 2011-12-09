#include <stdarg.h>

struct type_stack {
	int type;
	struct type_stack * previous;
};

void push_type(int t);
int pop_type();
void printTypeStack();

void print_asm_statement(char* cmd, int argc, ...);
char* iargs(char* str, int i);
char* fargs(char* str, float f);

struct type_stack * top_of_stack;
