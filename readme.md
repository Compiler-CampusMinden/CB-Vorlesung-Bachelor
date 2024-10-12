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

:::::: {.tabs groupid="modul-po"}
::: {.tab title="IFM 3.1 CB (PO23, 3. Semester)"}

| Vorlesung (2 SWS)                               | Praktikum (2 SWS)                                   |
|:------------------------------------------------|:----------------------------------------------------|
| Mi, 08:00 - 09:30 Uhr (online)                  | S3, G1: Di, 11:30 - 13:00 Uhr (online/Präsenz J101) |
| (Carsten: *Flipped Classroom*, BC: *Vorlesung*) | S3, G2: Fr, 14:00 - 15:30 Uhr (online/Präsenz J101) |
|                                                 | S3, G3: Mo, 09:15 - 10:45 Uhr (online/Präsenz J101) |
|                                                 | (Carsten: *online*, BC: *Präsenz*)                  |

Online-Sitzungen per Zoom (**Zugangsdaten siehe [ILIAS IFM 3.1 CB (PO23, 3. Semester)]**).
Sie _können_ hierzu den Raum J101 (siehe Stundenplan) nutzen.

:::
::: {.tab title="IFM 5.21 CB (PO18, 5. Semester)"}

| Vorlesung (2 SWS)                               | Praktikum (2 SWS)                      |
|:------------------------------------------------|:---------------------------------------|
| Mi, 08:00 - 09:30 Uhr (online)                  | S5, G1: Mi, 09:30 - 11:00 Uhr (online) |
| (Carsten: *Flipped Classroom*, BC: *Vorlesung*) | S5, G2: Mi, 09:30 - 11:00 Uhr (online) |
|                                                 | S5, G3: Mi, 09:30 - 11:00 Uhr (online) |
|                                                 | (Carsten: *online*, BC: *online*)      |

Online-Sitzungen per Zoom (**Zugangsdaten siehe [IFM 5.21 CB (PO18, 5. Semester)]**).
Sie _können_ hierzu den Raum J101 (siehe Stundenplan) nutzen.

:::
::::::

[ILIAS IFM 3.1 CB (PO23, 3. Semester)]: https://www.hsbi.de/elearning/goto.php?target=crs_1400596&client_id=FH-Bielefeld
[IFM 5.21 CB (PO18, 5. Semester)]: https://www.hsbi.de/elearning/goto.php?target=crs_1400603&client_id=FH-Bielefeld


## Fahrplan

:::::: {.tabs groupid="modul-po"}
::: {.tab title="IFM 3.1 CB (PO23, 3. Semester)"}

`{{% notice style="note" title="News" %}}`{=markdown}
`{{% expand title="09.10.24" %}}`{=markdown}

### Teams

Bitte bearbeiten Sie die Aufgaben in 3er Teams.

Es ist empfehlenswert, wenn alle Personen im Team in der selben Stundenplangruppe
(Praktikumsgruppe) sind. Sie können aber auch Teams über verschiedene Gruppen
hinweg bilden. Geben Sie individuell im ILIAS ab und stellen Sie die Lösung dann
individuell in Ihrer jeweiligen Praktikumsgruppe vor.

Sie können Ihre Teams jederzeit selbstständig im Semester ändern/wechseln.

**Achtung**: Den Vortrag zu [B07] müssen Sie aber **gemeinsam als Team** halten.
Wenn Ihre Teammitglieder aus verschiedenen Stundenplangruppen kommen sollten,
findet der Vortrag in der Gruppe statt, aus der die meisten der Teammitglieder
kommen. Bitte beachten Sie das bei der Teamwahl!

### Abgabe ILIAS

Das Abgabeverfahren im ILIAS wurde deutlich vereinfacht: Jede Person gibt für
jedes Blatt individuell direkt im ILIAS an, welche Aufgaben das Team bearbeitet
hat (also keine Teambildung und keine Textdatei mehr im ILIAS).

Bitte darauf achten, dass Sie das die angegebenen Aufgaben auch vorstellen können
müssen! Achten Sie bitte auch auf die mind. 60% für das Testat.

### Praktikum

Sie gehen einfach in das Praktikum, welches Ihrer Stundenplangruppe zugeordnet ist
und stellen dort individuell die Lösungen Ihres Teams vor.

Den Vortrag zu [B07] (letzte VL-Woche) halten Sie dann in die Praktikumsgruppe, in
der die meisten Teammitglieder sind. Bitte prüfen Sie, ob das für Sie passt (vom
Stundenplan her möglich ist) und wählen Sie ggf. ein anderes Team. Wir werden
rechtzeitig eine entsprechende Planung organisieren. Einige Vorträge werden wir
aber auch im Vorlesungsslot machen müssen, d.h. hier besteht bei Bedarf eine
Ausweichmöglichkeit.

