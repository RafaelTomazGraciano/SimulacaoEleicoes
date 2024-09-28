all: main

main: main.o funcoes.o
	gcc -Wall -o main main.o funcoes.o

main.o: main.c
	gcc -c -Wall main.c

funcoes.o: funcoes.c
	gcc -c -Wall funcoes.c

clean: 
	rm main.o
	rm funcoes.o
	rm main
