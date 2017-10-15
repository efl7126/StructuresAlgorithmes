# Makefile pour TP1.
# Adaptez ce fichier au besoin (si vous ajouter des fichiers).


# Choisir l'une des deux configurations (-g: Debug | -O2: Release)
OPTIONS = -g -O0 -Wall
#OPTIONS = -O2 -Wall

all : tp1

tp1 : tp1.o pointst.o bixi.o
	g++ ${OPTIONS} -o tp1 tp1.o pointst.o bixi.o
	
tp1.o : tp1.cpp pointst.o bixi.o
	g++ ${OPTIONS} -c -o tp1.o tp1.cpp

pointst.o : pointst.cpp pointst.h tableau.h
	g++ ${OPTIONS} -c -o pointst.o pointst.cpp

bixi.o : bixi.cpp bixi.h pointst.h tableau.h
	g++ ${OPTIONS} -c -o bixi.o bixi.cpp

clean:
	rm -rf tp1 *~ *.o

