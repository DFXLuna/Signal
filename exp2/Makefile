# Makefile
# Date: -1 Dec 1440
# Matt Grant

# old 
#main: main.cpp runPython.h numpyIO.cpp neuralnetwork.h neuron.h connection.h fitness.cpp
#	${CXX} ${CXXFLAGS} ${CXXPFLAGS} main.cpp fitness.cpp -c -o main.o
#	${CXX} -o main main.o ${CXXPLFLAGS}
CXX=g++
CXXFLAGS=-ggdb -std=c++11 -pthread
CXXPFLAGS=-I/usr/include/python3.5m  -Wno-unused-result -Wsign-compare -g -fstack-protector-strong -Wformat -Werror=format-security  -DNDEBUG -g -fwrapv -O3 -Wall
CXXPLFLAGS=-L/usr/lib -lpython3.5m -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions

.PHONY: clean

main: main.cpp fitness.cpp numpyIO.cpp neuralnetwork.h neuron.h connection.h evolve.h CPPN.h CPPNneuron.h
	${CXX} ${CXXFLAGS} main.cpp numpyIO.cpp fitness.cpp CPPN.cpp -o main

clean:
	/bin/rm -f main main.o *.csv
	

