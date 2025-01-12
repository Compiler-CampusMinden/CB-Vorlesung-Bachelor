/*
 * Einfache Testfälle für Variablen in C++
 *
 */


int main() {
    // Variablen mit Basisdatentypen (ohne Initialisierung)
    bool a;
    int b;
    char c;

    print_bool(a);  // ?? (nicht initialisiert)
    print_int(b);   // ?? (nicht initialisiert)
    print_char(c);  // ?? (nicht initialisiert)


    // Variablen mit Basisdatentypen (mit Initialisierung)
    bool aa = true;
    int bb = 42;
    char cc = 'c';

    print_bool(aa);  // true
    print_int(bb);   // 42
    print_char(cc);  // 'c'


    // Re-Definition darf nicht akzeptiert werden
//    bool aa = false;
//    int bb = 7;
//    char cc = 'x';


    return 0;
}
