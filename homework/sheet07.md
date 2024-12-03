---
archetype: assignment
title: "Blatt 07: Mini-Projekt C++"
author: "BC George, Carsten Gips (HSBI)"

hidden: true
---

<!--  pandoc -s -f markdown -t markdown+smart-grid_tables-multiline_tables-simple_tables --columns=94 --reference-links=true  sheet07.md  -o xxx.md  -->

## Aufgabe

Entwickeln Sie in Ihrem 3er-Team gemeinsam einen Interpreter *oder* einen Compiler für C++.

Nutzen Sie als Implementierungssprache Java. Sie können ANTLR zur Erstellung Ihres Lexers und
Parsers nutzen.

### Variante A: Interpreter

Der Interpreter muss den zu interpretierenden Code aus einer Datei einlesen können.

Sie brauchen keine interaktive Interpretation implementieren, d.h. eine REPL ist nicht
notwendig. Der Interpreter muss bei Bedarf an relevanten Stellen einen Log-Output erzeugen, um
die Arbeitsweise des Programms nachvollziehen zu können. Das Arbeitsergebnis soll auf der
Konsole ausgegeben werden.

### Variante B: Compiler

Der Compiler muss den zu kompilierenden Code aus einer Datei einlesen können.

Der Compiler soll gültigen Java-Code erzeugen und in eine Datei speichern. Definieren Sie ggf.
nötige Hilfsbibliotheken, so dass man den generierten Code zusammen mit den Hilfsbibliotheken
mit Java übersetzen und ausführen kann.

### Sprachumfang

Sie sollen mindestens folgende C++-Konzepte unterstützen:

-   Basisdatentypen: `bool`, `int`, `double`, `char`
-   Variablen
-   Arrays
-   C++-Referenzen
-   Kontrollfluss: `if`-`then`-`else`, `for`-Schleifen
-   Funktionen
-   Klassen
-   Einfach-Vererbung
-   Polymorphie (dynamisch, statisch)
-   Eingebaute Funktionen: `print_bool`, `print_int`, `print_double`, `print_char`

Beachten Sie bei der Umsetzung, dass Polymorphie in C++ etwas anders funktioniert als in Java.

Andere mit C++ verbundene Konzepte wie beispielsweise Präprozessor, Header-Files, Pointer oder
Templates brauchen Sie nicht umsetzen.

### Dokumente und Präsentation

Dokumentieren Sie den Entwicklungsprozess, die Herausforderungen und die Lösungen, die Sie
gefunden haben. Erstellen Sie dazu ein PDF mit 10 bis 16 Seiten (DIN-A4). Behandeln Sie darin
folgende Punkte:

-   Einführung ins Projekt
-   Technische Architektur des Interpreters bzw. Compilers
-   Reflexion: Herausforderungen und Lösungen
-   Fazit und Ausblick

Halten Sie eine Präsentation von ca. 30 Minuten (Termine siehe Fahrplan und Ankündigung), in
der Sie den Interpreter bzw. Compiler vorstellen und die Architektur und die von Ihnen
gewählten Lösungsansätze erläutern.

## Abgabeformat

Reichen Sie alle relevanten Unterlagen elektronisch über ILIAS ein. Dazu gehören:

1.  Quellcode des Interpreters bzw. Compilers (als ZIP)
2.  Projektdokumentation (als PDF)
3.  Präsentation (als PDF)

## Bewertungskriterien

1.  **Inhalt (50 Punkte)**

    -   **Themenverständnis (30 Punkte)**: Wurde das Thema klar und umfassend dargestellt?
        Wurde das Fachwissen adäquat vermittelt?
    -   **Argumentation und Nachvollziehbarkeit (20 Punkte)**: Sind die Konzepte logisch und
        schlüssig aufgebaut? Werden die Aussagen durch relevante Beispiele gestützt?

2.  **Struktur (30 Punkte)**

    -   **Aufbau (10 Punkte)**: Gibt es eine klare Einleitung, einen strukturierten Hauptteil
        und einen prägnanten Schluss?
    -   **Gestaltung (10 Punkte)**: Wurden geeignete und ansprechende visuelle Hilfsmittel
        eingesetzt (Diagramme, Abbildungen)? Unterstützen diese die Inhalte oder lenken sie
        eher ab?
    -   **Roter Faden (10 Punkte)**: Wird der rote Faden während des gesamten Vortrags
        beibehalten? Ist der Zusammenhang zwischen den einzelnen Punkten nachvollziehbar?

3.  **Präsentation (20 Punkte)**

    -   **Gestik, Mimik und Sprache (10 Punkte)**: Ist die Sprache klar, verständlich und
        angemessen? Ist die Stimmlage dynamisch und ansprechend? Ist das Tempo angemessen?
    -   **Zeitmanagement (10 Punkte)**: Wurde das der Zeitrahmen (30 Minuten pro Vortrag)
        eingehalten?

Gesamtbewertung: 100 Punkte
