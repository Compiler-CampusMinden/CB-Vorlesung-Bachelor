---
archetype: lecture-cg
title: "Einführung in C++ (Erinnerungen an C)"
linkTitle: "Einführung in C++"
author: "Carsten Gips (HSBI)"
readings:
  - key: "Breymann2011"
  - key: "cppreference.com"
  - key: "cprogramming.com"
tldr: |
    Für C wurde ein paar Jahre nach der Entstehung ein objektorientierter Aufsatz entwickelt: C++.
    Beide Sprachversionen werden aktiv weiterentwickelt, vor allem in C++ gibt es ca. alle 2 Jahre
    einen neuen Standard mit teilweise recht umfangreichen Ergänzungen. Hier fließen analog zu Java
    immer mehr Programmierkonzepte mit ein, die aus anderen Sprachen stammen (etwa funktionale
    Programmierung). Das macht das Erlernen und Beherrschen der Sprache nicht unbedingt leichter.
    Die für uns wichtigsten Neuerungen kamen mit C11 und C++11 bzw. C++14.

    C und C++ versuchen (im Gegensatz zu Java) ressourcenschonende Sprachen zu sein: Ein korrektes
    Programm soll so schnell wie möglich ausgeführt werden können und dabei so effizient wie möglich
    sein (etwa in Bezug auf den Speicherbedarf). Deshalb gibt es keine Laufzeitumgebung, der Quellcode
    wird direkt in ein ausführbares (und damit Betriebssystem-abhängiges) Binary compiliert. Beide
    Sprachen erlauben dem Programmierer den Zugriff auf die Speicherverwaltung und damit viele Freiheiten.
    Die Kehrseite ist natürlich, dass Programmierfehler (etwa bei der Speicherallokation oder bei
    Indexberechnungen) nicht von der Laufzeitumgebung entdeckt und abgefangen werden können.

    C-Programme sehen auf den ersten Blick Java-Code relativ ähnlich. Das ist nicht verwunderlich,
    da Java zeitlich nach C entwickelt wurde und die Syntax und große Teile der Schlüsselwörter
    von C übernommen hat. C++ hat die C-Syntax übernommen und fügt neue objektorientierte Konzepte
    hinzu. Mit gewissen Einschränkungen funktioniert also C-Code auch in C++.

    In C++ gibt es Klassen (mit Methoden und Attributen), und zusätzlich gibt es Funktionen. Der
    Einsprungpunkt in ein Programm ist (analog zu Java) die Funktion `main()`, die ein `int` als
    Ergebnis zurückliefert. Dieser Integer kann vom Aufrufer ausgewertet werden, wobei der Wert 0
    typischerweise als Erfolg interpretiert wird. Achtung: Das ist eine _Konvention_, d.h. es kann
    Programme geben, die andere Werte zurückliefern. Die Werte müssen dokumentiert werden.

    Bevor der Compiler den Quelltext "sieht", wird dieser von einem Präprozessor bearbeitet. Dieser
    hat verschiedene Aufgaben, unter anderem das Einbinden anderer Dateien. Dabei wird ein
    `#include "dateiname"` (sucht im aktuellen Ordner) bzw. `#include <dateiname>` (sucht im
    Standardverzeichnis) ersetzt durch den Inhalt der angegebenen Datei.

    C++-Code muss kompiliert werden. Dabei entsteht ein ausführbares Programm. Mit Make kann man den
    Kompiliervorgang über Regeln automatisieren (denken Sie an ANT in der Java-Welt, nur ohne XML).
    Eine Regel besteht aus einem Ziel (*Target*), einer Liste von Abhängigkeiten sowie einer Liste mit
    Aktionen (Anweisungen). Um ein Ziel zu "bauen" müssen zunächst alle Abhängigkeiten erfüllt sein
    (bzw. falls sie es nicht sind, erst noch "gebaut" werden - es muss entsprechend weitere Regeln
    geben, um diese Abhängigkeiten "bauen" zu können). Dann wird die Liste der Aktionen abgearbeitet.
    Ziele und Abhängigkeiten sind in der Regel Namen von Dateien, die existieren müssen bzw. über die
    Aktionen erzeugt werden sollen. Die Aktionen sind normale Befehlssequenzen, die man auch in einer
    Konsole eingeben könnte. Make berücksichtigt den Zeitstempel der Dateien: Ziele, die bereits
    existieren und deren Abhängigkeiten nicht neuer sind, werden nicht erneut gebaut.

    Die gute Nachricht: In Bezug auf Variablen, Operatoren und Kontrollfluss verhalten sich C und C++
    im Wesentlichen wie Java.

    Es gibt in C++ den Typ `bool` mit den Werten `true` und `false`.  Zusätzlich werden Integerwerte
    im boolschen Kontext (etwa in einer `if`-Abfrage) ausgewertet, wobei der Wert 0 einem `false`
    entspricht und alle anderen Integer-Werte einem `true`. (Dies steht etwas im Widerspruch zu den
    Werten, die in der `main`-Funktion per `return` zurückgeliefert werden: Hier bedeutet 0 in der
    Regel, dass alles OK war.)

    Die Basisdatentypen sind (bis auf `char` und `bool`) in ihrer Größe maschinenabhängig. Es kann
    also sein, dass Code, der auf einem 64bit-Laptop ohne Probleme läuft, auf einem Raspberry PI
    Überläufe verursacht! Um besonders ressourcenschonend zu arbeiten, kann man die Speichergröße
    für einige Basisdatentypen durch die Typmodifikatoren `short` und `long` beeinflussen sowie
    die Interpretation von Zahlenwerten mit oder ohne Vorzeichen (`signed`, `unsigned`) einstellen.

    Die Anzahl der für einen Typ oder eine Variable/Struktur benötigten Bytes bekommt man mit
    dem Operator `sizeof` heraus.

    Mit `typedef` kann man einen neuen Namen für bereits existierende Typen vergeben.
