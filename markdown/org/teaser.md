---
type: lecture-cg
title: "Modulvorstellung CB (Wahlfach Liste 1)"
author: "Carsten Gips (FH Bielefeld)"
weight: 6
hidden: true
youtube:
  - link: ""
    name: "Modulvorstellung CB (Wahlfach Liste 1)"
fhmedia:
  - link: ""
    name: "Modulvorstellung CB (Wahlfach Liste 1)"
---


::: notes
# Modulvorstellung CB
:::

## Sprachen verstehen, (formale) Texte transformieren

<!-- XXX ggf. mit Orga/Intro1 abgleichen -->

![Modulinhalte](figs/orga/mountain)\
[Quelle: [Bob Nystrom (CC BY-NC-ND 4.0/MIT)](https://github.com/munificent/craftinginterpreters/blob/master/site/image/a-map-of-the-territory/mountain.png)]{.origin}


::: notes
## Voraussichtliche Inhalte

*   Lexikalische Analyse
    *   Reguläre Ausdrücke
    *   Manuelle Implementierung
    *   Generierung mit ANTLR, Channels, Modes (Insel-Grammatiken)
    *   Error Recovery

*   Syntaxanalyse
    *   Kontextfreie Grammatiken (CFG)
    *   LL-Parser
        *   FIRST, FOLLOW
        *   LL(1), LL(k), LL(*)
        *   Umgang mit linksrekursiven Grammatiken
        *   Umgang mit Vorrang-Regeln und Assoziativität
        *   Manuelle Implementierung
        *   Generierung mit ANTLR
        *   Backtracking, Memoizing, Predicated Parsers; ANTLR4: ALL(*)
    *   LR-Parser
        *   Shift-Reduce
        *   LR(0), SLR(1), LR(1), LALR(1)
        *   Tools: Bison/Yacc (bzw. passendes Java-Tool)
    *   Error Recovery
    *   Grenze Lexer und Parser (aus praktischen Gesichtspunkten)

*   Semantische Analyse
    *   Attributierte Grammatiken
    *   Symboltabellen
        *   Berücksichtigung unterschiedlicher Sprachparadigmen
        *   Typen, Klassen, Polymorphie
        *   Namen und Scopes

*   Interpreter und Compiler
    *   Intermediate Representation (IR)
    *   Read-Eval-Schleife
    *   Translation: syntax-directed vs. rule-based vs. model-based
    *   Optimierungen: Peephole
:::


::: notes
## Ziele

*   Verständnis für die wichtigsten Konzepte im Compilerbau
*   Kenntnis relevanter aktueller Tools/Frameworks
*   Verständnis für wichtige Sprachparadigmen

\blueArrow Aufteilung: 40% Konzepte/Theorie, 60% Anwendung
:::


::: notes
## Veranstaltungsform
:::

\bigskip
\bigskip
\bigskip

2 SWS Vorlesung (mdl. Prüfung), 2 SWS Praktikum mit Testat


::::::::: notes
Im Praktikum wird es in der ersten Hälfte des Semesters voraussichtlich freie
Übungsblätter geben. In der zweiten Hälfte soll voraussichtlich ein kleines,
selbst gewähltes und mit den Dozenten abgestimmtes Projekt bearbeitet werden.


### Anmerkung zur Durchführung im Winter 2021

> Die Veranstaltung wird nach aktuellem Stand voraussichtlich rein digital
> durchgeführt: Für die Vorlesungen ist aktuell die Durchführung über
> Screencasts/Videos plus ausführliche Skripte und eine wöchentliche
> Sprechstunde (cagi) im Wechsel mit einer Live-Vorlesung über Zoom (BC)
> geplant. Für die Praktika ist aktuell die Durchführung über wöchentliche
> Zoom-Meetings geplant.


### Anmerkung zur Kooperation zw. FH Bielefeld und University of Alberta

Über das Projekt "We CAN virtuOWL" der FH Bielefeld ist im Winter 2021 eine
Kooperation mit der University of Alberta in Edmonton, Alberta (Canada) im
Modul "Compilerbau" gestartet.

Wir werden im Rahmen der Lehrveranstaltung wenige ausgewählte Sitzungen
gemeinsam mit Studierenden und Dozenten der University of Alberta durchführen.
Das genaue Konzept wird aktuell noch entwickelt, es sind gemeinsame Vorträge,
Diskussionsrunden oder auch kleine gemeinsame Aufgaben denkbar.

**Die Unterrichtssprache ist Deutsch**. Die gemeinsam durchgeführten Sitzungen
werden abweichend in **Englisch** durchgeführt.
:::::::::







<!-- DO NOT REMOVE - THIS IS A LAST SLIDE TO INDICATE THE LICENSE AND POSSIBLE EXCEPTIONS (IMAGES, ...). -->
::: slides
## LICENSE
![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)

Unless otherwise noted, this work is licensed under CC BY-SA 4.0.
:::
