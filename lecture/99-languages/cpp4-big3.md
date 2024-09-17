---
archetype: lecture-cg
title: "C++: Big3 und Operatoren"
author: "Carsten Gips (HSBI)"
readings:
  - key: "Breymann2011"
  - key: "cppreference.com"
  - key: "cprogramming.com"
tldr: |
    Für C++-Klassen kann  man Destruktoren, Copy-Konstruktoren und Zuweisungsoperatoren definieren.
    Wenn man keine eigenen definiert, erzeugt C++ Default-Varianten. Diese bereiten u.U. Probleme,
    wenn man Pointertypen für die Attribute verwendet: Dann werden u.U. nur flache Kopien erzeugt
    bzw. es wird u.U. der Platz auf dem Heap nicht freigegeben.

    Der Default-Destruktor ruft die Destruktoren der Objekt-Attribute auf. Der Copy-Konstruktor wird
    aufgerufen, wenn die linke Seite (einer scheinbaren "Zuweisung") ein unfertiges Objekt ist (noch
    zu bauen) und die rechte Seite ein fertiges Objekt ist. Der Zuweisungs-Operator wird dagegen
    aufgerufen, wenn auf beiden Seiten ein fertiges Objekt vorliegt.

    Innerhalb einer Klasse kann man über den **Pointer `this`** auf das eigene Objekt zugreifen
    (analog zu `self` in Python oder `this` in Java).

    Bei statischen Methoden und Attributen wird die Deklaration als `static` **nicht** in der
    Implementierung wiederholt! Statische Attribute müssen außerhalb der Klassendefinition einmal
    initialisiert werden!

    Methoden können als "konstant" ausgezeichnet werden (`const` rechts von der Parameterliste). Das
    `const` gehört zur Signatur der Methode! Konstante Methoden dürfen auf konstanten Objekten/Referenzen
    aufgerufen werden.
outcomes:
    - k2: "Problematik mit Defaultkonstruktoren/-operatoren (Pointer)"
    - k2: "Problematik konstanter Funktionen, wann werden diese aufgerufen"
    - k3: "'Big Three': Destruktor, Copy-Konstruktor, Zuweisungsoperator"
youtube:
  - link: "TODO"
    name: "VL C++: Big3 und Operatoren"
challenges: |
    **Konstruktor, Copy-Konstruktor, Zuweisungsoperator?**

    *   Erklären Sie die folgenden Anweisungen, worin liegt der Unterschied?

        ```cpp
        Dummy a;
        Dummy b = 3;
        Dummy c(4);
        ```

    *   Erklären Sie die folgenden Anweisungen:

        ```cpp
        Dummy a;
        Dummy b = 3;
        Dummy c(4);
        Dummy d = b;
        Dummy e(b);
        Dummy f;
        f = b;
        ```

    **Destruktor**

    *   Erklären Sie die Wirkungsweise eines Destruktors.
    *   Wann wird ein Destruktor aufgerufen?
    *   Warum ist `delete this` keine gute Idee (nicht nur im Destruktor)?!
    *   Was sollten Sie im Destruktor aufräumen, was nicht?

    **Die "Großen Drei"**

    1.  Beschreiben Sie den Unterschied der folgenden beiden Codeblöcke (`A` sei
        eine beliebige Klasse):

        ```cpp
        A a, b = a;
        ```

        ```cpp
        A a, b; b = a;
        ```

    2.  Erläutern Sie an einem **Beispiel** die Regel der "Big Three":

        > Ist ein Copy-Konstruktor, ein Destruktor oder ein eigener
        > Zuweisungsoperator notwendig, muss man in der Regel die jeweils anderen
        > beiden ebenfalls bereit stellen.

    3.  Beim Zuweisungsoperator werden Selbstzuweisungen, d.h. ein Objekt soll an
        sich selbst zugewiesen werden, üblicherweise durch eine entsprechende
        Prüfung vermieden.

        Begründen Sie diese Praxis, indem Sie ein **Beispiel konstruieren**, bei
        dem es zu Datenverlust kommt, wenn die Selbstzuweisung nicht unterbunden
        wird.

        ::: showme
        Wenn vor der Wertzuweisung der alte Inhalt freigegeben werden muss, führt
        Selbstzuweisung zum Fehler.

        Können Sie ein konkretes Beispiel angeben?
        :::

    **Quiz: Was passiert bei den folgenden Aufrufen?**

    ```cpp
    class Foo {
    public:
        const Foo &bar(const vector<Foo> &a) { return a[0]; }
    };

    int main() {
        Foo f;  vector<Foo> a = {"hello", "world", ":)"};

        Foo s1 = f.bar(a);
        const Foo &s2 = f.bar(a);
        Foo &s3 = f.bar(a);
        Foo s4;
        s4 = f.bar(a);

        return EXIT_SUCCESS;
    }
    ```

    <!--
    ```
    Foo s1 = f.bar(a);
    // legal: s1 wird neu erzeugt mit einem anderen Foo
    // -> Copy-Konstruktor wird fuer s1 aufgerufen

    const Foo &s2 = f.bar(a);
    // perfekt: s2 ist *kein* neues Foo,
    // sondern eine Referenz auf das erste Array-Element
    // -> keiner der *toren wird aufgerufen

    Foo &s3 = f.bar(a);
    // kompiliert nicht: Verletzung der const-heit für Parameter

    Foo s4; s4 = f.bar(a);
    // fast wie das Beispiel mit s1:
    // -> zuerst wird der Defaultkonstruktor fuer s4 aufgerufen
    // -> und dann der Zuweisungsoperator (links und rechts Foo's)
    ```

    [Beispiel: bigthree.cpp]{.bsp}
    -->
