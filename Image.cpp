// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Image.h"
#include <iostream>
#include <string>
using namespace std;

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
    assert(0 < width && width <= MAX_MATRIX_WIDTH);
    assert(0 < height && height <= MAX_MATRIX_HEIGHT);
    
    img->width = width;
    img->height = height;
    //this might not be right
    Matrix_init(&(img->red_channel), width, height);
    Matrix_init(&(img->green_channel), width, height);
    Matrix_init(&(img->blue_channel), width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
    string input;
    is >> input; // reads the P3
    cout << input;
    is >> input; // reads width
    cout << input;
    int width = stoi(input);
    img->width = width;
    is >> input; // reads height
    cout << input;
    int height = stoi(input);
    img->height = height;
    is >> input; //reads 255;
    cout << input;
    
    Matrix_init(&(img->red_channel), width, height);
    Matrix_init(&(img->green_channel), width, height);
    Matrix_init(&(img->blue_channel), width, height);
    int count = 0;
    int row = 0;
    int column = 0;
    while (is >> input) {
        if (row == 5) {
        cout << input;
        }
        else if (count == 0) { //reading in red value
            *Matrix_at(&(img->red_channel), row, column) = stoi(input);
            count++;
        }
        else if (count == 1) {
            *Matrix_at(&(img->green_channel), row, column) = stoi(input);
            count++;
        }
        else {
            *Matrix_at(&(img->blue_channel), row, column) = stoi(input);
            column++;
            if (column == width) {
                column = 0;
                row++;
            }
            count = 0;
        }
    }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
    os << "P3\n";
    os << Image_width(img) << " " << Image_height(img) << "\n";
    os << "255\n";
    for (int row = 0; row < Image_height(img); row++) {
        for (int column = 0; column < Image_width(img); column++) {
            os << Image_get_pixel(img, row, column).r << " ";
            os << Image_get_pixel(img, row, column).g << " ";
            os << Image_get_pixel(img, row, column).b << " ";
        }
        os << "\n";
    }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
    
    return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
    
    return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
    
    assert(0 <= row && row < Image_height(img));
    assert(0 <= column && column < Image_width(img));
    
    Pixel color;
    color.r = *Matrix_at(&(img->red_channel), row, column);
    color.g = *Matrix_at(&(img->green_channel), row, column);
    color.b =*Matrix_at(&(img->blue_channel), row, column);
    return color;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
    assert(0 <= row && row < Image_height(img));
    assert(0 <= column && column < Image_width(img));
    
    int red = color.r;
    int blue = color.b;
    int green = color.g;
    
    *Matrix_at(&(img->red_channel), row, column) = red;
    *Matrix_at(&(img->green_channel), row, column) = green;
    *Matrix_at(&(img->blue_channel), row, column) = blue;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
    
    //may have to use image_set pixel instead
    Matrix_fill(&(img->red_channel), color.r);
    Matrix_fill(&(img->green_channel), color.g);
    Matrix_fill(&(img->blue_channel), color.b);

}
