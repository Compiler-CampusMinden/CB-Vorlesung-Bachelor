---
archetype: lecture-cg
title: "Einführung in C++ (Erinnerungen an C)"
linkTitle: "Einführung in C++"
author: "Carsten Gips (HSBI)"
readings:
  - key: "Breymann2011"
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

    In C++ gibt es Klassen (mit Methoden und Attributen), und zusätzlich gibt es Funktionen. Der Einsprungpunkt in ein
    Programm ist (analog zu Java) die Funktion `main()`, die ein `int` als Ergebnis zurückliefert.
    Dieser Integer kann vom Aufrufer ausgewertet werden, wobei der Wert 0 typischerweise als Erfolg
    interpretiert wird. Achtung: Das ist eine Konvention, d.h. es kann Programme geben, die andere
    Werte zurückliefern. Die Werte müssen dokumentiert werden.

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

    TODO
outcomes:
  - k1: "Wie hängen C und C++ zusammen?"
  - k1: "Wichtigste Aufgaben des Präprozessors"
  - k3: "Aufbau, Übersetzen und Starten von einfachen C++-Programmen"
  - k3: "Ausgabe mit `printf()` und `std::cout`"
  - k3: "Erinnerung: Automatisiertes Übersetzen mit Hilfe von GNU Make und einfachsten Makefiles"

  - k2: "TODO"
youtube:
  - link: "TODO"
    name: "VL Einführung in C++ (Erinnerungen an C)"
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

```c
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

::: notes
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

```makefile
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

    ```makefile
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
:::

[Konsole: HelloWorld.cpp]{.bsp href="https://github.com/Compiler-CampusMinden/CB-Vorlesung-Bachelor/blob/master/lecture/99-languages/src/HelloWorld.cpp"}






## Thema 2: Grundlegende Konzepte

- Variablen und Datentypen in C++: `float`, `double`, `char`, `boolean`, `int`
- Einführung in Operatoren und Ausdrücke
- Ein- und Ausgabe von Daten mit `cin` und `cout`
- Kommentare und Formatierung von Code
- Eingebaute Funktionen/Operatoren: `printf`, `sizeof`, `<<`, `typedef`
- Namespaces, Scopes
- Präprozessor und Header


## Thema 3: Kontrollstrukturen

- Verzweigungen mit `if`, `else if` und `else`
- Schleifen mit `for`, `while` und `do while`
- Verwendung von logischen Operatoren


## Thema 4: Funktionen

- Definition und Verwendung von Funktionen
- Parameterübergabe an Funktionen
- Rückgabewerte von Funktionen
- Lokale und globale Variablen


## Thema 5: Arrays

- Einführung in Arrays
- Arbeiten mit Arrays und Schleifen: `vec3 foo[10]`
- Mehrdimensionale Arrays
- Verwendung von Standardbibliothekscontainern (z.B. `vector`)





## Wrap-Up

-   C/C++ sind enge Verwandte: kompilierte Sprachen, C++ fügt OO hinzu
-   Funktionsweise einfachster Make-Files

TODO







<!-- DO NOT REMOVE - THIS IS A LAST SLIDE TO INDICATE THE LICENSE AND POSSIBLE EXCEPTIONS (IMAGES, ...). -->
::: slides
## LICENSE
![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)

Unless otherwise noted, this work is licensed under CC BY-SA 4.0.
:::
