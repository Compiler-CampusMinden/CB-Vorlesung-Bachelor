/*
 * Einfache Testfälle für Ausdrücke und Zuweisungen in C++
 *
 */


int main() {
    // Einfache Ausdrücke
    print_int(1);           // 1
    print_int(1+2);         // 3
    print_int(1-2);         // -1
    print_int(3+4*2);       // 11
    print_int(4*2+3);       // 11
    print_int(3+4*2/4);     // 5


    // Variablen
    int x = 7;
    int y = 42;

    print_int(x);       // 7
    print_int(y);       // 42
    print_int(x+y);     // 49


    // Zuweisungen
    y = x;
    x = 9;
    print_int(x);   // 9
    print_int(y);   // 7


    // nicht erlaubte Zuweisungen
//    9 = x;


    return 0;
}
