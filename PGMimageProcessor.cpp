#include "PGMimageProcessor.h"

ORRKAU001::PGMimageProcessor::PGMimageProcessor(std::string filename)
{
    ORRKAU001::PGMimageProcessor::setFileName(filename);
}

ORRKAU001::PGMimageProcessor::PGMimageProcessor()
{

}

// making use of smart pointers, destructor not necessary
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
    //////////////////// file opening and manipulation //////////////
    std::cout << "The file is being read..." << std::endl;
	std::string f;
    std::string filename = "sloan_image.pgm";

    //get file comments
    std::string fileType = "";
    std::string comments = "";
    std::string blank = "";
    std::string widthheight = "";
    width = 0 ;
    height = 0; 
    std::string greyscale = "";
    int val = 0;
    int blocksize = 0;

    std::streampos size;
    char * memblock;

    char * mem;


    char hash = '#';
    
    
    //open the image in binary format
    std::ifstream file(ORRKAU001::PGMimageProcessor::filename, std::ios::in|std::ios::binary);
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
        
        ORRKAU001::PGMimageProcessor::wh = widthheight;
        int g = widthheight.find(" ");
        std::string w = widthheight.substr(0, g);
        std::string h = widthheight.substr(g+1, widthheight.length());

        width = atoi(w.c_str());
        height = atoi(h.c_str());
        
        ORRKAU001::PGMimageProcessor::setWidth(width);
        ORRKAU001::PGMimageProcessor::setHeight(height);

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
    std::vector<std::vector<std::pair<int, int>>> container;
    int in = 0;
    for (int x = 0; x < height ; x++)
    {
        //std::pair<int, int> p;
//        std::vector<std::pair<int, int>> vec;

       // std::shared_ptr<ConnectedComponent> c = std::make_shared<ConnectedComponent> ();
        for (int y = 0; y < width; y++)
        {
                std::pair<int, int> p;
            std::vector<std::pair<int, int>> vec;

            std::shared_ptr<ConnectedComponent> c = std::make_shared<ConnectedComponent> ();

            if (values[x][y] > threshold)
            {
                p.first = x;
                p.second = y;
                q.push(p); //add to the queue
                c -> addToVector(p); //add the component to the vector
                vec.push_back(p);
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
                        c -> addToVector(p); //add the component to the vector
                        vec.push_back(p);
                        values[a-1][b] = 0;
                        
                    }
                    if (east > threshold)
                    {
                        p.first = a;
                        p.second = b+1;
                        q.push(p);
                        c -> addToVector(p); //add the component to the vector
                        vec.push_back(p);
                        values[a][b+1] = 0;
                    }
                    if (west > threshold)
                    {
                        p.first = a;
                        p.second = b-1;
                        q.push(p);
                        c -> addToVector(p); //add the component to the vector
                        vec.push_back(p);
                        values[a][b-1] = 0;

                    }
                    if (south > threshold)
                    {
                        p.first = a-1;
                        p.second = b;
                        q.push(p);
                        c -> addToVector(p); //add the component to the vector
                        vec.push_back(p);
                        values[a-1][b] = 0;
                    }

                }
                //the queue is done here
                container.push_back(vec);
                //only add the connected component to container of smart pointers if it is more than the minumm size
                if (c -> containerSize() > minValidSize)
                {
                    c -> setID (in); // set the ID of the component ... increment by 1
                    //std::weak_ptr weak = c; //create a weak pointer to avoid cycles in the code
                    ORRKAU001::PGMimageProcessor::connectedComponentsContainer.push_back(c);
                    in++;
                }
                
                
            }
        }
        
            
          
    }

        std::cout << "--------------------------" << std::endl;

    ////////////////////////////////TESTER////////////////////
    unsigned char tester[height][width]; 
    for (int h = 0; h < height; h++)
    {
        for (int l = 0; l < width; l++)
        {
            tester[h][l] = 0;
        }
    }

    for (int i = 0; i < container.size(); i++)
    {
        std::vector<std::pair<int, int>> vec = container[i];
        for (int j = 0; j < vec.size(); j++)
        {
            std::pair<int, int> p = vec[j];
            int x = p.first;
            int y = p.second;
            tester[x][y] = 255;
        }
    }
    char * m;
    m = new char [width*height];
    int n = 0;
    for (int i = 0; i < height; i++ )
        {
            for (int j = 0; j < width; j++ )
            {
                m[n] = tester[i][j];
                n++;
            }
    }

    std::cout << "--------------------------" << std::endl;

    // std::ofstream Files("tester.pgm", std::ios::out|std::ios::binary);
    // if (Files.is_open())
    // {
    //     //file.seekg (0, ios::beg); //get the first position
    //     Files << fileType << std::endl;
    //     Files << "# " << comments << std::endl;
    //     Files << widthheight<< std::endl;;
    //     Files << greyscale << std::endl;;
    //     Files.write(m, blocksize);
    //     Files.close();

    // }
    // else {std::cout << "Unable to open file" << std::endl;}

    delete[] m;

    
    /////////////////////////////////////////////////////////

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

    // std::ofstream File("image.pgm", std::ios::out|std::ios::binary);
    // if (File.is_open())
    // {
    //     //file.seekg (0, ios::beg); //get the first position
    //     File << fileType << std::endl;
    //     File << "# " << comments << std::endl;
    //     File << widthheight<< std::endl;;
    //     File << greyscale << std::endl;;
    //     File.write(mem, blocksize);
    //     File.close();

    // }
    // else {std::cout << "Unable to open file" << std::endl;}

    delete[] mem;
    delete[] memblock;

    return ORRKAU001::PGMimageProcessor::connectedComponentsContainer.size();
}

