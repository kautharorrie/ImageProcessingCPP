#include "PGMimageProcessor.h"


using namespace std;
int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;

    ORRKAU001::PGMimageProcessor image;
    // std::cout << image.extractComponents(178, 1) << std::endl;
    // std::cout << image.writeComponents("writingTest.pgm") << std::endl;
    // std::cout << "Largest component size: " << image.getLargestSize() << std::endl;
    // std::cout << "Component count: " << image.getComponentCount() << std::endl;
    // std::cout << "Component count after min and max: " << image.filterComponentsBySize(5, 50) << std::endl;
    // std::cout << "Component count: " << image.getComponentCount() << std::endl;
    // std::cout << image.writeComponents("writingTest2.pgm") << std::endl;


    if (argc == 1)
    {
        std::cout << "Error reading command line input for extracted frames." << std::endl;
        return 0; // close the program
    }

    //get the filename 
    std::string filename = argv[argc-1];

    //set the filename in the PGMimage class to use for extraction.
    image.setFileName(filename);

    //use these flags to know if the user put in the following flags
    //will change to true if the user gave the following input
    bool s = false; //set max and min
    bool t = false; //set threshold
    bool p = false; //print out data
    bool w = false; //write out components to a file

    //image.extractComponents(178, 1);
    //image.writeComponents("write.pgm");

    int min = 3; //default minimum
    int max = 0; //width * height

    int threshold = 178;

    std::string outputFile = "";
    ///////////// USER INPUT ////////////////////
    /*
    *
    */
    for (int i = 1; i < argc; i++ )
    {
        std::string g = argv[i]; // save the value of the current user input
        
        // if the tag is -s
        if (g == "-s")
        {
            s = true;
            min = std::stoi(argv[i+1]);
            max = std::stoi(argv[i+2]);
            i+=2;
        }
        // if the tag is -t 
        if (g == "-t")
        {
            t = true;
            threshold = std::stoi(argv[i+1]);
            i+=1;
        }

        // if the tag is -t 
        if (g == "-p")
        {
            p = true;
            //i+=1;
        }

        // if the tag is -t 
        if (g == "-w")
        {
            w = true;
            outputFile = argv[i+1];
            i+=1;
        }
    }
    
    std::cout << s << " max: " << max << " min: " << min << std::endl;
    std::cout << t << std::endl;
    std::cout << p << std::endl;
    std::cout << w << std::endl;
   

    image.extractComponents(threshold, min);
    if(s)
    {
        image.filterComponentsBySize(min, max);
    }
    if (p)
    {
        image.printAllComponentData();
        std::cout << "The total number of components: " << image.getComponentCount() << std::endl;
        std::cout << "Size of largest component: " << image.getLargestSize() << std::endl;
        std::cout << "Size of smallest component: " << image.getSmallestSize() << std::endl;
         
    }
    if(w)
    {
        image.writeComponents(outputFile);
    }
    
    return 0;



}