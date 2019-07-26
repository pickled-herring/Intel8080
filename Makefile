FLAGS= -Wall -g
CC= gcc $(FLAGS)

all:
	$(CC) -o a disassemble.c
