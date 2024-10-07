---
archetype: assignment
title: "Blatt 01: Reguläre Sprachen"
author: "BC George, Carsten Gips (HSBI)"

hidden: true

sketch: true
---


## A1.1: Bezeicher in Programmiersprachen

Betrachen Sie eine Programmiersprache, in der die Bezeichner (= Namen für Variablen, Funktionen, Klassen, Methoden, ...) folgenden Aufbau haben:

*   Alle Variablennamen beginnen mit *V* oder **v**

*   Handelt es sich um globale Variablen, beginnen Sie mit **V**, lokale beginnen mit **v**

*   Funktions- und Methodenparameter beginnen mit **p**, KLassenparameter (bei der Definition von Vererbung) beginnen mit **P**

*   Weitere Bezeichner müssen mit einem Buchstaben (a.z, A-Z) beginnen

*   Die folgenden Zeichen dürfen Buchstaben, Ziffern und ein Untersreich sein

*   Bezeichner dürfen nicht mit einem Unterstrich enden

*   Alle Bezeichner müssen aus mindestens zwei Zeichen bestehen


Entwickeln Sie einen regulären Ausdruck, der den Aufbau der Bezeichner beschreibt.
Beachten Sie, dass Ihr regex alle zulässigen Bezeichner bechreiben muss, aber keinen einzigen unzulässigen bechreiben darf. Wählen Sie zwei Bezeichner aus der Spache und zeigen Sie, wie sie vom regex gematcht werden.

Entwickeln Sie einen DFA, der diese Bezeichner akzeptiert.
Beachten Sie, dass Ihr DFA alle zulässigen Bezeichner akzeptiren muss, aber keinen einzigen unzulässigen akzeptieren darf. Wählen Sie zwei Bezeichner aus der Spache und zeigen Sie, wie sie vom Automaten zeichenweise gelesen und akzeptiert werden.

Entwickeln Sie eine reguläre Grammatik, die diese Bezeichner generiert.
Beachten Sie, dass Ihre Grammatik alle zulässigen Bezeichner generieren können muss, aber keinen einzigen unzulässigen generieren darf. Wählen Sie zwei Bezeichner aus der Spache und zeigen Sie die Ableitungsbäume dazu.


## A1.2: Gleitkomamzahlen in Programmiersprachen
Recherchieren Sie zunächst den Aufbau von Gleitkomamzahlen in Python und Java.

Erstellen Sie für jede der beiden Programmiersprachen reguläre Ausdrücke, DFAs und reguläre Grammatiken wie in Aufgabe 1. Verifizieren Sie Ihre Lösungen wie in Aufgabe 1.


## A1.3: Welche Sprachen werden von den folgenden regulären Ausdrücken akzeptiert?