---


::: notes
## Big Three

-   Neben eigentlichen Konstruktor existieren in C++ weitere wichtige Konstruktoren:
    die sogenannten ["Big Three"]{.alert}:
    -   Destruktor: Gegenstück zum Konstruktor
    -   Copy-Konstruktor
    -   Zuweisungsoperator (`operator=`)
:::

## Big Three: Destruktor

-   Syntax: `Dummy::~Dummy();` \newline
    (Konstruktor mit vorgesetzter Tilde)

\bigskip

-   Wird aufgerufen:
    -   wenn ein Objekt seinen Scope verlässt, oder
    -   wenn explizit `delete` [für einen Pointer auf ein Objekt (auf dem Heap!)]{.notes} aufgerufen wird

-   Default-Destruktor ruft Destruktoren der Objekt-Attribute auf

[Konsole: destruktor.cpp]{.bsp}

## delete this?

::: notes
Erinnerung:

-   `this` ist ein Pointer auf das eigene Objekt
-   `delete` darf nur für Pointer auf Objekte, die mit `new` angelegt wurden,
    aufgerufen werden => Freigabe von Objekten auf dem Heap!
-   `delete` ruft den Destruktor eines Objekts auf ...

\bigskip

Frage: Ist das folgende Konstrukt sinnvoll? Ist es überhaupt erlaubt? Was
passiert dabei?
:::

```cpp
class Foo {
public:
    ~Foo() {
        delete this;
    }
};
```

::: notes
Analyse:

-   `delete` ruft den Destruktor des verwiesenen Objekts auf. Da `this` ein
    Pointer auf das eigene Objekt ist, ruft `delete this;` den eigenen
    Destruktor auf, der dann wiederum `delete this;` aufruft und so weiter.
    => Endlosschleife!

-   Außerdem wissen wir im Destruktor bzw. im Objekt gar nicht, ob das Objekt
    wirklich mit `new` auf dem Heap angelegt wurde! D.h. wenn wir nicht in
    die Endlosschleife eintreten würden, würde das Programm abstürzen.

\bigskip

Der Destruktor wird aufgerufen, wenn ein Objekt zerstört wird, d.h. wenn ein
Objekt seine Lebensdauer beendet (Verlassen des Scopes, in dem das Objekt
definiert wurde) bzw. wenn explizit ein `delete` auf das Objekt aufgerufen
wird (d.h. `delete` auf einen Pointer auf das Objekt, wobei dieses mit `new`
angelegt wurde).

