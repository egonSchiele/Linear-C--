lib: Matrix.o MatrixFunctions.o
	g++ -I/usr/local/boost -c Matrix.cpp MatrixFunctions.cpp
	ar crv libLinearCpp.a Matrix.o MatrixFunctions.o
test: test.cpp Matrix.cpp MatrixFunctions.cpp
	g++ -I/usr/local/boost test.cpp libLinearCpp.a -o test	
clean:
	-rm test *.o
docs:
	-rm -r doc
	doxygen
