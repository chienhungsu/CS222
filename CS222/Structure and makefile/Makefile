complex : main.o complex.o
	gcc -o complex main.o complex.o -lm 

complex.o : complex.c complex.h 
	gcc -c complex.c

main.o : main.c complex.h
	gcc -c main.c