/* iterate - with an iterator - though your container of connected
components and filter out (remove) all the components which do not
obey the size criteria pass as arguments. The number remaining
after this operation should be returned.
*/
int ORRKAU001::PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize)
{
    //std::vector<std::shared_ptr<ConnectedComponent>> ar = ORRKAU001::PGMimageProcessor::connectedComponentsContainer;
    std::vector<std::shared_ptr<ConnectedComponent>>::iterator ptr;
      
    // Displaying vector elements using begin() and end()
    std::shared_ptr<ConnectedComponent> com = std::make_shared<ConnectedComponent> ();
    for (ptr = ORRKAU001::PGMimageProcessor::connectedComponentsContainer.begin(); ptr < ORRKAU001::PGMimageProcessor::connectedComponentsContainer.end(); ptr++){
        com = *ptr;
        int size = com -> containerSize();
        if (size < minSize || size > maxSize)
        {
            ORRKAU001::PGMimageProcessor::connectedComponentsContainer.erase(ptr); //remove the connected component from the vector
        }
    }

    return ORRKAU001::PGMimageProcessor::connectedComponentsContainer.size();

}

/* create a new PGM file which contains all current components
(255=component pixel, 0 otherwise) and write this to outFileName as a
valid PGM. the return value indicates success of operation
*/
bool ORRKAU001::PGMimageProcessor::writeComponents(const std::string & outFileName)
{
   //get the width and height of the image
    int h = ORRKAU001::PGMimageProcessor::getHeight();
    int w = ORRKAU001::PGMimageProcessor::getWidth();
    
    //create a 2D array to later use to write out the binary values
    unsigned char values[h][w];

    //set all intial values of the array to zero
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            values[i][j] = 0;
        }
    }
    //loop through the container to get each and every component
    for (int k = 0; k < ORRKAU001::PGMimageProcessor::connectedComponentsContainer.size(); k++)
    {
        std::shared_ptr<ConnectedComponent> c = std::make_shared<ConnectedComponent> ();
        std::weak_ptr<ConnectedComponent> com = c;

        c = ORRKAU001::PGMimageProcessor::connectedComponentsContainer[k];
        std::vector<std::pair<int, int>> vec = c -> returnVector();
        //std::vector<std::pair<int, int>> vec = c.returnVector();

        //std::cout << "("<<c -> getID() << ", "<<vec.size() << ") ";
        //std::cout <<vec.size() << " ";
        for (int l = 0; l < vec.size(); l++)
        {
            std::pair <int, int> p;
            p = vec[l];
            int x = p.first;
            int y = p.second;
            //take each component pixel coordinates and update the empty 2D array
            values[x][y] = 255;
        }

       // std::cout << std::endl;

    }
    //std::cout << std::endl;

    char * mem;
    int blocksize = ORRKAU001::PGMimageProcessor::height*ORRKAU001::PGMimageProcessor::width;
    mem = new char [blocksize];
    int k = 0;
    for (int i = 0; i < ORRKAU001::PGMimageProcessor::height; i++ )
        {
            for (int j = 0; j < ORRKAU001::PGMimageProcessor::width; j++ )
            {
                if (values[i][j] == 255 )
                {
                    mem[k] = 255;
                }
                else{
                    mem[k] = 0;
                }
            }
    }

    std::cout << "------------writing--------------" << std::endl;

    std::ofstream File(outFileName, std::ios::out|std::ios::binary);
    if (File.is_open())
    {
        //file.seekg (0, ios::beg); //get the first position
        File << "P5" << std::endl;
        File << "#  " << std::endl;
        File << ORRKAU001::PGMimageProcessor::wh << std::endl;;
        File << "255" << std::endl;;
        File.write(mem, blocksize);
        File.close();

    }
    else 
    {
        std::cout << "Unable to open file" << std::endl;
        return false;
    }

    delete[] mem;
    

    

    //pass the 2D array into a char array (used for the file output)


    return true;
}

