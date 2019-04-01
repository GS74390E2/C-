//
// Created by G.Q on 2019/3/22.
//

#ifndef CLION_CPP_MATRIX_H
#define CLION_CPP_MATRIX_H

#include "../MyException.h"

template<class T>
class matrix {
    template<class Tx>
    friend std::ostream &operator<<(std::ostream &out, const matrix<Tx> &m);

    template<class Ty>
    friend std::istream &operator>>(std::istream &in, matrix<Ty> &m);

public:
    matrix(int theRows = 0, int theColumns = 0);

    matrix(const matrix<T> &m);

    ~matrix() { delete[] this->element; }

    int getRows() const { return this->rows; }

    int getColumns() const { return this->columns; }

    T &operator()(int i, int j) const;

    matrix<T> &operator=(const matrix<T> &m);

    // 矩阵计算

    matrix<T> operator+(const matrix<T> &m) const;

    matrix<T> operator-(const matrix<T> &m) const;

    matrix<T> operator*(const matrix<T> &m) const;

    void operator+=(const T &num);

    void operator-=(const T &num);

    void operator*=(const T &num);

    void operator/=(const T &num);

    matrix<T> &tranpose();

private:
    int rows, columns;
    T *element;     // 矩阵使用行主次序映射到一维数组
};

template<class T>
matrix<T>::matrix(int theRows, int theColumns) {
    // 检查行列数的合法性
    if (theRows < 0 || theColumns < 0)
        throw illegalParameterValue("Rows and columns Must Be >= 0");
    if ((theRows == 0 || theColumns == 0) && (theRows != 0 || theColumns != 0))
        throw illegalParameterValue("Either both or neither rows and columns should be zero");

    // 创建矩阵
    this->rows = theRows;
    this->columns = theColumns;
    this->element = new T[this->rows * this->columns];

    // tmp func
    for(int i = 0; i != this->rows * this->columns; ++i)
        this->element[i] = i;
}

template<class T>
matrix<T>::matrix(const matrix<T> &m) {
    this->rows = m.rows;
    this->columns = m.columns;
    this->element = new T[this->rows * this->columns];

    for (int i = 0; i != m.rows * m.columns; ++i)
        this->element[i] = m.element[i];
}

template<class T>
matrix<T> &matrix<T>::operator=(const matrix<T> &m) {
    if (this != &m) {
        delete[] this->element;
        this->rows = m.rows;
        this->columns = m.columns;
        this->element = new T[this->rows * this->columns];
        for (int i = 0; i != m.rows * m.columns; ++i)
            this->element[i] = m.element[i];
    }
    return *this;
}

template<class T>
T &matrix<T>::operator()(int i, int j) const {
    // 矩阵行列都从1开始计数
    if (i < 1 || i > this->rows || j < 1 || j > this->columns)
        throw matrixIndexOutOfBounds();
    return this->element[(i - 1) * this->columns + j - 1];
}

template<class T>
std::ostream &operator<<(std::ostream &out, const matrix<T> &m) {
    for (int i = 0; i != m.rows * m.columns; ++i)
        out << m.element[i] << " ";
    out << endl;
    return out;
}

template<class T>
std::istream &operator>>(std::istream &in, matrix<T> &m) {
    T num;
    in >> num;
    for (int i = 0; i != m.rows * m.columns; ++i)
        m.element[i] = num;
    return in;
}

// 矩阵运算
template<class T>
matrix<T> matrix<T>::operator+(const matrix<T> &m) const {
    // 检查矩阵是否合法
    if (this->rows != m.rows || this->columns != m.columns)
        throw matrixSizeMismatch();

    matrix<T> ret(this->rows, this->columns);
    for (int i = 0; i != this->rows * this->columns; ++i)
        ret.element[i] = this->element[i] + m.element[i];

    return ret;
}

template<class T>
matrix<T> matrix<T>::operator-(const matrix<T> &m) const {
    // 检查矩阵是否合法
    if (this->rows != m.rows || this->columns != m.columns)
        throw matrixSizeMismatch();

    matrix<T> ret(this->rows, this->columns);
    for (int i = 0; i != this->rows * this->columns; ++i)
        ret.element[i] = this->element[i] - m.element[i];

    return ret;
}

template<class T>
matrix<T> matrix<T>::operator*(const matrix<T> &m) const {
    // 检查矩阵是否合法
    if (this->columns != m.rows)
        throw matrixSizeMismatch();

    matrix<T> ret(this->rows, m.columns);
    int ct = 0, cm = 0, cw = 0;

    for (int i = 1; i <= this->rows; ++i) {
        for (int j = 1; j <= m.columns; ++j) {
            T sum = this->element[ct] * m.element[cm];
            for (int k = 2; k <= this->columns; ++k) {
                ++ct;
                cm += m.columns;
                sum += this->element[ct] * m.element[cm];
            }
            ret.element[cw++] = sum;
            ct -= this->columns - 1;
            cm = j;
        }
        ct += this->columns;
        cm = 0;
    }
    return ret;
}

template<class T>
void matrix<T>::operator+=(const T &num) {
    for (int i = 0; i != this->rows * this->columns; ++i)
        this->element[i] += num;
}

template<class T>
void matrix<T>::operator-=(const T &num) {
    for (int i = 0; i != this->rows * this->columns; ++i)
        this->element[i] -= num;
}

template<class T>
void matrix<T>::operator*=(const T &num) {
    for (int i = 0; i != this->rows * this->columns; ++i)
        this->element[i] *= num;
}

template<class T>
void matrix<T>::operator/=(const T &num) {
    if (num == 0)
        throw illegalParameterValue("/ num Must be != 0");
    for (int i = 0; i != this->rows * this->columns; ++i)
        this->element[i] /= num;
}

template<class T>
matrix<T> &matrix<T>::tranpose() {
    for (int i = 1; i <= this->rows; ++i) {
        for (int j = 1; j <= this->columns; ++j) {
            if (i == j)continue;
            T tmp = this->element[(i - 1) * this->columns + j - 1];
            this->element[(i - 1) * this->columns + j - 1] = this->element[(j - 1) * this->columns + i - 1];
            this->element[(j - 1) * this->columns + i - 1] = tmp;
        }
    }
    int tmp = this->rows;
    this->rows = this->columns;
    this->columns = tmp;
    return *this;
}

#endif //CLION_CPP_MATRIX_H
