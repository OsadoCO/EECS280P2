// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.

//test initialization at edge cases, test that values are initialized

//test print with many different widths and sizes (just 1 column, just 1 row)

//test width with edge case and non edge case
//test height with edge case and non edge case

//test Matrix_row and column fxns with the edge case and non edge case

//test Matrix_ate getting the border values, test central values


TEST(test_fill_basic) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory
    
    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(mat, 3, 5);
    Matrix_fill(mat, value);
    
    for(int r = 0; r < height; ++r){
        for(int c = 0; c < width; ++c){
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
    }
    delete mat; // delete the Matrix
}

TEST(test_print) {
    //write the test
}

TEST(test_init) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory
    int width = 1;
    int height = 1;
    Matrix_init(mat, width, height);
    ASSERT_EQUAL(Matrix_height(mat), 1);
    ASSERT_EQUAL(Matrix_width(mat), 1);
    delete mat;
    
    Matrix *mat1 = new Matrix; // create a Matrix in dynamic memory
    width = 5;
    height = 22;
    Matrix_init(mat1, width, height);
    ASSERT_EQUAL(Matrix_height(mat1), 22);
    ASSERT_EQUAL(Matrix_width(mat1), 5);
    delete mat1;
    
    Matrix *mat2 = new Matrix; // create a Matrix in dynamic memory
    Matrix_init(mat2, MAX_MATRIX_WIDTH, MAX_MATRIX_HEIGHT);
    ASSERT_EQUAL(Matrix_height(mat2), MAX_MATRIX_HEIGHT);
    ASSERT_EQUAL(Matrix_width(mat2), MAX_MATRIX_WIDTH);
    delete mat2;
}


//Test fill, checking the corners
TEST(test_fill){
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory
    
    int width = 7;
    int height = 4;
    const int value = 76;
    Matrix_init(mat, 7, 4);
    //TODO: add more init tests here
    Matrix_fill(mat, value);
    
    for(int r = 0; r < height; ++r){
        for(int c = 0; c < width; ++c){
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
    }
    delete mat; // delete the Matrix
    
    
}

//Test fill border, check that border is filled and not border parts are not filled
TEST(test_fill_border) {
    
    Matrix *mat = new Matrix;
    int width = 3;
    int height = 4;
    const int value = 5;
    Matrix_init(mat, 3, 4);
    Matrix_fill(mat, value);
    Matrix_fill_border(mat, 2);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1) {
                ASSERT_EQUAL(*Matrix_at(mat, i, j), 2);
            } else if (j == 0 || j == width - 1) {
                ASSERT_EQUAL(*Matrix_at(mat, i, j), 2);
            } else {
                ASSERT_NOT_EQUAL(*Matrix_at(mat, i, j), 2);
            }
        }
    }
    delete mat;
    
    Matrix *mat1 = new Matrix;
    const int value1 = 9;
    Matrix_init(mat1, width, height);
    Matrix_fill(mat1, value1);
    Matrix_fill_border(mat1, 1000);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1) {
                ASSERT_EQUAL(*Matrix_at(mat1, i, j), 1000);
            } else if (j == 0 || j == width - 1) {
                ASSERT_EQUAL(*Matrix_at(mat1, i, j), 1000);
            } else {
                ASSERT_NOT_EQUAL(*Matrix_at(mat1, i, j), 1000);
            }
        }
    }
    delete mat1;

}

