---
author: Carsten Gips (HSBI)
no_beamer: true
title: "Blatt 03: C-Int"
---

::: important
Für die erfolgreiche Bearbeitung dieses Übungsblattes müssen mindestens alle mit `*`
und `**` markierten Aufgaben gelöst werden.
:::

# (\*) Java-Projekt für L-Int einrichten

Legen Sie sich ein Java-Projekt für L-Int an. Nutzen Sie am besten Maven oder Gradle
für die Konfiguration. Dieses Projekt werden Sie im Laufe des Semesters immer wieder
erweitern.

Wenn Sie möchten, können Sie dazu eines der folgenden Templates als Basis benutzen:

-   Gradle: https://github.com/Compiler-CampusMinden/student-support-code-template
-   Maven:
    https://github.com/Compiler-CampusMinden/student-support-code-template-maven

Legen Sie die in der Vorlesung gezeigten Bausteine für L-Int in Ihrem Projekt an,
übernehmen Sie die gezeigte Funktionalität und machen Sie das Projekt kompilierbar.
Fehlende Funktionalität wird in den folgenden Aufgaben nachgereicht.

# (\*\*) L-Int Lexer: Funktion `skipIrrelevant()`

Wir haben in der Vorlesung die Funktion `skipIrrelevant()` gesehen, mit der nicht
benötigte Zeichen wie Whitespace und Kommentare übersprungen werden sollen und die
immer zu Beginn von `nextToken()` aufgerufen wird:

``` java
protected boolean skipIrrelevant() {}  // Homework
```

1.  Wie könnte diese Methode aussehen? Geben Sie eine Implementierung in Java an.
2.  Diskutieren Sie in der Gruppe, mit welchen Fällen Sie Ihre Implementierung
    testen könnten und notieren Sie diese für später.

# (\*) Subtraktion für L-Int

In der Vorlesung haben Sie L-Int als kleine Lisp-artige Sprache mit
Integer-Literalen, Addition und Subtraktion kennengelernt. Demonstriert wurde aber
nur die Verarbeitung von Integern und Addition.

1.  Klären Sie gemeinsam in der Übung:

    -   Welche Eingaben sind gültige L-Int-Ausdrücke?

    -   Wie werden mehrere Operanden einer Addition oder Subtraktion gruppiert?

    -   Welche Werte ergeben die folgenden Ausdrücke?

        ``` clojure
        (+ 1 2)
        (- 8 3)
        (- 20 5 3)
        (- 10 (+ 3 5))
        ```

2.  Notieren Sie außerdem mindestens zwei ungültige Eingaben. Mindestens eine davon
    soll eine Operation mit weniger als zwei Operanden sein.

3.  Ergänzen Sie nun die in der Vorlesung gezeigte Pipeline um die Subtraktion.

# (\*\*) Tests für L-Int

Schreiben Sie JUnit-Tests für L-Int. Prüfen Sie dabei mindestens:

-   ein Integer-Literal,
-   eine (zweistellige) Addition,
-   eine (zweistellige) Subtraktion,
-   einen geschachtelten Ausdruck,
-   eine mehrstellige Addition mit Linksassoziativität,
-   eine mehrstellige Subtraktion mit Linksassoziativität,
-   mindestens eine ungültige Eingabe.

Ein weiterer Test soll aufdecken, ob bei der Subtraktion versehentlich linker und
rechter Operand vertauscht wurden. Testen Sie daher beispielsweise sowohl `(- 7 2)`
als auch `(- 2 7)`.

Testen Sie nach Möglichkeit nicht nur die Auswertung, sondern auch die erzeugten
Token und ASTs. Dadurch können Sie Fehler in den einzelnen Phasen der Pipeline
besser voneinander unterscheiden.

# (\*) C++ ausprobieren: Compiler und ein erstes Programm

Wir werden in dieser Veranstaltung gemeinsam schrittweise C++ lernen und einen
Interpreter in Java für (einen stark eingeschränkten Teil von) C++ schreiben.

In dieser Aufgabe schreiben und übersetzen Sie zunächst kleine C++-Programme mit
einem "echten" Compiler. Hier geht es zunächst nicht um einen selbst geschriebenen
Interpreter, sondern darum, ein C++-Programm mit einem Compiler zu übersetzen und
das Ergebnis nativ auszuführen. Auf diese Weise haben Sie später eine Referenz für
die Ergebnisse aus Ihrem eigenen Interpreter ...

## Schritt 1: Compiler überprüfen und installieren

