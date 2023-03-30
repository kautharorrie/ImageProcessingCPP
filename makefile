fincomp: driver.o ConnectedComponent.o PGMimageProcessor.o
	g++ driver.o ConnectedComponent.o PGMimageProcessor.o -o findcomp -std=c++20

extractor.o: driver.cpp
	g++ -g -c driver.cpp -o driver.o -std=c++20

ConnectedComponent.o: ConnectedComponent.cpp
	g++ -g -c ConnectedComponent.cpp -o ConnectedComponent.o -std=c++20

PGMimageProcessor.o: PGMimageProcessor.cpp
	g++ -g -c PGMimageProcessor.cpp -o PGMimageProcessor.o -std=c++20

clean: 
	rm *.o findcomp
