Assignment 3 
Name: Kauthar Orrie 
Student No.: ORRKAU001
Date: 03/04/2023

Notes for the tutor marking:
    -i've included the following images in my submission that used to test my program: 
        : chess.pgm
        : maize.pgm
        : shapes.pgm
         - all these images take a threshold of > 178 
         - so should you choose to test this, you can use the threshold 178

How to run the program: 
- type 'make' in the terminal to compile the files and create binary files
- run program with using "./findcomp" to run the program
    NOTE:
        - to successfully run the program make sure you add the "-t", "-s", "-p" and "-w" flag, if the flags aren't specified the program will 
        print out some error messages 
        - format of input: 
                -> "./findcomp -t <threshold> -s <min> <max> -p -w <output file name> [inputfilename]"

Files included in submission:
- ConnectedComponent.cpp (source file)
	- includes the methods needed for the program
	- implements the methods used in the PGMimageProcessor.cpp file 

- ConnectedComponent.h (header file)
	- declares my namespace with my student number ORRKAU001
	- declares all the required methods which is defined within ConnectedComponent.cpp (source file)
	- declares all the '#include' files
    - declares the ConnectedComponent class which includes the constructor, destructor, public methods and variables

- PGMimageProcessor.cpp (source file)
	- includes the methods needed for the program
	- implements the methods used in the driver.cpp file 

- PGMimageProcessor.h (header file)
	- declares my namespace with my student number ORRKAU001
	- declares all the required methods which is defined within driver.cpp (source file)
	- declares all the '#include' files
    - declares the ConnectedComponent class which includes the constructor, destructor, public methods and variables

- driver.cpp (driver file)
	- the main includes the command loop to handle the user input and output
	- includes and implements methods from the source file PGMimageProcessor.cpp

- driver_tester.cpp
    - implements the unit tests for the PGMimageProcessor methods 

- makefile 
	- compiles the program

	