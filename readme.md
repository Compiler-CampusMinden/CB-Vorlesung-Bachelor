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
4.  Zwischencode: Intermediate Representation (IR)
5.  Backend: LLVM
6.  Interpreter: AST-Traversierung
7.  C++ als zu verarbeitende Programmiersprache


## Team

*   [BC George](https://www.hsbi.de/minden/ueber-uns/personenverzeichnis/birgit-christina-george)
*   [Carsten Gips](https://www.hsbi.de/minden/ueber-uns/personenverzeichnis/carsten-gips) (Sprechstunde nach Vereinbarung)


## Kursformat

:::::: {.tabs groupid="vl-pr"}
::: {.tab title="Vorlesung"}

**Vorlesung (2 SWS)**

Mi, 08:00 - 09:30 Uhr (online)

Durchführung als **Flipped Classroom** (Carsten) bzw. **Vorlesung** (BC).

:::
::: {.tab title="Praktikum"}

**Praktikum (2 SWS)**

| Praktikumsgruppe | Zeit                  | Raum                  |
|:-----------------|:----------------------|:----------------------|
| S3, Gruppe 1     | Di, 11:30 - 13:00 Uhr | online/Präsenz (J101) |
| S3, Gruppe 2     | Fr, 14:00 - 15:30 Uhr | online/Präsenz (J101) |
| S3, Gruppe 3     | Mo, 09:15 - 10:45 Uhr | online/Präsenz (J101) |
| S5               | Mi, 09:45 - 11:15 Uhr | online/Präsenz (J101) |

Durchführung **online** (Carsten) bzw. **Präsenz** (BC).

:::
::::::

Online-Sitzungen per Zoom (**Zugangsdaten siehe [ILIAS]**).
Sie _können_ hierzu den Raum J101 nutzen.

[ILIAS]: https://www.hsbi.de/elearning/goto.php?target=crs_1254524&client_id=FH-Bielefeld


## Prüfungsform, Note und Credits

**Parcoursprüfung mit Testat**, 5 ECTS (PO23/PO18)

*   **Testat**:
    1.  Mindestens 5 der Übungsblätter B01 - B06 erfolgreich bearbeitet, **und**
    2.  Mindestens 1 der Übungsblätter B07 - B08 erfolgreich bearbeitet, **und**
    3.  Aktive Teilnahme an mindestens 2 der 3 Edmonton-Termine.

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
    1.  Mündliche Prüfung (_ALL\*_) (individuell, ca. 45 Minuten)

    Die Note der mündlichen Prüfung ergibt die Gesamtnote.

:::
::::::


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

*   [ANTLR v4](https://github.com/antlr/antlr4)
*   JDK: Java SE 21 (LTS) ([Oracle](https://www.oracle.com/java/technologies/downloads/) oder
    [Alternativen](https://code.visualstudio.com/docs/languages/java#_install-a-java-development-kit-jdk),
    bitte 64-bit Version nutzen)
*   IDE: [Eclipse IDE for Java Developers](https://www.eclipse.org/downloads/) oder
    [IntelliJ IDEA (Community Edition)](https://www.jetbrains.com/idea/) oder
    [Visual Studio Code](https://code.visualstudio.com/) oder [Vim](https://www.vim.org/) oder ...
*   [Git](https://git-scm.com/)


## Fahrplan

### Vorlesung

Hier finden Sie einen abonnierbaren [Google Kalender] mit allen Terminen der Veranstaltung zum Einbinden in Ihre Kalender-App.

| Monat    | Tag                         | Vorlesung                                                                                                     | Lead Vorlesung |
|:---------|:----------------------------|:--------------------------------------------------------------------------------------------------------------|:---------------|
| Oktober  | 09.                         | [Orga] (**Zoom**); [Überblick], [Sprachen], [Anwendungen]                                                     | Carsten, BC    |
|          | 16.                         | [Reguläre Sprachen]                                                                                           | BC             |
|          | 23.                         | [CFG]                                                                                                         | BC             |
|          | 30.                         | [Lexer mit ANTLR], [Parser mit ANTLR]                                                                         | Carsten        |
| November | 06.                         | **Dienstbesprechung**                                                                                         |                |
|          | 13.                         | [Überblick Symboltabellen], [Symboltabellen: Scopes], [Symboltabellen: Funktionen], [Symboltabellen: Klassen] | Carsten        |
|          | 20.                         | [Überblick Zwischencode], Überblick Backend (LLVM)                                                            | BC, Carsten    |
|          | 27.                         | **Parcoursprüfung: Station 1 ILIAS (Grammar, Lexing, Parsing, Symboltabellen)**                               |                |
| Dezember | 04.                         | [AST-basierte Interpreter 1], [AST-basierte Interpreter 2]                                                    | Carsten        |
|          | 11.                         | C++ I: Datentypen, Arrays, Funktionen, Pointer, Referenzen                                                    | Carsten        |
|          | 18.                         | **Projektwoche Semester 1+3**                                                                                 |                |
|          | 25.                         | _Weihnachtspause_                                                                                             |                |
| Januar   | 01.                         | _Weihnachtspause_                                                                                             |                |
|          | 08.                         | C++ II: Klassen, Operatoren, Vererbung, Polymorphie                                                           | Carsten        |
|          | 15.                         | _Freies Arbeiten/Puffer_                                                                                      |                |
|          | 22.                         | Rückblick (**Zoom**), Prüfungsvorbereitung                                                                    | Carsten, BC    |
|          | _(Prüfungsphase 1. Termin)_ | **Parcoursprüfung: Station 2 mdl. (semant. Analyse, Interpreter, C++)**                                       |                |
|          | _(Prüfungsphase 2. Termin)_ | **Parcoursprüfung: mdl. Prüfung (ALL\*)**                                                                     |                |

### Praktikum

| Monat    | S3, G1 | S3, G2 | S3, G3 | S5  | Praktikum (PO23)                                                   | Praktikum (PO18 abweichend)                                                    | Lead Praktikum   |
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


[Google Kalender]: https://calendar.google.com/calendar/ical/5121604486803dcdb5cfaa8602b8b09ce76743d8b9216795606617cac807e595%40group.calendar.google.com/public/basic.ics

[Orga]: https://github.com/Compiler-CampusMinden/CB-Vorlesung-Bachelor/discussions/categories/q-a?discussions_q=category%3AQ%26A+is%3Aopen

[Überblick]: lecture/intro/overview.md
[Sprachen]: lecture/intro/languages.md
[Anwendungen]: lecture/intro/applications.md

[Reguläre Sprachen]: lecture/frontend/lexing/regular.md
[Lexer mit ANTLR]: lecture/frontend/lexing/antlr-lexing.md

[CFG]: lecture/frontend/parsing/cfg.md
[Parser mit ANTLR]: lecture/frontend/parsing/antlr-parsing.md

[Überblick Symboltabellen]: lecture/frontend/semantics/symboltables/intro-symbtab.md
[Symboltabellen: Scopes]: lecture/frontend/semantics/symboltables/scopes.md
[Symboltabellen: Funktionen]: lecture/frontend/semantics/symboltables/functions.md
[Symboltabellen: Klassen]: lecture/frontend/semantics/symboltables/classes.md

[Überblick Zwischencode]: lecture/intermediate/intro-ir.md

[AST-basierte Interpreter 1]: lecture/backend/interpretation/astdriven-part1.md
[AST-basierte Interpreter 2]: lecture/backend/interpretation/astdriven-part2.md

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
