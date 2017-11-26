# Makefile pour INF3105 / Lab12
#OPTIONS = -Wall           # option standard
#OPTIONS = -g -O0 -Wall    # pour rouler dans gdb
OPTIONS = -O2 -Wall        # pour optimiser
#

lab12 : lab12.cpp carte.h carte.o iocarte.o pointst.h pointst.o
	g++ ${OPTIONS} -o lab12 lab12.cpp pointst.o carte.o iocarte.o

carte.o : carte.cpp carte.h pointst.h
	g++ ${OPTIONS} -c -o carte.o carte.cpp

iocarte.o : iocarte.cpp carte.h
	g++ ${OPTIONS} -c -o iocarte.o iocarte.cpp

pointst.o : pointst.cpp pointst.h
	g++ ${OPTIONS} -c -o pointst.o pointst.cpp

clean:
	rm -rf lab12 *~ *.o

