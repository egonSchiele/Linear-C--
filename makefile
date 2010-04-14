test: test.cpp Matrix.cpp
	g++ -I/usr/local/boost test.cpp Matrix.cpp -o test	
clean:
	-rm test
