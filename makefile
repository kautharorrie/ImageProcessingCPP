extractor: driver.o FrameSequence.o
	g++ driver.o FrameSequence.o -o findcomp -std=c++20
extractor.o: driver.cpp
	g++ -g -c driver.cpp -o driver.o -std=c++20
FrameSequence.o: FrameSequence.cpp
	g++ -g -c FrameSequence.cpp -o FrameSequence.o -std=c++20
clean: 
	rm *.o findcomp
