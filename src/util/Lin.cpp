#include "Lin.h"

// Vector class
template <int T>
lin::Vec<T>::Vec() : 
    comps_ { new double[T]{} } {} 

template <int T>
lin::Vec<T>::Vec(const Vec<T>& toCopy) : 
    Vec() { 
    
    this->swap(toCopy);
}

template <int T>
lin::Vec<T>::Vec(double* comps) : 
    Vec() {
    
    for (int xx = 0; xx < T; xx++) {
        comps_[xx] = comps[xx];
    }
}

template <int T>
lin::Vec<T>::Vec(std::initializer_list<double> comps) : 
    Vec() {
    
    int xx{ 0 };
    for (double comp : comps) {
        comps_[xx] = comp;
        xx++;
    }
}

template <int T>
lin::Vec<T> lin::Vec<T>::cross(Vec<T> so) {
    return Vec<T> {
        this->get(1)*so.get(2) - this->get(2)*so.get(1), 
        this->get(2)*so.get(0) - this->get(0)*so.get(2), 
        this->get(0)*so.get(1) - this->get(1)*so.get(0)
    };
}

template <int T>
double lin::Vec<T>::dot(Vec<T> so) {

    double product = 0;

    for (int xx = 0; xx < T; xx++) {
        product += comps_[xx]*so.get(xx);
    }

    return product;
}

template <int T>
lin::Vec<T>& lin::Vec<T>::operator-(const Vec<T>& so) {

    for (int xx = 0; xx < T; xx++) {
        comps_[xx] -= so.get(xx);
    }

    return *this;
}

template <int T>
lin::Vec<T> lin::Vec<T>::operator*(double scalar) {

    double* comps = new double[T];
    
    for (int xx = 0; xx < T; xx++) {
        comps[xx] = scalar*this->get(xx);
    }

    return Vec<T>{comps};
}

template <int T>
lin::Vec<T>& lin::Vec<T>::operator=(const Vec<T>& toCopy) { 
    return this->swap(toCopy);
}

// Get the component at the pos
template <int T>
double lin::Vec<T>::get(int pos) const {

    if (pos >= T) {
        throw std::out_of_range("Accessing index of size T or larger");
    }

    return comps_[pos];
}

template <int T>
void lin::Vec<T>::print() const {
    
    for (int xx = 0; xx < T; xx++) {
        printf("%i: %f, ", xx, this->get(xx));
    }
    printf("\n");
}

// Helper method for copying
//  Necessary to not repeat code within the copy constructor
//  and the assignment operator. You are unable to use the 
//  assignment operator to initialize this object
template <int T>
lin::Vec<T>& lin::Vec<T>::swap(const Vec<T>& toCopy) {
    for (int xx = 0; xx < T; xx++) {
        comps_[xx] = toCopy.get(xx);
    }

    return *this;
}

// Matrix class
template <int T>
lin::Mat<T>::Mat() :
    ents_{ new double[T*T]{} } {}

template <int T>
lin::Mat<T>::Mat(const Mat& toCopy) :
    Mat() {

    this->swap(toCopy);
}

// Initialize with identity matrix
template <int T>
lin::Mat<T>::Mat(double i) : 
    Mat() {
    
    for (int xx = 0; xx < T*T; xx++) {
    
        if (xx / T == xx % T) {
            ents_[xx] = i;
        } else {
            ents_[xx] = 0;
        }
    }
}

template <int T>
lin::Mat<T>::Mat(double* entries) : 
    Mat() {
    
    for (int xx = 0; xx < T*T; xx++) {
        ents_[xx] = entries[xx];
    }
}

template <int T>
lin::Mat<T>::Mat(std::initializer_list<double> entries) : 
    Mat() {
    
    int xx{ 0 };
    for (double entry : entries) {
        ents_[xx] = entry;
        xx++;
    }
}

