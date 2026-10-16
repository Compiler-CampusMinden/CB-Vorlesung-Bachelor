---
author: Carsten Gips (HSBI)
no_beamer: true
title: "Blatt 03: C-int"
---

# (\*) Subtraktion für L-Int

In der Vorlesung haben Sie L-Int als kleine Lisp-artige Sprache mit Integer-Literalen, Addition und
Subtraktion kennengelernt. Demonstriert wurde aber nur die Verarbeitung von Integern und Addition.
In dieser Aufgabe legen Sie sich ein Java-Projekt an, in dem Sie den Code aus der Vorlesung über das
Semester hinweg verfolgen und immer wieder ergänzen können. Heute ergänzen Sie die in der Vorlesung
gezeigte Pipeline um die Subtraktion.

## Spezifikation und Beispiele

Legen Sie zunächst eine kurze Spezifikation für die Subtraktion in L-Int fest. Klären Sie gemeinsam in der Übung:

1. Welche Eingaben sind gültige L-Int-Ausdrücke?
2. Wie werden mehrere Operanden einer Addition oder Subtraktion gruppiert?
3. Welche Werte ergeben die folgenden Ausdrücke?

    ```clojure
    (+ 1 2)
    (- 8 3)
    (- 20 5 3)
    (- 10 (+ 3 5))
    ```

Notieren Sie außerdem mindestens zwei ungültige Eingaben. Mindestens eine davon soll eine Operation
mit weniger als zwei Operanden sein.

## L-Int-Pipeline erweitern

Legen Sie sich ein Java-Projekt an und ziehen sie die in der Vorlesung gezeigten Bausteine in Ihr Projekt.
Fügen Sie nun die nötigen Ergänzungen für die Subtraktion hinzu.

## Tests und Abnahmekriterien

Schreiben Sie JUnit-Tests. Prüfen Sie dabei mindestens:

* ein Integer-Literal,
* eine (zweistellige) Addition,
* eine (zweistellige) Subtraktion,
* einen geschachtelten Ausdruck,
* eine mehrstellige Addition mit Linksassoziativität,
* eine mehrstellige Subtraktion mit Linksassoziativität,
* mindestens eine ungültige Eingabe.

Ein weiterer Test soll aufdecken, ob bei der Subtraktion versehentlich linker und rechter Operand vertauscht wurden. Testen Sie daher beispielsweise sowohl `(- 7 2)` als auch `(- 2 7)`.

Abnahmekriterien:

* Gültige Ausdrücke werden in einen passenden AST übersetzt.
* Mehrstellige Operationen werden entsprechend der festgelegten Linksassoziativität aufgebaut.
* Operationen mit weniger als zwei Operanden werden abgelehnt.
* Der Interpreter berechnet die erwarteten Werte.
* Die Tests decken die genannten Fälle ab.


# (\*) Interpreter für L-Int mit Visitor-Pattern

In der Vorlesung wurde die `eval()`-Funktion im Interpreter für L-Int mit Pattern Matching und `switch`-Expressions aufgebaut.

Wie sieht das Äquivalent unter Benutzung des Visitor-Patterns aus? Diskutieren Sie die Strukturen und nötigen Änderungen/Erweiterungen
und implementieren Sie dieses in Java. Geben Sie ein Beispiel an, wie Sie den neuen Visitor aufrufen würden.

<!--
- Interface `ExprVisitor` mit `visit()`-Methode pro AST-Knoten, Rückgabe `Value`: `return e.lhs.accept(this) + e.rhs.accept(this)`
- AST ergänzen: `accept(ExprVisitor v)`-Methoden mit `v.visit(this)`
- `eval(Expr e)` mit `e.accept(v)`

vgl. https://github.com/Programmiermethoden-CampusMinden/Prog2-Lecture/blob/master/lecture/pattern/visitor.md
-->


# (\*) C++ ausprobieren: Compiler und ein erstes Programm

Wir werden in dieser Veranstaltung gemeinsam schrittweise C++ lernen und einen Interpreter in Java für (einen stark eingeschränkten Teil von) C++ schreiben.

In dieser Aufgabe schreiben und übersetzen Sie kleine native C++-Programme. Hier geht es zunächst nicht um einen Interpreter, sondern darum, ein C++-Programm mit einem Compiler auszuführen.


## Compiler überprüfen und installieren

Prüfen Sie in einem Terminal, ob ein C++-Compiler auf Ihrem System verfügbar ist:

```
clang++ --version
g++ --version
```

Falls kein Compiler gefunden wird:

