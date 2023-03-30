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


#include "FrameSequence.h"


using namespace std;
int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;

    //////////////////// file opening and manipulation //////////////
    std::cout << "The file is being read..." << std::endl;
	std::string f;
    std::string filename = "sloan_image.pgm";

    //get file comments
    std::string fileType = "";
    std::string comments = "";
    std::string blank = "";
    std::string widthheight = "";
    int width = 0 ;
    int height = 0; 
    std::string greyscale = "";
    int val = 0;
    int blocksize = 0;

    streampos size;
    char * memblock;

    char * mem;


    char hash = '#';
    
    //stores all extracted image frames
    std::vector<unsigned char **> imageSequence; //stores all extracted image frames


    //open the image in binary format
    ifstream file("sloan_image.pgm", ios::in|ios::binary);
    if (file.is_open())
    {

        getline(file >> std::ws, fileType);
        std::cout << "---------------- type: " << fileType << std::endl;

        getline(file >> std::ws, widthheight);

        // if the file has a comment line, deal with it accordingly
        if (widthheight[0] == hash)
        {
            comments = widthheight;
            std::cout << "---------------- type: " << widthheight << std::endl;
            getline(file >> std::ws, widthheight);
        }
        std::cout << "---------------- type: " << widthheight << std::endl;

        getline(file >> std::ws, greyscale);
        std::cout << "---------------- type: " << greyscale << std::endl;
        
        int g = widthheight.find(" ");
        std::string w = widthheight.substr(0, g);
        std::string h = widthheight.substr(g+1, widthheight.length());

        width = atoi(w.c_str());
        height = atoi(h.c_str());
        
        blocksize = width*height;
        //size = file.tellg();
        memblock = new char [blocksize];
        //file.seekg (0, ios::beg); //get the first position
        file.read (memblock, blocksize);
        file.close();

        cout << "the entire file content is in memory" << std::endl;


    }
    else {cout << "Unable to open file" << std::endl;}

    //create 2D vector to store values from file in [x][y] format
    unsigned char values[height][width]; 

    //create a 2D array for the overall image (the whole image)
    int index = 0;
    for (int a = 0; a < height; a++ )
    {
        for (int b = 0; b <width; b++ )
        {

            values[a][b] = memblock[index];
    
            index++; 
        }
    }

    std::cout << fileType[0] << std::endl;

    std::cout << "--------------------------" << std::endl;
    std::queue<int> q;

    for (int x = 0; x < height ; x++)
    {
       // std::cout << "check: " << x << std::endl;
        for (int y = 0; y < width; y++)
        {
           // std::cout << "y = " << y << std::endl;
            if (values[x][y] > 200)
            {
                values[x][y] = 0;        

                q.push(values[x][y]);
                while(!q.empty())
                {
                    int first = q.front();
                    if (first > 200)
                    {
                        values[x][y] = 0;
                        q.pop();
                    }
                    else 
                    {
                        q.pop();
                    }

                    int north =values[x-1][y];
                    int east = values[x][y+1];
                    int west = values[x][y-1];
                    int south = values[x+1][y];
                    //south
                    if (north > 200)
                    {
                        q.push(north);
                        values[x-1][y] = 0;
                        
                        //push its pixels to the queue
                        int x2 = x - 1;
                        q.push(values[x2-1][y]);
                        q.push(values[x2][y+1]);
                        q.push(values[x2][y-1]);
                        q.push(values[x2+1][y]);
                    }
                    if (east > 200)
                    {
                        q.push(east);
                        values[x][y+1] = 0;

                        //push its pixels to the queue
                        int y2 = y+1;
                        q.push(values[x-1][y2]);
                        q.push(values[x][y2+1]);
                        q.push(values[x][y2-1]);
                        q.push(values[x+1][y2]);
                    }
                    if (west > 200)
                    {
                        q.push(west);
                        values[x+1][y] = 0;

                        int y2 = y-1;
                        q.push(values[x-1][y2]);
                        q.push(values[x][y2+1]);
                        q.push(values[x][y2-1]);
                        q.push(values[x+1][y2]);

                    }
                    if (south > 200)
                    {
                        q.push(south);
                        values[x+1][y] = 0;

                        //push its pixels to the queue
                        int x2 = x + 1;
                        q.push(values[x2-1][y]);
                        q.push(values[x2][y+1]);
                        q.push(values[x2][y-1]);
                        q.push(values[x2+1][y]);
                    }

                }
            }
        }

        //std::cout << std::endl;
    }

    std::cout << "--------------------------" << std::endl;

    mem = new char [width*height];
    int k = 0;
    for (int i = 0; i < height; i++ )
        {
            for (int j = 0; j < width; j++ )
            {
                //mem[k] = values[i][j];
                if (values[i][j] == 0)
                {
                    mem[k] = 255;    
                }
                else
                {
                    mem[k] = 0;
                }
                k++;
            }
    }

    std::cout << "--------------------------" << std::endl;

    ofstream File("image.pgm", ios::out|ios::binary);
    if (File.is_open())
    {
        //file.seekg (0, ios::beg); //get the first position
        File << fileType << std::endl;
        File << "# " << comments << std::endl;
        File << widthheight<< std::endl;;
        File << greyscale << std::endl;;
        File.write(mem, blocksize);
        File.close();

    }
    else {cout << "Unable to open file" << std::endl;}

    delete[] mem;
    delete[] memblock;

    // int screen[][8] ={
    // {1, 1, 1, 1, 1, 1, 1, 1},
    // {1, 1, 1, 1, 1, 1, 0, 0},
    // {1, 0, 0, 1, 1, 0, 1, 1},
    // {1, 2, 2, 2, 2, 0, 1, 0},
    // {1, 1, 1, 2, 2, 0, 1, 0},
    // {1, 1, 1, 2, 2, 2, 2, 0},
    // {1, 1, 1, 1, 1, 2, 1, 1},
    // {1, 1, 1, 1, 1, 2, 2, 1}};

    // for (int x = 0; x < 8 ; x++)
    // {
    //     for (int y = 0; y <8; y++)
    //     {
    //         std::cout << screen[x][y] << ", " ; 
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << "--------------------------" << std::endl;
    // std::queue<int> q;

    // for (int x = 0; x < 8 ; x++)
    // {
    //     for (int y = 0; y <8; y++)
    //     {
    //         if (screen[x][y] == 1)
    //         {
    //             screen[x][y] = 5;        

    //             q.push(screen[x][y]);
    //             while(!q.empty())
    //             {
    //                 int first = q.front();
    //                 if (first == 1)
    //                 {
    //                     screen[x][y] = 5;
    //                     q.pop();
    //                 }
    //                 else 
    //                 {
    //                     q.pop();
    //                 }

    //                 int north = screen[x-1][y];
    //                 int east = screen[x][y+1];
    //                 int west = screen[x][y-1];
    //                 int south = screen[x+1][y];
    //                 //south
    //                 if (north == 1)
    //                 {
    //                     q.push(north);
    //                     screen[x-1][y] = 5;
                        
    //                     //push its pixels to the queue
    //                     int x2 = x - 1;
    //                     q.push(screen[x2-1][y]);
    //                     q.push(screen[x2][y+1]);
    //                     q.push(screen[x2][y-1]);
    //                     q.push(screen[x2+1][y]);
    //                 }
    //                 if (east == 1)
    //                 {
    //                     q.push(east);
    //                     screen[x][y+1] = 5;

    //                     //push its pixels to the queue
    //                     int y2 = y+1;
    //                     q.push(screen[x-1][y2]);
    //                     q.push(screen[x][y2+1]);
    //                     q.push(screen[x][y2-1]);
    //                     q.push(screen[x+1][y2]);
    //                 }
    //                 if (west == 1)
    //                 {
    //                     q.push(west);
    //                     screen[x+1][y] = 5;

    //                     int y2 = y-1;
    //                     q.push(screen[x-1][y2]);
    //                     q.push(screen[x][y2+1]);
    //                     q.push(screen[x][y2-1]);
    //                     q.push(screen[x+1][y2]);

    //                 }
    //                 if (south == 1)
    //                 {
    //                     q.push(south);
    //                     screen[x+1][y] = 5;

    //                     //push its pixels to the queue
    //                     int x2 = x + 1;
    //                     q.push(screen[x2-1][y]);
    //                     q.push(screen[x2][y+1]);
    //                     q.push(screen[x2][y-1]);
    //                     q.push(screen[x2+1][y]);
    //                 }

    //             }
    //         }
    //     }

    //     //std::cout << std::endl;
    // }

    
    // for (int x = 0; x < 8 ; x++)
    // {
    //     for (int y = 0; y <8; y++)
    //     {
    //         std::cout << screen[x][y] << ", " ; 
    //     }
    //     std::cout << std::endl;
    // }


    
    // queue<int> gquiz;
    // gquiz.push(10);
    // gquiz.push(20);
    // gquiz.push(30);

    // // cout << "\ngquiz.size() : " << gquiz.size();
    // // cout << "\ngquiz.front() : " << gquiz.front();
    // // cout << "\ngquiz.back() : " << gquiz.back();
  
    // // cout << "The queue gquiz is : ";
    // // while (!gquiz.empty()) {
    // //     cout << '\t' << gquiz.front();
    // //     gquiz.pop();
    // // }

    return 0;
    
   



}