Im Destruktor sollten **durch das Objekt verwaltete Resourcen freigegeben**
werden, d.h. sämtliche im Objekt mit `new` oder `malloc` allozierten Resourcen
auf dem Heap müssen freigegeben werden. Außerdem sollten ggf. offene Verbindungen
(offene Dateien, Datenbankverbindungen, Kommunikation, ...) geschlossen werden,
wenn sie durch das Objekt geöffnet wurden bzw. in der Verantwortung des Objekts
stehen. Einfache Datentypen oder Objekte, die nicht per Referenz oder Pointer
im Objekt verwaltet werden, werden automatisch freigegeben (denken Sie an das
Speichermodell - diese Daten "stehen" direkt im Speicherbereich des Objekts).

Der Speicherbereich für das Objekt selbst wird nach Beendigung des Destruktors
automatisch freigegeben (auf dem Stack wegen des Verlassen des Scopes (=>
automatische Variable), auf dem Heap durch das vorherige Aufrufen von `delete`
auf den Pointer auf das Objekt im Heap), d.h. Sie brauchen im Destruktor **kein**
`delete` auf "sich selbst" (das ist wie oben demonstriert sogar schädlich)!
:::

[Konsole: foo.cpp]{.bsp}

## Big Three: Copy-Konstruktor

-   Syntax: `Dummy::Dummy(const Dummy &);`

\bigskip

-   Wird aufgerufen bei:
    -   Deklaration mit Initialisierung mit Objekt
    -   Objektübergabe und -rückgabe mit Call-by-Value
    -   [Nicht bei Zuweisung]{.alert}

-   Default-Copy-Konstruktor kopiert einfach elementweise \newline
    => bei Pointern also nur **flache Kopie**

::: notes
"**Merkregel**": Linke Seite unfertiges Objekt (noch zu bauen), rechte Seite
fertiges Objekt.
:::

[Konsole: copyKonstruktor.cpp]{.bsp}

## Big Three: Zuweisungsoperator

-   Syntax: `Dummy &Dummy::operator=(const Dummy &)`

\bigskip

-   Wird aufgerufen:
    -   bei Zuweisung bereits initialisierter Objekte

-   Default-Zuweisungsoperator kopiert einfach elementweise \newline
    => bei Pointern also nur **flache Kopie**

::: notes
"**Merkregel**": Linke Seite fertiges Objekt, rechte Seite fertiges Objekt.
:::

[Konsole: zuweisungsOperator.cpp]{.bsp}

::: notes
## Big Three: Defaults

Kein eigener Konstruktor (Copy-Konstruktor, Destruktor, Zuweisungsoperator)
definiert? => Default-Konstruktor (-Copy-Konstruktor, -Destruktor,
-Zuweisungsoperator) vom Compiler generiert!

-   Defaults passen normalerweise, wenn die Data-Member
    -   `int`, `double`, `vector<int>`, `string`, `vector<string>` o.ä. sind

\smallskip

-   Problematisch, wenn Pointer dabei sind:
    -   Flache Kopien
    -   Speicherplatz auf Heap nicht freigegeben
:::

::::::::: notes
### Big Three: Vorsicht Defaults

:::::: columns
::: {.column width="50%"}

```cpp
class Dummy {
public:
    Dummy(int initValue = 0) {
        value = new int(initValue);
    }

    int getValue() {
        return *value;
    }
    void setValue(int a) {
        *value = a;
    }
private:
    int *value;
};

void main() {
    Dummy a(2);
    Dummy b = a;
    Dummy c;

    c=b;
    a.setValue(4);
}
```

:::
::: {.column width="50%"}

![](images/bigthreeDefaults.png)

:::
::::::
:::::::::

::: notes
## Hinweis Abarbeitungsreihenfolge

```cpp
Dummy a(0); Dummy b(1); Dummy c(2); Dummy d(3);
a = b = c = d; // entspricht: a.operator=(b.operator=(c.operator=(d)));
```
:::

## C++11: default und delete

