#include "ConnectedComponent.h"

//default constructor
ORRKAU001::ConnectedComponent::ConnectedComponent()
{
    ORRKAU001::ConnectedComponent::setID(0);
    ORRKAU001::ConnectedComponent::numberOfPixels = 0;
}


//parametised constructor
ORRKAU001::ConnectedComponent::ConnectedComponent(int i)
{
    ORRKAU001::ConnectedComponent::setID(i);
    ORRKAU001::ConnectedComponent::numberOfPixels = 0;
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
//copy constructor
ORRKAU001::ConnectedComponent::ConnectedComponent(const ConnectedComponent& oldCom) : numberOfPixels(oldCom.numberOfPixels), ID(oldCom.ID)
{
    for (int i = 0; i < ORRKAU001::ConnectedComponent::containerSize(); i++)
    {
        ORRKAU001::ConnectedComponent::components[i] = oldCom.components[i];
    }
}

//move constructor
ORRKAU001::ConnectedComponent::ConnectedComponent(ConnectedComponent&& oldCom) : numberOfPixels(oldCom.numberOfPixels), ID(oldCom.ID)
{
    //move data into current class
    ORRKAU001::ConnectedComponent::components =std::move(oldCom.components);
    
    //set all old PGM class variables to null; 
    oldCom.numberOfPixels = 0;
    oldCom.ID = 0;
    
    //delete old 
    for (int i = 0; i < oldCom.components.size(); i++)
    {
        oldCom.components[i].first = 0;
        oldCom.components[i].second = 0;
    }
   

}

//copy assigment implementation
ORRKAU001::ConnectedComponent& ORRKAU001::ConnectedComponent::operator=(const ORRKAU001::ConnectedComponent& oldCom)
{
    //ensure that the old class is not equal to the new 
    if (this == &oldCom) {return *this;}

    //copy all old class variables to new class
    ID = oldCom.ID;
    numberOfPixels = oldCom.numberOfPixels;
    for (int i = 0; i < ORRKAU001::ConnectedComponent::components.size(); i++)
    {
        ORRKAU001::ConnectedComponent::components[i] = oldCom.components[i];
    }
    return *this;
} 

//move assignment implementation
ORRKAU001::ConnectedComponent& ORRKAU001::ConnectedComponent::operator=(const ConnectedComponent&& oldCom)
{
    //move the vector into the new class vector
    ORRKAU001::ConnectedComponent::components = std::move(oldCom.components);
    ID = oldCom.ID;
    numberOfPixels = oldCom.numberOfPixels;

    //set all old PGM class variables to null; 
    oldCom.ID == 0;
    oldCom.numberOfPixels == 0;
    //delete old 
   
    //delete old 
    for (int i = 0; i < oldCom.components.size(); i++)
    {
        oldCom.components[i].first == 0;
        oldCom.components[i].second == 0;
    }

    //return this class
    return *this;
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
    return ORRKAU001::ConnectedComponent::components.size();
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




