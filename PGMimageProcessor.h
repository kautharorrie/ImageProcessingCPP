/**
 * .h file 
 * Assignment 3
 * CSC3022F 
 * Author: Kauthar Orrie
 *
 */
 
#ifndef PGMIMAGEPROCESSOR_H
#define PGMIMAGEPROCESSOR_H

#include "ConnectedComponent.h"

//declaring my namespace with my student number
namespace ORRKAU001
{
    //create Connected Component class
    class PGMimageProcessor
    {
        private:
            std::shared_ptr<ConnectedComponent> component;
            std::string filename;

            //container to store the smart pointers to connected components
            std::vector<std::weak_ptr<ConnectedComponent>> connectedComponentsContainer;
        public:
            PGMimageProcessor(); 
            PGMimageProcessor(std::string filename);
            ~PGMimageProcessor();

            void setFileName(std::string filename);

            int extractComponents(unsigned char threshold, int minValidSize);
            int filterComponentsBySize(int minSize, int maxSize);
            bool writeComponents(const std::string & outFileName);
            int getComponentCount(void) const;
            int getLargestSize(void) const;
            int getSmallestSize(void) const;
            void printComponentData(const ConnectedComponent & theComponent) const;
            
 

    };
}
#endif