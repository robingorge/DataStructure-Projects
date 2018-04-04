CXX=clang++
# CXX=g++


default: test


helper.o: helper.cpp
	${CXX} -c helper.cpp

prog1.o: prog1.cpp
	${CXX} -c prog1.cpp

test: helper.o prog1.o
	${CXX} helper.o prog1.o -o prog1

clean:
	/bin/rm -f *.o helper.o prog1.o prog1
