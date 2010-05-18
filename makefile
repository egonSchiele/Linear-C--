debug: test.cpp Matrix.cpp MatrixFunctions.cpp
	g++ -g -I/usr/local/boost test.cpp Matrix.cpp MatrixFunctions.cpp -o test	
test: test.cpp Matrix.cpp MatrixFunctions.cpp
	g++ -I/usr/local/boost test.cpp Matrix.cpp MatrixFunctions.cpp -o test	
lib: Matrix.o MatrixFunctions.o
	g++ -I/usr/local/boost -c Matrix.cpp MatrixFunctions.cpp
	ar crv libLinearCpp.a Matrix.o MatrixFunctions.o
clean:
	-rm test *.o libLinearCpp.a
docs:
	-rm -r doc
	doxygen
