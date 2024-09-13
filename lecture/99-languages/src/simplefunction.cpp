#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

/* Vorwaertsdeklaration */
int foo(int x);
// int foo(int x);

/*
double foo(double x) {
    cout << "foo(double), Parameter: " << x << endl;
    return 42.0;
}
*/

int main() {
    int x = foo(-1);
    cout << "Rückgabe: " << x << endl;  // printf("Rückgabe: %d\n", x);

    // foo(0.9);

    return EXIT_SUCCESS;
}

int foo(int x) {
    cout << "foo(int), Parameter: " << x << endl;
    return 42;
}

/*
int foo(int x) {
    cout << "foo(int), Parameter: " << x << endl;
    return 42;
}
*/