```cpp
class Dummy {
public:
    Dummy() = default;
    Dummy(int a) { value = a; }
    Dummy(const Dummy &a) = delete;

private:
    int value;
    Dummy &operator=(const Dummy &d);
};
```

::: notes
-   C++ erzeugt etliche triviale Methoden/Operatoren, sofern man diese nicht
    selbst definiert:
    -   Methoden:
        -   Standardkonstruktor
        -   Copy-Konstruktor
        -   Zuweisungsoperator
        -   Destruktor
    -   Operatoren:
        -   Operator `new`
        -   Operator `delete`
        -   Adresse von
        -   Indirektion
        -   Elementzugriff
        -   Elementindirektion
-   Vor C++11: Default-Methode/-Operator verbieten: Sichtbarkeit auf `private`
    setzen (Definition nicht nötig)
-   Ab C++11: Schlüsselwort `delete`: Entfernt Default-Methode/-Operator
-   C++11: Default-Methode/-Operator zusätzlich zu selbst implementierten:
    Schlüsselwort `default`
:::

[[Beispiel: defaultKonstruktor.cpp]{.bsp}]{.notes}

<!-- XXX
Beispiel 7.12 aus Grimm "C++11 für Programmierer", O'Reilly Verlag:

```cpp
class MyData{
public:
    explicit MyData(const MyData&);             // 3
    MyData& operator= (MyData&);                // 5
    virtual ~MyData() throw();                  // 2, 4
private:
    MyData();                                    // 1
};

MyData::MyData() = default;                    // 1
MyData::~MyData() throw() = default;           // 2, 4
MyData::MyData(const MyData&) = default;       // 3
MyData& MyData::operator=(MyData&) = default;  // 5
```

> Der Default-Konstruktor (1) ist privat, der Destruktor ist virtuell (2), und
> er besitzt eine Ausnahmespezifikation (4), der Copy-Konstruktor ist explizit
> (3), und zuletzt nimmt der Zuweisungsoperator (5) sein Argument nicht const an.
-->

## Statische Methoden und Attribute

```cpp
class Studi {
    static int getCount();
    static int count;
};
```

\bigskip

```cpp
int Studi::count = 0;

int Studi::getCount() {
    return Studi::count;
}
```

::: notes
-   Deklaration als `static` **nicht** in Implementierung wiederholen
-   Statische Attribute: Initialisierung außerhalb der Klasse!
:::

[Konsole: Studi.cpp (static)]{.bsp}

## Konstante Methoden und Kontexte

```cpp
class Studi {
    int getCredits() const;
    int getCredits();
};
```

\bigskip

```cpp
int Studi::getCredits() const {
    return credits;
}

int Studi::getCredits() {
    return credits;
}
```

::: notes
-   `const` gehört zur Signatur der Methode!
-   Konstante Methoden dürfen auf konstanten Objekten/Referenzen aufgerufen werden
:::

[Konsole: Studi.cpp (const)]{.bsp}

::: notes
```cpp
const foo wuppie(foo&, foo&);
```

-   `const`: Rückgabewert darf nicht als L-Wert benutzt werden: \newline
    `wuppie(a,b) = c;` ist verboten

\bigskip

=> Verweis auf [Move-Semantik](../move-semantics/move1.md) (L-Werte, R-Werte, ...)
:::

## Wrap-Up

-   Klassen: Destruktoren, Copy-Konstruktor, Zuweisungsoperator
-   Vorsicht mit Default-\*struktoren/-operatoren
-   Statische Methoden und Attribute:
    -   Deklaration als `static` **nicht** in Implementierung wiederholen
    -   Statische Attribute: Initialisierung außerhalb der Klasse!
-   Konstante Methoden und Kontexte
    -   `const` gehört zur Signatur der Methode!
    -   Konstante Methoden dürfen auf konstanten Objekten/Referenzen aufgerufen werden







<!-- DO NOT REMOVE - THIS IS A LAST SLIDE TO INDICATE THE LICENSE AND POSSIBLE EXCEPTIONS (IMAGES, ...). -->
::: slides
## LICENSE
![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)

Unless otherwise noted, this work is licensed under CC BY-SA 4.0.
:::
