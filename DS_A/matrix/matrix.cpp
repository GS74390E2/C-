//
// Created by G.Q on 2019/3/22.
//

#include "matrix.h"

void irregular_array() {
    int numberOfRows = 5;
    // 定义不规则数组每一行的长度
    int length[5] = {6, 3, 4, 2, 7};

    int **irregularArray = new int *[numberOfRows];

    for (int i = 0; i < numberOfRows; ++i)
        irregularArray[i] = new int[length[i]];

    irregularArray[2][3] = 5;
    irregularArray[4][6] = irregularArray[2][3] + 2;
    irregularArray[1][1] = 3;

    cout << irregularArray[2][3] << endl;
    cout << irregularArray[4][6] << endl;
    cout << irregularArray[1][1] << endl;
}

void test01() {
    try {
        // matrix<int> matrix1(-1, 1);
        matrix<int> matrix2(3, 4);
        matrix<int> matrix3(3, 4);
        matrix2 = matrix3;
        matrix2(1, 1);
    } catch (illegalParameterValue &e) {
        e.outputMessage();
    } catch (matrixIndexOutOfBounds &e) {
        e.what();
    }
}

void test02() {
    matrix<double> m1(3, 4);
    std::cin >> m1;
    cout << m1 << endl;

    matrix<double> m2(3, 4);
    std::cin >> m2;
    cout << m1 + m2 << endl;

    matrix<double> m3(4, 4);
    std::cin >> m3;
    cout << m3 << endl;

    cout << m1 * m3 << endl;

    cout << "****************************" << endl;
    int num1 = 1, num2 = 0;
    m3 += num1;
    cout << m3;
    cout << "****************************" << endl;
    try{
        m3 /= num2;
    }catch (illegalParameterValue &e){
        e.outputMessage();
    }
}

void test03(){
    matrix<double> m1(3, 4);
    cout << m1 << endl;

    m1 = m1.tranpose();
    cout << m1 << endl;
}

int main() {
    // irregular_array();

    // test01();

    // test02();

    test03();

    return 0;
}
