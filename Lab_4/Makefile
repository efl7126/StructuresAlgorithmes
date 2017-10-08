# Makefile pour le lab4

#Option -g pour avoir les infos de débogage
OPTIONS = -g -O0 -Wall

#Option -O3 pour le code optimisé
#OPTIONS = -O3 -Wall

all : test_pile test_file lab4 verif_memoire integration_tableau


# Syntaxe : cible : dépendance1 dépendance2 ...
# Ensuite, la ou les ligne(s) débutant par une tabulation (\t) donne les commandes pour construire une cible.

integration_tableau: integration_tableau.cpp pile.h
	g++ $(OPTIONS) -o integration_tableau integration_tableau.cpp

verif_memoire: verif_memoire.cpp lab4.cpp pile.h file.h
	g++ $(OPTIONS) -o verif_memoire verif_memoire.cpp

lab4: lab4.cpp pile.h file.h
	g++ $(OPTIONS) -o lab4 lab4.cpp

test_pile: test_pile.cpp pile.h
	g++ $(OPTIONS) -o test_pile test_pile.cpp

test_file: test_file.cpp file.h
	g++ $(OPTIONS) -o test_file test_file.cpp


clean :
	rm -rf test_pile test_file
	rm -f lab4

