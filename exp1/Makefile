# Makefile
# Date: -1 Dec 1440
# Matt Grant
CXX=g++
CXXFLAGS=-ggdb -std=c++11
CXXPFLAGS=-I/usr/include/python3.5m  -Wno-unused-result -Wsign-compare -g -fstack-protector-strong -Wformat -Werror=format-security  -DNDEBUG -g -fwrapv -O3 -Wall
CXXPLFLAGS=-L/usr/lib -lpython3.5m -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions

.PHONY: clean

main: main.cpp runPython.h numpyIO.h neuralnetwork.h neuron.h connection.h
	${CXX} ${CXXFLAGS} ${CXXPFLAGS} main.cpp -c -o main.o
	${CXX} -o main main.o ${CXXPLFLAGS}

noPython: main.cpp numpyIO.h neuralnetwork.h neuron.h connection.h
	${CXX} ${CXXFLAGS} main.cpp -o main

clean:
	/bin/rm -f main main.o
	

