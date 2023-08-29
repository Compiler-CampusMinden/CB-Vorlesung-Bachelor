---
archetype: "home"
title: "CB W22 B.Sc."
---


# IFM 5.21: Compilerbau (Winter 2022/23)

## Kursbeschreibung

![](admin/images/architektur_cb.png){width="80%"}

Der Compiler ist das wichtigste Werkzeug in der Informatik. In der Königsdisziplin der
Informatik schließt sich der Kreis, hier kommen die unterschiedlichen Algorithmen und
Datenstrukturen und Programmiersprachenkonzepte zur Anwendung.

In diesem Modul geht es um ein grundlegendes Verständnis für die wichtigsten Konzepte
im Compilerbau. Wir schauen uns dazu relevante aktuelle Tools und Frameworks an und
setzen diese bei der Erstellung eines kleinen Compiler-Frontends für [_Mini-Python_] ein.

[_Mini-Python_]: https://github.com/Compiler-CampusMinden/Mini-Python-Builder


## Überblick Modulinhalte

1.  Lexikalische Analyse: Scanner/Lexer
    *   Reguläre Ausdrücke
    *   Manuelle Implementierung, Generierung mit ANTLR

2.  Syntaxanalyse: Parser
    *   Kontextfreie Grammatiken (CFG)
    *   LL-Parser (Top-Down-Parser)
    *   Generierung mit ANTLR
    *   Error Recovery

3.  Symboltabellen
    *   Berücksichtigung unterschiedlicher Sprachparadigmen
    *   Typen, Klassen, Polymorphie
    *   Namen und Scopes

4.  Semantische Analyse
    *   Attributierte Grammatiken

5.  Zwischencode: Intermediate Representation (IR), LLVM

6.  Interpreter
    *   AST-Traversierung
    *   Read-Eval-Schleife


## Team