outcomes:
  - k1: "Wie hängen C und C++ zusammen?"
  - k1: "Wichtigste Unterschiede und Gemeinsamkeiten zu Java"
  - k1: "Wichtigste Aufgaben des Präprozessors"
  - k3: "Aufbau, Übersetzen und Starten von einfachen C++-Programmen"
  - k3: "Standard-Ein-/Ausgabe-Kanäle in C++ sowie die Operatoren `>>` und `<<`"
  - k3: "Nutzung der Basisdatentypen einschließlich der Modifikatoren"
  - k3: "Deklaration von Variablen, Nutzung von Kontrollstrukturen und Operatoren"
  - k3: "Interpretation von Integers im booleschen Kontext"
  - k3: "Nutzung des Scope-Operators `::`, Namensräume"
  - k3: "Benutzung von `sizeof` zur Bestimmung des Speicherbedarfs"
  - k3: "Benutzung von `typedef` zur Definition neuer Typen (Aliase bestehender Typen)"
  - k3: "Erinnerung: Automatisiertes Übersetzen mit Hilfe von GNU Make und einfachsten Makefiles"
#youtube:
#  - link: "TODO"
#    name: "VL Einführung in C++ (Erinnerungen an C)"
challenges: |
    *   Wie groß ist der Bereich der Basisdatentypen (Speicherbedarf, Zahlenbereich)?
        Wie können Sie das feststellen?

        ```c
        unsigned char a;
        int b;

        long long x[10];
        long long y[] = {1, 2, 3};
        long long z[7] = {3};
        ```

        <!--
        ```
        a: 1 Byte
        x: 10 Elemente, nicht initialisiert
        y: 3 Elemente, initialisiert wie angegeben
        z: 7 Elemente, erstes mit Wert 3, Rest mit 0 initialisiert
        ```
        -->

    *   Erklären Sie den Unterschied `sizeof(x)` vs. `sizeof(x)/sizeof(x[0])`!

    *   Warum ist der folgende Code-Schnipsel gefährlich?

        ```c
        if (i=3)
            printf("Vorsicht");
        else
            printf("Vorsicht (auch hier)");
        ```

    *   Limits kennen: Datentypen, Wertebereiche

        Schreiben Sie ein C-Programm, welches die größtmögliche `unsigned int` Zahl
        auf Ihrem System berechnet.

        Verwenden Sie hierzu **nicht** die Kenntnis der systemintern verwendeten Bytes
        (`sizeof`, ...). Nutzen Sie auch nicht die Konstanten/Makros/Funktionen aus
        `limits.h` oder `float.h` oder anderen Headerdateien!

        <!-- XXX
        ```c
        unsigned int x = 0; x--;
        ```
        -->
---


## Warum?

-   C++ erlaubt ressourcenschonende Programmierung
-   Objektorientierter "Aufsatz" auf C
-   Verbreitet bei hardwarenaher und/oder rechenintensiver Software