* Unter macOS können Sie clang++ üblicherweise über die Xcode Command Line Tools installieren.
* Unter Linux können Sie clang++ oder g++ über die Paketverwaltung Ihrer Distribution installieren.
* Unter Windows verwenden Sie zum Beispiel WSL oder eine anderweitig installierte C++-Toolchain.

*Anmerkung*: Für C++ verwenden Sie clang++ beziehungsweise g++, nicht clang beziehungsweise gcc. D.h. "gcc" meint in diesem Kontext "g++", "clang" meint tatsächlich "clang++". Normalerweise sind bei der Installation von gcc und clang automatisch beide Versionen (C und C++) dabei.


## Erstes Programm übersetzen und ausführen

Speichern Sie das folgende Programm als `hello.cpp`:

```cpp
#include <iostream>

int main() {
    int result = ((1 + 2) - 3);
    std::cout << result << '\n';
    return 0;
}
```


Übersetzen und starten Sie das Programm mit clang++:

```
clang++ -std=c++20 -Wall -Wextra -Wpedantic hello.cpp -o hello
./hello
```

Oder verwenden Sie g++:

```
g++ -std=c++20 -Wall -Wextra -Wpedantic hello.cpp -o hello
./hello
```

Unter Windows kann die ausführbare Datei hello.exe heißen. In PowerShell starten Sie sie beispielsweise mit:

```
.\hello.exe
```

Ändern Sie den Ausdruck in result und überprüfen Sie die Ausgabe für mindestens drei Beispiele.

## Erklärung des Programms

Für dieses Blatt benötigen Sie zunächst nur wenige C++-Konstrukte:


| Zweck                    | C++-Schreibweise               |
|:-------------------------|:-------------------------------|
| Integer-Variable anlegen | `int result = 42;`             |
| Addition                 | `1 + 2`                        |
| Subtraktion              | `7 - 2`                        |
| Klammerung               | `(1 + 2)`                      |
| Ausgabe einer Variablen  | `std::cout << result << '\n';` |
| Zeilenkommentar          | `// Kommentar`                 |

Ein L-Int-Ausdruck wie `(- (+ 1 2) 3)` lässt sich in C++-Schreibweise beispielsweise so darstellen:

```
((1 + 2) - 3)
(1 + 2) - 3
1 + 2 - 3
```







# (\*\*) C-Int: Addition und Subtraktion für Integer in C++

Wir legen in dieser Aufgabe die Basis für den Mini-C++-Interpreter, den wir
schrittweise über das Semester hinweg aufbauen.

::: tip
## In C++ sieht es so aus ...

Unsere Basisstufe C-Int soll analog zu L-Int Ausdrücke mit Integer-Literalen, Addition und Subtraktion erlauben. Dabei nutzen wir in C-Int die üblichere *infix* Notation:

```
2          // 2

1+2        // 3
(1+2)      // 3

1+2+3      // 6
(1+2)+3    // 6
((1+2)+3)  // 6
```

C++ erlaubt diese Ausdrücke ebenfalls. Allerdings bilden sie in C++ kein vollständiges Programm, man muss sie in ein `main()` und ein Statement wie beispielsweise
eine Zuweisung an eine Variable oder eine Ausgabe verpacken.

:::


## Java-Projekt einrichten

Legen Sie sich ein Java-Projekt für diese Aufgabe an. Nutzen Sie am besten Maven oder
Gradle für die Konfiguration.

Wenn Sie möchten, können Sie dazu eines der folgenden Templates klonen und damit starten:

- Gradle: https://github.com/Compiler-CampusMinden/student-support-code-template
- Maven: https://github.com/Compiler-CampusMinden/student-support-code-template-maven


## Konkrete Syntax für C-Int

Definieren Sie analog zur Vorlesung die konkrete Syntax für C-Int. Damit definieren Sie, welche Programme von Ihrem Lexer und Parser akzeptiert werden.

Whitespace darf zwischen den Bestandteilen eines Ausdrucks stehen. Zusätzlich sollen Sie C++-Zeilenkommentare der Form `// ...` bis zum Zeilenende unterstützen. Addition und Subtraktion haben immer zwei Operanden. Ausdrücke dürfen geklammert sein; nicht geklammerte Ausdrücke sind implizit von links nach rechts geklammert.

Beispiele für gültige C-Int-Ausdrücke:

```
42
1 + 2
(1 + 2)
1 + 2 - 3
((1 + 2) - 3)
(10 - (3 + 5))
```

Beispiele für Eingaben, die von dieser Grammatik nicht akzeptiert werden sollen:

```
(1 + 2
1 * 2
```


Besprechen Sie in der Übung:
* Welche konkreten Eingaben lässt die Grammatik zu?
* Welche Teile gehören zur konkreten Syntax?
* Welche Informationen müssen im AST erhalten bleiben?
* Warum müssen Klammern im AST nicht unbedingt als eigene Knoten vorkommen?


