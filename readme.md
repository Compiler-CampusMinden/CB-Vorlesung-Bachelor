---
archetype: "home"
title: "IFM 3.1: Compilerbau (PO23, Winter 2024/25)"
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
4.  Zwischencode: Intermediate Representation (IR), Builder
5.  Interpreter: AST-Traversierung


## Team

*   [BC George](https://www.hsbi.de/minden/ueber-uns/personenverzeichnis/birgit-christina-george)
*   [Carsten Gips](https://www.hsbi.de/minden/ueber-uns/personenverzeichnis/carsten-gips) (Sprechstunde nach Vereinbarung)


## Kursformat

:::::: {.tabs groupid="vl-pr"}
::: {.tab title="Vorlesung"}

**Vorlesung (2 SWS)**

Mi, 08:00 - 09:30 Uhr (online)

Durchführung als **Flipped Classroom**.

:::
::: {.tab title="Praktikum"}

**Praktikum (2 SWS)**

| Praktikumsgruppe | Zeit                  | Raum   |
|:-----------------|:----------------------|:-------|
| Gruppe 1         | Mi, 11:30 - 13:00 Uhr | online |
| Gruppe 2         | Mi, 09:45 - 11:15 Uhr | D320   |
| Gruppe 3         | Mi, 09:45 - 11:15 Uhr | online |
| Gruppe 4         | Mi, 11:30 - 13:00 Uhr | D320   |

Praktika Gruppen 2 und 4 in **Präsenz**.

:::
::::::

Online-Sitzungen per Zoom (**Zugangsdaten siehe [ILIAS]**).
Sie _können_ hierzu den Raum J104 nutzen.

[ILIAS]: https://www.hsbi.de/elearning/goto.php?target=crs_1254524&client_id=FH-Bielefeld


## Prüfungsform, Note und Credits

**Parcoursprüfung**, 5 ECTS (PO23)

:::::: {.tabs groupid="exams"}
::: {.tab title="Prüfung im ersten Zeitraum"}

*   **Stationen**:
    *   Praktikum: 10x Übungsblätter mit jeweils 1P
        (Einzelbearbeitung, mindestens 60% bearbeitet,
        fristgerechte Abgabe der Lösungen im ILIAS,
        Vorstellung der Lösungen im Praktikum => Punkte)
    *   Schriftliche Prüfung (digitale Klausur) mit 100P;
        [Prüfungsvorbereitung]
*   **Gesamtnote**: 4.0: ab 50P, alle 5P nächste Teilnote, 1.0: ab 95P

:::
::: {.tab title="Prüfung im zweiten Zeitraum"}

*   **Stationen**:
    *   Schriftliche Prüfung (digitale Klausur) mit 100P;
        [Prüfungsvorbereitung]
*   **Gesamtnote**: 4.0: ab 50P, alle 5P nächste Teilnote, 1.0: ab 95P

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

*   JDK: Java SE 21 (LTS) ([Oracle](https://www.oracle.com/java/technologies/downloads/) oder
    [Alternativen](https://code.visualstudio.com/docs/languages/java#_install-a-java-development-kit-jdk),
    bitte 64-bit Version nutzen)
*   [ANTLR v4](https://github.com/antlr/antlr4)
*   IDE: [Eclipse IDE for Java Developers](https://www.eclipse.org/downloads/) oder
    [IntelliJ IDEA (Community Edition)](https://www.jetbrains.com/idea/) oder
    [Visual Studio Code](https://code.visualstudio.com/) oder [Vim](https://www.vim.org/) oder ...
*   [Git](https://git-scm.com/)


## Fahrplan

### Vorlesung

Hier finden Sie einen abonnierbaren [Google Kalender] mit allen Terminen der Veranstaltung zum Einbinden in Ihre Kalender-App.

| Monat    | Tag   | Vorlesung                                                                                                     | Praktikum               | Lead        | Bemerkung                                                                       |
|:---------|:------|:--------------------------------------------------------------------------------------------------------------|:------------------------|:------------|:--------------------------------------------------------------------------------|
| Oktober  | 09.   | [Orga] (**Zoom**); [Überblick], [Sprachen], [Anwendungen]                                                     |                         | Carsten, BC |                                                                                 |
|          | 16.   | C++ I: Datentypen, Arrays, Funktionen, Pointer, Referenzen                                                    |                         | Carsten     |                                                                                 |
|          | 23.   | C++ II: Klassen, Operatoren, Vererbung, Polymorphie                                                           | [B01] C++ I             | Carsten     |                                                                                 |
|          | 30.   | [Reguläre Sprachen]                                                                                           | [B02] C++ II            | BC          | **Mo, 30.10., 17:00-18:00 Uhr, Edmonton I**: ANTLR + Live-Coding (CA)           |
| November | 06.   | **Parcoursprüfung: Station 1 (C++)**                                                                          |                         |             |                                                                                 |
|          | 13.   | [CFG]                                                                                                         | [B03] Reguläre Sprachen | BC          |                                                                                 |
|          | 20.   | [Lexer mit ANTLR], [Parser mit ANTLR]                                                                         | [B04] CFG               | Carsten     |                                                                                 |
|          | 27.   | AST                                                                                                           | [B05] ANTLR             | Carsten     | **Di, 28.11., 18:00-19:00 Uhr, Edmonton II**: Vortrag Mindener Projekte (DE)    |
| Dezember | 04.   | [Attributierte Grammatiken]                                                                                   | [B06] AST               | BC          | **Mi, 06.12., 18:00-19:00 Uhr, Edmonton III**: Vortrag Edmontoner Projekte (CA) |
|          | 11.   | **Parcoursprüfung: Station 2 (Grammars, Lexing, Parsing)**                                                    |                         |             |                                                                                 |
|          | 18.   | [Überblick Symboltabellen], [Symboltabellen: Scopes], [Symboltabellen: Funktionen], [Symboltabellen: Klassen] |                         | Carsten     |                                                                                 |
|          | 25.   | _Weihnachtspause_                                                                                             |                         |             |                                                                                 |
| Januar   | 01.   | _Weihnachtspause_                                                                                             |                         |             |                                                                                 |
|          | 08.   | [AST-basierte Interpreter 1], [AST-basierte Interpreter 2]                                                    | [B07] Symboltabellen    | Carsten     |                                                                                 |
|          | 15.   | [Überblick Zwischencode], Überblick Backend                                                                   | [B08] Interpreter       |             |                                                                                 |
|          | 22.   | Rückblick (**Zoom**)                                                                                          |                         | Carsten, BC |                                                                                 |
|          | _tbd_ | **Parcoursprüfung: Station 3 (Semant. Analyse, Interpreter)** (Termin 1, Campus Minden, B40)                  |                         |             |                                                                                 |


Abgabe der Übungsblätter jeweils **bis 08:00 Uhr** [im ILIAS](https://www.hsbi.de/elearning/goto.php?target=exc_1356670&client_id=FH-Bielefeld).


[Google Kalender]: https://calendar.google.com/calendar/ical/5121604486803dcdb5cfaa8602b8b09ce76743d8b9216795606617cac807e595%40group.calendar.google.com/public/basic.ics

[Orga]: https://github.com/Programmiermethoden-CampusMinden/Prog2-Lecture/discussions/categories/q-a

[Überblick]: lecture/intro/overview.md
[Sprachen]: lecture/intro/languages.md
[Anwendungen]: lecture/intro/applications.md

[Reguläre Sprachen]: lecture/frontend/lexing/regular.md
[Lexer mit ANTLR]: lecture/frontend/lexing/antlr-lexing.md

[CFG]: lecture/frontend/parsing/cfg.md
[LL-Parser]: lecture/frontend/parsing/ll-parser.md
[Parser mit ANTLR]: lecture/frontend/parsing/antlr-parsing.md
[Grenze Lexer und Parser]: lecture/frontend/parsing/finalwords.md

[Attributierte Grammatiken]: lecture/frontend/semantics/attribgrammars.md

[Überblick Symboltabellen]: lecture/frontend/semantics/symboltables/intro-symbtab.md
[Symboltabellen: Scopes]: lecture/frontend/semantics/symboltables/scopes.md
[Symboltabellen: Funktionen]: lecture/frontend/semantics/symboltables/functions.md
[Symboltabellen: Klassen]: lecture/frontend/semantics/symboltables/classes.md

[Überblick Zwischencode]: lecture/intermediate/intro-ir.md
[Mini-Python (Builder)]: lecture/backend/minipython-builder.md

[Syntaxgesteuerte Interpreter]: lecture/backend/interpretation/syntaxdriven.md
[AST-basierte Interpreter 1]: lecture/backend/interpretation/astdriven-part1.md
[AST-basierte Interpreter 2]: lecture/backend/interpretation/astdriven-part2.md

[B01]: homework/sheet01.md
[B02]: homework/sheet02.md
[B03]: homework/sheet03.md
[B04]: homework/sheet04.md
<!--
[B05]: homework/sheet05.md
[B06]: homework/sheet06.md
[B07]: homework/sheet07.md
[B08]: homework/sheet08.md
[B09]: homework/sheet09.md
[B10]: homework/sheet10.md
-->


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
