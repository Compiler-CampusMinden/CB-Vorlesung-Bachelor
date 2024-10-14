#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename Object = int, unsigned rows = 1, unsigned cols = 1>
class Matrix {
public:
    Matrix();
    vector <vector<Object>> xyField;
};


int main() {
    Matrix<> m1;
    Matrix<double, 12, 3> m2;
    Matrix<string> m3;
}


template<typename Object, unsigned rows, unsigned cols>
Matrix<Object, rows, cols>::Matrix() {
    cout << "rows: " << rows << ", cols: " << cols << endl;
}
