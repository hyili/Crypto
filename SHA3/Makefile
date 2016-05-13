CXX = g++
CXXFLAGS = -O3 -std=c++14

all: Main.o Sponge.o InternalFun.o
	${CXX} $^ ${CXXFLAGS} -o SHA3

%.o: %.cpp
	${CXX} $< ${CXXFLAGS} -c 

clean:
	rm -rf SHA3 *.o	