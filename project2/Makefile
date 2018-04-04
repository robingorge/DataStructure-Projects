CXX=clang++
# CXX=g++


default: test


helper.o: helper.cpp
	${CXX} -c helper.cpp

prog2.o: prog2.cpp
	${CXX} -c prog2.cpp

test: helper.o prog2.o
	${CXX} helper.o prog2.o -o prog2

clean:
	/bin/rm -f *.o helper.o prog2.o prog2