::: center
[**Sie werden C++ im Modul "Computergrafik" brauchen!**]{.alert}
:::

\bigskip
\pause

**Geschichte**

-   1971-73: [Ritchie]{.alert} entwickelt die Sprache [C]{.alert}
-   Ab 1979: Entwicklung von [C++]{.alert} durch Bjarne [Stroustrup]{.alert} bei AT&T
    -   Erweiterung der prozeduralen Sprache C
    -   Ursprünglich "C mit Klassen", später "C++" (Inkrement-Operator)
-   Bis heute: Fortlaufende Erweiterungen: alle 3 Jahre neuer Standard (C++11, C++14, ...)

::: notes
`{{% notice style="info" title="**C/C++ vs. Java**" %}}`{=markdown}
-   Java: Fokus auf Sicherheit und Robustheit
    -   Diverse Sicherheitschecks durch Compiler und VM (zb. Array-Zugriff)
    -   Speicherverwaltung (Garbage Collection), kein Speicherzugriff über Pointer
    -   Automatische Initialisierung von Variablen
-   C/C++: Fokus auf Effizienz (Speicher, Laufzeit) für korrekte Programme
    -   Vergleichsweise schwache Sicherheitschecks durch Compiler, keine VM \newline
        (d.h. keine Prüfung von Array-Indizes u.a.)
    -   Keine Garbage Collection, Programmierer hat direkten Zugriff auf Speicher
    -   Keine automatische Initialisierung von Variablen
`{{% /notice %}}`{=markdown}
:::


## Hello World!

``` c++
/*
 * HelloWorld.cpp (g++ -Wall HelloWorld.cpp)
 */

#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
    printf("Hello World from C++  :-)\n");
    cout << "Hello World from C++  :-)" << endl;
    std::cout << "Hello World from C++  :-)" << std::endl;

    return EXIT_SUCCESS;
}
```

::::::::: notes
### Beobachtungen

Jedes (ausführbare) C++-Programm hat genau eine `main()`-Funktion. Die `main()`-Funktion ist
_keine Methode_ einer Klasse: In C/C++ gibt es Funktionen auch außerhalb von Klassen.

In C++ gibt es Namespaces (dazu später mehr). Die aus der Standardbibliothek importierten
Funktionen sind in der Regel im Namespace `std` definiert. Mit `using namespace std;` können
Sie auf die Elemente direkt zugreifen. Wenn Sie das `using namespace std;` weglassen, müssten
Sie bei jeder Verwendung eines Symbols den Namensraum explizit dazu schreiben
`std::cout << "Hello World from C++  :-)" << std::endl;`.

Sie können im C++-Code auch Funktionen aus C benutzen, d.h. Sie können für die Ausgabe
beispielsweise `printf` nutzen (dazu müssen Sie den Header `<cstdio>` importieren). Die
"richtige" Ausgabe in C++ ist aber die Nutzung des Ausgabestreams `cout` und des
Ausgabeoperators `<<`. Das `endl` sorgt für einen zum jeweiligen Betriebssystem passenden
Zeilenumbruch.

Der Rückgabewert signalisiert Erfolg bzw. Fehler der Programmausführung. Dabei steht der Wert
0 traditionell für Erfolg (Konvention!). Besser Makros nutzen: `EXIT_SUCCESS` bzw.
`EXIT_FAILURE` (in `cstdlib`).

### Präprozessor

Der Präprozessor transformiert den Quellcode _vor_ dem Compiler-Lauf. Zu den wichtigsten
Aufgaben gehören dabei die Makrosubstitution (`#define Makroname Ersatztext`) und das Einfügen
von Header-Dateien (und anderen Dateien) per `#include`. Es gibt dabei zwei Formen, die an
unterschiedlichen Orten nach der angegebenen Datei suchen:

-   `#include "dateiname"` sucht im aktuellen Ordner
-   `#include <dateiname>` sucht im Standardverzeichnis

Das `#include` kann wie in C genutzt werden, aber es gibt auch die Form ohne die Dateiendung
".h". Da es in C keine Funktionsüberladung gibt (in C++ dagegen schon), müssen die C-Header
speziell markiert sein, um sie in C++ verwenden zu können. Für die Standard-Header ist dies
bereits erledigt, Sie finden diese mit einem "c" vorangestellt:

-   Include in C: `#include <stdio.h>`
-   Include in C++: `#include <cstdio>`

