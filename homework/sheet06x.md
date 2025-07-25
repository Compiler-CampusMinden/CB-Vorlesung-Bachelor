---
title: "Blatt 06x: C++ und dyn. Speicherverwaltung (IFM 5.21 CB PO18, 5. Semester)"
author: "Carsten Gips, BC George (HSBI)"
points: "10 Punkte"
---

<!--  pandoc -s -f markdown -t markdown+smart-grid_tables-multiline_tables-simple_tables --columns=94 --reference-links=true  sheet06x.md  -o xxx.md  -->

## Aufgaben

Bearbeiten Sie die auf [Blatt 06] definierten Aufgaben A6.1 (Token, 1P), A6.2 (Tokenizer, 1P),
A6.3 (Reference Counter, 1P) und A6.4 (Smartpointer, 3P).

Statt der Aufgabe A6.5 (Ringpuffer, 4P) bearbeiten Sie bitte die folgende Aufgabe (4P):

In C++ gibt es Pointer und dynamische Speicherverwaltung. Mit Hilfe des Operators `new` kann
Speicher auf dem Heap angefordert werden und man erhält einen Pointer auf den Start des
Bereichs, und mit dem Operator `delete` kann man Speicher wieder freigeben. Mit Hilfe der
Smartpointer wurde diese manuelle Freigabe zu einem gewissen Grad automatisiert.

Bauen Sie die dynamische Speicherverwaltung in Java nach:

1.  Modellieren Sie den Heap als Singleton-Datenstruktur.

    Die Datenstruktur kann eine bestimmte maximale Anzahl von allgemeinen Objekten (per
    `Object`-Referenz) speichern und soll einen indexbasierten Zugriff auf die Speicherplätze
    und damit die Objekte erlauben. Die Datenstruktur muss eine interne Buchführung haben,
    welche der Plätze noch frei sind. Die Datenstruktur muss Methoden analog zu `new` und
    `delete` haben, damit man von außen Platz auf dem simulierten Heap reservieren kann bzw.
    wieder freigeben kann. Bei `new` übergibt man eine `Object`-Referenz und erhält einen
    Pointer zurück, bei `delete` übergibt man einen Pointer.

2.  Modellieren Sie Pointer.

    Dies ist eine Datenstruktur, die auf ein Objekt im simulierten Heap "zeigt", indem sie den
    Index des Objekts in der Heap-Datenstruktur speichert. Beachten Sie, dass Pointer in C++
    typisiert sind (`char*`, `int*`, `Foo*`) und realisieren Sie dies entsprechend. Die
    Datenstruktur soll zusätzlich eine Methode zum "Dereferenzieren" aufweisen, damit man
    direkt auf das verwiesene Objekt zugreifen kann. Dabei muss das Objekt aus dem "Heap"
    geholt werden und von `Object` auf den jeweiligen Typ gecasted und zurückgeliefert werden.

**Hinweis**: Diese Aufgabe ist eine Vorarbeit für das nächste Blatt (Mini-Projekt).

**Hinweis**: Erinnern Sie sich an Generics in Java: `B<E> extends A<E>`, aber NICHT
`C<B> extends C<A>` (mit `B extends A`)! Generics werden hier also nicht helfen. Denkbar wäre
eine Vererbungshierarchie und die Überschreibung des Rückgabetyps der Basismethode für die
Dereferenzierung ([*covariant return type*]) oder ggf. die Modellierung mit Hilfe eines Enums.
Für dieses Blatt können Sie sich auf ein paar Beispiele für konkrete Pointertypen
beschränken - für das Mini-Projekt (nächstes Blatt) werden die nötigen Klassen dann beim
Kompilieren dynamisch durch Ihren eigenen Compiler als Java-Strukturen angelegt.

  [Blatt 06]: sheet06.md
  [*covariant return type*]: https://docs.oracle.com/javase/tutorial/java/javaOO/returnvalue.html
