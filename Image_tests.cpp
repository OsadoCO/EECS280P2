// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <fstream>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
    Image *img = new Image; // create an Image in dynamic memory
    
    const Pixel red = {255, 0, 0};
    const Pixel green = {0, 255, 0};
    const Pixel blue = {0, 0, 255};
    const Pixel white = {255, 255, 255};
    
    Image_init(img, 2, 2);
    Image_set_pixel(img, 0, 0, red);
    Image_set_pixel(img, 0, 1, green);
    Image_set_pixel(img, 1, 0, blue);
    Image_set_pixel(img, 1, 1, white);
    
    // Capture our output
    ostringstream s;
    Image_print(img, s);
    
    // Correct output
    ostringstream correct;
    correct << "P3\n2 2\n255\n";
    correct << "255 0 0 0 255 0 \n";
    correct << "0 0 255 255 255 255 \n";
    ASSERT_EQUAL(s.str(), correct.str());
    
    delete img; // delete the Image
}

TEST(Image_init) {
    Image *img = new Image; // create an Image in dynamic memory
    Image_init(img, 1, 1);
    ASSERT_EQUAL(Image_height(img), 1);
    ASSERT_EQUAL(Image_width(img), 1);
    delete img;
    
}

TEST(Image_init_2) {
    Image *img = new Image;
    
    string dog = "P3\n5 5\n255\n0 0 0 0 0 0 255 255 250 0 0 0 0 0 0\n";
    dog+= "255 255 250 126 66 0 126 66 0 126 66 0 255 255 250\n";
    dog+= "126 66 0 0 0 0 255 219 183 0 0 0 126 66 0\n";
    dog+= "255 219 183 255 219 183 0 0 0 255 219 183 255 219 183\n";
    dog+= "255 219 183 0 0 0 134 0 0 0 0 0 255 219 183\n";
    std::istringstream ss_input(dog);
    Image_init(img, ss_input);
    ASSERT_EQUAL(Image_height(img), 5);
    ASSERT_EQUAL(Image_width(img), 5);
    const Image *img2 = img;
    Pixel color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    ASSERT_TRUE(Pixel_equal(color, Image_get_pixel(img2, 0, 0)));
    
    color.r = 255;
    color.g = 219;
    color.b = 183;
    ASSERT_TRUE(Pixel_equal(color, Image_get_pixel(img2, Image_height(img2) - 1, Image_width(img2) - 1)));
    delete img;
    //    delete img2;
    //TODO: check values (last, first, a middle)
}

TEST(Image_print) {
    
}

TEST(set_pixel) {
    Image *img = new Image;
    Image_init(img, 4, 3);
    Pixel color;
    color.r = 255;
    color.b = 255;
    color.g = 255;
    Image_fill(img, color);
    const Image *img2 = img;
    ASSERT_TRUE(Pixel_equal(color, Image_get_pixel(img2, 1, 3)));
    color.r = 0;
    color.b = 0;
    color.g = 0;
    Image_set_pixel(img, 0, 0, color);
    ASSERT_TRUE(Pixel_equal(color, Image_get_pixel(img2, 0, 0)));
    color.r = 1;
    color.b = 29;
    color.g = 175;
    Image_set_pixel(img, 1, 3, color);
    ASSERT_TRUE(Pixel_equal(color, Image_get_pixel(img2, 1, 3)));
    color.r = 200;
    color.b = 255;
    color.g = 100;
    Image_set_pixel(img, Image_height(img) - 1, Image_width(img) - 1, color);
    ASSERT_TRUE(Pixel_equal(color, Image_get_pixel(img2, 2, 3)));
}

TEST(Image_fill) {
    Image *img = new Image;
    Image_init(img, 10, 7);
    Pixel color;
    color.r = 56;
    color.b = 26;
    color.g = 25;
    Image_fill(img, color);
    const Image *img2 = img;
    ASSERT_TRUE(Pixel_equal(color, Image_get_pixel(img2, 1, 3)));
    ASSERT_TRUE(Pixel_equal(color, Image_get_pixel(img2, 0, 0)));
    ASSERT_TRUE(Pixel_equal(color, Image_get_pixel(img2, 0, 9)));
    ASSERT_TRUE(Pixel_equal(color, Image_get_pixel(img2, 6, 0)));
    ASSERT_TRUE(Pixel_equal(color, Image_get_pixel(img2, 6, 9)));
    color.r = 57;
    ASSERT_FALSE(Pixel_equal(color, Image_get_pixel(img2, 1, 3)));
    Image_fill(img, color);
    ASSERT_TRUE(Pixel_equal(color, Image_get_pixel(img2, 1, 3)));
}
// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