Prüfen Sie in einem Terminal, ob ein C++-Compiler auf Ihrem System verfügbar ist:

    clang++ --version
    g++ --version

Falls kein Compiler gefunden wird:

-   Unter macOS können Sie clang++ üblicherweise über die Xcode Command Line Tools
    installieren.
-   Unter Linux können Sie clang++ oder g++ über die Paketverwaltung Ihrer
    Distribution installieren.
-   Unter Windows verwenden Sie zum Beispiel WSL oder eine anderweitig installierte
    C++-Toolchain.

::: tip
*Anmerkung*: Für C++ verwenden wir clang++ beziehungsweise g++, nicht clang
beziehungsweise gcc. D.h. "gcc" meint in diesem Kontext "g++", "clang" meint
tatsächlich "clang++". Normalerweise sind bei der Installation von gcc und clang
automatisch beide Versionen (C und C++) dabei.
:::

## Schritt 2: Erstes Programm übersetzen und ausführen

Speichern Sie das folgende Programm als `hello.cpp`:

``` cpp
#include <iostream>

int main() {
    int result = ((1 + 2) - 3);
    std::cout << "hello world: ";
    std::cout << result << '\n';
    return 0;
}
```

Übersetzen und starten Sie das Programm mit clang++:

    clang++ hello.cpp -o hello
    ./hello

Oder verwenden Sie g++:

    g++ hello.cpp -o hello
    ./hello

Unter Windows kann die ausführbare Datei `hello.exe` heißen. In PowerShell starten
Sie sie beispielsweise mit:

    .\hello.exe

Ändern Sie den arithmetischen Ausdruck in `result` und überprüfen Sie die Ausgabe
für mindestens drei Beispiele.

::: tip
## Erklärung des Programms

Für dieses Blatt benötigen Sie zunächst nur wenige C++-Konstrukte:

| Zweck | C++-Schreibweise | Java-Schreibweise | L-Int | C-Int |
|:------------------|:----------------------|:----------------|-------------|-------------|
| Integer-Variable anlegen | `int result = 42;` | `int result = 42;` | n.a. | n.a. |
| Addition | `1 + 2` | `1 + 2` | `(+ 1 2)` | `1 + 2` |
| Subtraktion | `7 - 2` | `7 - 2` | `(- 7 2)` | `7 - 2` |
| Klammerung | `(1 + 2)` | `(1 + 2)` | `(+ 1 2)` | `(1 + 2)` |
| Ausgabe einer Variablen | `std::cout << result << '\n';` | `IO.println(result)` | n.a. | n.a. |
| Zeilenkommentar | `// Kommentar` | `// Kommentar` | `;; Kommentar` | `// Kommentar` |
| Import Bibliotheken | `#include <iostream>` | `import ...;` | n.a. | n.a. |
:::

# (\*\*) C-Int: Addition und Subtraktion für Integer in C++

Wir legen in dieser Aufgabe die Basis für den Mini-C++-Interpreter, den wir
schrittweise über das Semester hinweg aufbauen.

::: important
## Waschzettel: In C++ sieht es so aus ...

Unsere Basisstufe **C-Int** soll analog zu L-Int **Ausdrücke mit Integer-Literalen,
Addition und Subtraktion** erlauben. Dabei nutzen wir in C-Int die in C++ übliche
*infix* Notation:

    2          // => 2

    1+2        // => 3
    (1+2)      // => 3

    1+2+3      // => 6
    (1+2)+3    // => 6
    ((1+2)+3)  // => 6

Ein L-Int-Ausdruck wie `(- (+ 1 2) 3)` lässt sich in C++- bzw. C-Int-Schreibweise
beispielsweise so darstellen:

    ((1 + 2) - 3)
    (1 + 2) - 3
    1 + 2 - 3

In C++ bilden diese Ausdrücke allerdings noch kein vollständiges Programm. Man
benötigt eine `main()`-Funktion als Rahmen und Einsprungspunkt für das Programm und
muss Ausdrücke in ein Statement wie beispielsweise eine Zuweisung an eine Variable
oder eine Ausgabe verpacken.
:::

## Schritt 1: Java-Projekt einrichten

