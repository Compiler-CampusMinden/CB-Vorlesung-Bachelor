---
archetype: assignment
title: "Meilenstein 01: Grammatik, ANTLR, AST (Mini-Python)"
author: "BC George, Carsten Gips (FH Bielefeld)"
weight: 1

hidden: true

sketch: true
---


## A1.1: Grammatik

Modifizieren Sie die Grammatik für [**Small C**](https://medium.com/\@efutch/a-small-c-language-definition-for-teaching-compiler-design-b70198531a2f)
folgendermaßen:

1.  Entfernen Sie folgende Elemente:
    *   die `for`-Schleife
    *   das `break`-Statement
    *   die Zufallszahlengenerierung mit `?n`
    *   die Zuweisungsoperatoren `+=`, `-=`, `*=` und `/=`
    *   die Modulo-Operation `%`
    *   den "Elvis"-Operator `?:` (ternäre Abfrage)
    *   die Auto-Inkrement-/-Dekrement-Operatoren `++` und `--`


2.  Bestimmen Sie die terminalen Symbole Ihrer Grammatik und deren Aufbau.


3.  Erklären Sie, wo in der Grammatik das Konzept der Zuweisung auftaucht und welche Auswirkungen
    dies auf die erlaubten Programme hat.



## A1.2: Erweiterung der Grammatik: Funktionen

Erweitern Sie die Grammatik von Blatt 01 um die Möglichkeit, Funktionen definieren und aufrufen zu
können. Funktionen sollen (wie in C) nicht innerhalb von Funktionen definiert werden können.
Globale Variablen sollen ebenfalls zwischen den Funktionsdefinitionen/-aufrufen definiert werden
können.

Hinweis: Sogenannte Vorwärtsdeklarationen sind nicht nötig.


## A1.3: Grammatik und Parser-Generatoren

Erzeugen Sie mithilfe der Grammatik und ANTLR einen Scanner und Parser, den Sie für die folgenden
Aufgaben nutzen.
