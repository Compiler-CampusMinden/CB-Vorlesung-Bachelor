#include <iostream>
#include <cstdlib>

using namespace std;

class Dummy {
public:
    Dummy() {
        cout << "\tparameterloser Konstruktor" << endl;
    }

    Dummy(int a) {
        cout << "\tKonstruktor mit Parameter: " << a << endl;
    }

    Dummy(const Dummy &a) {
        cout << "\tCopy-Konstruktor" << endl;
        value = a.value;
    }

    Dummy &operator=(const Dummy &d) {
        cout << "\tZuweisungsoperator " << endl;
    }

private:
    int value;
};


Dummy f(Dummy d) {
    return d;
}


int main() {
    cout << endl << "Deklaration mit Initialisierung (Wert): Dummy a(3);" << endl;
    Dummy a(3);

    cout << endl << "Deklaration mit Initialisierung (Wert): Dummy b = 42;" << endl;
    Dummy b = 42;

    cout << endl << "Deklaration mit Initialisierung (Objekt): Dummy c = a;" << endl;
    Dummy c = a;

    cout << endl << "Deklaration mit Initialisierung (Objekt): Dummy d(a);" << endl;
    Dummy d(a);

    cout << endl << endl << "Call-by-Value: Dummy erg = f(a);" << endl;
    Dummy erg = f(a);

    return EXIT_SUCCESS;
}