Legen Sie sich ein neues Java-Projekt für Ihren C-Int-Interpreter an (vgl. erste
Aufgabe "Java-Projekt für L-Int). Auch dieses Projekt werden Sie das Semester über
immer wieder erweitern und ergänzen.

## Schritt 2: Konkrete Syntax für C-Int

Definieren Sie analog zur Vorlesung die **konkrete Syntax für C-Int**. Damit
definieren Sie, welche Programme von Ihrem Lexer und Parser akzeptiert werden.

Whitespace darf zwischen den Bestandteilen eines Ausdrucks stehen und soll
übersprungen werden. Zusätzlich sollen Sie C++-Zeilenkommentare der Form `// ...`
bis zum Zeilenende unterstützen und überspringen. Addition und Subtraktion haben
immer zwei Integer-Operanden (`1-2`), dabei können mehrere Operationen verkettet
werden (`1+2+3+4`). Ausdrücke dürfen geklammert sein; nicht geklammerte Ausdrücke
sind in C-Int implizit von links nach rechts geklammert.

Besprechen Sie gemeinsam in der Übung:

-   Welche konkreten Eingaben soll die Grammatik zulassen, welche nicht?
-   Welche Teile gehören zur konkreten Syntax?

## Schritt 3: Abstrakte Syntax für C-Int

Definieren Sie analog zur Vorlesung die **abstrakte Syntax für C-Int**. Damit legen
Sie das Format für den AST von C-Int fest.

Diskutieren Sie gemeinsam in der Übung:

-   Welche Informationen aus dem Parse-Tree müssen im AST erhalten bleiben?
-   Warum müssen Klammern im AST nicht unbedingt als eigene Knoten vorkommen?

## Schritt 4: Interpreter-Pipeline für C-Int

Erstellen Sie nun analog zur Vorlesung für C-Int passend zu Ihrer konkreten und
abstrakten Grammatik:

-   eine Tokendefinition,
-   AST-Klassen und -Interfaces,
-   einen Lexer,
-   einen RD-Parser,
-   einen Interpreter.

Nutzen Sie am besten ein gemeinsames Package `cint` für diese Klassen.

Verwenden Sie für den Parser auf diesem Blatt keinen generierten ANTLR-Parser.
Implementieren Sie ihn wie in der Vorlesung von Hand.

## Schritt 5: Tests für C-Int

Schreiben Sie JUnit-Tests für die C-Int-Pipeline. Prüfen Sie mindestens:

-   ein Integer-Literal,
-   eine Addition,
-   eine Subtraktion,
-   einen geschachtelten Ausdruck,
-   Whitespace an unterschiedlichen Stellen,
-   ein zusätzliches Token nach einem vollständigen Ausdruck,
-   eine fehlende schließende Klammer,
-   einen ungültigen Operator oder ein unerwartetes Zeichen.

Testen Sie nach Möglichkeit nicht nur die Auswertung, sondern auch die erzeugten
Token und ASTs. Dadurch können Sie Fehler in den einzelnen Phasen der Pipeline
besser voneinander unterscheiden.

## Schritt 6: C-Int-Ergebnisse mit nativem C++ vergleichen

Schreiben Sie für die folgenden Ausdrücke jeweils ein vollständiges C++-Programm mit
`main()`, das den Ausdruck berechnet und das Ergebnis ausgibt:

    42
    (1 + 2)
    ((1 + 2) - 3)
    (10 - (3 + 5))

Übersetzen und starten Sie Ihre Programme mit clang++ oder g++. Vergleichen Sie die
Ausgaben mit den Ergebnissen Ihres C-Int-Interpreters. Notieren Sie anschließend:

1.  Zwei Gemeinsamkeiten zwischen der Auswertung im nativen C++-Programm und der
    Auswertung durch Ihren Interpreter.
2.  Zwei Unterschiede zwischen den beiden Verarbeitungswegen.

# (\*\*\*) Interpreter für L-Int mit Visitor-Pattern

In der Vorlesung wurde die `eval()`-Funktion im Interpreter für L-Int mit Pattern
Matching und `switch`-Expressions aufgebaut.

Wie sieht das Äquivalent unter Benutzung des Visitor-Patterns aus? Diskutieren Sie
die Strukturen und nötigen Änderungen/Erweiterungen und implementieren Sie dieses in
Java. Geben Sie ein Beispiel an, wie Sie den neuen Visitor aufrufen würden.

<!--
- Interface `ExprVisitor` mit `visit()`-Methode pro AST-Knoten, Rückgabe `Value`: `return e.lhs.accept(this) + e.rhs.accept(this)`
- AST ergänzen: `accept(ExprVisitor v)`-Methoden mit `v.visit(this)`
- `eval(Expr e)` mit `e.accept(v)`

vgl. https://github.com/Programmiermethoden-CampusMinden/Prog2-Lecture/blob/master/lecture/pattern/visitor.md
-->
