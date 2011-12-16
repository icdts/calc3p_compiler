#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "apm.h"
#include "apname.h"

#ifndef SDB

int print_instr();

WORD s[STORAGE];

int
main(argc,argv)
int argc;
char *argv[];
{
int fd;
int i;
int bytes;
char *buf;

if(argc <= 1)
	{
	fd = 0;
	}
else if((fd=open(argv[1],0)) >= 0)
	{
	}
else
	{
	buf = calloc(strlen(argv[1]) + 5, sizeof(char));
	strcpy(buf,argv[1]);
	strcat(buf,".apm");
	if((fd=open(buf,0)) == -1)
		{
		fprintf(stderr,"Can't open %s.\n",buf);
		exit(1);
		}
	}
bytes = read(fd,s,STORAGE*sizeof (WORD));
for(i=1;i<bytes/sizeof(WORD);i++)
	{
	printf("%04d ",i);
	i = print_instr(s,i, buf);
	printf("%s", buf);
	}
	exit(0);
}
#endif

int
print_instr(s, i, buf)
WORD  s[];
int i;
char *buf;
{
switch(s[i].Integer)
	{
	case I_ADD:
		sprintf(buf, "%s\n", I_ADD_NAME);
		break;
	case I_AND:
		sprintf(buf, "%s\n", I_AND_NAME);
		break;
	case I_ARROW:
		sprintf(buf, "%s addr:%d\n", I_ARROW_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_ASSIGN:
		sprintf(buf, "%s  words:%d\n", I_ASSIGN_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_BAR:
		sprintf(buf, "%s addr:%d\n", I_BAR_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_CALL:
		sprintf(buf, "%s lev:%d addr:%d\n", I_CALL_NAME,s[i+1].Integer,s[i+2].Integer);
		i += 2;
		break;
	case I_CONSTANT:
		sprintf(buf, "%s value:%d\n", I_CONSTANT_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_DIVIDE:
		sprintf(buf, "%s\n", I_DIVIDE_NAME);
		break;
	case I_ENDPROC:
		sprintf(buf, "%s\n", I_ENDPROC_NAME);
		break;
	case I_ENDPPROC:
		sprintf(buf, "%s args:%d\n", I_ENDPPROC_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_ENDPROG:
		sprintf(buf, "%s\n", I_ENDPROG_NAME);
		break;
	case I_EQUAL:
		sprintf(buf, "%s\n", I_EQUAL_NAME);
		break;
	case I_FI:
		sprintf(buf, "%s lineno:%d\n", I_FI_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_GREATER:
		sprintf(buf, "%s\n", I_GREATER_NAME);
		break;
	case I_INDEX:
		sprintf(buf, "%s bound:%d lineno:%d\n", I_INDEX_NAME,s[i+1].Integer,s[i+2].Integer);
		i += 2;
		break;
	case I_LESS:
		sprintf(buf, "%s\n", I_LESS_NAME);
		break;
	case I_MINUS:
		sprintf(buf, "%s\n", I_MINUS_NAME);
		break;
	case I_MODULO:
		sprintf(buf, "%s\n", I_MODULO_NAME);
		break;
	case I_MULTIPLY:
		sprintf(buf, "%s\n", I_MULTIPLY_NAME);
		break;
	case I_NOT:
		sprintf(buf, "%s\n", I_NOT_NAME);
		break;
	case I_OR:
		sprintf(buf, "%s\n", I_OR_NAME);
		break;
	case I_PROC:
		sprintf(buf, "%s varlen:%d addr:%d\n", I_PROC_NAME,s[i+1].Integer,s[i+2].Integer);
		i += 2;
		break;
	case I_PROG:
		sprintf(buf, "%s varlen:%d addr:%d\n", I_PROG_NAME,s[i+1].Integer,s[i+2].Integer);
		i += 2;
		break;
	case I_READ:
		sprintf(buf, "%s words:%d\n", I_READ_NAME,s[i+1].Integer);
		i += 1;
		break;
	case C_READ:
		sprintf(buf, "%s chars:%d\n", C_READ_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_SUBTRACT:
		sprintf(buf, "%s\n", I_SUBTRACT_NAME);
		break;
	case I_VALUE:
		sprintf(buf, "%s\n", I_VALUE_NAME);
		break;
	case I_VARIABLE:
		sprintf(buf, "%s lev:%d disp:%d\n", I_VARIABLE_NAME,s[i+1].Integer,s[i+2].Integer);
		i += 2;
		break;
	case I_WRITE:
		sprintf(buf, "%s words:%d\n", I_WRITE_NAME,s[i+1].Integer);
		i += 1;
		break;
	case C_WRITE:
		sprintf(buf, "%s chars:%d\n", C_WRITE_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_TO_R:
		sprintf(buf, "%s\n", I_TO_R_NAME);
		break;

	case R_ADD:
		sprintf(buf, "%s\n", R_ADD_NAME);
		break;
	case R_ASSIGN:
		sprintf(buf, "%s  words:%f\n", R_ASSIGN_NAME,s[i+1].Real);
		i += 1;
		break;
	case R_CONSTANT:
		sprintf(buf, "%s value:%f\n", R_CONSTANT_NAME,s[i+1].Real);
		i += 1;
		break;
	case R_DIVIDE:
		sprintf(buf, "%s\n", R_DIVIDE_NAME);
		break;
	case R_EQUAL:
		sprintf(buf, "%s\n", R_EQUAL_NAME);
		break;
	case R_GREATER:
		sprintf(buf, "%s\n", R_GREATER_NAME);
		break;
	case R_LESS:
		sprintf(buf, "%s\n", R_LESS_NAME);
		break;
	case R_MINUS:
		sprintf(buf, "%s\n", R_MINUS_NAME);
		break;
	case R_MULTIPLY:
		sprintf(buf, "%s\n", R_MULTIPLY_NAME);
		break;
	case R_READ:
		sprintf(buf, "%s words:%d\n", R_READ_NAME,s[i+1].Integer);
		i += 1;
		break;
	case R_SUBTRACT:
		sprintf(buf, "%s\n", R_SUBTRACT_NAME);
		break;
	case R_VALUE:
		sprintf(buf, "%s\n", R_VALUE_NAME);
		break;
	case R_VARIABLE:
		sprintf(buf, "%s lev:%d disp:%d\n", R_VARIABLE_NAME,s[i+1].Integer,s[i+2].Integer);
		i += 2;
		break;
	case R_WRITE:
		sprintf(buf, "%s words:%d\n", R_WRITE_NAME,s[i+1].Integer);
		i += 1;
		break;
	case R_TO_I:
		sprintf(buf, "%s\n", R_TO_I_NAME);
		break;

	case I_DO:
		sprintf(buf, "%s by:%d\n", DO_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_JMP_IF_TRUE:
		sprintf(buf, "%s to:%d\n", JMP_IF_TRUE_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_JMP_IF_FALSE :
		sprintf(buf, "%s by:%d\n", JMP_IF_FALSE_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_JR_IF_TRUE:
		sprintf(buf, "%s by:%d\n", JR_IF_TRUE_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_JR_IF_FALSE:
		sprintf(buf, "%s to:%d\n", JR_IF_FALSE_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_JR:
		sprintf(buf, "%s by:%d\n", JR_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_JMP:
		sprintf(buf, "%s to:%d\n", JMP_NAME,s[i+1].Integer);
		i += 1;
		break;
	case I_SWAP:
		sprintf(buf, "%s\n", SWAP_NAME);
		break;
	default:
		sprintf(buf, "DATA %d\n", s[i].Integer);
		break;
	}
	return i;
}

