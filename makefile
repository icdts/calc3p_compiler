calc3p: lex.yy.c y.tab.c
	gcc -g compiler.c y.tab.c lex.yy.c -o wat
lex.yy.c: y.tab.h lex.l
	lex lex.l
y.tab.c: y.tab.h
y.tab.h: yacc.y
	yacc -d yacc.y
clean:
	rm -rf y.tab.h y.tab.c lex.yy.c wat
