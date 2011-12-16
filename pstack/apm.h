#ifndef APMH
#define APMH
#define I_ADD		1
#define I_AND		2
#define I_ARROW		3
#define I_ASSIGN	4
#define I_BAR		5
#define I_CALL		6
#define I_CONSTANT	7
#define I_DIVIDE	8
#define I_ENDPROC	9
#define I_ENDPROG	10
#define I_EQUAL		11
#define I_FI		12
#define I_GREATER	13
#define I_INDEX		14
#define I_LESS		15
#define I_MINUS		16
#define I_MODULO	17
#define I_MULTIPLY	18
#define I_NOT		19
#define I_OR		20
#define I_PROC		21
#define I_PROG		22
#define I_READ		23
#define I_SUBTRACT	24
#define I_VALUE		25
#define I_VARIABLE	26
#define I_WRITE		27
#define I_TO_R		28

#define R_ADD		31
#define R_ASSIGN	34
#define R_CONSTANT	37
#define R_DIVIDE	38
#define R_EQUAL		41
#define R_GREATER	43
#define R_LESS		45
#define R_MINUS		46
#define R_MULTIPLY	48
#define R_READ		53
#define R_SUBTRACT	54
#define R_VALUE		55
#define R_VARIABLE	56
#define R_WRITE		57
#define R_TO_I		58
#define I_SWAP		59

#define I_DO		60
#define I_JMP_IF_TRUE	61
#define I_JMP_IF_FALSE 	62
#define I_JR_IF_TRUE	63
#define I_JR_IF_FALSE	64
#define I_JR		65
#define I_JMP		66
#define I_ENDPPROC	67

#define C_READ          68
#define C_WRITE         69

/* memory cells are assumed to be of type WORD */
typedef union word {
	int Integer;
	float Real;
	} WORD;

#define STORAGE (50*1024)
#endif
