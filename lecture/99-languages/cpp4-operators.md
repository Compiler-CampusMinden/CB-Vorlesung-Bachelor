---
author: Carsten Gips (HSBI)
title: "C++: Operatoren"
---

::: tldr
In C++ können existierende Operatoren überladen werden, etwa für die Nutzung mit eigenen Klassen. Dabei kann die
Überladung innerhalb einer Klassendefinition passieren (analog zur Implementierung einer Methode) oder außerhalb der
Klasse (analog zur Definition einer überladenen Funktion).

Beim Überladen in einer Klasse hat der Operator nur einen Parameter (beim Aufruf das Objekt auf der rechten Seite) und
man kann auf die Attribute der Klasse direkt zugreifen. Bei der Überladung außerhalb der Klasse hat der Operator zwei
Parameter und darf nicht auf die Attribute der Klasse zugreifen.

Man kann Funktionen, Methoden/Operatoren und Klassen als `friend` einer Klasse deklarieren. Damit bricht man die
Kapselung auf und erlaubt den Freunden den direkten Zugriff auf die internen Attribute einer Klasse.

Um bei der Implementierung von Post- und Präfix-Operatoren die Variante für den Compiler unterscheidbar zu machen, hat
die Signatur der Postfix-Variante einen Dummy-Parameter vom Typ `int`. Dieser wird beim Aufruf aber nicht genutzt.
:::

