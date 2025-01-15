/*
 * Einfache Testfälle für Klassen in C++
 *
 */


class A {
public:     // es reicht, wenn alles public ist (hier nur, damit das Beispiel mit g++ kompiliert)
    int value;
};

class B {
public:     // es reicht, wenn alles public ist (hier nur, damit das Beispiel mit g++ kompiliert)
    B() { value = 0; }
    B(int x) { value = x; }
    B(B& rhs) { value = rhs.value; }
    B& operator=(B& rhs) {  // Zuweisung ist der einzige notwendige Operator
        value = rhs.value;
        return *this;       // "this" und "*this" sollten im Klassenkontext erkannt werden
    }

    int value;
};

class C {
public:     // es reicht, wenn alles public ist (hier nur, damit das Beispiel mit g++ kompiliert)
    C() { value = 0; }
    C(int x) { value = x; }

    int value;
};


int main() {
    {
        // Klasse mit Defaults (C'tor, Zuweisung)
        print_char('A');        // 'A'

        A x;
        x.value = 9;
        print_int(x.value);     // 9

        A y(x);
        print_int(x.value);     // 9
        print_int(y.value);     // 9

        y.value = 7;
        print_int(x.value);     // 9
        print_int(y.value);     // 7

        A z = y;
        print_int(x.value);     // 9
        print_int(y.value);     // 7
        print_int(z.value);     // 7

        A foo;
        foo = z;
        z.value = 99;
        print_int(foo.value);   // 7
        print_int(z.value);     // 99
    }


    {
        // Klasse mit selbst implementierten C'toren und Zuweisung
        print_char('B');        // 'B'

        B x;
        x.value = 9;
        print_int(x.value);     // 9

        B y(x);
        print_int(x.value);     // 9
        print_int(y.value);     // 9

        y.value = 7;
        print_int(x.value);     // 9
        print_int(y.value);     // 7

        B z = y;
        print_int(x.value);     // 9
        print_int(y.value);     // 7
        print_int(z.value);     // 7

        B foo;
        foo = z;
        z.value = 99;
        print_int(foo.value);   // 7
        print_int(z.value);     // 99
    }


    {
        // Klasse mit TEILWEISE selbst implementierten C'toren und Zuweisung, Rest Default vom Compiler
        print_char('C');        // 'C'

        C x;
        x.value = 9;
        print_int(x.value);     // 9

        C y(x);
        print_int(x.value);     // 9
        print_int(y.value);     // 9

        y.value = 7;
        print_int(x.value);     // 9
        print_int(y.value);     // 7

        C z = y;
        print_int(x.value);     // 9
        print_int(y.value);     // 7
        print_int(z.value);     // 7

        C foo;
        foo = z;
        z.value = 99;
        print_int(foo.value);   // 7
        print_int(z.value);     // 99
    }


    return 0;
}
