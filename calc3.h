typedef enum { typeIntCon, typeFloatCon, typeId, typeOpr } nodeEnum;


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
} idNodeType;

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
        idNodeType id;          		/* identifiers */
        oprNodeType opr;        		/* operators */
    };
} nodeType;

extern variable *sym[99];
