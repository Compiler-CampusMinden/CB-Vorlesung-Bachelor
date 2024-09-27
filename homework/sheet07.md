---
archetype: assignment
title: "Blatt 07: Mini-Projekt C++"
author: "BC George, Carsten Gips (HSBI)"

hidden: true
---


## A7.1: Mini-Python, Builder

Erweitern Sie Ihr Projekt zu einem Compiler, indem Sie unseren [CBuilder]
einbinden. Erzeugen Sie damit aus dem geparsten Mini-Python-Code passenden
C-Code, den Sie mit der im [CBuilder] mitgelieferten [C-Runtime] in ein
lauffähiges Programm übersetzen und ausführen können. Beachten Sie dazu
auch die [Dokumentation].

[CBuilder]: https://github.com/Compiler-CampusMinden/Mini-Python-Builder
[C-Runtime]: https://github.com/Compiler-CampusMinden/Mini-Python-Builder/tree/master/c-runtime
[Dokumentation]: https://github.com/Compiler-CampusMinden/Mini-Python-Builder/tree/master/docs


## A7.2: Freie Aufgabe: Zusätzliche Konzepte und Features

Überlegen Sie sich zusätzliche Konzepte und Features, die Sie in Ihren
Interpreter/Compiler einbauen wollen. Dies können zusätzliche Features
auf Sprachebene sein oder Ergänzungen/Erweiterungen Ihres Interpreters
bzw. Compilers. Geben Sie im ILIAS eine kurze Konzeptskizze als PDF ab.

Beispiel: Sie könnten neue syntaktische Elemente in Mini-Python einführen,
die intern auf die existierende Semantik abgebildet werden ([_syntactic sugar_]).
Hier könnten Sie eine `for`-Schleife einbauen, die intern auf die bereits
existierende `while`-Schleife abgebildet wird. (Sie sollen sich aber
selbst Features überlegen - die `for`-Schleife können Sie also nicht
nehmen :-)

Stellen Sie diese Ideen im Praktikum vor und verteidigen Sie diese.

[_syntactic sugar_]: https://en.wikipedia.org/wiki/Syntactic_sugar


---


## Ausblick Wochen 01 bis 04 in 2024

### Umsetzung

Setzen Sie die im Praktikum abgestimmten Features bis zum Vortrag in den letzten
beiden Sitzungen um. Nutzen Sie aktiv die freigewordenen VL-Slots.
(_Wir hatten am Anfang des Semesters absichtlich einige Praktikumstermine mit
Vorlesungen belegt, damit Sie möglichst schnell die Inhalte kennenlernen und
dann die Praktikumsaufgaben entsprechend planen und umsetzen können. Zum
Ausgleich sind nun einige Vorlesungstermine am Ende des Semesters der freien
Arbeit gewidmet._)

### Vortrag

Bereiten Sie Ihren Vortrag zur Vorstellung der Ergebnisse Ihrer freien Aufgabe
(Konzeption und Umsetzung der zusätzlichen Features) in den letzten beiden
Sitzungen vor.



### Aufgabe C++

Hashing in C++ mit den einfachen Sprachmöglichkeiten ... => Prinzip erklären, Ein- und Ausgaben fordern

### Aufgabe CB

Grammatik, Parser, Symboltabelle, Typchecking, Übersetzung nach Java

Zusatzaufgabe für S5: Speicherverwaltung (Pointer, Heap)



### Aufgabe 1: Implementierung eines einfachen Tokenizers (25 Punkte)

Erstellen Sie eine Funktion `void tokenize(const std::string& input, std::vector<std::string>& tokens)`, die einen gegebenen String als Eingabe erhält und diesen in Tokens (Wörter) splittet. Nutzen Sie Referenzen, um die Token-Liste zu aktualisieren. Testen Sie die Funktion mit verschiedenen Eingabestrings und geben Sie die Tokens aus.


### Aufgabe 2: Syntaxanalyse mit Referenzen (30 Punkte)

Implementieren Sie eine einfache Funktion `bool parseExpression(const std::string& expr, int& result)`, die überprüft, ob eine als String dargestellte mathematische Ausdrucksform (z.B. "3 + 4") syntaktisch korrekt ist. Die Funktion soll das Ergebnis der Berechnung zurückgeben. Nutzen Sie Referenzen für den Rückgabewert und testen Sie die Funktion mit verschiedenen mathematischen Ausdrücken.


### Aufgabe 3: Symboltabelle verwalten (35 Punkte)

Definieren Sie eine Struktur `Symbol`, die Informationen wie `name`, `type` und `value` eines Symbols speichert. Implementieren Sie eine Klasse `SymbolTable` mit Methoden zum Hinzufügen und Suchen von Symbolen. Schreiben Sie eine Methode `void updateSymbol(const std::string& name, const int& value)`, die den Wert eines vorhanden Symbols aktualisiert. Testen Sie die Klasse in der `main`-Funktion, indem Sie eine Symboltabelle erstellen und mehrere Symbole hinzufügen und aktualisieren.


### Aufgabe 4: Generierung von Zwischencode (40 Punkte)

Entwickeln Sie eine Funktion `std::string generateIntermediateCode(const std::string& ast)`, die einen gegebenen abstrakten Syntaxbaum (AST) als String erhält und aus diesem einen einfachen Zwischencode erzeugt. Der Zwischencode sollte einfache Anweisungen zur arithmetischen Auswertung bieten. Nutzen Sie Referenzen, um den Zwischencode zurückzugeben, und demonstrieren Sie die Verwendung in der `main`-Funktion.

### Aufgabe 5: |Typüberprüfung und -konvertierung (45 Punkte)

Implementieren Sie eine Funktion `bool typeCheckAndConvert(const std::string& input, int& intValue, double& doubleValue)`, die überprüft, ob ein gegebenes Input-String in einen Integer oder Double konvertiert werden kann. Nutzen Sie Referenzen für die Rückgabe der konvertierten Werte und den Rückgabewert für den Erfolg der Konvertierung. Testen Sie die Funktion in der `main`-Funktion mit verschiedenen Dateneingaben und dokumentieren Sie die Ergebnisse.


**Bonusaufgabe (25 Punkte):**
Entwickeln Sie eine Funktion zur Auswertung von Variablenwerten `void evaluateVariables(const std::map<std::string, int>& variables, const std::string& expression, int& result)`, die eine Map von Variablen und ihren Werten sowie einen Ausdruck erhält. Die Funktion soll den Wert des Ausdrucks mit den gegebenen Variablen auswerten. Nutzen Sie Referenzen für die Rückgabe des Ergebnisses und testen Sie die Funktion in der `main`-Funktion.