template <int T>
lin::Vec<T> lin::Mat<T>::operator*(Vec<T> vector) {

    double* comps = new double[T];

    for (int xx = 0; xx < T; xx++) {
        comps[xx] = vector.dot(rowVec(xx));
    }

    return Vec<T>{comps};
}

template <int T>
lin::Mat<T>& lin::Mat<T>::operator=(const Mat<T>& toCopy) {
    return this->swap(toCopy);
}

// Get a row as a vector of length C
template <int T>
lin::Vec<T> lin::Mat<T>::rowVec(int pos) {

    double* row = new double[T];

    for (int xx = 0; xx < T; xx++) {
        row[xx] = ents_[(pos*T) + xx];
    }

    return Vec<T>{row};
}

// Get a column as a vector of length R
template <int T>
lin::Vec<T>  lin::Mat<T>::colVec(int pos) {

    double* col = new double[T];

    for (int xx = 0; xx < T; xx++) {
        col[xx] = ents_[(xx*T) + pos];
    }

    return Vec<T>{col};
}

// Get the entry at the position
template <int T>
double lin::Mat<T>::get(int pos) const {

    if (pos >= T*T) {
        throw std::out_of_range("Accessing index of size R*C or larger");
    }

    return ents_[pos];
}

// Helper method for copying
template <int T>
lin::Mat<T>& lin::Mat<T>::swap(const Mat<T>& toCopy) {
    for (int xx = 0; xx < T*T; xx++) {
        ents_[xx] = toCopy.get(xx);
    }

    return *this;
}


// Generate translation matrix for translation t
lin::Mat<4>& lin::translate(Mat<4>& m, Vec<3> t) {

    m = Mat<4>{
        1, 0, 0, t.get(0),
        0, 1, 0, t.get(1),
        0, 0, 1, t.get(2),
        0, 0, 0, 1
    };

    return m;
}

// Generate scaling matrix for scaling s
lin::Mat<4>& lin::scale(Mat<4>& m, Vec<3> s) {

    m = Mat<4>{
        s.get(0), 0, 0, 0,
        0, s.get(1), 0, 0,
        0, 0, s.get(2), 0,
        0, 0, 0, 1
    };

    return m;
} 

// Generate rotation matrix for rotation with yaw, pitch, and roll
lin::Mat<4>& lin::rotate(Mat<4>& m, Vec<3> ro) {

    double y = ro.get(0), p = ro.get(1), r = ro.get(2);

    // Using General rotation matrix
    m = Mat<4>{
        cos(y)*cos(p), cos(y)*sin(p)*sin(r)-sin(y)*cos(r), cos(y)*sin(p)*cos(r)+sin(y)*sin(r), 0,
        sin(y)*cos(p), sin(y)*sin(p)*sin(r)+cos(y)*cos(r), sin(y)*sin(p)*cos(r)-cos(y)*sin(r), 0,
        -sin(p), cos(p)*sin(r), cos(p)*cos(r), 0,
        0, 0, 0, 1
    };

    return m;
}

// Generate projection matrix for perspective projection
lin::Mat<4>& lin::project(Mat<4>& m, Vec<4> p) {

    // Field of view
    double fov = p.get(0);
    // Aspect ration
    double ar = p.get(1);
    // Near clipping plane
    double np = p.get(2);
    // Far clipping plane
    double fp = p.get(3);

    double nmf = np - fp;

    // y scaling factor
    double ys = 1 / tan(fov / 2);
    // x scaling factor
    double xs = ys / ar;

    m = Mat<4>{
        xs, 0, 0, 0,
        0, ys, 0, 0,
        0, 0, ((fp + np) / nmf), -1,
        0, 0, ((2*fp*np) / nmf), 0
    };

    return m;
}

// Explicit instantiation of specific template use cases;
//  Otherwise undefined reference thrown
template class lin::Vec<2>;
template class lin::Vec<3>;
template class lin::Vec<4>;

template class lin::Mat<3>;
template class lin::Mat<4>;