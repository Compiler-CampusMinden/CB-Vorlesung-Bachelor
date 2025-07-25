---
title: "LL-Parser"
author: "BC George (HSBI)"
readings:
  - "@Aho2023"
  - "@hopcroft2003"
outcomes:
  - k1: "Top-Down-Analyse"
  - k1: "LL-Parser"
  - k2: "Schreiben von LL-Parsern"
  - k3: "Top-Down Analyse programmieren"
attachments:
  - link: "https://raw.githubusercontent.com/Compiler-CampusMinden/AnnotatedSlides/master/ll-parser.ann.ba.pdf"
    name: "Annotierte Folien: LL-Parser"
---


# Wiederholung


## PDAs und kontextfreie Grammatiken

*   Warum reichen uns DFAs nicht zum Matchen von Eingabezeichen?
*   Wie könnnen wir sie minimal erweitern?
*   Sind PDAs deterministisch?
*   Wie sind kontextfreie Grammatiken definiert?
*   Sind kontextfreie Grammatiken eindeutig?

# Motivation


## Was brauchen wir für die Syntaxanalyse von Programmen?

*   einen Grammatiktypen, aus dem sich manuell oder automatisiert ein Programm zur deterministischen Syntaxanalyse (=Parser) erstellen lässt
*   einen Algorithmus zum Parsen von Programmen mit Hilfe einer solchen Grammatik


## Themen für heute

*   Automatische Generierung von Top-Down-Parsern aus LL-Grammatiken



# Syntaxanalyse

## Syntax

Wir verstehen unter Syntax eine Menge von Regeln, die die Struktur von Daten (z. B. Programmen) bestimmen.

Syntaxanalyse ist die Bestimmung, ob Eingabedaten einer vorgegebenen Syntax entsprechen.

Diese vorgegebene Syntax wird im Compilerbau mit einer kontextfreien Grammatik beschrieben und mit einem sogenannten **Parser** analysiert.

Wir beshäftigen uns heute mit LL-Parsing, mit dem man eine Teilmenge der eindeutigen kontextfreien Grammatiken syntaktich analysieren kann.

Der Ableitungsbaumwird von oben nach unten aufgebaut.


## Ziele der Syntaxanalyse

*   aussagekräftige Fehlermeldungen, wenn ein Eingabeprogramm syntaktisch nicht korrekt ist
*   evtl. Fehlerkorrektur
*   Bestimmung der syntaktischen Struktur eines Programms
*   Erstellung des AST (abstrakter Syntaxbaum): Der Parse Tree ohne Symbole, die nach der Syntaxanalyse inhaltlich irrelevant sind (z. B. Semikolons, manche Schlüsselwörter)
*   die Symboltablelle(n) mit Informationen bzgl. Bezeichner (Variable, Funktionen und Methoden, Klassen, benutzerdefinierte Typen, Parameter, ...), aber auch die Gültigkeitsbereiche.


# LL(k)-Grammatiken

## First-Mengen

$S \rightarrow A \ \vert \ B \ \vert \ C$

Welche Produktion nehmen?

Wir brauchen die "terminalen k-Anfänge" von Ableitungen von Nichtterminalen, um eindeutig die nächste zu benutzende Produktion festzulegen. $k$ ist dabei die Anzahl der Vorschautoken.

**Def.:** Wir definieren $First$ - Mengen einer Grammatik wie folgt:

*   $a \in T^\ast, |a| \leq k: {First}_k (a) = \lbrace a\rbrace$
*   $a \in T^\ast, |a| > k: {First}_k (a) = \lbrace v \in T^\ast \mid a = vw, |v| = k\rbrace$
*   $\alpha \in (N \cup T)^\ast \backslash T^\ast: {First}_k (\alpha) = \lbrace v \in T^\ast \mid  \alpha \overset{\ast}{\Rightarrow} w,\text{mit}\ w \in T^\ast, First_k(w) = \lbrace v \rbrace \rbrace$


## Linksableitungen

**Def.:** Bei einer kontextfreien Grammatik $G$ ist die *Linksableitung* von $\alpha \in (N \cup T)^{\ast}$ die Ableitung, die man erhält, wenn in jedem Schritt das am weitesten links stehende Nichtterminal in $\alpha$ abgeleitet wird.

Man schreibt $\alpha \overset{\ast}{\Rightarrow}_l \beta.$


