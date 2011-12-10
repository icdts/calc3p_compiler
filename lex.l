%{
#include <stdlib.h>
#include <string.h>
#include "calc3.h"
#include "y.tab.h"
//#define LEX_DEBUG

void yyerror(char *);
int current_next_var_index = 0;

typedef struct var {
	int index;
	struct var* next;
	char* name;
} var;

struct var * first_var;

int find_var(char*  name);
int current_next_index = 0;
%}

%%

"int"		{
				yylval.iType = typeIntId; 
				return TYPE;
			};
"float"		{
				yylval.iType = typeFloatId; 
				return TYPE;
			};
"for"			return FOR;
">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"+="			return PluE;
"-="			return MinE;
"*="			return MulE;
"/="			return DivE;
"%="			return ModE;
"while"         return WHILE;
"do"			return DO;
"until"			return UNTIL;
"if"            return IF;
"else"          return ELSE;
"print"         return PRINT;
"step"			return STEP;
"to"			return TO;
"//"[^\n]*			return COMMENT;
"/*"([^\*]|\*[^/])*"*/" return COMMENT;

[a-zA-Z_][a-zA-Z_0-9]*	{
                yylval.sIndex = find_var(yytext);
                return VARIABLE;
            }

0           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }
[0-9][0-9]*"."[0-9][0-9]* {
				yylval.fValue = atof(yytext);
                return FLOAT;
			}

[1-9][0-9]* {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[-()<>=+*/;{}%.] {
                return *yytext;
             }

[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("Unknown character");

%%

int find_var(char*  name){
	struct var *prev = NULL;
	struct var *current = first_var;

	while ( current != NULL ){
		if( strcmp(current->name,name) == 0 ){
			return current->index;
		}
		prev = current;
		current = current->next;
	}

	//Didn't find it
	struct var *new = (struct var *)malloc(sizeof(struct var));
	new->index = current_next_index;
	current_next_index = current_next_index + 1;

	new->name = (char *)malloc(sizeof(char*));
	strcpy(new->name,name);
	new->next = NULL;

	if( prev == NULL ){
		first_var = new;
	}else{
		prev->next = new;
	}

	return new->index;
}

int yywrap(void) {
    return 1;
}
