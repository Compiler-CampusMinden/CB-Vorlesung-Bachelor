/*
 * g++ -Wall -std=c++14 Studi.cpp
 */

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


class Studi {
public:
    Studi(const string &n, int c);

    int getCredits() const;
    int getCredits();

    static int getCount();

private:
    string name;
    int credits = 1;   // geht seit C++11

    static int count;
};


int Studi::count = 0;  // statische Attribute MUESSEN ausserhalb der Klasse initialisiert werden

int Studi::getCount() {
    return Studi::count;
}

Studi::Studi(const string &n, int c) {
    name = n;
    credits = c;
    count += 1;
}

int Studi::getCredits() const {
    cout << "\tStudi::getCredits() const" << endl;
    return credits;
}

int Studi::getCredits() {
    cout << "\tStudi::getCredits()" << endl;
    return credits;
}


void f(Studi &s) {
    cout << "Aufruf von f(Studi &s)" << endl;
    s.getCredits();
}

void fc(const Studi &s) {
    cout << "Aufruf von f(constStudi &s)" << endl;
    s.getCredits();
}


int main() {
    cout << "Anzahl der bekannten Studis: " << Studi::getCount() << endl << endl;

    Studi a("Heiner", 9);
    cout << "Heiners Credits: " << a.getCredits() << endl;
    cout << "Anzahl der bekannten Studis: " << Studi::getCount() << endl << endl;

    f(a);
    fc(a);

    return EXIT_SUCCESS;
}
