#include <iostream>
#include <fstream>
#include <string>
#include "Image.h"
#include "Matrix.h"
#include "processing.h"
using namespace std;

int main (int argc, char * argv[]) {
    
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
        delete img;
        return -1;
    }
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
         (desiredHeight <= 0 || desiredHeight > Image_height(img)))) {
        //if desired width andheightnotgreater than0ornot<=original dimensions
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        delete img;
        return -1;
    }
    seam_carve(img, desiredWidth, desiredHeight);
    ofstream fout;
    string out_filename = argv[2];
    fout.open(out_filename);
    if (!fout.is_open()) {
        cout << "Error opening file: " << out_filename << endl;
        delete img;
        return -1;
    }
    Image_print(img, fout);
    fin.close();
    fout.close();
    delete img;
    return 0;
}
