<<<<<<< HEAD
CXX=g++-10
=======
CXX=g++
>>>>>>> 0076cec5568db16e9f0c5c8ebd94d7913372586e
CXXFLAGS=-std=c++20 -Wall -Werror -g

all : main

<<<<<<< HEAD
main : game.o main.o random.o
=======
main : main.o
>>>>>>> 0076cec5568db16e9f0c5c8ebd94d7913372586e
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o : %.cpp %.hpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

<<<<<<< HEAD
.PHONY: clean

clean:
	rm -f *.o main
=======

.PHONY: clean

clean:
	rm -f *.o main
>>>>>>> 0076cec5568db16e9f0c5c8ebd94d7913372586e