### Übersetzen, Linken, Ausführen

C++-Dateien werden üblicherweise mit der Endung "**.cpp**" oder ".cxx" oder ".cc"
abgespeichert, Header-Dateien mit den Endungen ".hpp" oder ".hxx" oder ".hh".

Zum Übersetzen und Linken in einem Arbeitsschritt rufen Sie den Compiler auf:
`g++ HelloWorld.cpp` bzw. besser **`g++ -Wall -o helloworld HelloWorld.cpp`**. Die Option
`-Wall` sorgt dafür, dass alle Warnungen aktiviert werden.

Ausführen können Sie das erzeugte Programm in der Konsole mit: `./helloworld`. Der aktuelle
Ordner ist üblicherweise (aus Sicherheitsgründen) nicht im Suchpfad für ausführbare Dateien
enthalten. Deshalb muss man explizit angeben, dass ein Programm im aktuellen Ordner (`.`)
ausgeführt werden soll.

### Automatisieren der Buildvorgänge: GNU Make

#### Makefile: Textdatei mit Regeln für das Programm `make`

-   Abläufe automatisieren: Kompilieren, testen, Pakete bauen, aufräumen, ...
-   Java: `ant`, C/C++: `make`
-   Achtung: Verschiedene Make-Dialekte! Wir nutzen _GNU Make_!

``` makefile
 # Kommentar
 Ziel1: AbhaengigkeitenListe1
     Aktionen1

 Ziel2: AbhaengigkeitenListe2
     Aktionen2

 # ... und so weiter :-)
 # ACHTUNG:
 # Vor den Aktionen <TAB> benutzen, keine Leerzeichen!!!
 # Vorsicht mit Editor-Einstellungen!
```

Bedeutung: Um das Ziel `Ziel1` zu erzeugen, müssen alle Abhängigkeiten der Liste
`AbhaengigkeitenListe1` erfüllt sein. Dann werden die Aktionen in `Aktionen1` durchgeführt,
um `Ziel1` zu erzeugen. Aber nur, falls das Ziel `Ziel1` nicht existiert oder veraltet ist!

Falls die Abhängigkeiten nicht erfüllt sind, wird nach Regeln gesucht, um diese zu erzeugen.
Das bedeutet, dass u.U. zunächst weitere Targets "gebaut" werden, bevor die Aktionenliste
ausgeführt wird.

Die Ziele und Abhängigkeiten sind i.d.R. Dateien (müssen es aber nicht sein).

#### Makefiles: Fiktives Beispiel

-   Annahme: Projekt besteht aus der Datei `main.cpp`, daraus soll das Programm
    "tollesProgramm" erzeugt werden
-   Passendes Makefile:

    ``` makefile
    CXXFLAGS = -Wall

    .PHONY: all
    all: tollesProgramm

    tollesProgramm: main.o
        $(CXX) $(LDFLAGS) $< $(LDLIBS) -o $@

    %.o: %.cpp
        $(CXX) $(CXXFLAGS) -c $< -o $@

    .PHONY: clean
    clean:
        rm -rf tollesProgramm *.o *.~
    ```

Bedeutung: Um das Ziel `all` zu erzeugen, muss die Abhängigkeit `tollesProgramm` erfüllt sein.
Beachten Sie, dass im Beispiel `all` kein Dateiname ist, `tollesProgramm` dagegen schon.

Um `tollesProgramm` zu erzeugen, muss die Datei `main.o` vorhanden sein. Falls sie es nicht
ist, wird sie mit Hilfe des dritten Targets erzeugt. Das `%` ist dabei ein Patternmatcher,
d.h. wenn nach einem `main.o` gesucht ist, matcht `%.o` (das `%` bindet sich dabei an "main")
und auf der rechten Seite des Targets steht als Abhängigkeit `main.cpp`.

Die Variablen `CXX`, `CXXFLAGS`, `LDFLAGS` und `LDLIBS` sind vordefinierte Variablen:

-   `CXX`: C++-Compiler, Default: `g++`
-   `CXXFLAGS` Extra Flags für den C++-Compiler (nur für Kompilieren)
-   `LDFLAGS`: Extra Flags, die für das Linken genutzt werden (Beispiel: `-L.`; **nicht** `-lm`)
-   `LDLIBS`: Bibliotheken, die für das Linken genutzt werden (Beispiel: `-lm -lfoo`; **nicht** `-L.`)

