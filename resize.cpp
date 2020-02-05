#include <iostream>
#include <fstream>
#include <string>
#include "Image.h"
#include "Matrix.h"
#include "processing.h"
using namespace std;

int main (int argc, char * argv[]) {
    
//    The program is invoked with three or four arguments. If no height argument is supplied, the original height is kept (i.e. only the width is resized). If your program takes about 30 seconds for large images, that’s ok. There’s a lot of computation involved.
//
//    The program checks that the command line arguments obey the following rules:
//
//    There are 4 or 5 arguments, including the executable name itself (i.e. argv[0]).
//    The desired width is greater than 0 and less than or equal to the original width of the input image.
//    The desired height is greater than 0 and less than or equal to the original height of the input image.
//    If any of these are violated, use the following lines of code (literally) to print an error message.
    
    //TODO: check the proper order for the error messages
    
    if (!(argc == 4 || argc == 5)) { //if not 4 or 5 args
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return -1;
    }
    Image *img = new Image;
    string in_filename = argv[1]; //gets the name for the input ppm file
    ifstream fin;
    fin.open(in_filename);
    if (!fin.is_open()) {
        cout << "Error opening file: " << in_filename << endl;
        return -1;
    }
    fin.close();
    
    Image_init(img, fin);
    int desiredWidth = atoi(argv[3]);
    bool hasHeight = false;
    int desiredHeight = 0;
    if (argc > 4) { //ensures not indexing out of bounds
        desiredHeight = atoi(argv[4]);
        hasHeight = true;
    }
    if ((desiredWidth <= 0 || desiredWidth > Image_width(img)) ||
        (!hasHeight ||
         desiredHeight <= 0 || desiredHeight > Image_height(img))) {
    //if desired width and height notgreater than 0 or not<=original dimensions
         cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return -1;
    }
    seam_carve(img, desiredWidth, desiredHeight);
    ofstream fout;
    string out_filename = argv[2];
    fout.open(out_filename);
    if (!fout.is_open()) {
           cout << "Error opening file: " << out_filename << endl;
           return -1;
       }
    Image_print(img, fout);
    fin.close();
    
    return 0;
}
