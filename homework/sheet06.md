---
archetype: assignment
title: "Blatt 06: C++"
author: "Carsten Gips, BC George (HSBI)"

hidden: true
---

<!--  pandoc -s -f markdown -t markdown+smart-grid_tables-multiline_tables-simple_tables --columns=94 --reference-links=true  sheet06.md  -o xxx.md  -->

## A6.1: TODO

TODO


## A6.2: TODO

TODO


**S5**: noch irgendwas Richtung Speicherverwaltung/Heap extra


### Aufgabe 1: Implementierung eines einfachen Tokenizers (25 Punkte)

Erstellen Sie eine Funktion `void tokenize(const std::string& input, std::vector<std::string>& tokens)`, die einen gegebenen String als Eingabe erhält und diesen in Tokens (Wörter) splittet. Nutzen Sie Referenzen, um die Token-Liste zu aktualisieren. Testen Sie die Funktion mit verschiedenen Eingabestrings und geben Sie die Tokens aus.


### Aufgabe 2: Syntaxanalyse mit Referenzen (30 Punkte)

Implementieren Sie eine einfache Funktion `bool parseExpression(const std::string& expr, int& result)`, die überprüft, ob eine als String dargestellte mathematische Ausdrucksform (z.B. "3 + 4") syntaktisch korrekt ist. Die Funktion soll das Ergebnis der Berechnung zurückgeben. Nutzen Sie Referenzen für den Rückgabewert und testen Sie die Funktion mit verschiedenen mathematischen Ausdrücken.




### Aufgabe 1: Überladene Funktionen (15 Punkte)

Erstellen Sie eine C++-Bibliothek mit überladenen Funktionen, um den Flächeninhalt verschiedener Formen zu berechnen. Implementieren Sie folgende Funktionen:

- `double area(double radius)`: Berechnet die Fläche eines Kreises.
- `double area(double width, double height)`: Berechnet die Fläche eines Rechtecks.
- `double area(double side1, double side2, double side3)`: Berechnet die Fläche eines Dreiecks mithilfe der Heronschen Formel.

Testen Sie Ihre Implementierung in der `main`-Funktion mit unterschiedlichen Parametern.


### Aufgabe 2: Pointer und Arrays (20 Punkte)

Schreiben Sie eine Funktion `void initializeArray(int* arr, int size)`, die ein Array von Ganzzahlen mit aufsteigenden Werten initialisiert (beginnend bei 1). Erstellen Sie in der `main`-Funktion ein dynamisches Array, initialisieren Sie es mit Ihrer Funktion und geben Sie die Werte aus. Stellen Sie sicher, dass der Speicher ordnungsgemäß freigegeben wird.


### Aufgabe 3: Mehrdimensionale Arrays mit Pointer-Arithmetik (25 Punkte)

Erstellen Sie eine Funktion `void transposeMatrix(int* matrix, int rows, int cols)`, die eine Matrix (2D-Array) transponiert. Nutzen Sie Pointer-Arithmetik und zeigen Sie die ursprüngliche und die transponierte Matrix in der `main`-Funktion an. Achten Sie darauf, den Speicher für die Matrix dynamisch zu allozieren und zu deallozieren.


### Aufgabe 4: Memory Management und Fehlerbehandlung (25 Punkte)

Implementieren Sie eine Funktion `int* allocateAndFillArray(int size)`, die ein Array alloziert, es mit zufälligen Werten befüllt (zwischen 1 und 100) und zurückgibt. Fügen Sie einfache Fehlerbehandlungen für die Speicherzuweisung hinzu. In der `main`-Funktion sollten die Werte des Arrays ausgegeben und danach der Speicher freigegeben werden.


### Aufgabe 5: Komplexe Datenverwaltung mit Referenzen (30 Punkte)

Erstellen Sie eine Struktur `Student`, die `name`, `matrikelnummer` und `note` enthält. Implementieren Sie folgende Funktionen:

- `void setStudentDetails(Student& s, const std::string& name, int matrikelnummer, double note)`: Setzt die Werte eines Studenten.
- `double calculateAverage(const Student* students, int count)`: Berechnet den Durchschnitt der Noten eines gegebenen Studenten-Arrays.

In der `main`-Funktion sollten Sie mindestens 5 Studenten anlegen, deren Werte initialisieren und den Durchschnitt der Noten ausgeben.

**Bonusaufgabe (15 Punkte):**
Implementieren Sie eine Funktion `void countVowels(const std::string& str, int& count)`, die die Anzahl der Vokale in einem gegebenen String zählt. Testen Sie die Funktion in der `main`-Funktion mit verschiedenen Eingaben. Verwenden Sie dabei Referenzen zur Rückgabe des Zählers.