`{{% /expand %}}`{=markdown}
`{{% /notice %}}`{=markdown}

Hier finden Sie einen abonnierbaren [Google Kalender IFM 3.1 CB (PO23, 3. Semester)] mit allen Terminen der Veranstaltung zum Einbinden in Ihre Kalender-App.

Abgabe der Übungsblätter jeweils **Montag bis 09:00 Uhr** im [ILIAS](https://www.hsbi.de/elearning/goto.php?target=exc_1420724&client_id=FH-Bielefeld). Vorstellung der Lösung im jeweiligen Praktikum in der Abgabewoche.

| Monat                | Woche | Vorlesung                                                                                                                                     | Lead        | Abgabe Aufgabenblatt           | Vorstellung Praktikum                  |
|:---------------------|:------|:----------------------------------------------------------------------------------------------------------------------------------------------|:------------|:-------------------------------|:---------------------------------------|
| Oktober              | 41    | 09.: [Orga] (*Zoom*); [Überblick], [Sprachen], [Anwendungen]                                                                                  | Carsten, BC |                                |                                        |
|                      | 42    | 16.: [Reguläre Sprachen]                                                                                                                      | BC          |                                |                                        |
|                      | 43    | 23.: [CFG]                                                                                                                                    | BC          | 21.: [B01] Reguläre Sprachen   | 21. / 22. / 25. (BC, *Präsenz*)        |
|                      | 44    | 29.: **18:00 - 19:30 Uhr (online): Edmonton I: ANTLR + Live-Coding**                                                                          | _Edmonton_  |                                |                                        |
|                      | 44    | 30.: [Lexer mit ANTLR], [Parser mit ANTLR]                                                                                                    | Carsten     |                                |                                        |
| November             | 45    | 06.: *Dienstbesprechung*                                                                                                                      |             | 04.: [B02] CFG                 | 04. / 05. / 08. (BC, *Präsenz*)        |
|                      | 46    | 13.: [Überblick Symboltabellen], [Symboltabellen: Scopes], [Symboltabellen: Funktionen], [Symboltabellen: Klassen]                            | Carsten     | 11.: [B03] ANTLR               | 11. / 12. / 15. (Carsten, *online*)    |
|                      | 47    | 20.: [**09:45 - 10:30 Uhr, 10:45 - 11:30 Uhr (B40): Parcoursprüfung: Station 1 ILIAS (Grammar, Lexing, Parsing), siehe Ankündigung**]{.alert} |             | 18.: [B04] Semantische Analyse | 18. / 19. / 22. (Carsten, *online*)    |
|                      | 48    | 26.: **18:00 - 19:30 Uhr (online): Edmonton II: Vorträge Mindener Projekte**                                                                  | _Minden_    |                                |                                        |
|                      | 48    | 27.: [Überblick Zwischencode], Überblick Backend (LLVM)                                                                                       | BC, Carsten |                                |                                        |
| Dezember             | 49    | 03.: **18:00 - 19:30 Uhr (online): Edmonton III: Vorträge Edmontoner Projekte**                                                               | _Edmonton_  |                                |                                        |
|                      | 49    | 04.: [AST-basierte Interpreter 1], [AST-basierte Interpreter 2]                                                                               | Carsten     |                                |                                        |
|                      | 50    | 11.: C++ I: [Basics], [Pointer & Referenzen], [Klassen]                                                                                       | Carsten     | 09.: [B05] Interpreter         | 09. / 10. / 13. (Carsten, *online*)    |
|                      | 51    | 18.: **Projektwoche Semester 1+3**                                                                                                            |             |                                |                                        |
|                      | 52    | 25.: _Weihnachtspause_                                                                                                                        |             |                                |                                        |
| Januar               | 01    | 01.: _Weihnachtspause_                                                                                                                        |             |                                |                                        |
|                      | 02    | 08.: C++ II: [Big 3], [Operatoren], [Vererbung & Polymorphie]                                                                                 | Carsten     | 06.: [B06] C++                 | 06. / 07. / 10. (Carsten, *online*)    |
|                      | 03    | 15.: _Freies Arbeiten/Puffer_                                                                                                                 |             |                                |                                        |
|                      | 04    | 22.: [**Parcoursprüfung: Station 2 [B07] (VL- und Praktika-Slots, siehe Ankündigung)**]{.alert}                                               | Carsten, BC | 20.: [B07] Mini-Projekt        | 20. / 21. / 24. (Carsten/BC, *online*) |
| _(Prüfungsphase I)_  |       | _Keine separate Prüfung_                                                                                                                      |             |                                |                                        |
| _(Prüfungsphase II)_ |       | [**Parcoursprüfung: Do, 27. Mar 2025, 08-18 Uhr, mdl. Prüfung (alle Themen)**]{.alert} (je Prüfung ca. 45', Vergabe ca. 2 Wochen vorher)      |             |                                |                                        |

:::
::: {.tab title="IFM 5.21 CB (PO18, 5. Semester)"}

`{{% notice style="note" title="News" %}}`{=markdown}
`{{% expand title="09.10.24" %}}`{=markdown}

### Teams

Bitte bearbeiten Sie die Aufgaben in 3er Teams.

Es ist empfehlenswert, wenn alle Personen im Team in der selben Stundenplangruppe
(Praktikumsgruppe) sind. Sie können aber auch Teams über verschiedene Gruppen
hinweg bilden. Geben Sie individuell im ILIAS ab und stellen Sie die Lösung dann
individuell in Ihrer jeweiligen Praktikumsgruppe vor.

Sie können Ihre Teams jederzeit selbstständig im Semester ändern/wechseln.

**Achtung**: Den Vortrag zu [B07x] müssen Sie (wie auch den Vortrag zu [B04x]) aber
**gemeinsam als Team** halten. Wenn Ihre Teammitglieder aus verschiedenen
Stundenplangruppen kommen sollten, findet der Vortrag in der Gruppe statt, aus der
die meisten der Teammitglieder kommen. Bitte beachten Sie das bei der Teamwahl!

### Abgabe ILIAS

Das Abgabeverfahren im ILIAS wurde deutlich vereinfacht: Jede Person gibt für
jedes Blatt individuell direkt im ILIAS an, welche Aufgaben das Team bearbeitet
hat (also keine Teambildung und keine Textdatei mehr im ILIAS).

Bitte darauf achten, dass Sie das die angegebenen Aufgaben auch vorstellen können
müssen! Achten Sie bitte auch auf die mind. 60% für das Testat.

### Praktikum

Sie gehen einfach in das Praktikum, welches Ihrer Stundenplangruppe zugeordnet ist
und stellen dort individuell die Lösungen Ihres Teams vor.

Den Vortrag zu [B07x] (letzte VL-Woche) halten Sie dann in die Praktikumsgruppe, in
der die meisten Teammitglieder sind. Bitte prüfen Sie, ob das für Sie passt (vom
Stundenplan her möglich ist) und wählen Sie ggf. ein anderes Team. Wir werden
rechtzeitig eine entsprechende Planung organisieren. Einige Vorträge werden wir
aber auch im Vorlesungsslot machen müssen, d.h. hier besteht bei Bedarf eine
Ausweichmöglichkeit.

`{{% /expand %}}`{=markdown}
`{{% /notice %}}`{=markdown}

Hier finden Sie einen abonnierbaren [Google Kalender IFM 5.21 CB (PO18, 5. Semester)] mit allen Terminen der Veranstaltung zum Einbinden in Ihre Kalender-App.

Abgabe der Übungsblätter jeweils **Mittwoch bis 09:00 Uhr** im [ILIAS](https://www.hsbi.de/elearning/goto.php?target=exc_1420725&client_id=FH-Bielefeld). Vorstellung der Lösung im jeweiligen Praktikum in der Abgabewoche.

| Monat                | Tag | Vorlesung                                                                                                                                | Lead          | Abgabe Aufgabenblatt & Vorstellung Praktikum                                    |
|:---------------------|:----|:-----------------------------------------------------------------------------------------------------------------------------------------|:--------------|:--------------------------------------------------------------------------------|
| Oktober              | 09. | [Orga] (*Zoom*); [Überblick], [Sprachen], [Anwendungen]                                                                                  | Carsten, BC   |                                                                                 |
|                      | 16. | [Reguläre Sprachen]                                                                                                                      | BC            |                                                                                 |
|                      | 23. | [CFG]                                                                                                                                    | BC            | [B01] Reguläre Sprachen (BC, *online*)                                          |
|                      | 29. | **18:00 - 19:30 Uhr (online): Edmonton I: ANTLR + Live-Coding**                                                                          | _Edmonton_    |                                                                                 |
|                      | 30. | [Lexer mit ANTLR], [Parser mit ANTLR]                                                                                                    | Carsten       |                                                                                 |
| November             | 06. | *Dienstbesprechung*                                                                                                                      |               | [B02] CFG (BC, *online*)                                                        |
|                      | 13. | [Überblick Symboltabellen], [Symboltabellen: Scopes], [Symboltabellen: Funktionen], [Symboltabellen: Klassen]                            | Carsten       | [B03] ANTLR (Carsten, *online*)                                                 |
|                      | 20. | [**08:00 - 09:30 Uhr (online): Vortrag: Vorstellung der Lösung von [B04x] ("Generalprobe")**]{.alert}                                    |               | [B04x] Semantische Analyse (Abgabe)                                             |
|                      | 26. | [**18:00 - 19:30 Uhr (online): Parcoursprüfung: Station 1 / Edmonton II: Vorträge Mindener Projekte: [B04x]**]{.alert}                   | _Minden (S5)_ |                                                                                 |
|                      | 27. | [Überblick Zwischencode], Überblick Backend (LLVM)                                                                                       | BC, Carsten   |                                                                                 |
| Dezember             | 03. | **18:00 - 19:30 Uhr (online): Edmonton III: Vorträge Edmontoner Projekte**                                                               | _Edmonton_    |                                                                                 |
|                      | 04. | [AST-basierte Interpreter 1], [AST-basierte Interpreter 2]                                                                               | Carsten       |                                                                                 |
|                      | 11. | C++ I: [Basics], [Pointer & Referenzen], [Klassen]                                                                                       | Carsten       | [B05x] Interpreter (Carsten, *online*)                                          |
|                      | 18. | **Projektwoche Semester 1+3**                                                                                                            |               |                                                                                 |
|                      | 25. | _Weihnachtspause_                                                                                                                        |               |                                                                                 |
| Januar               | 01. | _Weihnachtspause_                                                                                                                        |               |                                                                                 |
|                      | 08. | C++ II: [Big 3], [Operatoren], [Vererbung & Polymorphie]                                                                                 | Carsten       | [B06x] C++ und Pointer/Speicherverwaltung (Runtime in Java) (Carsten, *online*) |
|                      | 15. | _Freies Arbeiten/Puffer_                                                                                                                 |               |                                                                                 |
|                      | 22. | [**Parcoursprüfung: Station 2 [B07x] (VL- und Praktika-Slots, siehe Ankündigung)**]{.alert}                                              | Carsten, BC   | [B07x] Mini-Projekt (Carsten/BC, *online*)                                      |
| _(Prüfungsphase I)_  |     | _Keine separate Prüfung_                                                                                                                 |               |                                                                                 |
| _(Prüfungsphase II)_ |     | [**Parcoursprüfung: Do, 27. Mar 2025, 08-18 Uhr, mdl. Prüfung (alle Themen)**]{.alert} (je Prüfung ca. 45', Vergabe ca. 2 Wochen vorher) |               |                                                                                 |

:::
::::::


[Google Kalender IFM 3.1 CB (PO23, 3. Semester)]: https://calendar.google.com/calendar/ical/07021c87022fe3f132fa2e2e799b230b5ab9c7088c85d152f2beab8f1b5218af%40group.calendar.google.com/public/basic.ics
[Google Kalender IFM 5.21 CB (PO18, 5. Semester)]: https://calendar.google.com/calendar/ical/643ebb4721e215c2b2f2ac0330d5642f6cf9efe18cd16548e2e08f8bfa199336%40group.calendar.google.com/public/basic.ics

[Orga]: https://www.hsbi.de/elearning/data/FH-Bielefeld/lm_data/lm_1360443/index.html#überblick-modulinhalte

[Überblick]: lecture/00-intro/overview.md
[Sprachen]: lecture/00-intro/languages.md
[Anwendungen]: lecture/00-intro/applications.md

[Reguläre Sprachen]: lecture/01-lexing/regular.md
[Lexer mit ANTLR]: lecture/01-lexing/antlr-lexing.md

[CFG]: lecture/02-parsing/cfg.md
<!-- [LL-Parser]: lecture/02-parsing/ll-parser.md -->
[Parser mit ANTLR]: lecture/02-parsing/antlr-parsing.md
<!-- [Grenze Lexer und Parser]: lecture/02-parsing/finalwords.md -->

<!-- [Attributierte Grammatiken]: lecture/03-semantics/attribgrammars.md -->
[Überblick Symboltabellen]: lecture/03-semantics/symbtab0-intro.md
[Symboltabellen: Scopes]: lecture/03-semantics/symbtab1-scopes.md
[Symboltabellen: Funktionen]: lecture/03-semantics/symbtab2-functions.md
[Symboltabellen: Klassen]: lecture/03-semantics/symbtab3-classes.md

[Überblick Zwischencode]: lecture/04-intermediate/intro-ir.md

<!-- [Syntaxgesteuerte Interpreter]: lecture/06-interpretation/syntaxdriven.md -->
[AST-basierte Interpreter 1]: lecture/06-interpretation/astdriven-part1.md
[AST-basierte Interpreter 2]: lecture/06-interpretation/astdriven-part2.md

<!-- [Builder für Mini-Python]: lecture/07-codegen/minipython-builder.md -->

[Basics]: lecture/99-languages/cpp0-basics.md
[Pointer & Referenzen]: lecture/99-languages/cpp1-pointer.md
[Klassen]: lecture/99-languages/cpp2-classes.md
[Big 3]: lecture/99-languages/cpp3-big3.md
[Operatoren]: lecture/99-languages/cpp4-operators.md
[Vererbung & Polymorphie]: lecture/99-languages/cpp5-inheritance.md

[B01]: homework/sheet01.md
[B02]: homework/sheet02.md
[B03]: homework/sheet03.md
[B04]: homework/sheet04.md
[B05]: homework/sheet05.md
[B06]: homework/sheet06.md
[B07]: homework/sheet07.md
[B04x]: homework/sheet04x.md
[B05x]: homework/sheet05x.md
[B06x]: homework/sheet06.md
[B07x]: homework/sheet07.md


## Prüfungsform, Note und Credits

:::::::::::: {.tabs groupid="modul-po"}
::::::::: {.tab title="IFM 3.1 CB (PO23, 3. Semester)"}

**Parcoursprüfung plus Testat**, 5 ECTS (PO23)

*   **Testat**: Vergabe der Credit-Points
    1.  Mindestens 4 der Übungsblätter [B01], [B02], [B03], [B04], [B05] und [B06] erfolgreich bearbeitet, **und**
    2.  **aktive** Teilnahme an allen 3 Edmonton-Terminen.

    ("erfolgreich bearbeitet": Bearbeitung in 3er Teams, je mindestens 60% bearbeitet,
    fristgerechte Abgabe der Lösungen im ILIAS, Vorstellung der Lösungen im Praktikum)

:::::: {.tabs groupid="exams"}
::: {.tab title="Prüfung im ersten Zeitraum"}

*   **Stationen**:
    1.  ILIAS-Test (einzeln, 20.11.)
    2.  Vorstellung Mini-Projekt [B07] (3er Teams, letzte VL-Woche)

    Beide Stationen ergeben zu je 50% die Gesamtnote.

:::
::: {.tab title="Prüfung im zweiten Zeitraum"}

*   **Stationen**:
    1.  Mündliche Prüfung (individuell, ca. 45 Minuten, zweiter Prüfungszeitraum)

    Die Note der mündlichen Prüfung ergibt die Gesamtnote.

:::
::::::

:::::::::
::::::::: {.tab title="IFM 5.21 CB (PO18, 5. Semester)"}

**Parcoursprüfung plus Testat**, 5 ECTS (PO18)

*   **Testat**: Vergabe der Credit-Points
    1.  Mindestens 4 der Übungsblätter [B01], [B02], [B03], [B04x], [B05x] und [B06x] erfolgreich bearbeitet, **und**
    2.  **aktive** Teilnahme an allen 3 Edmonton-Terminen.

    ("erfolgreich bearbeitet": Bearbeitung in 3er Teams, je mindestens 60% bearbeitet,
    fristgerechte Abgabe der Lösungen im ILIAS, Vorstellung der Lösungen im Praktikum)

:::::: {.tabs groupid="exams"}
::: {.tab title="Prüfung im ersten Zeitraum"}

*   **Stationen**:
    1.  Vortrag (3er Team, 20.11. zur Probe und 26.11. auf Edmonton II-Treffen in englischer Sprache): Vorstellung der Lösung von [B04x]
    2.  Vorstellung Mini-Projekt [B07x] (3er Teams, letzte VL-Woche)

    Beide Stationen ergeben zu je 50% die Gesamtnote.

:::
::: {.tab title="Prüfung im zweiten Zeitraum"}

*   **Stationen**:
    1.  Mündliche Prüfung (individuell, ca. 45 Minuten, zweiter Prüfungszeitraum)

    Die Note der mündlichen Prüfung ergibt die Gesamtnote.

:::
::::::

:::::::::
::::::::::::


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
