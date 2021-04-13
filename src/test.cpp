#include <iostream>

#include "Lin.h"

int main2() {
    printf("Testing Instantiation\n");
    lin::Vec<3> testVec1{3.0, 5.0, 4.0};
    lin::Vec<3> testVec2{2.0, 1.0, 2.0};

    testVec1.print();
    testVec2.print();

    printf("Testing cross product\n");
    lin::Vec<3> resultant = testVec1.cross(testVec2);

    testVec1.print();

    printf("resultant\n");
    resultant.print();

    printf("Testing dot product\n");
    double result = testVec1.dot(testVec2);

    printf("result: %f\n", result);

    lin::Vec<3> copied(testVec1);
    copied.print();

    printf("Scalar multiplication\n");
    lin::Vec<3> mult = copied*3;
    mult.print();


    double entries[] {
        1.0, 0.0, 0.0, 10.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };

    lin::Mat<4> matrix(2);
    lin::Vec<4> testo{10, 10, 10, 1};
    testo.print();

    printf("Printing matrix\n");
    for (int xx = 0; xx < 4; xx++) {
        matrix.rowVec(xx).print();
    }

    (matrix*testo).print();

    return 0;
}