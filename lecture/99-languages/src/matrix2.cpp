#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename Object, unsigned rows, unsigned cols>
class Matrix {
public:
    Matrix();
    vector <vector<Object>> xyField;
};


int main() {
    Matrix<int, 1, 1> m1;
    Matrix<double, 12, 3> m2;
    Matrix<string, 1, 1> m3;
}


template<typename Object, unsigned rows, unsigned cols>
Matrix<Object, rows, cols>::Matrix() {
    cout << "rows: " << rows << ", cols: " << cols << endl;
}
