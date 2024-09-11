---
archetype: lecture-cg
title: "Fortgeschrittene Konzepte in C++"
author: "Carsten Gips (HSBI)"
readings:
  - key: "Aho2023"
    comment: "Kapitel 1 Introduction"
  - key: "Grune2012"
    comment: "Kapitel 1 Introduction"
tldr: |
  TODO
outcomes:
  - k2: "TODO"
youtube:
  - link: "TODO"
    name: "VL Fortgeschrittene Konzepte in C++"
---


## Thema 1: Arrays

- Einführung in Arrays
- Arbeiten mit Arrays und Schleifen: `vec3 foo[10]`
- Mehrdimensionale Arrays
- Verwendung von Standardbibliothekscontainern (z.B. `vector`)


## Thema 2: Referenzen und Pointer

- Einführung in Speicherverwaltung
- Konzept eines Pointers
    - Pointer und Arrays, Pointer-Arithmetik
    - Speicherverwaltung (`new`, `delete`)
- Konzept einer Referenz
- Copy-Semantik: Call-by-Value vs. Call-by-Reference
    - `bar  foo(wuppie&,  bar)` (ja)
    - `bar& foo(fluppie*, bar)` (eher nicht)
- Arbeiten mit Pointern und Referenzen


## Thema 3: Klassen und Objekte

- Definition von Klassen und Objekten in C++ und Structs
- Konstruktoren und Destruktoren
- Zuweisung (nur Verwendung, nicht Definition)
- Einsatz von (Mathe-) Operatoren für Klassen/Objekte => `a * b` ist wie `a.mult(b)`


## Thema 4: Vererbung und Polymorphismus

- Vererbung in C++: Einfache und Mehrfachvererbung
- Polymorphismus und virtuelle Funktionen
- Abstrakte Klassen und reine virtuelle Funktionen


## Wrap-Up

TODO







<!-- DO NOT REMOVE - THIS IS A LAST SLIDE TO INDICATE THE LICENSE AND POSSIBLE EXCEPTIONS (IMAGES, ...). -->
::: slides
## LICENSE
![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)

Unless otherwise noted, this work is licensed under CC BY-SA 4.0.
:::
