all: MatrixTests.cpp MatrixFunctionsTests.cpp
	g++ -I/usr/local/boost MatrixTests.cpp ../Matrix.cpp ../MatrixFunctions.cpp -o MatrixTests -lUnitTest++
	g++ -I/usr/local/boost MatrixFunctionsTests.cpp ../Matrix.cpp ../MatrixFunctions.cpp -o MatrixFunctionsTests -lUnitTest++

functions: MatrixFunctionsTests.cpp
	g++ -I/usr/local/boost MatrixFunctionsTests.cpp ../Matrix.cpp ../MatrixFunctions.cpp -o MatrixFunctionsTests -lUnitTest++
	
clean:
	-rm MatrixTests MatrixFunctionsTests