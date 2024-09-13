---
archetype: lecture-cg
title: "C++: Funktionen"
author: "Carsten Gips (HSBI)"
readings:
  - key: "Breymann2011"
tldr: |
    In C++ gibt es Funktionen (analog zu Methoden in Java), diese existieren unabhängig von Klassen.

    Wenn eine Funktion aufgerufen wird, muss dem Compiler die Signatur zur Prüfung bekannt sein. Das
    bedeutet, dass die Funktion entweder zuvor komplett definiert werden muss oder zumindest zuvor
    deklariert werden muss (die Definition kann auch später in der Datei kommen oder in einer anderen
    Datei). Das Vorab-Deklarieren einer Funktion nennt man auch "Funktionsprototypen".

    Eine Deklaration darf (so lange sie konsistent ist) mehrfach vorkommen, eine Definition immer nur
    exakt einmal. Dabei werden alle Code-Teile, die zu einem Programm zusammencompiliert werden,
    gemeinsam betrachtet. => Das ist auch als **One-Definition-Rule** bekannt.

    In C++ gilt beim Funktionsaufruf immer zunächst immer die Parameterübergabe per **call-by-value**
    (dito bei der Rückgabe von Werten). Wenn Referenzen oder Pointer eingesetzt werden, wird dagegen
    auch ein _call-by-reference_ möglich. (Dazu später mehr.)

    Unterscheidung in globale, lokale und lokale statische Variablen mit unterschiedlicher Lebensdauer und
    unterschiedlicher Initialisierung durch den Compiler.
outcomes:
    - k2: "Unterschied zwischen Deklaration und Definition, One Definition Rule"
    - k2: "Problematik bei der Deklaration parameterloser Funktionen"
    - k2: "Call-by-Value-Semantik bei der Parameterübergabe"
    - k2: "Sichtbarkeit und Initialisierung von Variablen"
    - k3: "Definition und Deklaration von Funktionen"
    - k3: "Nutzung lokaler und globaler und lokaler statischer Variablen"
youtube:
  - link: "TODO"
    name: "VL C++: Funktionen"
---


## Funktionen in C++

-   Funktionen sind mit Methoden in Java vergleichbar

    => sind aber [unabhängig]{.alert} von Klassen bzw. Objekten

\bigskip

-   Syntax:

    ``` cpp
    Rueckgabetyp Funktionsname(Parameterliste) {
        Anweisungen (Implementierung)
    }
    ```

\bigskip

-   Aufruf: Nennung des Namens (mit Argumenten) im Programmcode

    ``` cpp
    int x = foo(42);
    ```

::: notes
Unterschied "Parameter" und "Argument":

-   Funktion hat "Parameter" in ihrer Parameterliste, auch "formale Parameter" genannt
-   Beim Aufruf werden "Argumente" übergeben, auch "aktuelle Parameter" genannt

    In der Praxis verwendet man beide Begriffe i.d.R. synonym.

Anmerkungen zum Beispiel:

-   Compiler "liest" Quellcode von oben nach unten
-   Funktionen müssen [vor]{.alert} ihrer Verwendung [deklariert]{.alert} sein,
    d.h. es muss zumindest ihre Signatur bekannt sein (siehe nächste Folie)
:::


## Funktionen: Deklaration vs. Definition

-   **Deklaration**: [(Funktions-) Prototyp]{.alert}: Festlegen von
    [Signatur]{.alert} [(d.h. Funktionsname und Anzahl, Typ, Reihenfolge der Parameter)]{.notes} u. Rückgabetyp

    ``` cpp
    void machWas(int, int);
    ```

\smallskip

-   **Definition**: [Implementierung]{.alert} der Funktion

    ``` cpp
    void machWas(int a, int b) {
        cout << "a: " << a << ", b: " << b << endl;
    }
    ```

\bigskip

-   Compiler "liest" Quellcode von oben nach unten
-   Funktionen müssen [vor]{.alert} ihrer Verwendung [mindestens]{.notes} [deklariert]{.alert} sein
-   Deklaration: Variablennamen können weggelassen werden

::: notes
Allgemein:

-   Deklaration: Macht einen Namen bekannt und legt den Typ der Variablen bzw.
    die Schnittstelle der Funktionen fest.
-   Definition: Deklaration plus Reservierung von Speicherplatz für die
    Variable oder Implementierung einer Funktion/Struktur/...
:::

[Konsole: simplefunction.cpp]{.bsp href="https://github.com/Compiler-CampusMinden/CB-Vorlesung-Bachelor/blob/master/lecture/99-languages/src/simplefunction.cpp"}


## One Definition Rule (für Funktionen)

::: center
Jede Funktion darf im **gesamten** Programm nur [**einmal definiert**]{.alert} sein!
:::


