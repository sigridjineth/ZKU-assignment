CC=g++
CFLAGS=-O3 -I.
DEPS_HPP = circom.hpp calcwit.hpp fr.hpp
DEPS_O = main.o calcwit.o fr.o fr_asm.o

all: merkle_root

%.o: %.cpp $(DEPS_HPP)
	$(CC) -c $< $(CFLAGS)
fr_asm.o: fr.asm
	nasm -felf64 fr.asm -o fr_asm.o

merkle_root: $(DEPS_O) merkle_root.o
	$(CC) -o merkle_root *.o -lgmp
