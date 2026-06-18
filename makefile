all: damas

damas: main.o captura.o tabuleiro.o jogo.o engine.o
	gcc main.o captura.o tabuleiro.o jogo.o engine.o -o damas

main.o: main.c captura.h tabuleiro.h jogo.h engine.h
	gcc -Wall -Wextra -std=c99 -c main.c -o main.o

captura.o: captura.c captura.h
	gcc -Wall -Wextra -std=c99 -c captura.c -o captura.o

tabuleiro.o: tabuleiro.c tabuleiro.h
	gcc -Wall -Wextra -std=c99 -c tabuleiro.c -o tabuleiro.o

jogo.o: jogo.c jogo.h
	gcc -Wall -Wextra -std=c99 -c jogo.c -o jogo.o

clean:
	rm -f *.o damas
#Tem que ajeitar ainda depende de como os arquivos se entrelacarão
