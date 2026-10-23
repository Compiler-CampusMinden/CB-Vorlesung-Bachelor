---
author: Carsten Gips (HSBI)
no_beamer: true
title: "Blatt 04: L-Expr und C-Expr (Vorrang, unäres Minus und ANTLR)"
---

::: important
Für die erfolgreiche Bearbeitung dieses Übungsblattes müssen mindestens alle mit `*`
und `**` markierten Aufgaben gelöst werden.

Die Aufgaben mit `***` sind als Vertiefung gedacht.
:::

# (\*) L-Expr: Multiplikation und Division ergänzen

Sie haben in der Vorlesung L-Int kennengelernt (Integer-Literale, Addition,
Subtraktion in Lispy-Notation) und L-Expr als Erweiterung um Multiplikation und
Division gesehen.

1.  **Konkrete Syntax verstehen**

    Klären Sie in der Übung gemeinsam:

    -   Welche Ausdrücke sind **gültige** L-Expr-Ausdrücke?
    -   Wie werden mehrstellige Multiplikationen und Divisionen gruppiert
        (Assoziativität)?
    -   Welche Werte ergeben die folgenden Ausdrücke?

``` clojure
```

          (* 2 3)
          (/ 8 2)
          (* 2 3 4)
          (/ 12 3 2)
          (* (+ 1 2) 3)
          (/ 12 (* 2 2))

Nutzen Sie dabei die Semantik der ganzzahligen Division wie in Java (Abrunden
Richtung 0).

2.  **Ungültige Eingaben**

    Notieren Sie mindestens zwei **ungültige** L-Expr-Eingaben, z.B.:

    -   Operationen mit weniger als zwei Operanden,
    -   falsche Klammerung,
    -   unerwartete Token.

3.  **Pipeline um Multiplikation/Division erweitern**

    Ergänzen Sie Ihre L-Int-Pipeline vollständig um Multiplikation und Division:

    -   Lexer: neue Token für `*` und `/`.
    -   Parser (RD-Parser für Lispy): zusätzliche Alternativen in den passenden
        Grammatikregeln.
    -   AST: neue Knotenklassen `Mul` und `Div`.
    -   Interpreter: Auswertung von `Mul` und `Div` (linksassoziativ, Java-Integer-
        Division).

# (\*\*) L-Expr: Unäres Minus als syntaktischer Zucker

Wir wollen in L-Expr unäres Minus (`-x`) zulassen, ohne einen eigenen AST-Knoten
dafür einzuführen.

1.  **Konkrete Syntax für unäres Minus**

    Erweitern Sie Ihre konkrete Lispy-Syntax so, dass auch Ausdrücke der Form

``` clojure
```

         (- 3)
         (- (+ 1 2))
         (- (* 2 3))

syntaktisch erlaubt sind und als "unäres Minus" interpretiert werden.

Diskutieren Sie:

    - Sollen auch mehrere Argumente bei `-` erlaubt bleiben (wie bisher bei L-Int)?
    - Wie unterscheiden Sie "klassische" mehrstellige Subtraktion von unärem Minus?

2.  **Desugaring-Idee**

    Formulieren Sie, wie unäres Minus in "normale" Subtraktions-Ausdrücke
    umgeschrieben werden kann, z.B.:

    -   `(- x)` $\to$ `(- 0 x)`
    -   `(- (+ 1 2))` $\to$ `(- 0 (+ 1 2))`

    Geben Sie dies zunächst rein **informell in Worten** an.

3.  **AST-Seite**

    Beschreiben Sie, wie Sie Ihre AST-Konstruktion anpassen würden:

    -   Variante A: Parser erzeugt zunächst einen temporären `UnaryMinus`-Knoten und
        ein nachgelagerter Schritt wandelt in `Sub(IntLit(0), expr)` um.
    -   Variante B: Parser erkennt unäres Minus und baut **direkt** einen `Sub`-
        Knoten mit linker Konstante `0`.

    Entscheiden Sie sich für eine der Varianten und skizzieren Sie, wo der
    Desugaring-Schritt in Ihre Pipeline passt.

# (\*) C++ ausprobieren: Vorrang und unäres Minus live testen

Wir wollen die Vorrangregeln und unäres Minus **direkt in C++** ausprobieren.

::: important
## Waschzettel: In C++ sieht es so aus ...

| Zweck           | L-Expr (Lispy)  | C++ (Infix)    |
|:----------------|:----------------|:---------------|
| Multiplikation  | `(* 2 3)`       | `2 * 3`        |
| Division        | `(/ 8 3)`       | `8 / 3`        |
| Addition        | `(+ 1 2 3)`     | `1 + 2 + 3`    |
| Subtraktion     | `(- 7 2 1)`     | `7 - 2 - 1`    |
| Unäres Minus    | `(- 3)`         | `-3`           |
| Klammerung      | `(* (+ 1 2) 3)` | `(1 + 2) * 3`  |
| Zeilenkommentar | `;; Kommentar`  | `// Kommentar` |
:::

