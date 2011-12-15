%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "calc3.h"
#define YYDEBUG 1
#define YYERROR_VERBOSE 1
/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id(int i);
nodeType *proc(int i);
nodeType *iCon(int value);
nodeType *fCon(float value);
nodeType *defVar(int type, int var);
void freeNode(nodeType *p);
int ex(nodeType *p);
int yylex(void);
void print_all();

void yyerror(const char *s);

variable *sym[99];                    /* symbol table */
nodeType * top;
%}

%union {
    int iValue;                 /* integer value */
	float fValue;				/* float value */
    char sIndex;                /* symbol table index */
	int iType;					/* Type enum */
    nodeType *nPtr;             /* node pointer */
};

%token <iValue> INTEGER
%token <fValue> FLOAT
%token <sIndex> VARIABLE
%token <iType> TYPE
%token DO UNTIL WHILE IF PRINT FOR STEP TO COMMENT PROG PROC FUNC CALL
%nonassoc IFX
%nonassoc ELSE
%nonassoc FUNC_STMT
%nonassoc FUNC_NO_ARG

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%left PluE MinE MulE DivE ModE
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list def_var function

%%

program:
        function                { top = opr(PROG,1,$1); ex(top); freeNode(top); print_all(); exit(0); }
        ;

function:
          stmt function							         		{ $$ = opr(';', 2, $1, $2); }
		| PROC VARIABLE '(' ')' '{' stmt '}' function			{ $$ = opr(PROC, 3, proc($2), $6, $8);} //No args
        | /* NULL */ 						{ $$ = opr(';', 2, NULL, NULL); }
        ;
def_var: 
		TYPE VARIABLE				 { $$ = defVar($1,$2); }
		;
stmt:
        ';'															{ $$ = opr(';', 2, NULL, NULL); }
		| COMMENT													{ $$ = opr('c', 0); }
        | expr ';'                       							{ $$ = $1; }
		| def_var ';'					 							{ $$ = $1; }
        | PRINT expr ';'                 							{ $$ = opr(PRINT, 1, $2); }
        | VARIABLE '=' expr ';'         				 			{ $$ = opr('=', 2, id($1), $3); }
        | VARIABLE PluE expr ';'         				 			{ $$ = opr(PluE, 2, id($1), $3); }
        | VARIABLE MinE expr ';'         				 			{ $$ = opr(MinE, 2, id($1), $3); }
        | VARIABLE MulE expr ';'         				 			{ $$ = opr(MulE, 2, id($1), $3); }
        | VARIABLE DivE expr ';'         				 			{ $$ = opr(DivE, 2, id($1), $3); }
        | VARIABLE ModE expr ';'         				 			{ $$ = opr(ModE, 2, id($1), $3); }
        | WHILE '(' expr ')' stmt        							{ $$ = opr(WHILE, 2, $3, $5); }
		| DO stmt WHILE '(' expr ')'								{ $$ = opr(DO, 2, $2, $5); }
		| DO stmt UNTIL '(' expr ')'								{ $$ = opr(UNTIL, 2, $2, $5); }
		| FOR '(' VARIABLE '=' expr STEP expr TO expr ')' stmt		{ $$ = opr(FOR, 5, id($3),$5,$7,$9,$11); }
        | IF '(' expr ')' stmt %prec IFX 							{ $$ = opr(IF, 2, $3, $5); }
        | IF '(' expr ')' stmt ELSE stmt 							{ $$ = opr(IF, 3, $3, $5, $7); }
        | '{' stmt_list '}'											{ $$ = $2; }
		| VARIABLE '(' ')'											{ $$ = opr(CALL, 1, proc($1)); }
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;

expr:
          INTEGER               { $$ = iCon($1); }
        | FLOAT					{ $$ = fCon($1); }
        | VARIABLE              { $$ = id($1); }
        | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }
        | expr '+' expr         { $$ = opr('+', 2, $1, $3); }
        | expr '-' expr         { $$ = opr('-', 2, $1, $3); }
        | expr '*' expr         { $$ = opr('*', 2, $1, $3); }
        | expr '/' expr         { $$ = opr('/', 2, $1, $3); }
        | expr '<' expr         { $$ = opr('<', 2, $1, $3); }
        | expr '>' expr         { $$ = opr('>', 2, $1, $3); }
		| expr '%' expr			{ $$ = opr('%', 2, $1, $3); }
        | expr GE expr          { $$ = opr(GE, 2, $1, $3); }
        | expr LE expr          { $$ = opr(LE, 2, $1, $3); }
        | expr NE expr          { $$ = opr(NE, 2, $1, $3); }
        | expr EQ expr          { $$ = opr(EQ, 2, $1, $3); }
        | '(' expr ')'          { $$ = $2; }
        ;

%%

#define SIZEOF_NODETYPE ((char *)&p->iCon - (char *)p)



nodeType *iCon(int value) {
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(integerConNodeType);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeIntCon;
    p->iCon.value = value;

    return p;
}

nodeType *fCon(float value) {
    nodeType *p;
    size_t nodeSize;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(floatConNodeType);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeFloatCon;
    p->fCon.value = value;

    return p;
}

nodeType *id(int i) {
    nodeType *p;
    size_t nodeSize;

	if( sym[i] == NULL ){
		yyerror("variable used before definition");
	}

    // allocate node 
	//fprintf(stderr,"i: %d",i);
	//fprintf(stderr,"sym[i]->type: %d",sym[i]->type);
	//fprintf(stderr,"typeIntId: %d",typeIntId);
	if( sym[i]->type == typeIntId ){ 
    	nodeSize = SIZEOF_NODETYPE + sizeof(intIdNodeType);
	}else{
    	nodeSize = SIZEOF_NODETYPE + sizeof(floatIdNodeType);
	}
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
	//fprintf(stderr,"VAR %d has type %d",i,sym[i]->type);
    p->type = sym[i]->type;
	
	if( p->type == typeIntId ){
    	p->iId.i = i;
	}else if( p->type == typeFloatId ){
    	p->fId.i = i;
		//fprintf(stderr,"Setting fId = %d\n",p->fId.i);
	}else{
		printf("Unkown error");
		exit(1);
	}

    return p;
}

nodeType *proc(int i){
    nodeType *p;
    size_t nodeSize;

	if( sym[i] == NULL ){
		yyerror("variable used before definition");
	}

    // allocate node 
    nodeSize = SIZEOF_NODETYPE + sizeof(intIdNodeType);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeProc;
	
	p->iId.i = i;

    return p;
}

nodeType *defVar(int type, int var){
	//fprintf(stderr,"defining variable %d as type %d\n", var, type);
	if( sym[var] == NULL ){
		sym[var] = (variable *)malloc(sizeof(variable *));

		//fprintf(stderr,"Defining %d var as type %d\n",var,type);
		sym[var]->type = type;
	
		return opr('D', 0);
	}else{
		yyerror("variable defined twice.");
		exit(1);
	}
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    size_t nodeSize;
    int i;

    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(oprNodeType) +
        (nops - 1) * sizeof(nodeType*);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType*);
    va_end(ap);
    return p;
}

void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(const char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(int argc, char **argv){
	if(argc > 1){
		stdin = fopen(argv[1],"r"); 
	}
    yyparse();

	if(argc > 1){
		fclose(stdin);
	}
    return 0;
}
