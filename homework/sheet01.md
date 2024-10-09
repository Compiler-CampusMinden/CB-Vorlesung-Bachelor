---
archetype: assignment
title: "Blatt 01: Reguläre Sprachen"
author: "BC George, Carsten Gips (HSBI)"

hidden: true

sketch: true
---

## A1.1 Sprachen von regulären Ausdrücken

Welche Sprache wird von dem folgenden regulären Ausdruck beschrieben?

$a\ +\ a\ (a\ +\ b)^*\ a$


## A1.2: Bezeicher in Programmiersprachen

Betrachen Sie eine Programmiersprache, in der die Bezeichner (= Namen für Variablen, Funktionen, Klassen, Methoden, ...) folgenden Aufbau haben:

*   Alle Variablennamen beginnen mit **V** oder **v**

*   Handelt es sich um globale Variablen, beginnen Sie mit **V**, lokale beginnen mit **v**

*   Funktions- und Methodenparameter beginnen mit **p**, KLassenparameter (bei der Definition von Vererbung) beginnen mit **P**

*   Weitere Bezeichner müssen mit einem Buchstaben (a-z, A-Z) beginnen

*   Die folgenden Zeichen dürfen Buchstaben, Ziffern und ein Untersreich sein

*   Bezeichner dürfen nicht mit einem Unterstrich enden

*   Alle Bezeichner müssen aus mindestens zwei Zeichen bestehen


Entwickeln Sie einen regulären Ausdruck, der den Aufbau der Bezeichner beschreibt.
Beachten Sie, dass Ihr regex alle zulässigen Bezeichner bechreiben muss, aber keinen einzigen unzulässigen bechreiben darf. Wählen Sie zwei Bezeichner aus der Spache und zeigen Sie, wie sie vom regex gematcht werden.

Entwickeln Sie einen DFA, der diese Bezeichner akzeptiert.
Beachten Sie, dass Ihr DFA alle zulässigen Bezeichner akzeptiren muss, aber keinen einzigen unzulässigen akzeptieren darf. Wählen Sie zwei Bezeichner aus der Spache und zeigen Sie, wie sie vom Automaten zeichenweise gelesen und akzeptiert werden.

Entwickeln Sie eine reguläre Grammatik, die diese Bezeichner generiert.
Beachten Sie, dass Ihre Grammatik alle zulässigen Bezeichner generieren können muss, aber keinen einzigen unzulässigen generieren darf. Wählen Sie zwei Bezeichner aus der Spache und zeigen Sie die Ableitungsbäume dazu.


## A1.3: Gleitkomamzahlen in Programmiersprachen
Recherchieren Sie zunächst den Aufbau von Gleitkomamzahlen in Python und Java.

Erstellen Sie für jede der beiden Programmiersprachen reguläre Ausdrücke, DFAs und reguläre Grammatiken wie in Aufgabe 1. Verifizieren Sie Ihre Lösungen wie in Aufgabe 1.


## A1.4: Mailadressen?

Warum ist der folgende regex ungeeignet für die Verarbeitung von Mailadressen?

\medskip

$(a-z)^+@(a-z).(a-z)$

\medskip

Bitte beachten Sie, dass die Schreibweise a-z nicht unserer Definition genügt. Eigentlich müsste jedes Zeichen aufgeführt werden:

$a + b + c + c + \ldots + z$ ist besser, aber immer noch nicht richtig. Warum?

Anmerkung: Diese Darstellung wird ab jetzt akzeptiert.

Verbessern Sie den gegebenen regulären Ausdruck.

## A1.5: Sprache eines DFAs

Entwickeln Sie einen DFA, der nur Wörter über $\Sigma = \{1,2,3\}$ akzeptiert, deren zweitletztes Zeichen dasselbe ist wie das zweite.

## A1.6 Der zweitletzte Buchstabe

Entwickeln Sie einen DFA, der nur Wörter über $\Sigma = \{1,2,3\}$ akzeptiert, deren zweitletztes Zeichen dasselbe ist wie das zweite.

## A 1.7 Sprache einer regulären Grammatik

Welche Sprache generiert die folgende Grammatik?

$S \rightarrow a A$

$A \rightarrow d B \ | \ b A \ | \ c A $

$B \rightarrow a c \ | \ b C \ | \ c A$

$C \rightarrow \epsilon$





