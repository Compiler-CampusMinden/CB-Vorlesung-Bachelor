---
archetype: "home"
title: "IFM 3.1 (PO23) / IFM 5.21 (PO18): Compilerbau (Winter 2024/25)"
---


![](admin/images/architektur_cb.png){width="80%"}


## Kursbeschreibung

Der Compiler ist das wichtigste Werkzeug in der Informatik. In der Königsdisziplin der
Informatik schließt sich der Kreis, hier kommen die unterschiedlichen Algorithmen und
Datenstrukturen und Programmiersprachenkonzepte zur Anwendung.

In diesem Modul geht es um ein grundlegendes Verständnis für die wichtigsten Konzepte
im Compilerbau. Wir schauen uns dazu relevante aktuelle Tools und Frameworks an und
setzen diese bei der Erstellung eines kleinen Compiler-Frontends für C++ ein.


## Überblick Modulinhalte

1.  Lexikalische Analyse: Scanner/Lexer
    *   Reguläre Sprachen
    *   Generierung mit ANTLR
2.  Syntaxanalyse: Parser
    *   Kontextfreie Grammatiken (CFG)
    *   LL-Parser (Top-Down-Parser)
    *   Generierung mit ANTLR
3.  Semantische Analyse: Attributierte Grammatiken und Symboltabellen
    *   Namen und Scopes
    *   Typen, Klassen, Polymorphie
4.  Zwischencode: Intermediate Representation (IR), LLVM-IR
5.  Backend:
    *   LLVM
    *   Interpreter: AST-Traversierung
6.  C++ als zu verarbeitende Programmiersprache


## Team