Die Variablen `$<`, `$^` und `$@` lösen auf das Ziel bzw. die Abhängigkeiten eines Targets auf:

-   `$<` => gibt die erste Abhängigkeit an
-   `$^` => gibt alle Abhängigkeiten an
-   `$@` => gibt das Ziel an

Falls die Datei `tollesProgramm` nicht existiert oder aber älter ist als `main.o`, wird die
Regel des Targets `tollesProgramm` ausgeführt, um die Datei `tollesProgramm` zu erzeugen:
`g++ main.o -o tollesProgramm`.

**Hinweis**: Das Beispiel entspricht den minimalen Kenntnissen, die Sie über Make haben müssen.

#### Makefiles: Typische Aufrufe

-   `make` \newline
    Sucht nach Datei mit dem Namen "GNUmakefile", "makefile" oder "Makefile" und erzeugt das
    erste Ziel in der Datei

    Konvention: Das erste Ziel hat den Namen `all`

-   `make -f <datei>` \newline
    Sucht die Datei mit dem angegebenen Namen, erzeugt das erste Ziel in der Datei

-   `make -f <datei> <ziel>` \newline
    Sucht die Datei mit dem angegebenen Namen, erzeugt das Ziel `<ziel>`

-   `make <ziel>` \newline
    Sucht nach Datei mit dem Namen "GNUmakefile", "makefile" oder "Makefile" und erzeugt das
    Ziel `<ziel>`
:::::::::

[Konsole: HelloWorld.cpp]{.bsp href="https://github.com/Compiler-CampusMinden/CB-Vorlesung-Bachelor/blob/master/lecture/99-languages/src/HelloWorld.cpp"}


## Variablen, Operatoren, Kontrollfluss

::: center
[**Im Wesentlichen wie von Java gewohnt ... :-)**]{.alert}
:::

\bigskip
\bigskip

-   Wichtig(st)e Abweichung:

    Im booleschen Kontext wird `int` als Wahrheitswert interpretiert: \newline
    Alle Werte ungleich 0 entsprechen `true` (!)

    ::: notes
    **Anmerkung**: Dies steht im Widerspruch zu den Werten, die in der `main`-Funktion per
    `return` zurückgeliefert werden: Hier bedeutet 0 in der Regel, dass alles OK war.
    :::

\bigskip

=> Vorsicht mit

``` c
int c;
if (c=4) { ... }
```

::: notes
**Beispiele für Schleifen und Kontrollstrukturen in C/C++**

``` c
int x=5, y=1;


if (x>5) {
    x++;
} else if(y<=1) {
    y = y-x;
} else {
    y = 2*x;
}


while (y>0) {
    y--;
}


for (x=0; x<10; x++) {
    y = y*y;
}
```
:::


## Basisdatentypen

|          |                                             |
|:---------|:--------------------------------------------|
| `char`   | Zeichen (ASCII, 8 Bit bzw. 1 Byte)          |
| `int`    | Ganze Zahl (16, 32 oder 64 Bit)             |
| `float`  | Gleitkommazahl (typ. 32 Bit)                |
| `double` | Doppelt genaue Gleitkommazahl (typ. 64 Bit) |
| `void`   | Ohne/kein Wert                              |
| `bool`   | `true`, `false`                             |

Außerdem Arrays und Pointer mit diesen Typen möglich.


::::::::: notes
## Typmodifikatoren ändern Bedeutung

Vorangestellte Modifikatoren ändern Bedeutung:

1.  Länge im Speicher

    |         |                                        |
    | :------ | :------------------------------------- |
    | `short` | Speicher: halbe Wortlänge              |
    | `long`  | Speicher: doppelte/dreifache Wortlänge |

2.  Vorzeichen

    |            |                                     |
    | :--------- | :---------------------------------- |
    | `signed`   | mit Vorzeichen (Default bei Zahlen) |
    | `unsigned` | ohne Vorzeichen                     |

Anwendung auf ganze Zahlen:

-   `short` und `long` sind Synonyme für `short int` und `long int`
-   `long long` ist typischerweise eine ganze Zahl mit 8 Byte
-   `unsigned char` sind Zahlen von 0, ..., 255 (1 Byte)
-   zusätzlich: `long double` (nur diese Form)

Sie können `short`, `long` und `long long` nur für ganze Zahlen (`int`) nutzen, mit der Ausnahme `long double`.
Dagegen können `signed` und `unsigned` sowohl für `char` als auch für `int` benutzt werden.