## Funktionen und Parameter

-   Funktionen "ohne" Parameter:

    -   Leere Parameter-Liste^[Achtung: C-Compiler akzeptiert [**alle**]{.alert}
        Parameter!] oder Schlüsselwort `void`

    ```c
    void fkt();
    void fkt(void);
    ```

\smallskip

-   Funktionen **mit** Parameter:

    -   Deklaration: Variablennamen können weggelassen werden
    -   Definition: Variablennamen müssen angegeben werden

    ```c
    void fkt(int, char);
    void fkt(int a, char b);

    void fkt(int a, char b) { ... }
    ```

::: notes
### Leere Parameterliste in C

Wenn eine Funktion keine Parameter hat, können Sie wie in C die Parameterliste
entweder einfach leer lassen (`int fkt();`) oder das Schlüsselwort `void`
nutzen (`int fkt(void);`).

Betrachten Sie folgendes Beispiel:

``` c
// Legal in C
int wuppie();                   // Deklaration: "Ich verrate Dir nicht, wieviele Parameter wuppie() hat."
int wuppie(int x) { return x; } // Aufruf mit Argumenten => ist okay

// Fehler in C
int fluppie(void);               // Deklaration: fluppie() hat KEINE Parameter!
int fluppie(int x) { return x; } // Aufruf mit Argumenten => Compiler-Fehler
```

Wenn Sie eine mit leerer Parameterliste deklarierte Funktion definieren bzw.
aufrufen, akzeptiert der C-Compiler dennoch **alle** übergebenen Parameter. Dies
kann zu schwer verständlichen Fehlern führen! Sobald eine Funktion explizit
mit dem Schlüsselwort `void` in der Parameterliste deklariert wird, **muss**
diese dann auch ohne Parameter aufgerufen werden.

[=> **Bevorzugen Sie in C die Variante mit dem Schlüsselwort `void`!**]{.alert}

### Leere Parameterliste in C++

Keine Parameter: Leere Liste und Schlüsselwort `void` **gleichwertig**

``` cpp
void fkt();
void fkt(void);
```
:::


::: notes
## Defaultparameter in C++

-   Parameter mit Defaultwerten am [**Ende**]{.alert} der Parameterliste
-   Bei Trennung von Deklaration und Definition: Defaultparameter
    [**nur**]{.alert} in Deklaration

``` cpp
// Deklaration
void f(int i, int j=1, int k=2);

// Definition
void f(int i, int j, int k) { ... }
```
:::


::: notes
## Überladen von Funktionen

-   Funktionen im **gleichen Gültigkeitsbereich** können überladen werden
-   Zu beachten:
    1.  Funktionsname identisch
    2.  Signatur (Anzahl, Typen der Parameter) muss [unterschiedlich]{.alert} sein
    3.  Rückgabewert darf variieren

=> [Warnung]{.alert}: Überladene Funktionen sollten gleichartige
Operationen für unterschiedliche Datentypen bereitstellen!
:::


::: notes
## Probleme beim Überladen von Funktionen

1.  Defaultparameter

    ``` cpp
    int maximum(int, int);
    int maximum(int, int, int=10);
    ```

2.  Identische Signatur, Unterschied nur im Rückgabewert

    ``` cpp
    int maximum(int, int);
    double maximum(int, int);
    ```

3.  Überladen nur für Funktionen des selben Gültigkeitsbereichs!

    ``` cpp
    #include <iostream>
    using namespace std;

    void f(char c) {
        cout << "f(char): " << c << endl;
    }
    void f(int i) {
        cout << "f(int): " << i << endl;
    }


    int main() {
        void f(int i);  // f(char) nicht mehr sichtbar!
        f('a');

        return 0;
    }
    ```
:::


## Parameterübergabe in C: Call-by-Value

:::::: columns
::: {.column}

``` cpp
int add_5(int x) {
    x += 5;
    return x;
}

int main() {
    int erg, i=0;
    erg = add_5(i);
}
```

:::
::: {.column}

```
Aufrufer-Sicht
                 i                             erg
              +------+                       +------+
              |      |                       |      |
              +---+--+                       +---^--+
                  |                              |
                  |                              |
------------------+------------------------------+-------
      Kopie bei   |                       Kopie  |
      Aufruf      |                       bei    |
                  |                       return |
              +---v--+                           |
              |      +---------------------------+
              +------+
                 x
Funktionssicht
```

:::
::::::

::: notes
-   Default in C/C++ ist die [call-by-value]{.alert} Semantik:
    -   Argumente werden bei Übergabe [kopiert]{.alert}
    -   Ergebniswerte werden bei Rückgabe [kopiert]{.alert}
-   Folgen:
    -   Keine Seiteneffekte durch Verändern von übergebenen Strukturen
    -   Negative Auswirkungen auf Laufzeit bei großen Daten

