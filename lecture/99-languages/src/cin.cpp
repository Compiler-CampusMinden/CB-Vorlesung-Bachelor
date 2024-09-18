#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main() {
    // liest alle Ziffern bis zum ersten Nicht-Ziffernzeichen
    // (fuehrende Whitespaces werden ignoriert!)
    int zahl;
    cin >> zahl;
    cout << "Gelesener int: '" << zahl << endl;

    // einzelne Zeichen (auch Whitespaces) lesen
    char c; cin.get(c);
    cout << "Gelesener char: '" << c << endl;


    // Eingabe: "100  12.4[Enter]"
    int i; double d; cin >> i >> d;
    cout << "Gelesen: int '" << i << "'; double '" << d << endl;


    // Unterschiedliches Einlesen von Strings
    string myString;

    cin >> myString;            // Eingabe "Hallo Welt" liest nur "Hallo"
    cout << "Gelesen string: '" << myString << endl;

    getline(cin, myString);     // liest komplette Zeile (bis zum Enter)
    cout << "Gelesene Zeile: '" << myString << endl;


    return EXIT_SUCCESS;
}