*   [BC George](https://www.hsbi.de/minden/ueber-uns/personenverzeichnis/birgit-christina-george)
*   [Carsten Gips](https://www.hsbi.de/minden/ueber-uns/personenverzeichnis/carsten-gips) (Sprechstunde nach Vereinbarung)


## Kursformat

| Vorlesung (2 SWS)                               | Praktikum (2 SWS)                                   |
|:------------------------------------------------|:----------------------------------------------------|
| Mi, 08:00 - 09:30 Uhr (online)                  | S3, G1: Di, 11:30 - 13:00 Uhr (online/Präsenz J101) |
| (Carsten: *Flipped Classroom*, BC: *Vorlesung*) | S3, G2: Fr, 14:00 - 15:30 Uhr (online/Präsenz J101) |
|                                                 | S3, G3: Mo, 09:15 - 10:45 Uhr (online/Präsenz J101) |
|                                                 | S5: Mi, 09:45 - 11:15 Uhr (online/Präsenz J101)     |
|                                                 | (Carsten: *online*, BC: *Präsenz*)                  |

Online-Sitzungen per Zoom (**Zugangsdaten siehe [ILIAS]**).
Sie _können_ hierzu den Raum J101 nutzen.

[ILIAS]: https://www.hsbi.de/elearning/goto.php?target=crs_1254524&client_id=FH-Bielefeld


## Prüfungsform, Note und Credits

**Parcoursprüfung mit Testat**, 5 ECTS (PO23/PO18)

*   **Testat**:
    1.  Mindestens 5 der Übungsblätter B01 - B06 erfolgreich bearbeitet, **und**
    2.  mindestens 1 der Übungsblätter B07 - B08 erfolgreich bearbeitet, **und**
    3.  aktive Teilnahme an mindestens 2 der 3 Edmonton-Termine.

    ("erfolgreich bearbeitet": Bearbeitung 3er Team, je mindestens 80% bearbeitet,
    fristgerechte Abgabe der Lösungen im ILIAS, Vorstellung der Lösungen im Praktikum)

:::::: {.tabs groupid="exams"}
::: {.tab title="Prüfung im ersten Zeitraum"}

*   **Stationen**:
    1.  27.11. (ILIAS-Test, einzeln): Grammar, Lexing, Parsing, Symboltabellen
    2.  Prüfungszeitraum I (Mündliche Prüfung, 3er Teams): semantische Analyse, Interpreter, C++

    Beide Stationen ergeben zu je 50% die Gesamtnote.

:::
::: {.tab title="Prüfung im zweiten Zeitraum"}

*   **Stationen**:
    1.  Prüfungszeitraum II: Mündliche Prüfung (individuell, ca. 45 Minuten)

    Die Note der mündlichen Prüfung ergibt die Gesamtnote.

:::
::::::


## Materialien

1.  ["**Compilers: Principles, Techniques, and Tools**"](https://learning.oreilly.com/library/view/compilers-principles-techniques/9789357054881/).
    Aho, A. V. und Lam, M. S. und Sethi, R. und Ullman, J. D. and Bansal, S., Pearson India, 2023.
    ISBN [978-9-3570-5488-1](https://fhb-bielefeld.digibib.net/openurl?isbn=978-9-3570-5488-1).
    [Online](https://learning.oreilly.com/library/view/compilers-principles-techniques/9789357054881/) über die [O'Reilly-Lernplattform](https://www.oreilly.com/library-access/).
2.  ["**Crafting Interpreters**"](https://github.com/munificent/craftinginterpreters).
    Nystrom, R., Genever Benning, 2021.
    ISBN [978-0-9905829-3-9](https://fhb-bielefeld.digibib.net/openurl?isbn=978-0-9905829-3-9).
    [Online](https://www.craftinginterpreters.com/).
3.  ["**The Definitive ANTLR 4 Reference**"](https://learning.oreilly.com/library/view/the-definitive-antlr/9781941222621/).
    Parr, T., Pragmatic Bookshelf, 2014. ISBN [978-1-9343-5699-9](https://fhb-bielefeld.digibib.net/openurl?isbn=978-1-9343-5699-9).
    [Online](https://learning.oreilly.com/library/view/the-definitive-antlr/9781941222621/) über die [O'Reilly-Lernplattform](https://www.oreilly.com/library-access/).
4.  ["Writing a C Compiler"](https://learning.oreilly.com/library/view/writing-a-c/9781098182229/).
    Sandler, N., No Starch Press, 2024. ISBN [978-1-0981-8222-9](https://fhb-bielefeld.digibib.net/openurl?isbn=978-1-0981-8222-9).
    [Online](https://learning.oreilly.com/library/view/writing-a-c/9781098182229/) über die [O'Reilly-Lernplattform](https://www.oreilly.com/library-access/).


## Fahrplan

Hier finden Sie einen abonnierbaren [Google Kalender] mit allen Terminen der Veranstaltung zum Einbinden in Ihre Kalender-App.

### Vorlesung

| Monat    | Tag                         | Vorlesung                                                                                                     | Lead        |
|:---------|:----------------------------|:--------------------------------------------------------------------------------------------------------------|:------------|
| Oktober  | 09.                         | [Orga] (**Zoom**); [Überblick], [Sprachen], [Anwendungen]                                                     | Carsten, BC |
|          | 16.                         | [Reguläre Sprachen]                                                                                           | BC          |
|          | 23.                         | [CFG]                                                                                                         | BC          |
|          | 30.                         | [Lexer mit ANTLR], [Parser mit ANTLR]                                                                         | Carsten     |
| November | 06.                         | **Dienstbesprechung**                                                                                         |             |
|          | 13.                         | [Überblick Symboltabellen], [Symboltabellen: Scopes], [Symboltabellen: Funktionen], [Symboltabellen: Klassen] | Carsten     |
|          | 20.                         | [Überblick Zwischencode], Überblick Backend (LLVM)                                                            | BC, Carsten |
|          | 27.                         | **Parcoursprüfung: Station 1 ILIAS (Grammar, Lexing, Parsing, Symboltabellen)**                               |             |
| Dezember | 04.                         | [AST-basierte Interpreter 1], [AST-basierte Interpreter 2]                                                    | Carsten     |
|          | 11.                         | C++ I: Datentypen, Arrays, Funktionen, Pointer, Referenzen                                                    | Carsten     |
|          | 18.                         | **Projektwoche Semester 1+3**                                                                                 |             |
|          | 25.                         | _Weihnachtspause_                                                                                             |             |
| Januar   | 01.                         | _Weihnachtspause_                                                                                             |             |
|          | 08.                         | C++ II: Klassen, Operatoren, Vererbung, Polymorphie                                                           | Carsten     |
|          | 15.                         | _Freies Arbeiten/Puffer_                                                                                      |             |
|          | 22.                         | Rückblick (**Zoom**), Prüfungsvorbereitung                                                                    | Carsten, BC |
|          | _(Prüfungsphase 1. Termin)_ | **Parcoursprüfung: Station 2 mdl. (semant. Analyse, Interpreter, C++)**                                       |             |
|          | _(Prüfungsphase 2. Termin)_ | **Parcoursprüfung: mdl. Prüfung (alle Themen)**                                                               |             |

### Praktikum

| Monat    | S3, G1 | S3, G2 | S3, G3 | S5  | Praktikum (PO23)                                                   | Praktikum (PO18 abweichend)                                                    | Lead/Modus       |
|:---------|:-------|:-------|:-------|:----|:-------------------------------------------------------------------|:-------------------------------------------------------------------------------|:-----------------|
| Oktober  | 22.    | 25.    | 21.    | 23. | [B01] Reguläre Sprachen                                            |                                                                                | BC (Präsenz)     |
| November | 05.    | 08.    | 04.    | 06. | [B02] CFG                                                          |                                                                                | BC  (Präsenz)    |
|          | 12.    | 15.    | 11.    | 13. | [B03] ANTLR                                                        |                                                                                | Carsten (online) |
|          | 19.    | 22.    | 18.    | 20. | [B04] Symboltabellen                                               |                                                                                | Carsten (online) |
| Dezember | 10.    | 13.    | 09.    | 11. | [B05] Interpreter                                                  |                                                                                | Carsten (online) |
| Januar   | 07.    | 10.    | 06.    | 08. | [B06] C++                                                          | [B06]: C++ und Pointer+Speicherverwaltung                                      | Carsten (online) |
|          | 14.    | 17.    | 13.    | 15. | [B07] C++: Grammar, ANTLR, Symboltabelle, Pretty Printer/Formatter | [B07] C++: Grammar, ANTLR, Symboltabelle, Pretty Printer/Formatter und Pointer | Carsten (online) |
|          | 21.    | 24.    | 20.    | 22. | [B08] C++: Interpreter, Code-Gen. C++2Java                         | [B08] C++: Interpreter, Code-Gen. C++2Java und Speicherverwaltung              | Carsten (online) |

Abgabe der Übungsblätter jeweils **bis Montag, 09:00 Uhr** [im ILIAS](https://www.hsbi.de/elearning/goto.php?target=exc_1356670&client_id=FH-Bielefeld).

### Termine mit Edmonton

| Monat    | Tag | Zeit | Inhalt                                               |
|:---------|:----|:-----|:-----------------------------------------------------|
| Oktober  | 30. | tbd  | Edmonton I: ANTLR + Live-Coding (CA)                 |
| November | 27. | tbd  | Edmonton II: Vorträge Mindener Projekte (Master, DE) |
| Dezember | 04. | tbd  | Edmonton III: Vorträge Edmontoner Projekte (CA)      |


[Google Kalender]: https://calendar.google.com/calendar/ical/5121604486803dcdb5cfaa8602b8b09ce76743d8b9216795606617cac807e595%40group.calendar.google.com/public/basic.ics

[Orga]: https://github.com/Compiler-CampusMinden/CB-Vorlesung-Bachelor/discussions/categories/q-a?discussions_q=category%3AQ%26A+is%3Aopen

[Überblick]: lecture/00-intro/overview.md
[Sprachen]: lecture/00-intro/languages.md
[Anwendungen]: lecture/00-intro/applications.md

[Reguläre Sprachen]: lecture/01-lexing/regular.md
[Lexer mit ANTLR]: lecture/01-lexing/antlr-lexing.md

[CFG]: lecture/02-parsing/cfg.md
[Parser mit ANTLR]: lecture/02-parsing/antlr-parsing.md

[Überblick Symboltabellen]: lecture/03-semantics/symboltables/intro-symbtab.md
[Symboltabellen: Scopes]: lecture/03-semantics/symboltables/scopes.md
[Symboltabellen: Funktionen]: lecture/03-semantics/symboltables/functions.md
[Symboltabellen: Klassen]: lecture/03-semantics/symboltables/classes.md

[Überblick Zwischencode]: lecture/04-intermediate/intro-ir.md

[AST-basierte Interpreter 1]: lecture/06-interpretation/astdriven-part1.md
[AST-basierte Interpreter 2]: lecture/06-interpretation/astdriven-part2.md

[B01]: homework/sheet01.md
[B02]: homework/sheet02.md
[B03]: homework/sheet03.md
[B04]: homework/sheet04.md
[B05]: homework/sheet05.md
[B06]: homework/sheet06.md
[B07]: homework/sheet07.md
[B08]: homework/sheet08.md


## Förderungen und Kooperationen

### Kooperation mit University of Alberta, Edmonton (Kanada)

Über das Projekt ["We CAN virtuOWL"] der Fachhochschule Bielefeld ist im Frühjahr 2021 eine
Kooperation mit der [University of Alberta] (Edmonton/Alberta, Kanada) im Modul "Compilerbau"
gestartet.

Wir freuen uns, auch in diesem Semester wieder drei gemeinsame Sitzungen für beide
Hochschulen anbieten zu können. (Diese Termine werden in englischer Sprache durchgeführt.)

["We CAN virtuOWL"]: https://www.uni-bielefeld.de/international/profil/netzwerk/alberta-owl/we-can-virtuowl/
[University of Alberta]: https://www.hsbi.de/en/international-office/alberta-owl-cooperation







<!-- DO NOT REMOVE - THIS IS A LAST SLIDE TO INDICATE THE LICENSE AND POSSIBLE EXCEPTIONS (IMAGES, ...). -->
::: slides
## LICENSE
![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)

Unless otherwise noted, this work is licensed under CC BY-SA 4.0.
:::
