FLAGS= -Wall -g
CC= gcc $(FLAGS)

all:
	core.o main

clean: 
	rm -rf *.o

core.o: core.c core.h
	$(CC) -c $<

main: main.c core.o
	$(CC) -o $@ $^

#all:
	#$(CC) -o a disassemble.c