Ausnahme: Übergabe von C++-Referenzen oder Pointern
(wobei Pointer streng genommen auch kopiert werden, also per call-by-value übergeben werden ...)
:::


## Globale Variablen (externe Variablen)

```c
int a = 1;

int main() {
    extern int a;
}
```

::: notes
-   Außerhalb **jeder** Funktion definierte Variablen

\smallskip

-   Existieren die **gesamte** Programmlebensdauer über
-   Müssen bei _Nutzung_ in Funktionen als `extern` deklariert werden

\bigskip
=> Werden auch als [**externe Variablen**]{.alert} bezeichnet
:::

\bigskip
\bigskip

_Hinweis_: `extern` für globale Konstanten bedeutet etwas **leicht** anderes

::: notes
Varianten für Nutzung globaler Variablen in Funktionen:

-   Deklaration der globalen Variable vor Funktionsdefinition:
    -   In Funktion als `extern` deklarieren, oder
    -   In Funktion direkt (ohne Deklaration) nutzen ...
-   Deklaration der globalen Variable nach Funktionsdefinition: In Funktion als `extern` deklarieren
:::

[Konsole: extern.c]{.bsp}

## Lokale Variablen (automatische Variablen)

```c
int b = 1;

void f() {
    int b = 42;
}

int main() {
    int b = 3;

    {
        int b = 7;
    }
}
```

::: notes
-   Innerhalb einer Funktion (oder Blockes) definierte Variablen
    -   Gilt auch für Variablen aus Parameterliste

\smallskip

-   Überdecken **globale Variablen** gleichen Namens

-   Sichtbarkeit:
    -   Außerhalb der Funktion/Blockes nicht zugreifbar
    -   Beim Betreten der Funktion Reservierung von Speicherplatz für lokale
        Variablen
    -   Dieser wird beim Verlassen des Blockes/Funktion automatisch wieder
        freigegeben
    -   Namen sind nur nach Deklaration und innerhalb des Blockes, in dem sie
        deklariert wurden, gültig
    -   Namen sind auch gültig für innerhalb des Blockes neu angelegte innere
        Blöcke

    Software Engineering: Vermeiden Sie lokale Namen, die Namen aus einem
    äußeren Scope überdecken!

\bigskip
=> Werden auch als [**automatische Variablen**]{.alert} bezeichnet
:::

[Konsole: sichtbarkeit.c]{.bsp}

## Schlüsselwort static

```c
void foo() {
    static int x = 42;
    x++;
    printf("x=%d\n", x);
}

int main() {
    foo();  foo();  foo();
}
```

::: notes
-   Lokale Variablen mit "Gedächtnis": Definition mit dem vorangestellten Schlüsselwort "static"

    ```c
    static int callCount;
    ```

\smallskip

-   Eigenschaften:
    -   Wert bleibt für die folgenden Funktionsaufrufe erhalten
    -   Wert kann in der Funktion verändert werden
    -   Dennoch: lokale Variable, d.h. von außen nicht sichtbar/gültig
:::

\bigskip
\bigskip

_Hinweis_: `static` für globale Variablen bedeutet etwas anderes

[[Beispiel: static.c]{.bsp}]{.notes}

## Initialisierung

(Automatische) Initialisierung von Variablen hängt von ihrer Speicherklasse ab!

\bigskip

-   Extern
    -   Mit dem Wert 0 oder vorgegebenem Wert
    -   Bereits vor Programmstart (im Code enthalten)

\smallskip

-   Automatisch
    -   Werden [nicht]{.alert} automatisch initialisiert (!)
    -   Bei vorgegebenem Wert ab Aufruf der Funktion

\smallskip

-   Statisch
    -   Mit dem Wert 0 oder vorgegebenem Wert
    -   Ab erstem Aufruf der Funktion

[Konsole: initVar.c]{.bsp}



## Wrap-Up

-   **Funktionen**: Kapselung von Operationen
    -   Funktionen in C analog zu Methoden in Java
    -   Existieren unabhängig von Klassen (gibt in C auch keine)
    -   Überladen von Funktionen [(analog zu Java)]{.notes}
    -   Defaultparameter bei Funktionen
-   Deklaration vs. Definition, Funktionsprototypen, **One-Definition-Rule**
-   Parameterübergabe: **call-by-value** (Standard in C)
-   Unterscheidung globale, lokale und lokale statische Variablen







<!-- DO NOT REMOVE - THIS IS A LAST SLIDE TO INDICATE THE LICENSE AND POSSIBLE EXCEPTIONS (IMAGES, ...). -->
::: slides
## LICENSE
![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)

Unless otherwise noted, this work is licensed under CC BY-SA 4.0.
:::
