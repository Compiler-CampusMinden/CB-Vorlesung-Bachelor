---
archetype: assignment
title: "Blatt 02: CFG"
author: "BC George, Carsten Gips (HSBI)"
points: "10 Punkte"

hidden: true
---

<!--  pandoc -s -f markdown -t markdown+smart-grid_tables-multiline_tables-simple_tables --columns=94 --reference-links=true  sheet02.md  -o xxx.md  -->

## A2.1: PDA (2P)

Erstellen Sie eine deterministischen PDA, der die Sprache
$L = \lbrace w \in {a, b, c}^* | w\ \text{hat doppelt so viele a's wie c's} \rbrace$ akzeptiert.

Beschreiben Sie Schritt für Schritt, wie der PDA die Eingaben *bcaba* und *bccac* abarbeitet.


## A2.2: Akzeptierte Sprache (1P)

Ist der folgenden PDA deterministisch? Warum (nicht)?


Bild folgt

Welche Sprache akzeptiert er?


## A2.3: Epsilon-Übergänge (2P)

Entwickeln Sie einen Algorithmus, der einen PDA mit $\epsilon$ - Übergängen in einen ohne diese umwandelt.


## A2.4 Kontextfreie Sprache (1P)

Welche Sprache generiert die folgende kontextfreie (Teil-) Grammatik?

$G = (\lbrace Statement, Condition, \ldots \rbrace, \lbrace "if", "else", \ldots \rbrace, P, Statement)$

mit $P =$

$\lbrace Statement \rightarrow "if"\ Condition\ Statement\ | \ "if"\ Condition\ Statement\ "else"\ Statement$

$Condition \rightarrow \ldots\}$

Ist die Grammatik mehrdeutig? Warum (nicht)?


## A2.5 Kontextfreie Grammatik (2P)

Enwickeln Sie eine kontextfreie Grammatik für die Sprache

$L = \{a^ib^jc^k\ | \ i = j \lor j = k\}$

Zeigen Sie, dass die Grammatik mehrdeutig ist. Entwickeln Sie einen PDA für diese Sprache.


## A2.6 Kontextfreie Grammatik (2P)

Die folgende kontextfreie Grammatik ist mehrdeutig. Warum? Welche Sprache erzeugt sie? Wandeln Sie sie in eine eindeutige Grammatik um.

$G = (\{S\}, \{a, b\}, P, S)$ mit $P =$

$\{S \rightarrow SS\ | \ aS\ |\ Sb\ |\ \epsilon\}$




