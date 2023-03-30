#include "PGMimageProcessor.h"

ORRKAU001::PGMimageProcessor::PGMimageProcessor(std::string filename)
{
    ORRKAU001::PGMimageProcessor::setFileName(filename);
}

ORRKAU001::PGMimageProcessor::PGMimageProcessor()
{

}

ORRKAU001::PGMimageProcessor::~PGMimageProcessor()
{

}

// set the filename private variable ""
void ORRKAU001::PGMimageProcessor::setFileName(std::string f)
{
    ORRKAU001::PGMimageProcessor::filename = f;
}

/*  process the input image to extract all the connected components,
    based on the supplied threshold (0...255) and excluding any components
    of less than the minValidSize. The final number of components that
    you store in your container (after discarding undersized one)
    must be returned.
*/
int ORRKAU001::PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
{
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

    std::streampos size;
    char * memblock;

    char * mem;


    char hash = '#';
    

    //open the image in binary format
    std::ifstream file("chess.pgm", std::ios::in|std::ios::binary);
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

        std::cout << "the entire file content is in memory" << std::endl;


    }
    else {std::cout << "Unable to open file" << std::endl;}

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

    std::queue<std::pair<int, int>> q;

    for (int x = 0; x < height ; x++)
    {
        for (int y = 0; y < width; y++)
        {
            std::pair<int, int> p;
            
            if (values[x][y] > threshold)
            {
                p.first = x;
                p.second = y;
                q.push(p);
                values[x][y] = 0;

                while(!q.empty())
                {
                    std::pair<int, int> first = q.front();
                    q.pop();
                    int a = first.first;
                    int b = first.second;
                    int north = values[a-1][b];
                    int east = values[a][b+1];
                    int west = values[a][b-1];
                    int south = values[a+1][b];

                    if (north> threshold)
                    {
                        p.first = a-1;
                        p.second = b;
                        q.push(p);
                        values[a-1][b] = 0;
                        
                    }
                    if (east > threshold)
                    {
                        p.first = a;
                        p.second = b+1;
                        q.push(p);
                        values[a][b+1] = 0;
                    }
                    if (west > threshold)
                    {
                        p.first = a;
                        p.second = b-1;
                        q.push(p);
                        values[a][b-1] = 0;

                    }
                    if (south > threshold)
                    {
                        p.first = a-1;
                        p.second = b;
                        q.push(p);
                        values[a-1][b] = 0;
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

    std::ofstream File("image.pgm", std::ios::out|std::ios::binary);
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
    else {std::cout << "Unable to open file" << std::endl;}

    delete[] mem;
    delete[] memblock;

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
    return 0;
}

/* print the data for a component to std::cout
see ConnectedComponent class;
print out to std::cout: component ID, number of pixels
*/
void ORRKAU001::PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const
{
    std::cout << "pgm image processor" << std::endl;
}