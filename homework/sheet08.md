---
author: Carsten Gips, BC George (HSBI)
no_beamer: true
title: "Blatt 08: Mini-Projekt C++"
---

# Aufgabe

Entwickeln Sie in Ihrem 3er-Team gemeinsam einen Interpreter für C++.

Nutzen Sie als Implementierungssprache Java.[^1] Sie können ANTLR zur Erstellung
Ihres Lexers und Parsers einsetzen, Sie können aber auch gern einen selbst
implementierten LL-Parser mit *recursive descent* einsetzen.

Der Interpreter muss den zu interpretierenden C++-Code zumindest beim Start aus
einer Datei einlesen können.

Danach soll dem User eine REPL angeboten werden, die einen Prompt in der Konsole
ausgibt und in der weitere C++-Statements eingegeben werden können, die dann im
Kontext des bisher verarbeiteten Codes interpretiert werden. Nach der Interpretation
soll es eine Ausgabe des letzten Ergebnisses (oder Fehlers) auf der Konsole geben,
und dann soll ein neuer Prompt ausgegeben und auf die nächste User-Eingabe gewartet
werden. Implementieren Sie eine spezielle Eingabe, mit der die REPL beendet werden
kann.

Entwickeln Sie in Ergänzung zu den Vorgaben weitere verschiedene Eingabebeispiele in
unterschiedlicher Komplexität, mit denen Sie Ihren Interpreter testen
können.

## Sprachumfang

Sie sollen mindestens folgende C++-Konzepte unterstützen:

-   Basisdatentypen: `bool`, `int`, `char`
-   Variablen
-   Arrays
-   C++-Referenzen
-   Zuweisungen und Expressions
-   Kontrollfluss: `if`-`then`-`else`, `while`-Schleifen
-   Funktionen (Definition, Deklaration, Aufrufe)
-   Klassen (mit Attributen und Methoden), Initialisierungslisten
-   Einfach-Vererbung
-   Polymorphie (dynamisch, statisch)
-   Eingebaute Funktionen: `print_bool`, `print_int`, `print_char` (Ausgabe eines
    Werts des jeweiligen Typs auf der Konsole)

Beachten Sie bei der Umsetzung, dass Polymorphie in C++ etwas anders funktioniert
als in Java.

Andere mit C++ verbundene Konzepte wie beispielsweise Präprozessor, Header-Files,
Pointer, Templates, Sichtbarkeiten in Klassen, Trennung Deklaration/Implementierung
bei Klassen (Trennung .h und .cpp) brauchen Sie
nicht umsetzen.

Sie finden im
[Starter-Projekt](https://github.com/Compiler-CampusMinden/student-support-code-template/tree/master/src/main/resources/cpp)
einige Beispiele, die mindestens umgesetzt werden sollten und die Sie zum Testen
Ihres Interpreters nutzen können. Beachten Sie, dass diese Sammlung
nicht vollständig ist.

## Projektvorstellung: Walk-Through statt Präsentation

Stellen Sie Ihr Projekt am Semesterende vor (Termine siehe Fahrplan und
Ankündigung).

Jedes Team hat dafür 15 Minuten Zeit.

Gehen Sie dabei am Code durch Ihr Projekt und diskutieren Sie relevante Teile,
mindestens aber:

-   Grammatik
-   AST
-   Semantische Analyse
-   Interpreter

Demonstrieren Sie die Funktionsfähigkeit mit Ihren C++-Codebeispielen.

**Sie sollen keine Folien erstellen. Die Präsentation soll live in der IDE
erfolgen.**

# Abgabeformat

Geben Sie im Post Mortem die URL zu Ihrem Repo an. Denken Sie daran, dass das Repo öffentlich einsehbar sein muss.

[^1]: Nach vorheriger **Absprache** können Sie auch eine andere
    Implementierungssprache verwenden.