// return number of components
int ORRKAU001::PGMimageProcessor::getComponentCount(void) const
{
    return ORRKAU001::PGMimageProcessor::connectedComponentsContainer.size();
}

// return number of pixels in largest component
int ORRKAU001::PGMimageProcessor::getLargestSize(void) const
{
    int largest = 0;
    std::vector<std::shared_ptr<ConnectedComponent>> ar = ORRKAU001::PGMimageProcessor::connectedComponentsContainer;
    std::vector<std::shared_ptr<ConnectedComponent>>::iterator ptr;
      
    // Displaying vector elements using begin() and end()
    std::shared_ptr<ConnectedComponent> com = std::make_shared<ConnectedComponent> ();
    for (ptr = ar.begin(); ptr < ar.end(); ptr++){
        com = *ptr;
        int size = com -> containerSize();

        if (size > largest)
        {
            largest = size;
        }
    }
    return largest;
}

// return number of pixels in smallest component
int ORRKAU001::PGMimageProcessor::getSmallestSize(void) const
{
    int smallest = 0;
    
    std::vector<std::shared_ptr<ConnectedComponent>> ar = ORRKAU001::PGMimageProcessor::connectedComponentsContainer;
    std::vector<std::shared_ptr<ConnectedComponent>>::iterator ptr;
      
    // Displaying vector elements using begin() and end()
    std::shared_ptr<ConnectedComponent> com = std::make_shared<ConnectedComponent> ();
    for (ptr = ar.begin(); ptr < ar.end(); ptr++){

        com = *ptr;
        int vec = com -> containerSize();

        if (smallest == 0)
        {
            smallest = vec;
        }
        else if (vec < smallest)
        {
            smallest = vec;
        }
    }

    return smallest;
    
}

/* print the data for a component to std::cout
see ConnectedComponent class;
print out to std::cout: component ID, number of pixels
*/
void ORRKAU001::PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const

{
    ORRKAU001::ConnectedComponent com = theComponent;
    int id = com.getID();
    int numOfPixels = com.containerSize();
    std::cout << "The ID of component is: " << id << " and the number of pixels are: " << numOfPixels << std::endl;
}


void ORRKAU001::PGMimageProcessor::printAllComponentData()
{
    std::vector<std::shared_ptr<ConnectedComponent>> ar = ORRKAU001::PGMimageProcessor::connectedComponentsContainer;
    std::vector<std::shared_ptr<ConnectedComponent>>::iterator ptr;
      
    // Displaying vector elements using begin() and end()
    std::shared_ptr<ConnectedComponent> com = std::make_shared<ConnectedComponent> ();
    for (ptr = ar.begin(); ptr < ar.end(); ptr++){
        com = *ptr;
        std::cout << "The ID of component is: " << com -> getID() << ". The number of pixels are: " << com -> containerSize() << std::endl;  
    }

}

//set height 
void ORRKAU001::PGMimageProcessor::setHeight(int h)
{
    ORRKAU001::PGMimageProcessor::height = h;
}
//set width

void ORRKAU001::PGMimageProcessor::setWidth(int w)
{
    ORRKAU001::PGMimageProcessor::width = w;
}

//set height 
int ORRKAU001::PGMimageProcessor::getHeight(void)
{
    return ORRKAU001::PGMimageProcessor::height;
}

//set width
int ORRKAU001::PGMimageProcessor::getWidth(void)
{
    return ORRKAU001::PGMimageProcessor::width;
}

// set the filename private variable ""
void ORRKAU001::PGMimageProcessor::setFileName(std::string f)
{
    ORRKAU001::PGMimageProcessor::filename = f;
}
