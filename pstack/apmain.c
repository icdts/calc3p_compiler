#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apm.h"
#include "apname.h"

WORD storage[STORAGE];
int maxStorage = 0;

FILE *yyin;
int yyparse(void);

int
main(argc,argv)
int argc;
char *argv[];
{
char *buf;

if(argc <= 1)
	{
	yyin = stdin;
	}
else if((yyin=fopen(argv[1],"r")) != NULL)
	{
	}
else
	{
	buf = calloc(strlen(argv[1]) + 5, sizeof(char));
	strcpy(buf,argv[1]);
	strcat(buf,".aa");
	if((yyin=fopen(buf,"r")) == NULL)
		{
		fprintf(stderr,"Can't open %s.\n",buf);
		exit(1);
		}
	}
	storage[0].Integer = 0;
	yyparse();
	fwrite(storage, sizeof(WORD), maxStorage+1, stdout);
	exit(0);
}