-   [BC George](https://www.hsbi.de/minden/ueber-uns/personenverzeichnis/birgit-christina-george)
-   [Carsten Gips](https://www.hsbi.de/minden/ueber-uns/personenverzeichnis/carsten-gips)


## Kursformat

| Vorlesung (2 SWS)     | Praktikum (2 SWS)     |
|:----------------------|:----------------------|
| Mi, 08:00 - 09:30 Uhr | Mi, 15:45 - 17:15 Uhr |
| online/C1             | online/C1             |

Durchführung als **Flipped Classroom/online** (Carsten) bzw. **Hybrid-Vorlesung** (BC):
Sitzungen per Zoom (**Zugangsdaten siehe [ILIAS]**)

[ILIAS]: https://www.hsbi.de/elearning/goto.php?target=crs_1091711&client_id=FH-Bielefeld

### Prüfungsform, Note und Credits

**Projektarbeit**, 5 ECTS

-   **Vortrag I**: Umsetzung von objektorientierten Konzepten in Grammatik,
    Symboltabelle und Interpreter, 30 Minuten Dauer
-   **Vortrag II**: Vorstellung der Projektergebnisse, 30 Minuten Dauer

**Gesamtnote: 35% Vortrag I plus 65% Vortrag II**


## Materialien

### Literatur

1.  "**Compiler: Prinzipien, Techniken und Werkzeuge**".
    Aho, A. V. und Lam, M. S. und Sethi, R. und Ullman, J. D., Pearson Studium, 2008.
    ISBN [978-3-8273-7097-6](https://fhb-bielefeld.digibib.net/openurl?isbn=978-3-8273-7097-6).

2.  ["**Crafting Interpreters**"](https://github.com/munificent/craftinginterpreters).
    Nystrom, R., Genever Benning, 2021.
    ISBN [978-0-9905829-3-9](https://fhb-bielefeld.digibib.net/openurl?isbn=978-0-9905829-3-9).

3.  "Introduction to Compiler Design".
    Mogensen, T., Springer, 2017.
    ISBN [978-3-319-66966-3](https://fhb-bielefeld.digibib.net/openurl?isbn=978-3-319-66966-3).
    DOI [10.1007/978-3-319-66966-3](https://doi.org/10.1007/978-3-319-66966-3).

4.  "The Definitive ANTLR 4 Reference".
    Parr, T., Pragmatic Bookshelf, 2014. ISBN [978-1-9343-5699-9](https://fhb-bielefeld.digibib.net/openurl?isbn=978-1-9343-5699-9).

### Tools

*   [github.com/antlr](https://github.com/antlr/antlr4)


## Fahrplan

`{{< schedule >}}`{=markdown}

**Hinweis**: Abgabe der Hausaufgaben bis jeweils 08.00 Uhr im ILIAS.


## Förderungen und Kooperationen

### Kooperation mit University of Alberta, Edmonton (Kanada)

Über das Projekt ["We CAN virtuOWL"] der Fachhochschule Bielefeld ist im Frühjahr 2021 eine
Kooperation mit der [University of Alberta] (Edmonton/Alberta, Kanada) im Modul "Compilerbau"
gestartet.

Wir freuen uns, auch in diesem Semester wieder drei gemeinsame Sitzungen für beide
Hochschulen anbieten zu können. (Diese Termine werden in englischer Sprache durchgeführt.)

["We CAN virtuOWL"]: https://www.uni-bielefeld.de/international/profil/netzwerk/alberta-owl/we-can-virtuowl/
[University of Alberta]: https://www.hsbi.de/en/international-office/alberta-owl-cooperation


<!-- reference to all markdown pages used in the current semester (to be replaced using a proper schedule table) -->
::: slides
<details>
[Syllabus](admin/syllabus.md)
[Resources](admin/resources.md)
[Grading](admin/grading.md)
[Prüfungsvorbereitung](admin/exams.md)
[FAQ](admin/faq.md)

[Intro](lecture/intro/readme.md)                                        <!-- because of sub-sub-dirs -->
[Überblick](lecture/intro/overview.md)
[Sprachen](lecture/intro/languages.md)
[Anwendungen](lecture/intro/applications.md)

[Frontend](lecture/frontend/readme.md)                                  <!-- because of sub-sub-dirs -->
[Lexer](lecture/frontend/lexing/readme.md)                              <!-- because of sub-sub-dirs -->
[Reguläre Sprachen](lecture/frontend/lexing/regular.md)
[Handcodierter Lexer](lecture/frontend/lexing/recursive.md)
[Lexer mit ANTLR](lecture/frontend/lexing/antlr-lexing.md)

[Parser](lecture/frontend/parsing/readme.md)                            <!-- because of sub-sub-dirs -->
[CFG](lecture/frontend/parsing/cfg.md)
[LL-Parser (Theorie)](lecture/frontend/parsing/ll-parser-theory.md)
[LL-Parser (Praxis)](lecture/frontend/parsing/ll-parser-impl.md)
[Parser mit ANTLR](lecture/frontend/parsing/antlr-parsing.md)
[Error Revocery](lecture/frontend/parsing/recovery.md)
[Grenze Lexer und Parser](lecture/frontend/parsing/finalwords.md)

[Typen](lecture/frontend/semantics/readme.md)                           <!-- because of sub-sub-dirs -->
[Attributierte Grammatiken](lecture/frontend/semantics/attribgrammars.md)

[Symboltabellen](lecture/frontend/semantics/symboltables/readme.md)     <!-- because of sub-sub-dirs -->
[Überblick Symboltabellen](lecture/frontend/semantics/symboltables/intro-symbtab.md)
[Symboltabellen: Scopes](lecture/frontend/semantics/symboltables/scopes.md)
[Symboltabellen: Funktionen](lecture/frontend/semantics/symboltables/functions.md)
[Symboltabellen: Klassen](lecture/frontend/semantics/symboltables/classes.md)

[IR](lecture/intermediate/readme.md)                                    <!-- because of sub-sub-dirs -->
[Überblick Zwischencode](lecture/intermediate/intro-ir.md)

[Backend](lecture/backend/readme.md)                                    <!-- because of sub-sub-dirs -->
<!-- [Mini-Python (Builder)](lecture/backend/minipython-builder.md) -->

[Interpreter](lecture/backend/interpretation/readme.md)                 <!-- because of sub-sub-dirs -->
[Syntaxgesteuerte Interpreter](lecture/backend/interpretation/syntaxdriven.md)
[AST-basierte Interpreter 1](lecture/backend/interpretation/astdriven-part1.md)
[AST-basierte Interpreter 2](lecture/backend/interpretation/astdriven-part2.md)
[Garbage Collection](lecture/backend/interpretation/gc.md)

[B01](homework/sheet01.md)
[B02](homework/sheet02.md)
[B03](homework/sheet03.md)
[B04](homework/sheet04.md)
</details>
:::







<!-- DO NOT REMOVE - THIS IS A LAST SLIDE TO INDICATE THE LICENSE AND POSSIBLE EXCEPTIONS (IMAGES, ...). -->
::: slides
## LICENSE
![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)

Unless otherwise noted, this work is licensed under CC BY-SA 4.0.
:::
