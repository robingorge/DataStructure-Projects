CXX=clang++
# CXX=g++


default: test


helper.o: helper.cpp
	${CXX} -c helper.cpp

prog3.o: prog3.cpp
	${CXX} -c prog3.cpp

test: helper.o prog3.o
	${CXX} helper.o prog3.o -o prog3

clean:
	/bin/rm -f *.o helper.o prog3.o prog3