2.  **C++-Programm: Vorrang und Assoziativität**

    Schreiben Sie ein C++-Programm `expr.cpp`, das folgende Ausdrücke auswertet und
    jeweils das Ergebnis ausgibt (Sie dürfen mehrere `std::cout`-Zeilen verwenden):

          1 + 2 * 3
          (1 + 2) * 3
          8 / 4 / 2
          (8 / 4) / 2
          8 / (4 / 2)
          7 - 2 - 1
          7 - (2 - 1)
          -3 * 4
          -(3 * 4)

    Vorschlag für das Grundgerüst:

        #include <iostream>

        int main() {
            std::cout << (1 + 2 * 3) << '\n';
            // ...
            return 0;
        }

    Übersetzen und starten Sie das Programm mit `clang++` oder `g++`:

        clang++ expr.cpp -o expr
        ./expr

    oder

        g++ expr.cpp -o expr
        ./expr

3.  **Vergleich mit Ihrer Grammatik und Java-Division**

    Vergleichen Sie die beobachteten C++-Ergebnisse mit

    -   Ihrer gestuften Grammatik (Vorrang, Assoziativität),
    -   und der ganzzahligen Java-Division.

    Zusatz: Überlegen Sie, welchen Wert die folgenden Ausdrücke in Ihrer
    Java-Implementierung und in C++ liefern (bei ganzzahliger Division):

        7 / 3
        -7 / 3
        7 / -3
        -7 / -3

    Begründen Sie kurz, dass (oder ob) das mit Ihrer Interpreter-Semantik
    übereinstimmt.

# (\*\*) C-Expr: Vorrangregeln in einer gestuften Grammatik (Infix-Variante)

Wir betrachten eine C++-artige Infix-Syntax, die nur Integer-Literale sowie
Addition, Subtraktion, Multiplikation, Division und unäres Minus erlaubt.

1.  **Konkrete Grammatik (Gestufte Variante)**

    Definieren Sie eine konkrete Grammatik (z.B. in EBNF), die folgende
    Anforderungen erfüllt:

    -   Zulässige Ausdrücke enthalten:
        -   Integer-Literale,
        -   binäre Operatoren `+`, `-`, `*`, `/`,
        -   **unäres Minus** (`-x`),
        -   Klammern `(` und `)`.
    -   Multiplikation/Division haben **höheren Vorrang** als Addition/Subtraktion.
    -   Alle vier Operatoren sind **linksassoziativ**.
    -   Whitespace darf an beliebigen sinnvollen Stellen stehen und wird ignoriert.

    Skizzieren Sie Ihre Grammatik ausdrücklich mit gestuften Regeln, z.B.
    `expr`/`term`/`factor`, inklusive einer sinnvollen Stelle für unäres Minus
    (typischerweise innerhalb von `factor`).

2.  **Beispiele überprüfen**

    Überprüfen Sie mit Ihrer Grammatik:

    -   Wie wird `1 + 2 * 3` geparst und ausgewertet?
    -   Wie wird `8 / 4 / 2` geparst und ausgewertet?
    -   Wie wird `-3 * 4` geparst und ausgewertet?
    -   Wie werden Klammern berücksichtigt, z.B. `(1 + 2) * 3`, `-(1 + 2) * 3`?

    Zeichnen Sie **mindestens einen** Parse-Tree für einen Ausdruck ohne Klammern
    und **einen** Parse-Tree mit Klammern und unärem Minus.

# (\*\*) ANTLR-Grammatik für C-Expr (Infix-Variante)

Wir wollen nun eine ANTLR-Grammatik für eine einfache Infix-Variante von C-Expr
bauen. Nutzen Sie entweder die gestufte Variante oder die linksrekursive Variante
mit Vorrang über Alternativen und unärem Minus.

1.  **ANTLR-Grammatik definieren**

    Definieren Sie eine ANTLR-Grammatik `CExpr.g4`, die folgendes akzeptiert:

    -   Integer-Literale (`INT`).
    -   Binäre Operatoren `+`, `-`, `*`, `/` mit C++-üblichem Vorrang
        (Multiplikation/Division binden stärker).
    -   Unäres Minus (`-x`).
    -   Klammern `(` und `)`.
    -   Whitespace wird ignoriert.

    Nutzen Sie eine der beiden Varianten:

    -   **Gestuft** (`expr`/`term`/`factor` mit unärem Minus in `factor`), oder
    -   **Linksrekursiv** mit geordneter Alternativliste und `<assoc=left>`, plus
        zusätzlicher Alternative für `UnaryMinus`.

