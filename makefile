test: test.cpp Matrix.cpp MatrixFunctions.cpp
	g++ -I/usr/local/boost test.cpp Matrix.cpp MatrixFunctions.cpp -o test	
clean:
	-rm test
docs:
	-rm -r doc
	doxygen