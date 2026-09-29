---
no_beamer: true
no_pdf: true
title: Reguläre Sprachen, kontextfreie Grammatiken und Sprachen, lexikalische und
  syntaktische Analyse
---

In der lexikalischen Analyse soll ein Lexer (auch "Scanner") den Zeichenstrom in
eine Folge von Token zerlegen. Zur Spezifikation der Token werden in der Regel
reguläre Ausdrücke verwendet.

In der syntaktischen Analyse arbeitet ein Parser mit dem Tokenstrom, der vom Lexer
kommt. Mit Hilfe einer Grammatik wird geprüft, ob gültige Sätze im Sinne der
Sprache/Grammatik gebildet wurden. Der Parser erzeugt dabei den Parse-Tree. Man kann
verschiedene Parser unterscheiden, beispielsweise die LL- und die LR-Parser.
