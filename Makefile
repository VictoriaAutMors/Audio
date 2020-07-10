all:
	mkdir bin -p
	g++ source/complex.cpp source/fourier.cpp source/complex.hpp -o bin/fourier -Wall -Werror -std=c++11

clean:
	rm /bin/*
	rmdir bin

