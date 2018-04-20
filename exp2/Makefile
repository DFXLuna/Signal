# Makefile
# Date: -1 Dec 1440
# Matt Grant

CXX=g++
CXXFLAGS=-Wall -std=c++11 -pthread -O1
CXXDFLAGS=-Wall -ggdb -std=c++11

.PHONY: clean

main: main.cpp fitness.cpp numpyIO.cpp neuralnetwork.h neuron.h connection.h evolve.h
	${CXX} ${CXXFLAGS} main.cpp numpyIO.cpp fitness.cpp -o main

debug: main.cpp fitness.cpp numpyIO.cpp neuralnetwork.h neuron.h connection.h evolve.h
	${CXX} ${CXXDFLAGS} main.cpp numpyIO.cpp fitness.cpp -o main

clean:
	/bin/rm -f main main.o *.csv
	

