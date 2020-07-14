all:
	mkdir bin -p
	g++ source/Fourier.cpp -o bin/Furie
	g++ source/vad.cpp -o bin/vad 

clean:
	rm /bin/*
	rmdir bin

