/*
 * Created by G.Q on 2019/3/12.
 * 异常类
 */

#ifndef CLION_CPP_MYEXCEPTION_H
#define CLION_CPP_MYEXCEPTION_H

#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

class illegalParameterValue {
public:
    illegalParameterValue() : message("Illegal parameter value") {}

    illegalParameterValue(string theMessage) : message(theMessage) {}

    void outputMessage() {
        cout << message << endl;
    }
private:
    string message;
};

class matrixIndexOutOfBounds{
public:
    matrixIndexOutOfBounds():message("matrix i or j is out of range"){}
    void what(){
        cout << message << endl;
    }
private:
    string message;
};

class matrixSizeMismatch{
public:
    matrixSizeMismatch():message("matrix A and matrix B are not same size"){}
    void what(){
        cout << message << endl;
    }
private:
    string message;
};

class stackEmpty{
public:
    stackEmpty():message("stack is empty"){}
    void what(){
        cout << message << endl;
    }
private:
    string message;
};

#endif //CLION_CPP_MYEXCEPTION_H
