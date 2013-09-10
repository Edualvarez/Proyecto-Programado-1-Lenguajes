proyecto1: proyecto1.o
	gcc -m32 -o proyecto1 proyecto1.o

proyecto1.o: proyecto1.c
	gcc -f elf -o proyecto1.o proyecto1.c
