#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename Object>
class Matrix {
public:
    Matrix(unsigned rows = 1, unsigned cols = 1);
    vector <vector<Object>> xyField;
};


int main() {
//    Matrix m;     // Problem: Matrix ist eine Template-Klasse!
    Matrix<int> m1;
    Matrix<double> m2(12, 3);
    Matrix<string> m3;
}


template<typename Object>
Matrix<Object>::Matrix(unsigned rows, unsigned cols) {
    cout << "rows: " << rows << ", cols: " << cols << endl;
}
