CXX=g++
CXXFLAGS=-O2 -pedantic -Wall -Wextra -ansi -std=c++17

all: fotofile

fotofile:  fotofile.cpp
	$(CXX) $(CXXFLAGS) -o fotofile fotofile.cpp

clean:
	rm -f *.o fotofile 
