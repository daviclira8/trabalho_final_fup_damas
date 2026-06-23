<<<<<<< HEAD
/*
Davi Carvalho Lira 605144
Felipe Gabriel Sasaki 599549
Roger Levi Forte de Brito 601576
*/

=======
<<<<<<< HEAD
=======
>>>>>>> main
all: damas

damas: main.o captura.o tabuleiro.o jogo.o engine.o
	gcc main.o captura.o tabuleiro.o jogo.o engine.o -o damas

<<<<<<< HEAD
main.o: main.c
=======
main.o: main.c captura.h tabuleiro.h jogo.h engine.h
>>>>>>> main
	gcc -Wall -Wextra -std=c99 -c main.c -o main.o

captura.o: captura.c captura.h
	gcc -Wall -Wextra -std=c99 -c captura.c -o captura.o

tabuleiro.o: tabuleiro.c tabuleiro.h
	gcc -Wall -Wextra -std=c99 -c tabuleiro.c -o tabuleiro.o

jogo.o: jogo.c jogo.h
	gcc -Wall -Wextra -std=c99 -c jogo.c -o jogo.o

<<<<<<< HEAD
engine.o: engine.c engine.h
	gcc -Wall -Wextra -std=c99 -c engine.c -o engine.o

clean:
	rm -f *.o damas
=======
clean:
	rm -f *.o damas
#Tem que ajeitar ainda depende de como os arquivos se entrelacarão
>>>>>>> 2bb68577d06381f04bff2f8e1d00fe85e90f2526
>>>>>>> main