2.  **Testfälle überlegen**

    Notieren Sie mindestens fünf Testausdrücke, die Sie mit der Grammatik parsen
    möchten, z.B.:

        42
        1+2*3
        (1+2)*3
        -3*4
        8/4/2
        7-2-1
        -(1+2)*3

    Überlegen Sie, wie die Parse-Bäume ungefähr aussehen sollten (Skizze).

# (\*\*) ANTLR-Visitor: Auswertung von C-Expr

Nutzen Sie Ihre ANTLR-Grammatik aus der vorherigen Aufgabe und lassen Sie ANTLR den
Parser und Visitor generieren.

1.  **Evaluations-Visitor implementieren**

    Implementieren Sie einen Evaluations-Visitor, der einen `Integer` zurückliefert
    und C-Expr-Ausdrücke vollständig auswertet (die vier Operatoren, unäres Minus
    und Klammern).

    -   Wählen Sie den generischen Typ angemessen, z.B. `CExprBaseVisitor<Integer>`.
    -   Überschreiben Sie alle `visitXYZ()`-Methoden, für die Sie eine eigene
        Semantik benötigen (mindestens die Operatorregeln, Int-Literal-Regel, unäres
        Minus).
    -   Verwenden Sie Java-Integer-Division.

2.  **Testen des Visitors**

    Schreiben Sie eine kleine `main()`-Methode in Java, die:

    -   einen Ausdruck als String entgegennimmt (z.B. fest im Code oder über
        Kommandozeilenargumente),
    -   Lexer und Parser von ANTLR aufruft (`CExprLexer`, `CExprParser`),
    -   den Parse-Baum für die oberste Regel (`expr`) holt,
    -   Ihren `EvalVisitor` darauf anwendet und das Ergebnis ausgibt.

3.  **Reflexion: Default-Visitor vs. Überschreiben**

    Beantworten Sie schriftlich:

    -   Für welche Regeln Ihrer Grammatik reicht die Default-Implementierung
        `visitChildren()` aus? Begründen Sie.
    -   Für welche Regeln ist eine explizite `visitXYZ()`-Methode notwendig? Geben
        Sie kurz an, was dort ungefähr passieren muss (z.B. unäres Minus: `0 - x`).

# (\*\*\*) Vertiefung: AST-Bau statt direkter Auswertung

Bisher wertet Ihr Visitor die Ausdrücke direkt aus. Alternativ könnten Sie einen
Visitor schreiben, der einen **AST** für C-Expr aufbaut (ähnlich Ihrer Lispy-ASTs).

1.  **AST-Klassen für C-Expr**

    Definieren Sie AST-Klassen (z.B. `IntLit`, `Add`, `Sub`, `Mul`, `Div`) für
    C-Expr. Unäres Minus soll auch hier nicht als eigener Knoten vorkommen, sondern
    als `Sub(IntLit(0), expr)` modelliert werden.

2.  **AST-Builder-Visitor**

    Implementieren Sie einen ANTLR-Visitor, der statt eines `Integer` einen
    `Expr`-AST-Knoten zurückliefert. Vergleichen Sie Aufbau und Code mit Ihrem
    Evaluations-Visitor.

3.  **Diskussionsfrage**

    Skizzieren Sie Vor- und Nachteile der beiden Ansätze:

    -   Direkte Auswertung im ANTLR-Visitor.
    -   Erst AST-Bau im ANTLR-Visitor und spätere Auswertung in einem getrennten
        Interpreter.

    Gehen Sie dabei auch kurz darauf ein, wie gut sich unäres Minus jeweils
    integrieren lässt.


---



::: tip
## Exkurs: Non-greedy Lexer-Regeln

Die regulären Ausdrücke `(...)?`, `(...)*` und `(...)+` sind *greedy* und versuchen
soviel Input wie möglich zu matchen.

Falls dies nicht sinnvoll sein sollte, kann man mit einem weiteren `?` das Verhalten
auf *non-greedy* umschalten. Allerdings können non-greedy Regeln das Verhalten des
Lexers u.U. schwer vorhersehbar machen!


Non-greedy Regeln versuchen *so wenig* Zeichen wie möglich zu matchen

``` antlr
FOO     : 'foo' .*? 'bar' ;
BAR     : 'bar' ;
```

Hier würde ein "foo42barbar" zu `FOO` gefolgt von `BAR` erkannt werden.

Achtung: Nach [dem Abarbeiten]{.notes} einer non-greedy Sub-Regel [in einer
Lexer-Regel]{.notes} gilt "*first match wins*"

