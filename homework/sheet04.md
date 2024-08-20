---
archetype: assignment
title: "Blatt 04: Builder und freie Aufgabe (Mini-Python)"
author: "BC George, Carsten Gips (HSBI)"

hidden: true
---


## A4.1: Mini-Python, Builder

Erweitern Sie Ihr Projekt zu einem Compiler, indem Sie unseren [CBuilder]
einbinden. Erzeugen Sie damit aus dem geparsten Mini-Python-Code passenden
C-Code, den Sie mit der im [CBuilder] mitgelieferten [C-Runtime] in ein
lauffähiges Programm übersetzen und ausführen können. Beachten Sie dazu
auch die [Dokumentation].

[CBuilder]: https://github.com/Compiler-CampusMinden/Mini-Python-Builder
[C-Runtime]: https://github.com/Compiler-CampusMinden/Mini-Python-Builder/tree/master/c-runtime
[Dokumentation]: https://github.com/Compiler-CampusMinden/Mini-Python-Builder/tree/master/docs


## A4.2: Freie Aufgabe: Zusätzliche Konzepte und Features

Überlegen Sie sich zusätzliche Konzepte und Features, die Sie in Ihren
Interpreter/Compiler einbauen wollen. Dies können zusätzliche Features
auf Sprachebene sein oder Ergänzungen/Erweiterungen Ihres Interpreters
bzw. Compilers. Geben Sie im ILIAS eine kurze Konzeptskizze als PDF ab.

Beispiel: Sie könnten neue syntaktische Elemente in Mini-Python einführen,
die intern auf die existierende Semantik abgebildet werden ([_syntactic sugar_]).
Hier könnten Sie eine `for`-Schleife einbauen, die intern auf die bereits
existierende `while`-Schleife abgebildet wird. (Sie sollen sich aber
selbst Features überlegen - die `for`-Schleife können Sie also nicht
nehmen :-)

Stellen Sie diese Ideen im Praktikum vor und verteidigen Sie diese.

[_syntactic sugar_]: https://en.wikipedia.org/wiki/Syntactic_sugar


---


## Ausblick Wochen 01 bis 04 in 2024

### Umsetzung

Setzen Sie die im Praktikum abgestimmten Features bis zum Vortrag in den letzten
beiden Sitzungen um. Nutzen Sie aktiv die freigewordenen VL-Slots.
(_Wir hatten am Anfang des Semesters absichtlich einige Praktikumstermine mit
Vorlesungen belegt, damit Sie möglichst schnell die Inhalte kennenlernen und
dann die Praktikumsaufgaben entsprechend planen und umsetzen können. Zum
Ausgleich sind nun einige Vorlesungstermine am Ende des Semesters der freien
Arbeit gewidmet._)

### Vortrag

Bereiten Sie Ihren Vortrag zur Vorstellung der Ergebnisse Ihrer freien Aufgabe
(Konzeption und Umsetzung der zusätzlichen Features in den letzten beiden
Sitzungen vor.
