CXX=clang++
# CXX=g++


default: test


helper.o: helper.cpp
	${CXX} -c helper.cpp

prog4.o: prog4.cpp
	${CXX} -c prog4.cpp

test: helper.o prog4.o
	${CXX} helper.o prog4.o -o prog4

clean:
	/bin/rm -f *.o helper.o prog4.o prog4
