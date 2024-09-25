all: main

trabalho: main.o funcoes.o
	gcc -o main main.o funcoes.o

clean: 
	rm trabalho2.o
	rm estoque.o
	rm trabalho