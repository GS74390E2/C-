//
// Created by G.Q on 2019/3/26.
//

#ifndef CLION_CPP_DIAGONALMATRIX_H
#define CLION_CPP_DIAGONALMATRIX_H

#include "../MyException.h"

template<class T>
class diagonalMatrix {
public:
    diagonalMatrix(int theN = 10);

    ~diagonalMatrix() { delete[] this->element; }

    T get(int i, int j) const;

    void set(int i, int j, const T &newValue);

private:
    int n;
    T *element;
};

template<class T>
diagonalMatrix<T>::diagonalMatrix(int theN) {
    if (theN < 1)
        throw illegalParameterValue("Matrix size Must be > 0");
    this->n = theN;
    this->element = new T[n];
}

template <class T>
T diagonalMatrix<T>::get(int i, int j) const {
    if(i < 1 || j < 1 || i > this->n || j > this->n)
        throw matrixIndexOutOfBounds();
    if(i == j)
        return this->element[(i - 1) * this->n + j - 1];
    else
        return 0;
}

template <class T>
void diagonalMatrix<T>::set(int i, int j, const T &newValue) {
    if(i < 1 || j < 1 || i > this->n || j > this->n)
        throw matrixIndexOutOfBounds();

    if(i == j)
        this->element[(i - 1) * this->n + j - 1];
    else{
        if(newValue != 0)
            throw illegalParameterValue("nondiagonal elements must be zero");
    }
}

#endif //CLION_CPP_DIAGONALMATRIX_H
