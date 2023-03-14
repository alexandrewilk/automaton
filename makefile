automaton: main.o stack.o interpreteurAutomate.o
	gcc -o automaton $^ -Wall
interpreteurAutomate.o : interpreteurAutomate.c stack.h
	gcc -o interpreteurAutomate.o -c interpreteurAutomate.c -Wall
stack.o : stack.c
	gcc -o stack.o -c stack.c -Wall
clear: 
	rm -rf *.o
totalclear : clear
	rm -rf automaton