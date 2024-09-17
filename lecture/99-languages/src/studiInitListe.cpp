#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Date {
public:
    Date() {
        cout << "\tKlasse Date, parameterloser Konstruktor" << endl;
    }

    Date(string d) {
        cout << "\tKlasse Date, Konstruktor mit Parameter" << endl;
    }

    Date(const Date &d) {
        cout << "\tKlasse Date, Copy-Konstruktor" << endl;
    }

    Date &operator=(const Date &d) {
        cout << "\tKlasse Date, Zuweisungsoperator" << endl;
        return *this;
    }

};

class Student {
public:
    Student(const string &n, const Date &d, double c) : credits(c), name(n), birthday(d) {
    }

//private:
    string name;
    Date birthday;
    double credits = 0.9;   // geht seit C++11
};

int main() {
    Date d("01.01.1980");

    cout << endl << "Anlegen eines Studenten" << endl;
    Student a("Heiner", d, 9);
    cout << "Heiners Credits: " << a.credits << endl;

    return EXIT_SUCCESS;
}
