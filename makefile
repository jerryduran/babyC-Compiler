all: Parser Scanner BabyC  
	gcc BabyC.tab.o lex.yy.o driver.o abt.o -o bcc 

BabyC: driver.o abt.o

		
Scanner: BabyC.lex
	flex BabyC.lex
	gcc -c lex.yy.c
	
 Parser: BabyC.y
	bison -d BabyC.y
	gcc -c BabyC.tab.c

%.o: %.c
	gcc -c $<
