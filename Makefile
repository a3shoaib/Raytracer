CXX = g++

CXXFLAGS = --std=c++17 -Wall -F /Library/Frameworks
LDFLAGS = -framework SDL2 -F /Library/Frameworks -I /Library/Frameworks/SDL2.framework/Headers

all: main

main: main.o
	$(CXX) main.o -o main $(LDFLAGS)

obj/main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm main.o main
	