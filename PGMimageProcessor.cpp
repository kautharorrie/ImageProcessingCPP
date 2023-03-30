#include "PGMimageProcessor.h"

ORRKAU001::PGMimageProcessor::PGMimageProcessor()
{

}

ORRKAU001::PGMimageProcessor::~PGMimageProcessor()
{

}

/*  process the input image to extract all the connected components,
    based on the supplied threshold (0...255) and excluding any components
    of less than the minValidSize. The final number of components that
    you store in your container (after discarding undersized one)
    must be returned.
*/
int ORRKAU001::PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
{
    return 0;
}

/* iterate - with an iterator - though your container of connected
components and filter out (remove) all the components which do not
obey the size criteria pass as arguments. The number remaining
after this operation should be returned.
*/
int ORRKAU001::PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize)
{
    return 0;
}

/* create a new PGM file which contains all current components
(255=component pixel, 0 otherwise) and write this to outFileName as a
valid PGM. the return value indicates success of operation
*/
bool writeComponents(const std::string & outFileName)
{
    return true;
}

// return number of components
int ORRKAU001::PGMimageProcessor::getComponentCount(void) const
{
    return 0;
}

// return number of pixels in largest component
int ORRKAU001::PGMimageProcessor::getLargestSize(void) const
{
    return 0;
}

// return number of pixels in smallest component
int ORRKAU001::PGMimageProcessor::getSmallestSize(void) const
{

}

/* print the data for a component to std::cout
see ConnectedComponent class;
print out to std::cout: component ID, number of pixels
*/
void ORRKAU001::PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const
{

}