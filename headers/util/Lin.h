#pragma once

#include <stdexcept>
#include <initializer_list>
#include <stdio.h>

namespace lin {

    template <int T>
    class vec {
    public:
        vec() : 
            components { new double[T]{} } {} 

        vec(const vec<T>& toCopy) : 
            vec() { 
            
            this->swap(toCopy);
        }

        vec(double* comps) : 
            vec() {
            
            for (int xx = 0; xx < T; xx++) {
                this->components[xx] = comps[xx];
            }
        }

        vec(std::initializer_list<double> comps) : 
            vec() {
            
            int xx{ 0 };
            for (double comp : comps) {
                this->components[xx] = comp;
                xx++;
            }
        }

        vec<T> cross(vec<T> so) {
            return vec<T> {
                this->get(1)*so.get(2) - this->get(2)*so.get(1), 
                this->get(2)*so.get(0) - this->get(0)*so.get(2), 
                this->get(0)*so.get(1) - this->get(1)*so.get(0)
            };
        }

        double dot(vec<T> so) {

            double product = 0;

            for (int xx = 0; xx < T; xx++) {
                product += this->components[xx]*so.get(xx);
            }

            return product;
        }

        vec<T> operator*(double scalar) {

            double* comps = new double[T];
            
            for (int xx = 0; xx < T; xx++) {
                comps[xx] = scalar*this->get(xx);
            }

            return vec<T>{comps};
        }

        vec<T>& operator=(const vec<T>& toCopy) { 
            return this->swap(toCopy);
        }

        double get(int pos) const {

            if (pos >= T) {
                throw std::out_of_range("Accessing index of size T or larger");
            }

            return this->components[pos];
        }

        void print() const {
            
            for (int xx = 0; xx < T; xx++) {
                printf("%i: %f, ", xx, this->get(xx));
            }
            printf("\n");
        }

    private:
        vec<T>& swap(const vec<T>& toCopy) {
            for (int xx = 0; xx < T; xx++) {
                this->components[xx] = toCopy.get(xx);
            }

            return *this;
        }

        double* components;
    };

    template <int R, int C>
    class mat {
    public:
        mat() :
            entries{ new double[R*C]{} } {}

        mat(const mat& toCopy) :
            mat() {

            this->swap(toCopy);
        }

        mat(double* entries) : 
            mat() {
            
            for (int xx = 0; xx < R*C; xx++) {
                this->entries[xx] = entries[xx];
            }
        }

        mat(std::initializer_list<double> entries) : 
            mat() {
            
            int xx{ 0 };
            for (double entry : entries) {
                this->entries[xx] = entry;
                xx++;
            }
        }

        vec<C> operator*(vec<C> vector) {

            double* comps = new double[R];

            for (int xx = 0; xx < C; xx++) {
                comps[xx] = vector.dot(rowVec(xx));
            }

            return vec<C>{comps};
        }

        mat<R, C>& operator=(const mat<R, C>& toCopy) {
            return *this->swap(toCopy);
        }

        vec<C> rowVec(int pos) {

            double* row = new double[C];

            for (int xx = 0; xx < C; xx++) {
                row[xx] = entries[(pos*C) + xx];
            }

            return vec<C>{row};
        }

        vec<R> colVec(int pos) {

            double* col = new double[R];

            for (int xx = 0; xx < R; xx++) {
                col[xx] = this->entries[(xx*R) + pos];
            }

            return vec<R>{col};
        }

        double get(int pos) const {

            if (pos >= R*C) {
                throw std::out_of_range("Accessing index of size R*C or larger");
            }

            return this->entries[pos];
        }

    private:
        mat<R, C>& swap(const mat<R, C>& toCopy) {
            for (int xx = 0; xx < R*C; xx++) {
                this->entries[xx] = toCopy.get(xx);
            }

            return *this;
        }

        double* entries;
    };

}