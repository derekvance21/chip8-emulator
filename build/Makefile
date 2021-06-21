CC = g++
CFLAGS = -Wall -g

default: main


main: main.o chip8.o opcode.o
	$(CC) $(CFLAGS) -o chip8 main.o chip8.o opcode.o

main.o: ../src/main.cc ../src/chip8.h
	$(CC) $(CFLAGS) -c ../src/main.cc

chip8.o: ../src/chip8.cc opcode.o
	$(CC) $(CFLAGS) -c ../src/chip8.cc

opcode.o: ../src/opcode.cc 
	$(CC) $(CFLAGS) -c ../src/opcode.cc