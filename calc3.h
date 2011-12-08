#include <stdio.h>
#include <stdlib.h>

typedef enum { typeIntCon, typeFloatCon, typeIntId, typeFloatId, typeOpr } nodeEnum;

typedef struct {
	int type;
} variable;

/* constants */
typedef struct {
    int value;                  /* value of constant */
} integerConNodeType;

typedef struct {
	float value;
} floatConNodeType;

/* identifiers */
typedef struct {
    int i;                      /* subscript to ident array */
	int defined;
	int type;
} intIdNodeType;

typedef struct {
    int i;                      /* subscript to ident array */
	int defined;
	int type;
} floatIdNodeType;

/* operators */
typedef struct {
    int oper;                   /* operator */
    int nops;                   /* number of operands */
    struct nodeTypeTag *op[1];  /* operands (expandable) */
} oprNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;              /* type of node */

    /* union must be last entry in nodeType */
    /* because operNodeType may dynamically increase */
    union {
        integerConNodeType iCon;        /* integer constants */
		floatConNodeType fCon;			/* float constants */
        intIdNodeType iId;          		/* identifiers */
		floatIdNodeType fId;
        oprNodeType opr;        		/* operators */
    };
} nodeType;

struct type_stack {
	int type;
	struct type_stack * previous;
};

void push_type(int t);
int pop_type();
void printTypeStack();

extern variable *sym[99];
struct type_stack * top_of_stack;
