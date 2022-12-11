assembler: prog.o print.o macro.o oneCheck.o secondCheck.o
	gcc -g -ansi prog.o print.o macro.o oneCheck.o secondCheck.o -o assembler
prog.o: prog.c oneCheck.h
	gcc -c -Wall -ansi -pedantic prog.c -o prog.o
print.o: print.c print.h
	gcc -c -Wall -ansi -pedantic print.c -o print.o 
macro.o: macro.c macro.h
	gcc -c -Wall -ansi -pedantic macro.c -o macro.o
oneCheck.o: oneCheck.c oneCheck.h print.h macro.h
	gcc -c -Wall -ansi -pedantic oneCheck.c -o oneCheck.o
secondCheck.o: secondCheck.c secondCheck.h oneCheck.h
	gcc -c -Wall -ansi -pedantic secondCheck.c -o secondCheck.o
