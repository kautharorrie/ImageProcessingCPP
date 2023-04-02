#include "ConnectedComponent.h"

//default constructor
ORRKAU001::ConnectedComponent::ConnectedComponent()
{
    ORRKAU001::ConnectedComponent::setID(0);
}


//parametised constructor
ORRKAU001::ConnectedComponent::ConnectedComponent(int i)
{
    ORRKAU001::ConnectedComponent::setID(i);
}

//destructor
ORRKAU001::ConnectedComponent::~ConnectedComponent()
{

}

/**
 * set the ID of the connected components 
 * take in the ID and set the private variable ID 
 */
void ORRKAU001::ConnectedComponent::setID(int id)
{
    ORRKAU001::ConnectedComponent::ID = id;
}

/**
 * set the number of pixels
 * the number of pixels is equal to the size of the vector
 */
void ORRKAU001::ConnectedComponent::setNumberOfPixels(void)
{
    //number of pixels is equal to the container size
    ORRKAU001::ConnectedComponent::numberOfPixels = ORRKAU001::ConnectedComponent::components.size();
}

/**
 * return the number of pixels inside the connected component
 */
int ORRKAU001::ConnectedComponent::containerSize(void)
{
    ORRKAU001::ConnectedComponent::setNumberOfPixels();
    return ORRKAU001::ConnectedComponent::numberOfPixels;
}

/*
 * Add a pixel to the vector to hold the connected components
*/
void ORRKAU001::ConnectedComponent::addToVector(std::pair<int, int> p)
{
    ORRKAU001::ConnectedComponent::components.push_back(p);
}

std::vector<std::pair<int, int>> ORRKAU001::ConnectedComponent::returnVector(void)
{
    return ORRKAU001::ConnectedComponent::components;
}

int ORRKAU001::ConnectedComponent::getID(void)
{
    return ORRKAU001::ConnectedComponent::ID;
}