//Test max where max is in different spots in data
TEST(test_max){
    Matrix *mat = new Matrix;
    int width = 7;
    int height = 6;
    const int value = 5;
    const int value1 = -5;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);
    ASSERT_EQUAL(Matrix_max(mat), 5);
    Matrix_fill_border(mat, 10);
    ASSERT_EQUAL(Matrix_max(mat), 10);
    *Matrix_at(mat, 5, 4) = 39;
    ASSERT_EQUAL(Matrix_max(mat), 39);
    Matrix_fill(mat, value1);
    ASSERT_EQUAL(Matrix_max(mat), -5);
    *Matrix_at(mat, 3, 5) = -3;
    ASSERT_EQUAL(Matrix_max(mat), -3);
    Matrix_fill_border(mat, -1);
    ASSERT_EQUAL(Matrix_max(mat), -1);
    *Matrix_at(mat, 1, 6) = 0;
    ASSERT_EQUAL(Matrix_max(mat), 0);
    *Matrix_at(mat,0,0) = 9;
    ASSERT_EQUAL(Matrix_max(mat), 9);
    *Matrix_at(mat,(Matrix_height(mat) - 1),(Matrix_width(mat) - 1)) = 100;
    ASSERT_EQUAL(Matrix_max(mat), 100);
    ASSERT_EQUAL(*Matrix_at(mat,(Matrix_height(mat) - 1),(Matrix_width(mat) - 1)),100);
    delete mat;
}

TEST(col_of_min_in_row) {
    Matrix *mat = new Matrix;
    int width = 9;
    int height = 7;
    const int value = 9;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 5, 0, 9), 0);
    *Matrix_at(mat, 5, 4) = 10;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 5, 4, 8), 5);
    *Matrix_at(mat, 5, 6) = 0;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 5, 4, 8), 6);
    *Matrix_at(mat, 4, 7) = -2;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 4, 0, 8), 7);
    *Matrix_at(mat, 6, 2) = 7;
    *Matrix_at(mat, 6, 7) = -10;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 6, 1, 8), 7);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 6, 2, 7), 2);
    delete mat;
}

TEST(min_in_row) {
    Matrix *mat = new Matrix;
    int width = 5;
    int height = 9;
    const int value = 9;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);
    *Matrix_at(mat, 5, 4) = 10;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 5, 0, 4), 9);
    *Matrix_at(mat, 5, 2) = 0;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 5, 0, 3), 0);
    *Matrix_at(mat, 3, 2) = -2;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 3, 1, 4), -2);
    *Matrix_at(mat, 4, 2) = 7;
    *Matrix_at(mat, 4, 0) = -10;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 4, 0, 3), -10);
    *Matrix_at(mat, 4, 2) = -77;
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 4, 0, 2), -10);
    delete mat;
}

TEST(one_row) {
    Matrix *mat = new Matrix;
    int width = 1;
    int height = 1;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, -81);
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 1), 0);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 1), -81);
    *Matrix_at(mat, 0, 0) = -82;
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 1), 0);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 1), -82);
    delete mat;
}

TEST(Matrix_at_tests) {
    Matrix *mat = new Matrix;
    int width = 1;
    int height = 1;
    Matrix_init(mat, width, height);
    int *ptr = Matrix_at(mat, 0, 0);
    ASSERT_EQUAL(ptr, mat->data);
    
    width = 3;
    height = 2;
    Matrix_init(mat, width, height);
    ptr = Matrix_at(mat, 1, 2);
    ASSERT_EQUAL(ptr, mat->data + 5);
    
    width = 4;
    height = 4;
    Matrix_init(mat, width, height);
    ptr = Matrix_at(mat, 2, 1);
    ASSERT_EQUAL(ptr, mat->data + 9);
    delete mat;
}

TEST(Matrix_at_const) {
    
    Matrix *mat = new Matrix;
    int width = 1;
    int height = 1;
    Matrix_init(mat, width, height);
    const Matrix *mat2 = mat;
    const int *ptr = mat2->data;
    ASSERT_EQUAL(Matrix_at(mat2,0,0),ptr);
    ASSERT_EQUAL(*Matrix_at(mat2,0,0),
                 *ptr);
    delete mat;
    
    width = 4;
    height = 3;
    Matrix *mat4 = new Matrix;
    Matrix_init(mat4, width, height);
    const Matrix *mat3 = mat4;
    ptr = mat3->data + 11;
    ASSERT_EQUAL(Matrix_at(mat3, Matrix_height(mat3) - 1,Matrix_width(mat3) - 1),ptr);
    ASSERT_EQUAL(Matrix_at(mat3, Matrix_height(mat3) - 1,Matrix_width(mat3) - 1),ptr);
    delete mat4;
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