::: youtube
-   [VL C++: Operatoren](https://youtu.be/lCe0mmO613M)
:::

# Überladen von Operatoren *in* Klassen

\bigskip

``` cpp
MyString a, b("hallo");
a = b;      // ???
```

\pause
\bigskip

``` cpp
a.operator=(b);
```

::: notes
Aufruf `a=b` ist äquivalent zu `a.operator=(b)`

Überladen ähnlich wie bei Methoden:
:::

\pause
\bigskip

``` cpp
class MyString {
    MyString &operator=(const MyString &s) {
        if (this != &s) {
            // mach was :-)
        }
        return *this;
    }
};
```

::: notes
Analog weitere Operatoren, etwa `operator==`, `operator+`, ... überladen
:::

# Überladen von Operatoren *außerhalb* von Klassen

\bigskip

``` cpp
MyString a("hallo");
cout << a << endl;
```

\pause
\bigskip

``` cpp
class MyString {
    ostream &operator<<(ostream &o) { return o << str; }
};
```

::: notes
**So funktioniert das leider nicht!**
:::

\pause
\bigskip

-   Erinnerung: `cout << a` entspricht `cout.operator<<(a)`
    -   Operator kann nicht in `MyString` überladen werden!
    -   Klasse `ostream` müsste erweitert werden `\newline`{=tex} =\> Geht aber nicht, da System-weite Klasse!

\smallskip

=\> Lösung: Operator **außerhalb** der Klasse überladen =\> 2 Parameter

# Überladen von Operatoren *außerhalb* von Klassen (cnt.)

::: notes
Operator außerhalb der Klasse überladen =\> 2 Parameter
:::

``` cpp
ostream &operator<<(ostream &out, const MyString &s) {
    return out << s.str;
}
```

\bigskip

-   Nachteil: Benötigt Zugriff auf Klassen-Interna
    -   entweder umständlich über Getter-Funktionen

    -   oder als `friend` der Klasse `MyString` deklarieren

        [Alternativ Zugriffsmethoden (aka *Getter*) nutzen wie `toString()` ...]{.notes}

\bigskip
\bigskip

**Anmerkung**: Rückgabe der Referenz auf den Stream erlaubt die typische Verkettung: `cout << s1 << s2 << endl;`

# Meine Freunde dürfen in mein Wohnzimmer

``` cpp
void test();

class TestDummy {
    int ganzTolleMethode();
};


class Dummy {
    private:
        int *value;

    friend class TestDummy;
    friend int TestDummy::ganzTolleMethode();
    friend void test();
};
```

# (Fast) alle Operatoren lassen sich überladen

::: notes
-   Alle normalen arithmetischen Operatoren
-   Zuweisung, Vergleich, Ein-/Ausgabe
-   Index-Operator `[]`, Pointer-Dereferenzierung `*` und `->`, sowie `()`, `new` und `delete` (auch in `[]`-Form)
:::

\smallskip

-   **Ausnahmen**:
    1.  **.**
    2.  **::**
    3.  **?:**
    4.  **sizeof**

\bigskip
\bigskip

-   Anmerkungen:
    -   Beim Überladen muss die Arität erhalten bleiben
    -   Nur *existierende* Operatoren lassen sich überladen `\newline`{=tex} =\> Es lassen sich keine neuen Operatoren
        erschaffen

\bigskip

Vgl. Tabelle 9.1 (S. 318) im @Breymann2011

# Implizite Typkonvertierungen bei Aufruf

``` cpp
MyString s;
s != "123";     // ???
"123" != s;     // ???
```

\bigskip

-   Operatoren **in** Klasse überladen: Typ der linken Seite muss **exakt** passen

    ::: notes
    ``` cpp
    class MyString {
    public:
        MyString(const char *s = "");
        bool operator!=(const MyString&);
    };

    MyString s;
    s != "123";    // impliziter Aufruf des Konstruktors, danach MyString::operator!=
    "123" != s;    // KEIN operator!=(char*, MyString&) vorhanden!
    ```

    Das ist letztlich wie bei einem Methodenaufruf: Um die richtige Methode aufzurufen, muss der Typ (die Klasse) des
    Objekts bekannt sein.
    :::

-   Operatoren **außerhalb** überladen: Konvertierung auf *beiden* Seiten möglich

    ::: notes
    ``` cpp
    class MyString {
    public:
        MyString(const char *s = "");
    };
    bool operator!=(const MyString&, const MyString&);
    ```
    :::

::: notes
**NIEMALS** beide Formen gleichzeitig für einen Operator implementieren!
:::

# Anmerkung zu "++" und "-$\,$-" Operatoren: Präfix und Postfix

-   Präfix: `\quad`{=tex}`o1 = ++o2;`
    -   Objekt soll **vor Auswertung** inkrementiert werden
    -   Signatur: `Typ &operator++()`

\bigskip
\smallskip

-   Postfix: `\quad`{=tex}`o1 = o2++;`
    -   Objekt soll erst **nach Auswertung** inkrementiert werden
    -   Signatur: `Typ operator++(int)` [(=\> `int` dient nur zur Unterscheidung der Präfix-Variante, wird **nie**
        benutzt)]{.notes}

# Weitere Anmerkungen

-   Operatoren werden **nicht** vom System zusammengesetzt

    ::: notes
    -   `operator+` und `operator+=` sind zwei verschiedene Operatoren!
    -   Implementierung ist prinzipiell unabhängig! `\newline`{=tex} =\> Erwartung: `operator+=` $\;==\;$ (`operator+`
        $\;+\;$ `operator=`)
    :::

\bigskip

-   Operatoren lassen sich in C++ verketten:

    ``` cpp
    Dummy a(0); Dummy b(1); Dummy c(2);
    a = b = c;  // a.operator=(b.operator=(c));
    ```

\bigskip

-   Übertreiben Sie nicht!

    ``` cpp
    Firma f;
    Person p;
    f += p;  // ??!
    ```

    ::: notes
    Nutzen Sie im Zweifel lieber Methoden mit aussagekräftigen Namen!
    :::

# Wrap-Up

-   Überladen von Operatoren (innerhalb und außerhalb einer Klasse)
    -   Innerhalb: 1 Parameter (Objekt auf der rechten Seite)
    -   Außerhalb: 2 Parameter
-   Zugriff auf Attribute: `friend` einer Klasse
-   Implementierung von Post- und Präfix-Operatoren

::: readings
-   @Breymann2011
-   @cppreference.com
-   @cprogramming.com
:::

::: outcomes
-   k2: Implizite Typkonvertierungen bei Operatoren
-   k3: Überladen von Operatoren (innerhalb bzw. außerhalb einer Klasse)
-   k3: Anwendung der Deklaration als friend
-   k3: Implementierung von Post- und Präfix-Operatoren
:::

::: challenges
**Operator "++"**

Betrachten Sie die folgende Klasse:

``` cpp
class Studi {
public:
    Studi(int credits);
    ~Studi();
private:
    int *credits;
};
```

Implementieren Sie den `operator++` sowohl in der Präfix- als auch in der Postfix-Variante.

<!--
`o1 = o2++;` entspricht `o1 = o2.operator++(int);` und muss

1.  erst eine Kopie von `o2` erzeugen,
2.  dann `o2` inkrementieren, und
3.  die ursprüngliche Kopie von `o2` zurückliefern

\bigskip
=> Rückgabe einer **Kopie** (keine Referenz)!

[Konsole: MyString.cpp (operator++)]{.ex}
-->

**C'toren und Operatoren: Was muss noch *deklariert* werden?**

``` cpp
class Studi {
public:
    Studi(int credits);
private:
    int *credits;
};

int main() {
    Studi a(1), b, *c = new Studi(99);
    b = *c+a+1;
    std::cout << "b: '" << b << "' credits" << std::endl;

    return 0;
}
```

<!--
*   Nur Compilieren:

    ```cpp
    Studi();
    Studi operator+(const Studi&);
    friend ostream &operator<<(ostream&, const Studi&);
    ```

*   Zusätzlich sinnvoll wg. Pointer:

    ```cpp
    Studi(const Studi&);
    Studi &operator=(const Studi&);
    ```
:::
-->

**Schreiben Sie Code, damit folgender Code kompiliert:**

``` cpp
test wuppie;
bool fluppie = wuppie(3);
```
:::