## Abstrakte Syntax für C-Int

Definieren Sie analog zur Vorlesung die abstrakte Syntax für C-Int. Damit legen Sie das Format für den AST von C-Int fest.


## Pipeline für C-Int

Erstellen Sie nun analog zur Vorlesung für C-Int passend

- eine Tokendefinition,
- AST-Klassen und -Interfaces,
- einen Lexer,
- einen RD-Parser,
- einen Interpreter.

Nutzen Sie am besten ein gemeinsames Package für diese Klassen.

Ihre Implementierung soll:

* Integer-Literale sowie `(`, `)`, `+` und `-` erkennen,
* Whitespace und Zeilenkommentare überspringen,
* am Ende ein EOF-Token erzeugen,
* für gültige Eingaben einen passenden AST aufbauen,
* nach dem vollständigen Ausdruck prüfen, dass keine weiteren Token folgen,
* gültige ASTs korrekt auswerten.

Verwenden Sie für den Parser auf diesem Blatt keinen generierten ANTLR-Parser. Implementieren Sie ihn wie in der Vorlesung von Hand.

## Tests und Abnahmekriterien

Schreiben Sie JUnit-Tests für die C-Int-Pipeline. Prüfen Sie mindestens:

* ein Integer-Literal,
* eine Addition,
* eine Subtraktion,
* einen geschachtelten Ausdruck,
* Whitespace an unterschiedlichen Stellen,
* ein zusätzliches Token nach einem vollständigen Ausdruck,
* eine fehlende schließende Klammer,
* einen ungültigen Operator oder ein unerwartetes Zeichen.

Testen Sie nach Möglichkeit nicht nur die Auswertung, sondern auch die erzeugten Token und ASTs. Dadurch können Sie Fehler in den einzelnen Phasen der Pipeline besser voneinander unterscheiden.

Abnahmekriterien:

* Gültige C-Int-Ausdrücke werden vollständig erkannt und geparst.
* Der erzeugte AST repräsentiert die Operationen und Operanden korrekt.
* Der Interpreter berechnet die erwarteten Werte.
* Ungültige oder nicht vollständig konsumierte Eingaben werden abgelehnt.
* Ihre Tests decken die genannten Fälle ab.

## C-Int-Ergebnisse mit nativem C++ vergleichen

Schreiben Sie für die folgenden Ausdrücke jeweils ein vollständiges C++-Programm mit `main()`, das den Ausdruck berechnet und das Ergebnis ausgibt:

```
42
(1 + 2)
((1 + 2) - 3)
(10 - (3 + 5))
```

Übersetzen und starten Sie Ihre Programme mit clang++ oder g++. Vergleichen Sie die Ausgaben mit den Ergebnissen Ihres C-Int-Interpreters.
Notieren Sie anschließend:

1. Zwei Gemeinsamkeiten zwischen der Auswertung im nativen C++-Programm und der Auswertung durch Ihren Interpreter.
2. Zwei Unterschiede zwischen den beiden Verarbeitungswegen.





# (\*\*) Bäume (Wiederholung)

Sie finden in einer Codebasis diese Java-Strukturen:

```java
public sealed interface Expr permits Num, Add, Parens {}

public record Num(int value) implements Expr {}
public record Add(Expr left, Expr right) implements Expr {}
public record Parens(Expr inner) implements Expr {}
```

1. Welche Strukuren lassen sich mit diesen Klassen/Interfaces bilden? Geben Sie ein konkretes Beispiel an.
2. Implementieren Sie eine Methode, die eine Struktur vom Typ `Expr` als Argument erhält und darauf rekursiv Vereinfachungen durchführt:
    - `(x)` liefert `x`
    - `x+0` liefert `x`
    - `0+x` liefert `x`

    Erstellen Sie zwei Varianten:

    1. Einsatz des Visitor-Patterns
    2. Einsatz von manueller Traversierung mit `switch`-Expressions und Pattern Matching



---

# Zeitbudget als Orientierung

* L-Int-Spezifikation, Implementierung und Tests: etwa 2-2,5 Stunden
* C++-Compiler einrichten und erste Programme ausführen: etwa 0,5 Stunden
* C-Int-Grammatik, AST, Implementierung und Tests: etwa 2,5-3 Stunden
* Vergleich, Fehlersuche: etwa 0,5–1 Stunde

Die genannten Zeiten sind Richtwerte. Wenn der Compiler oder das Build-System Probleme macht, notieren Sie die Fehlermeldung und Ihre bisherigen Schritte, statt unverhältnismäßig viel Zeit mit der Umgebungssuche zu verbringen.
