#pragma once

#include <stdexcept>
#include <initializer_list>
#include <math.h>
#include <stdio.h>

namespace lin {

    template <int T>
    class Vec;

    template<int T>
    class Mat;

    Mat<4>& translate(Mat<4>&, Vec<3>);
    Mat<4>& scale(Mat<4>&, Vec<3>);
    Mat<4>& rotate(Mat<4>&, Vec<3>);
    Mat<4>& project(Mat<4>&, Vec<4>);


}


// Vector class
template <int T>
class lin::Vec {
public:
    Vec();
    Vec(const Vec<T>&);
    Vec(double*);
    Vec(std::initializer_list<double>);

    Vec<T> cross(Vec<T>);
    double dot(Vec<T>);
    Vec<T> operator*(double);
    Vec<T>& operator=(const Vec<T>&);
    double get(int) const;
    void print() const;

private:
    Vec<T>& swap(const Vec<T>&);

    double* comps_;
};

// Matrix class
template <int T>
class lin::Mat {
public:
    Mat();
    Mat(const Mat&);
    Mat(double);
    Mat(double*);
    Mat(std::initializer_list<double>);

    Vec<T> operator*(Vec<T>);
    Mat<T>& operator=(const Mat<T>&);
    Vec<T> rowVec(int);
    Vec<T> colVec(int);
    double get(int) const;

private:
    Mat<T>& swap(const Mat<T>&);

    double* ents_;
};