---
archetype: assignment
title: "Blatt 06x: Lisp in Lisp (IFM 5.21 CB PO18, 5. Semester)"
author: "Carsten Gips, BC George (HSBI)"
points: "10 Punkte"

hidden: true
---

<!--  pandoc -s -f markdown -t markdown+smart-grid_tables-multiline_tables-simple_tables --columns=94 --reference-links=true  sheet06x.md  -o xxx.md  -->

## Zusammenfassung

Auf [Blatt 05](sheet05x.md) haben Sie einen Interpreter für einen Mini-Lisp-Dialekt implementiert. Dabei war die Implementierungssprache Java, der Lexer und Parser wurden mit ANTLR erzeugt.

Mit einigen kleinen Erweiterungen kann man nun in diesem Mini-Lisp-Dialekt einen Interpreter für Mini-Lisp schreiben. Dieser neue Interpreter für Mini-Lisp ist also in Mini-Lisp geschrieben und läuft im in Java programmierten Interpreter von [Blatt 05](sheet05x.md). Wenn man es richtig anstellt, kann man in diesen neuen Interpreter sogar in sich selbst ausführen lassen - wir haben einen sogenannten ["metazirkulären Interpreter"](https://en.wikipedia.org/wiki/Meta-circular_evaluator).

## Methodik

In unserem Mini-Lisp können wir bereits mit Variablen, Funktionen und Kontrollstrukturen umgehen sowie einfache Listen erzeugen.

Die im Interpreter benötigten Tabellen (Symboltabellen, Environments/Memoryblocks) können wir als Listen über Listen anlegen. Dabei wird für die in der Hauptliste gespeicherten Elementlisten jeweils eine bestimmte Reihenfolge der Elemente vereinbart, beispielsweise ist der erste Eintrag der Name und der zweite Eintrag ein Wert o.ä.:

```python
# Formulierung der Environments in Java (hier Pseudocode)
class Environment:
    Map<String, Object> values;
    Environment enclosing;
```

```clojure
(def environment
    (list
        (list "foo", foo)
        (list "bar", bar)
        (list "wuppie", 3)
        (list "fluppie", 4)
    )
)
```

Für den Interpreter benötigen wir entsprechend noch etwas umfangreichere Operationen auf Listen, um beispielsweise auf das erste Element des Rests einer Liste o.ä. zugreifen zu können oder um Elemente an Listen anfügen zu können.

Zusätzlich benötigen wir noch ein syntaktisches Element `quote`, mit dem die sofortige Auswertung von S-Expressions allgemein verhindert wird. Normalerweise würde `(list 2 (+ 1 1))` als `(2 2)` weiter verarbeitet - wenn der hintere Ausdruck erhalten bleiben soll, muss die Auswertung verhindert werden. Dies kann man mit *Quoting* erreichen: `(list 2 '(+ 1 1))` würde wie gewünscht `(2 (+ 1 1))` ergeben (das "`'`" ist dabei der Quoting-Operator).



## Aufgaben

### A6.1: TODO (1P)

TODO

### A6.2: TODO (1P)

TODO

### A6.3: TODO (1P)

TODO

### A6.4: TODO (3P)

TODO

### A6.5: TODO (4P)

TODO
