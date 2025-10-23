flags=-O2 -Wall -std=c23
ldflags=-lbu

.PHONY: clean

all: clean alloc

alloc: alloc.o heap.o
	cc $(flags) $^ -o $@ $(ldflags)

alloc.o: alloc.c alloc.h
	cc $(flags) -c $<

heap.o: heap.asm
	nasm -f elf $^

clean:
	rm -f *.o alloc