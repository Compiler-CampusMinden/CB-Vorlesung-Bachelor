#include <iostream>
#include <cstdlib>

using namespace std;

class Wuppie {
public:
    Wuppie(int initValue = 0) : value(initValue) {
    }

    ~Wuppie() {
        cout << "Wuppie: AUTSCH!" << endl;
    }

private:
    int value;
};


class Fluppie {
private:
    Wuppie w;
};


int main() {
    {
        cout << "im Scope" << endl;
        Wuppie a;
        cout << "vor Verlassen des Scopes" << endl;
    }
    cout << "nach Scope" << endl << endl;

    Wuppie *a = new Wuppie;
    delete a;

    cout << endl << "jetzt ein Fluppie" << endl;
    {
        cout << "im Scope" << endl;
        Fluppie a;
        cout << "vor Verlassen des Scopes" << endl;
    }
    cout << "nach Scope" << endl << endl;


    return EXIT_SUCCESS;
}
