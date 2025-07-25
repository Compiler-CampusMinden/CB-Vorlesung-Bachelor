---
title: "Blatt 05x: Interpreter (IFM 5.21 CB PO18, 5. Semester)"
author: "Carsten Gips, BC George (HSBI)"
points: "10 Punkte"
---

<!--  pandoc -s -f markdown -t markdown+smart-grid_tables-multiline_tables-simple_tables --columns=94 --reference-links=true  sheet05x.md  -o xxx.md  -->

# Aufgaben

Betrachten Sie die auf [Blatt 05] definierte Sprache.

Ergänzen Sie diese Sprache um passende syntaktische Strukturen, mit denen man die aus anderen
Sprachen bekannten `for`- und `while`-Schleifen formulieren kann. Bleiben Sie dabei so nah an
der Lisp-artigen Sprache wie möglich! Lösen Sie diese Strukturen nach dem Parsen als
"*syntactic sugar*" auf und transformieren Sie diese geeignet in einen rekursiven Aufruf einer
(beim Traversieren jeweils neu generierten) Hilfsfunktion.

Lösen Sie mit dieser erweiterten Sprachdefinition die auf [Blatt 05] gestellten Aufgaben.

  [Blatt 05]: sheet05.md
