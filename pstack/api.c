#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "apm.h"
#include "apname.h"

#ifndef SDB

void allocate();
void execute();

WORD St[STORAGE];
int s;	/* Stack Pointer */
int p;  /* Program Counter */
int b;  /* Base Register */
int stackbottom;

int
main(argc,argv)
int argc;
char *argv[];
{
int fd;
int verbose;
char buf[256];

verbose=0;
strncpy(buf,argv[1], 251);
strcat(buf,".apm");
if((fd=open(buf,0)) == -1)
	{
	fprintf(stderr,"Can't open %s.\n",buf);
	exit(1);
	}
if(argc > 2) verbose=1;
stackbottom=read(fd,St,STORAGE*sizeof (WORD));
stackbottom /= sizeof (WORD);
for(p=1;St[p].Integer != 0&&p<STORAGE;)
	{
	if(verbose)printf("%04d ",p);
	execute(St, &p, &s, &b, verbose);
	}
fprintf(stderr,"Runaway machine\n");
exit(1);
}
#else
#include "sdb.h"
void die();
extern char Tags[];
#endif

void
execute(Mem, pr, sr, br, verbose)
WORD Mem[];
int *pr, *sr, *br, verbose;
{
	register int p, b;
	int s;
	int x;
	int level;
	char buf[256];
	
	p = *pr; s = *sr; b = *br;
	switch(Mem[p].Integer)
		{
		case I_ADD:
			if(verbose)printf("%s\n",I_ADD_NAME);
			p++; s--;
			Mem[s].Integer += Mem[s+1].Integer;
			break;
		case I_AND:
			if(verbose)printf("%s\n",I_AND_NAME);
			p++; s--;
			if(Mem[s].Integer) Mem[s].Integer=Mem[s+1].Integer;
			break;
		case I_ARROW:
			if(verbose)printf("%s addr:%d\n", I_ARROW_NAME,Mem[p+1].Integer);
			if(Mem[s].Integer)
				p += 2;
			else
				p = Mem[p+1].Integer;
			s--;
			break;
		case I_ASSIGN:
			if(verbose)printf("%s words:%d\n", I_ASSIGN_NAME ,Mem[p+1].Integer);
			s = s - 2*Mem[p+1].Integer;
			x = s;
			while(x<s+Mem[p+1].Integer)
				{
				x++;
				Mem[Mem[x].Integer].Integer = Mem[x+Mem[p+1].Integer].Integer;
				}
			p += 2;
			break;
		case I_BAR:
			if(verbose)printf("%s addr:%d\n", I_BAR_NAME ,Mem[p+1].Integer);
			p = Mem[p+1].Integer;
			break;
		case I_CALL:
			if(verbose)printf("%s level:%d addr:%d\n", I_CALL_NAME ,Mem[p+1].Integer,Mem[p+2].Integer);
			allocate(&s, 3);
			x = b;
			level=Mem[p+1].Integer;
			while(level > 0)
				{
				x = Mem[x].Integer;
				level--;
				}
			Mem[s-2].Integer=x;
			Mem[s-1].Integer=b;
			Mem[s].Integer=p+3;
			b=s-2;
			p=Mem[p+2].Integer;
			break;
		case I_CONSTANT:
			if(verbose)printf("%s value:%d\n", I_CONSTANT_NAME ,Mem[p+1].Integer);
			allocate(&s, 1);
			Mem[s].Integer=Mem[p+1].Integer;
			p += 2;
			break;
		case I_DIVIDE:
			if(verbose)printf("%s\n", I_DIVIDE_NAME);
			p++; s--;
			Mem[s].Integer /= Mem[s+1].Integer;
			break;
		case I_ENDPROC:
			if(verbose)printf("%s\n", I_ENDPROC_NAME);
			s = b-1;
			p=Mem[b+2].Integer;
			b=Mem[b+1].Integer;
			break;
		case I_ENDPPROC:
			if(verbose)printf("%s\n", I_ENDPPROC_NAME);
			s = b - (1 + Mem[p+1].Integer);
			p=Mem[b+2].Integer;
			b=Mem[b+1].Integer;
			break;
		case I_ENDPROG:
			if(verbose)printf("%s\n", I_ENDPROG_NAME);
#ifndef SDB
			exit(0);
#else
			die();
#endif
			break;
		case I_EQUAL:
			if(verbose)printf("%s\n", I_EQUAL_NAME);
			p++; s--;
			Mem[s].Integer = (Mem[s].Integer==Mem[s+1].Integer);
			break;
		case I_FI:
			if(verbose)printf("%s lineno:%d\n",I_FI_NAME, Mem[p+1].Integer);
			printf("If statement fails at line %d.\n",
				Mem[p+1].Integer);
#ifndef SDB
			exit(1);
#else
			die();
#endif
			break;
		case I_GREATER:
			if(verbose)printf("%s\n", I_GREATER_NAME);
			p++; s--;
			Mem[s].Integer = (Mem[s].Integer>Mem[s+1].Integer);
			break;
		case I_INDEX:
			if(verbose)printf("%s bound:%d lineno:%d\n", I_INDEX_NAME ,Mem[p+1].Integer,Mem[p+2].Integer);
			x=Mem[s].Integer; s--;
			if(x<1||x>Mem[p+1].Integer)
				{
				printf("Array bound error at line %d.\n",
					Mem[p+2].Integer);
				printf("x is %d\n", x);
#ifndef SDB
				exit(1);
#else
				die();
#endif
				}
			Mem[s].Integer = Mem[s].Integer +x-1;
			p += 3;
			break;
		case I_LESS:
			if(verbose)printf("%s\n", I_LESS_NAME);
			p++; s--;
			Mem[s].Integer = (Mem[s].Integer<Mem[s+1].Integer);
			break;
		case I_MINUS:
			if(verbose)printf("%s\n", I_MINUS_NAME);
			Mem[s].Integer = -Mem[s].Integer;
			p++;
			break;
		case I_MODULO:
			if(verbose)printf("%s\n", I_MODULO_NAME);
			p++; s--;
			Mem[s].Integer %= Mem[s+1].Integer;
			break;
		case I_MULTIPLY:
			if(verbose)printf("%s\n", I_MULTIPLY_NAME);
			p++; s--;
			Mem[s].Integer *= Mem[s+1].Integer;
			break;
		case I_NOT:
			if(verbose)printf("%s\n", I_NOT_NAME);
			Mem[s].Integer = !Mem[s].Integer;
			p++;
			break;
		case I_OR:
			if(verbose)printf("%s\n", I_OR_NAME);
			p++; s--;
			if(!Mem[s].Integer)
				Mem[s].Integer = Mem[s+1].Integer;
			break;
		case I_PROC:
			if(verbose)printf("%s  varlen:%d addr:%d\n", I_PROC_NAME,Mem[p+1].Integer,Mem[p+2].Integer);
			allocate(&s, Mem[p+1].Integer);
			p=Mem[p+2].Integer;
			break;
		case I_PROG:
			if(verbose)printf("%s varlen:%d addr:%d\n", I_PROG_NAME ,Mem[p+1].Integer,Mem[p+2].Integer);
			b = stackbottom;
			s = b;
			allocate(&s, Mem[p+1].Integer+2);
			p=Mem[p+2].Integer;
			break;
		case I_READ:
			if(verbose)printf("%s words:%d\n", I_READ_NAME ,Mem[p+1].Integer);
			s = s - Mem[p+1].Integer;
			x = s;
			while(x < s+Mem[p+1].Integer)
				{
				x++;
				printf("input-> ");
				fgets(buf,256,stdin);
				Mem[Mem[x].Integer].Integer=atoi(buf);
				}
			p += 2;
			break;
		case C_READ:
			if(verbose)printf("%s chars:%d\n", C_READ_NAME ,Mem[p+1].Integer);
			s = s - Mem[p+1].Integer;
			x = s;
			while(x < s+Mem[p+1].Integer)
				{
				int c;
				x++;
				c = fgetc(stdin);
				if(c == EOF) c = 0;
				Mem[Mem[x].Integer].Integer=c;
				if(verbose)printf("%s read char:%d '%c'\n", C_READ_NAME ,c,c);
				}
			p += 2;
			break;
		case I_SUBTRACT:
			if(verbose)printf("%s\n", I_SUBTRACT_NAME);
			p++; s--;
			Mem[s].Integer -= Mem[s+1].Integer;
			break;
		case I_VALUE:
			if(verbose)printf("%s\n", I_VALUE_NAME);
			Mem[s].Integer = Mem[Mem[s].Integer].Integer;
			p++;
			break;
		case I_VARIABLE:
			if(verbose)printf("%s level:%d displacement:%d\n", I_VARIABLE_NAME ,Mem[p+1].Integer,Mem[p+2].Integer);
			allocate(&s, 1);
			x = b;
			level=Mem[p+1].Integer;
			while(level > 0)
				{
				x=Mem[x].Integer;
				level --;
				}
			Mem[s].Integer = x + Mem[p+2].Integer;
			p += 3;
			break;
		case I_WRITE:
			if(verbose)printf("%s words:%d\n", I_WRITE_NAME ,Mem[p+1].Integer);
			s = s - Mem[p+1].Integer;
			x = s;
			while(x < s+Mem[p+1].Integer)
				{
				x++;
				printf("%6d ",Mem[x].Integer);
				}
			printf("\n");
			p += 2;
			break;
		case C_WRITE:
			if(verbose)printf("%s chars:%d\n", C_WRITE_NAME ,Mem[p+1].Integer);
			s = s - Mem[p+1].Integer;
			x = s;
			while(x < s+Mem[p+1].Integer)
				{
				x++;
				printf("%c",(char)Mem[x].Integer);
				}
			p += 2;
			break;
		case I_TO_R:
			if(verbose)printf("%s\n", I_TO_R_NAME);
			Mem[s].Real = (float) Mem[s].Integer;
			p++;
			break;

/* the real operations follow */
		case R_ADD:
			if(verbose)printf("%s\n",R_ADD_NAME);
			p++; s--;
			Mem[s].Real += Mem[s+1].Real;
			break;
		case R_ASSIGN:
			if(verbose)printf("%s words:%d\n", R_ASSIGN_NAME ,Mem[p+1].Integer);
			s = s - 2*Mem[p+1].Integer;
			x = s;
			while(x<s+Mem[p+1].Integer)
				{
				x++;
				Mem[Mem[x].Integer].Real = Mem[x+Mem[p+1].Integer].Real;
				}
			p += 2;
			break;
		case R_CONSTANT:
			if(verbose)printf("%s value:%f\n", R_CONSTANT_NAME ,Mem[p+1].Real);
			allocate(&s, 1);
			Mem[s].Real=Mem[p+1].Real;
			p += 2;
			break;
		case R_DIVIDE:
			if(verbose)printf("%s\n", R_DIVIDE_NAME);
			p++; s--;
			Mem[s].Real /= Mem[s+1].Real;
			break;
		case R_EQUAL:
			if(verbose)printf("%s\n", R_EQUAL_NAME);
			p++; s--;
			Mem[s].Integer = (Mem[s].Real==Mem[s+1].Real);
			break;
		case R_GREATER:
			if(verbose)printf("%s\n", R_GREATER_NAME);
			p++; s--;
			Mem[s].Integer = (Mem[s].Real>Mem[s+1].Real);
			break;
		case R_LESS:
			if(verbose)printf("%s\n", R_LESS_NAME);
			p++; s--;
			Mem[s].Integer = (Mem[s].Real<Mem[s+1].Real);
			break;
		case R_MINUS:
			if(verbose)printf("%s\n", R_MINUS_NAME);
			Mem[s].Real = -Mem[s].Real;
			p++;
			break;
		case R_MULTIPLY:
			if(verbose)printf("%s\n", R_MULTIPLY_NAME);
			p++; s--;
			Mem[s].Real *= Mem[s+1].Real;
			break;
		case R_READ:
			if(verbose)printf("%s words:%d\n", R_READ_NAME ,Mem[p+1].Integer);
			s = s - Mem[p+1].Integer;
			x = s;
			while(x < s+Mem[p+1].Integer)
				{
				x++;
				printf("input-> ");
				fgets(buf,256,stdin);
				Mem[Mem[x].Integer].Real=atof(buf);
				}
			p += 2;
			break;
		case R_SUBTRACT:
			if(verbose)printf("%s\n", R_SUBTRACT_NAME);
			p++; s--;
			Mem[s].Real -= Mem[s+1].Real;
			break;
		case R_VALUE:
			if(verbose)printf("%s\n", R_VALUE_NAME);
			Mem[s].Real = Mem[Mem[s].Integer].Real;
			p++;
			break;
		case R_VARIABLE:
			if(verbose)printf("%s level:%d displacement:%d\n", R_VARIABLE_NAME ,Mem[p+1].Integer,Mem[p+2].Integer);
			allocate(&s, 1);
			x = b;
			level=Mem[p+1].Integer;
			while(level > 0)
				{
				x=Mem[x].Integer;
				level --;
				}
			Mem[s].Integer = x + Mem[p+2].Integer;
			p += 3;
			break;
		case R_WRITE:
			if(verbose)printf("%s words:%d\n", R_WRITE_NAME ,Mem[p+1].Integer);
			s = s - Mem[p+1].Integer;
			x = s;
			while(x < s+Mem[p+1].Integer)
				{
				x++;
				printf("%6.3f ",Mem[x].Real);
				}
			printf("\n");
			p += 2;
			break;
		case R_TO_I:
			if(verbose)printf("%s\n", R_TO_I_NAME);
			Mem[s].Integer = (int) Mem[s].Real;
			p++;
			break;

/*finally, the jump operations */
		case I_DO:
			/* REDUNDANT, same as JR_IF_FALSE */
			if(verbose)printf("%s to:%d\n", DO_NAME, Mem[p+1].Integer);
			p = (!Mem[s].Integer) ? p+Mem[p+1].Integer : p+2;
			s--;
			break;
		case I_JMP_IF_TRUE:
			if(verbose)printf("%s to:%d\n", JMP_IF_TRUE_NAME ,Mem[p+1].Integer);
			p = (Mem[s].Integer) ? Mem[p+1].Integer : p+2;
			s--;
			break;
		case I_JMP_IF_FALSE:
			if(verbose)printf("%s to:%d\n", JMP_IF_FALSE_NAME ,Mem[p+1].Integer);
			p = (!Mem[s].Integer) ? Mem[p+1].Integer : p+2;
			s--;
			break;
		case I_JR_IF_TRUE:
			if(verbose)printf("%s to:%d\n", JR_IF_TRUE_NAME ,Mem[p+1].Integer);
			p = (Mem[s].Integer) ? p+Mem[p+1].Integer : p+2;
			s--;
			break;
		case I_JR_IF_FALSE:
			if(verbose)printf("%s to:%d\n", JR_IF_FALSE_NAME ,Mem[p+1].Integer);
			p = (!Mem[s].Integer) ? p+Mem[p+1].Integer : p+2;
			s--;
			break;
		case I_JMP:
		/* REDUNDANT, same as I_BAR */
			if(verbose)printf("%s addr:%d\n", JMP_NAME ,Mem[p+1].Integer);
			p = Mem[p+1].Integer;
			break;
		case I_JR:
			if(verbose)printf("%s addr:%d\n", JR_NAME ,Mem[p+1].Integer);
			p = p+Mem[p+1].Integer;
			break;
		case I_SWAP:
			if (verbose)printf("%s\n", SWAP_NAME);
			{
			WORD x;
			x = Mem[s]; Mem[s] = Mem[s-1]; Mem[s-1] = x;
			}
			p++;
		}
	*pr = p; *sr = s; *br = b;
	if(verbose) {
		int j;
		printf("TOS");
		for(j=s; j>=b; --j) {
			printf(" %d", Mem[j].Integer);
		}
		printf("\n");
	}
}

void
allocate(sr, words)
int words, *sr;
{
#ifdef SDB
	int i;
	char  *Tagptr;

	i = *sr;
	Tagptr = Tags + i+1;
	for (i=1;i<=words; i++) 
		*Tagptr++ = INT_MASK;
#endif
(*sr) += words;
if((*sr) > STORAGE)
	{
	fprintf(stderr,"Stack Overflow\n");
#ifndef SDB
	exit(1);
#else
	die();
#endif
	}
}
