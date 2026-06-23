#Davi Carvalho Lira 605144
#Felipe Gabriel Sasaki 599549
#Roger Levi Forte de Brito 601576

all: damas

damas: main.o captura.o tabuleiro.o engine.o
	gcc main.o captura.o tabuleiro.o engine.o -o damas

main.o: main.c captura.h tabuleiro.h engine.h
	gcc -Wall -Wextra -std=c99 -c main.c -o main.o

engine.o: engine.c engine.h tabuleiro.h captura.h
	gcc -Wall -Wextra -std=c99 -c engine.c -o engine.o

captura.o: captura.c captura.h tabuleiro.h
	gcc -Wall -Wextra -std=c99 -c captura.c -o captura.o

tabuleiro.o: tabuleiro.c tabuleiro.h
	gcc -Wall -Wextra -std=c99 -c tabuleiro.c -o tabuleiro.o

clean:
	rm -f *.o damas