vgl. [en.wikipedia.org/wiki/C_data_types](https://en.wikipedia.org/wiki/C_data_types)
:::::::::


## Arrays und Vektoren in C++

-   Syntax: `Typ Name[AnzahlElemente];`

    ```c
    int myArray[100];
    int myArray2[] = {1, 2, 3, 4};
    ```

    ::: notes
    **Guter Stil**: Anzahl der Elemente als Konstante deklarieren

    -   [Compiler]{.alert} reserviert sofort Speicher auf dem [Stack]{.alert} \newline
        => **statisch**: im Programmlauf nicht änderbar
    -   Zugriff über den Indexoperator []
    -   Achtung: "roher" Speicher, d.h. **keinerlei Methoden**
    -   Größe nachträglich bestimmen mit `sizeof`:

        ```c
        int myArray[100], i;
        int cnt = sizeof(myArray)/sizeof(myArryay[0]);
        ```
    :::

-   Vordefinierter Vektor-Datentyp `vector`

    ::: notes
    -   Einbinden über `#include <vector>`
    -   Anlegen eines neuen Arrays mit 10 Elementen für Integer:
    :::

    ```cpp
    vector<int> v(10);
    vector<double> meinVektor = {1.1, 2.2, 3.3, 4.4};
    meinVektor.push_back(5.5);
    cout << meinVektor.size() << endl;
    ```

    ::: notes
    -   Zugriff auf Elemente:
    :::

    ```cpp
    cout << v[0] << endl;       // ohne Bereichspruefung!
    cout << v.at(1000) << endl; // mit interner Bereichspruefung
    ```

    ::: notes
    -   Zuweisung (mit Kopieren):
    :::

    ```cpp
    vector<double> andererVektor;
    andererVektor = meinVektor;
    ```

    ::: notes
    -   Dynamische Datenstruktur:

    ```cpp
    vector<int> meineDaten;      // initiale Groesse: 0
    meineDaten.push_back(123);   // Wert anhaengen

    meineDaten.pop_back(); // Wert loeschen
    meineDaten.empty();    // leer?
    ```
    :::

::: notes
[**Vorsicht!**]{.alert} `vector<int> arr();` ist **kein** Vektor der Länge 0,
sondern deklariert eine **neue Funktion**!
:::


## Größe eines Datentyps ist maschinenabhängig

::: center
[**Der reservierte Speicherbereich und damit auch der Zahlenbereich für einen einfachen Typ in C/C++ ist maschinenabhängig!**]{.alert}
:::

::: notes
-   Zahlenbereiche für konkrete Implementierung in Header-Files definiert

    `limits.h` und `float.h`: Konstanten `INT_MAX`, `INT_MIN`, ...

-   Alternativ Herausfinden der Größe in Bytes: Operator `sizeof`

    Syntax: `sizeof(Typ)`
:::

\bigskip
\bigskip
\bigskip

Es gilt in C/C++:

-   `sizeof(unsigned char)` $=$ 1
-   `sizeof(short int)` $=$ 2
-   `sizeof(short int)` $\le$ `sizeof(int)` $\le$ `sizeof(long int)`
-   `sizeof(float)` $\le$ `sizeof(double)` $\le$ `sizeof(long double)`

::: notes
**Hinweis Arrays**: `sizeof` gibt immer die Anzahl der Bytes für einen Typ oder eine
Variable zurück. Bei Array ist das nicht unbedingt die Anzahl der Elemente im Array!

Beispiel:

``` c
char a[10];
double b[10];
```

`sizeof(a)` würde den Wert 10 als Ergebnis liefern, da ein `char` in C/C++ immer exakt ein
Byte benötigt und entsprechend 10 `char` 10 Byte. `sizeof(b)` ist maschinenabhängig und
liefert die Anzahl der Bytes, die man für die Darstellung von 10 Double-Werten benötigt.

Wenn man die Anzahl der Elemente im Array mit `sizeof` herausfinden will, muss man den
Gesamtwert für das Array noch durch den Speicherbedarf eines Elements teilen, also
beispielsweise `sizeof(b)/sizeof(b[0])`.
:::


## Alias-Namen für Typen mit typedef

Syntax: `typedef existTyp neuerName;`

``` c
typedef unsigned long uint32;
uint32 x, y, z;
```

::: notes
Im Beispiel ist `unint32` ein neuer Name für den existierenden Typ `unsigned long`, d.h.
die Variablen `x`, `y` und `z` sind `unsigned long`.
:::


## Ein- und Ausgabe mit printf() und cin/cout

-   `printf(formatstring, ...)`

    ::: notes
    -   Einbinden über `#include <cstdio>`
    -   Format-String: Text und Formatierung der restlichen Parameter: `%[flags][width][.precision]conversion`

        -   `flags`: hängt von der konkreten Ausgabe ab
        -   `width`: Feldbreite
        -   `precision`: Anzahl der Dezimalstellen
        -   `conversion`: (Beispiele)

            |     |                   |
            | :-- | :---------------- |
            | c   | Zeichen (Char)    |
            | d   | Integer (dezimal) |
            | f   | Gleitkommazahl    |
    :::

-   Standardkanäle: `cin` (Standardeingabe), `cout` (Standardausgabe), `cerr` (Standardfehlerausgabe)

    ::: notes
    -   Genauer: `cout` ist ein Ausgabestrom, auf dem der Operator `<<` schreibt
    -   Einbinden über `#include <iostream>`
    -   Implementierung der Ein- und Ausgabeoperatoren (`>>`, `<<`) für Basistypen und Standardklassen vorhanden
    -   Automatische Konvertierungen für Basistypen und Standardklassen
    :::

    ``` cpp
    // Ausgabe, auch verkettet
    string foo = "fluppie";
    cout << "hello world :" << foo << endl;

    // liest alle Ziffern bis zum ersten Nicht-Ziffernzeichen
    // (fuehrende Whitespaces werden ignoriert!)
    int zahl; cin >> zahl;
    ```

    ::: notes
    ``` cpp
    // Einzelne Zeichen (auch Whitespaces) lesen
    char c; cin.get(c);
    ```
    :::

[Beispiel: cin.cpp]{.bsp href="https://github.com/Compiler-CampusMinden/CB-Vorlesung-Bachelor/blob/master/lecture/99-languages/src/cin.cpp"}


## Sichtbarkeit und Gültigkeit und Namespaces

::: notes
Wie in Java:

-   Namen sind nur nach Deklaration und innerhalb des Blockes, in dem sie deklariert wurden, gültig
-   Namen sind auch gültig für innerhalb des Blockes neu angelegte innere Blöcke
-   Namen in inneren Blöcken können Namen aus äußeren Scopes überdecken

Zusätzlich gibt es noch benannte Scopes und einen Scope-Operator.
:::

-   C++ enthält den Scope-Operator `::` => Zugriff auf global sichtbare Variablen

    ``` cpp
    int a=1;
    int main() {
        int a = 10;
        cout << "lokal: " << a << "global: " << ::a << endl;
    }
    ```

-   Alle Namen aus `XYZ` zugänglich machen: `using namespace XYZ;`

    ``` cpp
    using namespace std;
    cout << "Hello World" << endl;
    ```

-   Alternativ gezielter Zugriff auf einzelne Namen: `XYZ::name`

    ```cpp
    std::cout << "Hello World" << std::endl;
    ```

::: notes
-   Namensraum `XYZ` deklarieren

    ```cpp
    namespace XYZ {
        ...
    }
    ```
:::

[Beispiel: cppScope.cpp]{.bsp href="https://github.com/Compiler-CampusMinden/CB-Vorlesung-Bachelor/blob/master/lecture/99-languages/src/cppScope.cpp"}


## Wrap-Up

-   C/C++ sind enge Verwandte: kompilierte Sprachen, C++ fügt OO hinzu
-   Funktionsweise einfachster Make-Files

\smallskip

-   Wichtigste Unterschiede zu Java
    -   Kontrollfluss wie in Java
    -   Basisdatentypen vorhanden
    -   Typ-Modifikatoren zur Steuerung des Speicherbedarfs/Wertebereich
    -   Integer können im booleschen Kontext ausgewertet werden
    -   Operator `sizeof` zur Bestimmung des Speicherbedarfs
    -   Alias-Namen für existierende Typen mit `typedef` definierbar







<!-- DO NOT REMOVE - THIS IS A LAST SLIDE TO INDICATE THE LICENSE AND POSSIBLE EXCEPTIONS (IMAGES, ...). -->
::: slides
## LICENSE
![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)

Unless otherwise noted, this work is licensed under CC BY-SA 4.0.
:::
