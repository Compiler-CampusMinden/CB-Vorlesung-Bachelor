#include <iostream>

using namespace std;

template<typename T>
bool kleiner(const T &a, const T &b) {
    cout << "kleiner: allgemeines Template \t\t => ";
    return a < b;
}

/*
template <>
bool kleiner<int>(const int &a, const int &b) {
    cout << "kleiner: spezialisiertes Template \t => ";
    return a < b;
}
*/

/*
bool kleiner(const int &a, const int &b) {
    cout << "kleiner: normale Funktion \t\t => ";
    return a < b;
}
*/

int main() {
    cout << "kleiner(3, 6):           " << kleiner(3, 6) << endl;                // true
    cout << "kleiner(3.1, 3.4):       " << kleiner(3.1, 3.4) << endl << endl;    // true

    cout << "kleiner<int>(3, 6):      " << kleiner<int>(3, 6) << endl;           // true
    cout << "kleiner<double>(3, 3.4): " << kleiner<double>(3, 3.4) << endl;      // true
    cout << "kleiner<int>(3.4, 3):    " << kleiner<int>(3.4, 3) << endl;         // false
    cout << "kleiner<int>(3, 3.4):    " << kleiner<int>(3, 3.4) << endl << endl; // false

    cout << "kleiner(3, 3.4):         " << kleiner(3, 3.4) << endl;              // PROBLEM
    cout << "kleiner(3.4, 3):         " << kleiner(3.4, 3) << endl;              // PROBLEM

    return 0;
}