`.*? ('4' | '42')`

=\> [Der Teil]{.notes} `'42'` [auf der rechten Seite]{.notes} ist "toter Code"
(wegen der non-greedy Sub-Regel `.*?`)!

Die Eingabe "x4" würde korrekt erkannt, währende "x42" nur als "x4" erkannt wird und
für die verbleibende "2" würde ein *token recognition error* geworfen.

Die Empfehlung ist, non-greedy Lexer-Regeln nur sparsam einzusetzen (vgl.
[github.com/antlr/antlr4/blob/master/doc/wildcard.md](https://github.com/antlr/antlr4/blob/master/doc/wildcard.md)).
:::

::: tip
## Exkurs: Konflikte in Regeln und implizite Token

Wenn mehrere Alternativen einer Regel anwendbar sind, entscheidet sich ANTLR für die
erste Alternative.

Wenn sich mehrere Tokenregeln überlappen, "gewinnt" auch hier die zuerst definierte
Regel.

``` antlr
def : 'func' ID '(' ')' block ;

FOR : 'for' ;
ID  : [a-z][a-zA-Z]* ;
```

Hier werden ein implizites Token `'func'` sowie die expliziten Token `FOR` und `ID`
definiert. Dabei sind die Lexeme für `'func'` und `FOR` auch in `ID` enthalten.
Dennoch werden `'func'` und `FOR` erkannt und nicht über `ID` gematcht, weil sie
*vor* der Regel `ID` definiert sind.

Tatsächlich sortiert ANTLR die Regeln intern um, so dass alle Parser-Regeln *vor*
den Lexer-Regeln definiert sind. Die impliziten Token werden dabei noch *vor* den
expliziten Token-Regeln angeordnet. Im obigen Beispiel hat also `'func'` eine höhere
Priorität als `FOR`, und `FOR` hat eine höhere Priorität als `ID`. Aus diesem Grund
gibt es die Konvention, die Parser-Regeln in der Grammatik vor den Lexer-Regeln zu
definieren - dies entspricht quasi der Anordnung, die ANTLR bei der Verarbeitung
sowieso erzeugen würde.

Aus diesem Grund würde auch eine Umsortierung der obigen Grammatik funktionieren:

``` antlr
FOR : 'for' ;
ID  : [a-z][a-zA-Z]* ;

def : 'func' ID '(' ')' block ;
```

Intern würde ANTLR die Parser-Regel `def` wieder vor den beiden Lexer-Regeln
anordnen, und zwischen den Parser-Regeln und den Lexer-Regeln die impliziten Token
(hier `'func'`).

## Exkurs: Lustige Probleme mit überlappenden Token (typische Stolperfalle)

Die folgende Grammatik sieht harmlos aus:

``` antlr
foo  :  (ID '(' ')' '=' '0' | ID | NUM) EOF ;

ID      : [a-z][a-zA-Z]* ;
NUM     : [0-9]+ ;
WS      : [ \t\n]+ -> skip ;
```

Was passiert bei der Eingabe von `10` und `01` und `a() = 0`, wie sieht der
Parse-Tree aus? Was passiert bei der Eingabe von `0`?

Antwort: `10` wird als `foo -> NUM(10)` erkannt, `01` als `foo -> NUM(01)`, und
`a() = 0` wird zu einem `foo -> ID(a), (, ), =, 0`. Dagegen ist die Eingabe `0` ein
Fehler!

Das liegt hier an überlappenden Token-Definitionen: Die `0` wird als implizites
Token definiert, während die Integerzahlen als explizites Token `NUM` definiert
werden. Damit ist die `0` in `NUM` enthalten. Da ANTLR die impliziten Token intern
vor den expliziten Token definiert (egal, in welcher Reihenfolge wir die Grammatik
aufbauen), fällt die Eingabe "0" an das implizite Token `0` und nicht an `NUM`. Da
es keine Regel gibt, wo eine einzelne "0" erlaubt ist, bekommen wir einen Fehler.
Sobald die Eingabe länger wird, greift wieder die Regel des längsten Matches und
`NUM` "gewinnt".

:::
:::



## Vorrang und Assoziativität

Betrachten Sie erneut die Grammatik aus der Vorlesung


```ebnf
expr  ::= term ('+' term)*
term  ::= atom ('*' atom)*
atom  ::= '-' atom
        | INT
```

Bauen Sie noch die Subtraktion und die Division mit ein.

Außerdem sollen geklammerte
Ausdrücke erlaubt werden, z.B. `1*(2+3)`. Wo muss die Regel ergänzt werden, um
die korrekte Präzedenz zu erhalten?
