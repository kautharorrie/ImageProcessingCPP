#include "PGMimageProcessor.h"


using namespace std;
int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;

    ORRKAU001::PGMimageProcessor image;
    std::cout << image.extractComponents(200, 1) << std::endl;

    
    

    return 0;
    
   



}