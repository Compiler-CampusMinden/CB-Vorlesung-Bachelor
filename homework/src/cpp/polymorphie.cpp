class A {
public:     // es reicht, wenn alles public ist (hier nur, damit das Beispiel mit g++ kompiliert)
    A(int x) { aval = x; }

    void foo() { print_char('A'); print_char('f'); print_int(aval); }

    int aval;
};

class B : public A {
public:     // es reicht, wenn alles public ist (hier nur, damit das Beispiel mit g++ kompiliert)
    // C'tor muss Basisklasse initialisieren
    B(int x) : A(x+3) { bval = x; }

    // überschriebene Methode aus A
    virtual void foo() { print_char('B'); print_char('f'); print_int(aval); print_int(bval); }

    // eigene Methode
    void bar() { print_char('B'); print_char('b'); print_int(aval); print_int(bval); }

    int bval;
};

class C : public B {
public:     // es reicht, wenn alles public ist (hier nur, damit das Beispiel mit g++ kompiliert)
    // C'tor muss Basisklasse initialisieren
    C(int x) : B(x+9) { cval = x; }

    // überschriebene Methode aus B
    void foo() { print_char('C'); print_char('f'); print_int(aval); print_int(bval); print_int(cval); }

    // eigene Methode
    void bar() { print_char('C'); print_char('b'); print_int(aval); print_int(bval); print_int(cval); }

    int cval;
};


int main() {
    {
        // Statische Polymorphie (Normalfall)
        print_char(' '); print_char('A'); print_char(' ');  // 'A'

        B b(9);
        A a = b;

        b.foo();    // B, f, 12, 9
        b.bar();    // B, b, 12, 9

        a.foo();    // A, f, 12         => statische Polymorphie
//        a.bar();    // nicht erlaubt!
    }

    {
        // Statische Polymorphie (trotz Basisklassenreferenz)
        print_char(' '); print_char('B'); print_char(' ');  // 'B'

        B b(9);
        A &a = b;

        b.foo();    // B, f, 12, 9
        b.bar();    // B, b, 12, 9

        a.foo();    // A, f, 12         => statische Polymorphie
    }

    {
        // Dynamische Polymorphie (Basisklassenreferenz und virtuelle Methode)
        print_char(' '); print_char('C'); print_char(' ');  // 'C'

        C c(9);
        B &b = c;

        c.foo();    // C, f, 21, 18, 9
        c.bar();    // C, b, 21, 18, 9

        b.foo();    // C, f, 21, 18, 9      => dynamische Polymorphie
        b.bar();    // B, b, 21, 18         => statische Polymorphie
    }


    return 0;
}
