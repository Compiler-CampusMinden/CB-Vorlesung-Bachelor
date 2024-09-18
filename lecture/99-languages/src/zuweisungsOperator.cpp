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
    }

    Dummy &operator=(const Dummy &d) {
        cout << "\tZuweisungsoperator " << endl;

        // wird nur aufgerufen, wenn rechts und links
        // bereits initialisierte Objekte vorhanden sind!
        if (this != &d) {  // Standard Alias-Test (vermeide a=a)
            value = d.value;
        }
        return *this;  // erlaubt a=b=c
    }

private:
    int value;
};


int main() {
    cout << endl << "Deklaration mit Initialisierung (Wert): Dummy a = 2;" << endl;
    Dummy a = 2;

    cout << endl << "Deklaration mit anschliessender Zuweisung: Dummy b; b = a;" << endl;
    Dummy b;
    b = a;

    cout << endl << endl << "Raetsel?!: Dummy c; c = 2;" << endl;
    Dummy c;
    c = 2;


    return EXIT_SUCCESS;
}
