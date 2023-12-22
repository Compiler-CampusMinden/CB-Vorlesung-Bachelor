---
archetype: "home"
title: "IFM 5.21: Compilerbau (Winter 2023/24)"
---


![](admin/images/architektur_cb.png){width="80%"}


## Kursbeschreibung

Der Compiler ist das wichtigste Werkzeug in der Informatik. In der Königsdisziplin der
Informatik schließt sich der Kreis, hier kommen die unterschiedlichen Algorithmen und
Datenstrukturen und Programmiersprachenkonzepte zur Anwendung.

In diesem Modul geht es um ein grundlegendes Verständnis für die wichtigsten Konzepte
im Compilerbau. Wir schauen uns dazu relevante aktuelle Tools und Frameworks an und
setzen diese bei der Erstellung eines kleinen Compiler-Frontends für [_Mini-Python_] ein.

[_Mini-Python_]: https://github.com/Compiler-CampusMinden/Mini-Python-Builder


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
*   [Carsten Gips](https://www.hsbi.de/minden/ueber-uns/personenverzeichnis/carsten-gips)


## Kursformat

| Vorlesung (2 SWS)     | Praktikum (2 SWS)     |
|:----------------------|:----------------------|
| Di, 08:00 - 09:30 Uhr | Fr, 16:15 - 17:45 Uhr |
| online/C1             | online/D328           |

Durchführung als **Flipped Classroom** (Carsten) bzw. **Vorlesung** (BC):
alle Sitzungen online/per Zoom (**Zugangsdaten siehe [ILIAS]**)

[ILIAS]: https://www.hsbi.de/elearning/goto.php?target=crs_1254524&client_id=FH-Bielefeld

## Prüfungsform, Note und Credits

**Parcoursprüfung**, 5 ECTS

*   **unbenotet**: Alle vier Übungsblätter ausreichend bearbeitet und Ergebnisse vorgestellt/diskutiert
*   **unbenotet**: Aktive Teilnahme an den drei gemeinsamen Terminen mit der University of Alberta (Edmonton)
*   **benotet (30%)**: Vortrag: Vorstellung der Ergebnisse der freien Aufgabe, 30 Minuten Dauer
*   **benotet (70%)**: Mündliche Prüfung

**Gesamtnote: 30% Vortrag plus 70% mdl. Prüfung**


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

### Vorlesung

| Woche  | Datum                                | Themen                                                                                                              | Lead        | Bemerkung       |
|:------:|:-------------------------------------|:--------------------------------------------------------------------------------------------------------------------|:------------|:----------------|
|   41   | Di, 10.10.                           | Orga (**Zoom**) \|\| [Überblick] \| [Sprachen] \| [Anwendungen]                                                     | Carsten, BC |                 |
|   42   | Di, 17.10.                           | [Reguläre Sprachen]                                                                                                 | BC          |                 |
|   42   | Fr, 20.10. (**Praktikum**)           | [Lexer mit ANTLR]                                                                                                   | Carsten     |                 |
|   43   | Di, 24.10.                           | [CFG]                                                                                                               | BC          |                 |
|   43   | Fr, 27.10. (**Praktikum**)           | [LL-Parser]                                                                                                         | BC          |                 |
|   44   | **Mo, 30.10., 17:00-18:00 Uhr**      | **Edmonton I**: ANTLR + Live-Coding (CA)                                                                            |             | online bzw. H10 |
|   44   | Di, 31.10.                           | [Parser mit ANTLR] \| [Grenze Lexer und Parser]                                                                     | Carsten     |                 |
|   45   | Di, 07.11.                           | [Überblick Symboltabellen] \| [Symboltabellen: Scopes] \| [Symboltabellen: Funktionen] \| [Symboltabellen: Klassen] | Carsten     | [B01]           |
| ~~46~~ | ~~Di, 14.11.~~                       | ~~[Attributierte Grammatiken]~~                                                                                     | ~~BC~~      |                 |
|   46   | Fr, 17.11. (**Praktikum**)           | [Syntaxgesteuerte Interpreter] \| [AST-basierte Interpreter 1] \| [AST-basierte Interpreter 2]                      | Carsten     |                 |
|   47   | Di, 21.11.                           | [Attributierte Grammatiken]                                                                                         | BC          | [B02]           |
|   48   | Di, 28.11.                           | [Überblick Zwischencode] \| [Mini-Python (Builder)]                                                                 | BC          |                 |
|   48   | **Di, 28.11., 18:00-19:00 Uhr**      | **Edmonton II**: Vortrag Mindener Projekte (DE)                                                                     |             |                 |
|   49   | **Mi, 06.12., 18:00-19:00 Uhr**      | **Edmonton III**: Vortrag Edmontoner Projekte (CA)                                                                  |             | [B03]           |
|   50   | Di, 12.12.                           | Freies Arbeiten / [B03] (Nachfrist)                                                                                 | Carsten     |                 |
|   51   | Di, 19.12.                           | [B04]                                                                                                               | Carsten, BC |                 |
|   02   | Di, 09.01.                           | Freies Arbeiten                                                                                                     | Carsten     |                 |
|   03   | Di, 16.01.                           | Freies Arbeiten                                                                                                     | Carsten     |                 |
|   04   | **Mo, 22.01., 11:45-13:15 Uhr, B70** | **Besuch von Prof. Nelson Amaral in Minden (Vortrag und Gespräch mit Studierenden), B70**                           | BC          |                 |
|   04   | Di, 23.01.                           | Vortrag: [Termine siehe Etherpad]                                                                                   | Carsten, BC |                 |
|   04   | Fr, 26.01. (**Praktikum**)           | Vortrag: [Termine siehe Etherpad]                                                                                   | Carsten, BC |                 |

[Termine siehe Etherpad]: https://www.hsbi.de/elearning/goto.php?target=xpdl_1331973&client_id=FH-Bielefeld

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

### Praktikum

| Woche | Blatt                                          | Abgabe ILIAS                                                                                                                                        | Vorstellung Praktikum                                    |
|:-----:|:-----------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------|:---------------------------------------------------------|
|  45   | [B01]: Grammatik, ANTLR, AST (Mini-Python)     | Fr, 10.11., 16:00 Uhr ([Link](https://www.hsbi.de/elearning/goto.php?target=exc_1258623&client_id=FH-Bielefeld))                                    | Fr, 10.11.                                               |
|  47   | [B02]: AST und Symboltabellen (Mini-Python)    | Fr, 24.11., 16:00 Uhr ([Link](https://www.hsbi.de/elearning/goto.php?target=exc_1258623&client_id=FH-Bielefeld))                                    | Fr, 24.11.                                               |
|  49   | [B03]: Interpreter (Mini-Python)               | Fr, 08.12., 16:00 Uhr ([Link](https://www.hsbi.de/elearning/goto.php?target=exc_1258623&client_id=FH-Bielefeld)) (Nachfrist: Di, 12.12., 08:00 Uhr) | Fr, 08.12. (Nachfrist: Di, 12.12., **Vorlesungsslot**)   |
|  51   | [B04]: Builder und freie Aufgabe (Mini-Python) | **Di, 19.12., 08:00 Uhr** ([Link](https://www.hsbi.de/elearning/goto.php?target=exc_1258623&client_id=FH-Bielefeld))                                | Di, 19.12. (**Vorlesungsslot**)                          |
|  04   | Freie Aufgabe (Mini-Python)                    | **Di, 23.01., 08:00 Uhr** ([Link](https://www.hsbi.de/elearning/goto.php?target=exc_1258623&client_id=FH-Bielefeld))                                | Di, 23.01. (**Vorlesungsslot**) / Fr, 26.01. (Praktikum) |

[B01]: homework/sheet01.md
[B02]: homework/sheet02.md
[B03]: homework/sheet03.md
[B04]: homework/sheet04.md


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