## LL(k)-Grammatiken

**Def.:** Eine kontextfreie Grammatik *G = (N, T, P, S)* ist genau dann eine *LL(k)*-Grammatik, wenn für alle Linksableitungen der Form:

$S \overset{\ast}{\Rightarrow}_l\ wA \gamma\ {\Rightarrow}_l\ w\alpha\gamma \overset{\ast}{\Rightarrow}_l wx$

und

$S \overset{\ast}{\Rightarrow}_l wA \gamma {\Rightarrow}_l w\beta\gamma \overset{\ast}{\Rightarrow}_l wy$


mit $(w, x, y \in T^\ast, \alpha, \beta, \gamma \in (N \cup T)^\ast, A \in N)$ und $First_k(x) = First_k(y)$
gilt:

$\alpha = \beta$


## LL(1)-Grammatiken

:::notes
Hier entsteht ein Tafelbild.
:::



## LL(k)-Sprachen

Die von *LL(k)*-Grammatiken erzeugten Sprachen sind eine echte Teilmenge der deterministisch parsbaren Sprachen.

Die von *LL(k)*-Grammatiken erzeugten Sprachen sind eine echte Teilmenge der von *LL(k+1)*-Grammatiken erzeugten Sprachen.

Für eine kontextfreie Grammatik *G* ist nicht entscheidbar, ob es eine *LL(1)* - Grammatik *G'* gibt mit $L(G) = L(G')$.

In der Praxis reichen $LL(1)$ - Grammatiken oft. Hier gibt es effiziente Parsergeneratoren (hier: ANTLR), deren Eingabe eine LL(k)- (meist LL(1)-) Grammatik ist, und die als Ausgabe den Quellcode eines (effizienten) tabellengesteuerten Parsers generieren.


##  Algorithmus: Konstruktion einer LL-Parsertabelle {.fragile}

**Eingabe:** Eine  Grammatik G = (N, T, P, S)

**Ausgabe:** Eine Parsertabelle *P*

![Algorithmus zur Generierung einer LL-Parsertabelle](images/LL-Parsertabelle.png){width="60%"}

Hier ist $\perp$ das Endezeichen des Inputs.
Statt $First_1(\alpha)$ wird oft nur $First(\alpha)$ geschrieben.

## LL-Parsertabellen

:::notes
Hier entsteht ein Tafelbild.
:::

## LL-Parsertabellen

Rekursive Programmierung bedeutet, dass das Laufzeitsystem einen Stack benutzt. Diesen Stack kann man auch "selbst programmieren", d. h. einen PDA implementieren. Dabei wird ebenfalls die oben genannte Tabelle zur Bestimmung der nächsten anzuwendenden Produktion benutzt. Der Stack enthält die zu erwartenden Eingabezeichen, wenn immer eine Linksableitung gebildet wird. Diese Zeichen im Stack werden mit dem Input gematcht.

## Algorithmus: Tabellengesteuertes LL-Parsen mit einem PDA {.fragile}

**Eingabe:** Eine  Grammatik G = (N, T, P, S), eine Parsertabelle *P* mit "$w\perp$" als initialem Kellerinhalt

**Ausgabe:** Wenn $w \in L(G)$,  eine Linksableitung von $w$, Fehler sonst

![Algorithmus zum tabellengesteuerten LL-Parsen](images/LL-Parser.png){width="49%"}



## Ergebnisse der Syntaxanalyse

*   eventuelle  Syntaxfehler mit Angabe der Fehlerart und des -Ortes
*   Fehlerkorrektur
*   Format für die Weiterverarbeitung:
    *   Ableitungsbaum oder Syntaxbaum oder Parse Tree
    *   abstrakter Syntaxbaum (AST): Der Parse Tree ohne Symbole, die nach der Syntaxanalyse inhaltlich irrelevant sind (z. B. ;, Klammern, manche Schlüsselwörter, $\ldots$)
*   Symboltabelle


## Wrap-Up

*   Syntaxanalyse wird mit deterministisch kontextfreien Grammatiken durchgeführt.
*   Eine Teilmenge der dazu gehörigen Sprachen lässt sich top-down parsen.
*   Ein effizienter LL(k)-Parser realisiert einen DPDA und kann automatisch aus einer LL(k)-Grammatik generiert werden.
*   Der Parser liefert in der Regel einen abstrakten Syntaxbaum.
