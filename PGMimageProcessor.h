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
            //std::shared_ptr<ConnectedComponent> component;
            std::string filename;

            // int height;
            // int width;

        public:
            PGMimageProcessor(); 
            PGMimageProcessor(std::string filename);
            ~PGMimageProcessor();
            PGMimageProcessor(const PGMimageProcessor& oldPGM); //copy constructor
            PGMimageProcessor(PGMimageProcessor&& oldPGM); //move constructor
            PGMimageProcessor& operator=(const PGMimageProcessor& oldPGM); //copy assignment
            PGMimageProcessor& operator=(const PGMimageProcessor&& oldPGM); //move assignment

            int height = 0;
            int width = 0;
            std::string wh = ""; 
            //container to store the smart pointers to connected components
            std::vector<std::shared_ptr<ConnectedComponent>> connectedComponentsContainer;

            void setFileName(std::string filename);

            int extractComponents(unsigned char threshold, int minValidSize);
            int filterComponentsBySize(int minSize, int maxSize);
            bool writeComponents(const std::string & outFileName);
            int getComponentCount(void) const;
            int getLargestSize(void) const;
            int getSmallestSize(void) const;
            void printComponentData(const ConnectedComponent & theComponent) const;
            void setHeight(int height);
            void setWidth(int width);
            int getWidth(void) ;
            int getHeight(void) ;
            void printAllComponentData(void);
            
 

    };
}
#endif