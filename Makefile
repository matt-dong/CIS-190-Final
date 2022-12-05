CXX=g++-10
CXXFLAGS=-std=c++20 -Wall -Werror -g

all : main

main : game.o main.o random.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o : %.cpp %.hpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o main
