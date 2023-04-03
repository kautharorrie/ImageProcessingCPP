/**
 * .h file 
 * Assignment 3
 * CSC3022F 
 * Author: Kauthar Orrie
 *
 */
 
#ifndef CONNECTEDCOMPONENT_H
#define CONNECTEDCOMPONENT_H


#include <string.h>
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <queue>
#include <iterator>

//declaring my namespace with my student number
namespace ORRKAU001
{
    //create Connected Component class
    class ConnectedComponent
    {
        //private variables + functions
        private: 
            int numberOfPixels; //number of pixels within the component
            int ID; //get the ID of the component

            //a container (vector) to store the components
            std::vector<std::pair<int, int>> components;

        //public variables + functions
        public:
            ConnectedComponent(void); //constructor declaration
            ~ConnectedComponent(); //destructor declaration
            ConnectedComponent(int ID); //parametised constructor declaration
            ConnectedComponent(const ConnectedComponent& oldCom); //copy constructor
            ConnectedComponent(ConnectedComponent&& oldCom); //move constructor
            ConnectedComponent& operator=(const ConnectedComponent& oldCom); //copy assignment
            ConnectedComponent& operator=(const ConnectedComponent&& oldCom); //move assignment

            //method to set the ID of the connected components
            void setID(int i);

            //method to get the current size of the container 
            int containerSize(void);

            //set number of pixels
            void setNumberOfPixels(void); 

            int getID(void);

            //add to vector (container)
            void addToVector(std::pair<int,int> p);

            std::vector<std::pair<int, int>> returnVector (void);

    };
}


#endif