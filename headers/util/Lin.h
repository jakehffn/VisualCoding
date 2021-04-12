#pragma once

#include <stdexcept>
#include <initializer_list>
#include <math.h>
#include <stdio.h>

namespace lin {

    template <int T>
    class Vec;

    template<int R, int C>
    class Mat;

    Mat<4, 4>& translate(Mat<4, 4>&, Vec<3>);
    Mat<4, 4>& scale(Mat<4, 4>&, Vec<3>);
    Mat<4, 4>& rotate(Mat<4, 4>&, Vec<3>);


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
template <int R, int C>
class lin::Mat {
public:
    Mat();
    Mat(const Mat&);
    Mat(double*);
    Mat(std::initializer_list<double>);

    Vec<R> operator*(Vec<R>);
    Mat<R, C>& operator=(const Mat<R, C>&);
    Vec<C> rowVec(int);
    Vec<R> colVec(int);
    double get(int) const;

private:
    Mat<R, C>& swap(const Mat<R, C>&);

    double* ents_;
};