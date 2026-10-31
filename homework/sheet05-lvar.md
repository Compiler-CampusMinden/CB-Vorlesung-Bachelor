---
author: Carsten Gips (HSBI)
no_beamer: true
title: "Blatt 05: L-Var und C-Var (Variablen, State, Scopes)"
---

::: important
Für die erfolgreiche Bearbeitung dieses Übungsblattes müssen mindestens alle mit `*`
und `**` markierten Aufgaben gelöst werden.

Die Aufgaben mit `***` sind als Vertiefung gedacht.
:::

Dieses Blatt knüpft an folgende Vorlesungseinheiten an:

-   L-Expr: Multiplikation/Division und unäres Minus
-   L-Expr: Vorrang und Assoziativität
-   L-Expr: ANTLR-Grammatik und Vorrangregeln
-   L-Expr: ANTLR-Visitoren und Rückgabewerte

# (\*) L-Var: `NameResolverLvar#resolve()` ergänzen und L-Var-Pipeline aufbauen

Sie haben in der Vorlesung für L-Var den Name-Resolver `NameResolverLvar`
kennengelernt. Dabei wurde die Implementierung für die AST-Knoten `ExprStmt` und
`AssignStmt` (beides `Stmt`) sowie `SubExpr`, `MulExpr` und `DivExpr` (alle drei
`Expr`) nicht gezeigt.

Erstellen Sie Ihre L-Var-Pipeline, d.h. ergänzen Sie die Grammatik und leiten den
AST-Builder `class LispyAstBuilderLvar extends LispyAstBuilderLexpr` ab. Erstellen
Sie den `NameResolverLvar` mit den aus der Vorlesung bekannten Elementen und
ergänzen Sie diese mit den fehlenden fünf Fällen. Leiten Sie ebenfalls einen neuen
Interpreter `class InterpreterLvar extends InterpreterLexpr` ab.

------------------------------------------------------------------------------------

TODO

# (\*\*) C-Expr: Vorrangregeln in einer gestuften Grammatik

Wir erstellen nun **C-Expr**, indem wir **C-Int vom letzten Blatt** um
Multiplikation, Division, unäres Minus und geklammerte Ausdrücke erweitern.

C-Expr soll analog zu L-Expr **Multiplikation und Division und unäres Minus und
geklammerte Ausdrücke** erlauben, aber in C++-üblicher Infix-Notation und unter
Beachtung der üblichen Vorrang- und Assoziativitätsregeln.

::: important
## Waschzettel: In C++ sieht es so aus ...

| Zweck          | L-Expr (Lispy)  | C-Expr (Mini-C++) |
|:---------------|:----------------|:------------------|
| Multiplikation | `(* 2 3)`       | `2 * 3`           |
| Division       | `(/ 8 3)`       | `8 / 3`           |
| Unäres Minus   | `(- 3)`         | `-3`              |
| Klammerung     | `(* (+ 1 2) 3)` | `(1 + 2) * 3`     |

Während in Lispy (L-Int, L-Expr) die Operatoren für `+`, `-`, `*`, `/` mehrstellig
sein können, sind sie in C++ (C-Int, C-Expr) **binär** (bzw. `-` zusätzlich unär).
:::

## Schritt 1: C-Expr ausprobieren: Vorrang und unäres Minus live testen

Wir wollen zunächst die Vorrangregeln und unäres Minus **direkt in C++**
ausprobieren.

Schreiben Sie ein C++-Programm `expr.cpp`, das folgende Ausdrücke auswertet und
jeweils das Ergebnis über `std::cout` ausgibt:

    1 + 2 * 3
    (1 + 2) * 3
    8 / 4 / 2
    (8 / 4) / 2
    8 / (4 / 2)
    7 - 2 - 1
    7 - (2 - 1)
    -3 * 4
    -(3 * 4)
    -(1 + 2) * 3

Übersetzen Sie es mit g++/clang und prüfen Sie, ob jeweils das Ergebnis Ihren
Erwartungen entspricht.

## Schritt 2: Konkrete Syntax für C-Expr (gestufte Variante)

Definieren Sie eine **konkrete Grammatik für C-Expr** (in EBNF), die folgende
Anforderungen erfüllt:

-   Zulässige Ausdrücke enthalten:
    -   Integer-Literale
    -   binäre Operatoren `+`, `-`, `*`, `/`
    -   unäres Minus: `-x`
    -   Klammern `(` und `)`
-   Vorrang:
    -   `*` und `/` **binden stärker** als `+` und `-`
    -   Unäres Minus und geklammerte Ausdrücke haben höchsten Vorrang
-   Alle vier Operatoren sind **linksassoziativ**
-   Whitespace darf an beliebigen sinnvollen Stellen stehen und wird ignoriert
-   Zeilenkommentare werden ab dem `//` bis zum Zeilenende ignoriert

Skizzieren Sie Ihre Grammatik ausdrücklich mit **gestuften Regeln**, z.B. mit den
Ebenen `expr`/`term`/`atom`.

Überprüfen Sie mit Ihrer Grammatik:

-   Wie wird `1 + 2 * 3` geparst und ausgewertet?
-   Wie wird `8 / 4 / 2` geparst und ausgewertet?
-   Wie wird `-3 * 4` geparst und ausgewertet?
-   Wie werden Klammern berücksichtigt, z.B. `(1 + 2) * 3`, `-(1 + 2) * 3`?

Zeichnen Sie jeweils den Parse-Tree. Entspricht das dem Verhalten von C++ aus der
vorigen Aufgabe?

## Schritt 3: ANTLR-Grammatiken für C-Expr

Definieren Sie zwei **ANTLR-Grammatiken** für **C-Expr**:

-   einmal mit **gestuften Regeln**, und
-   einmal mit **linksrekursiven Alternativen**.

Berücksichtigen Sie dabei die für C-Expr formulierten Operatoren und Vorrangregeln
und Assoziativitäten.

## Schritt 4: Abstrakte Syntax für C-Expr

Definieren Sie nun die **abstrakte Syntax für C-Expr**. Orientieren Sie sich an der
Vorlesung und bauen Sie auf Ihrer abstrakten Syntax von C-Int auf.

Diskutieren Sie: Welche neuen AST-Knoten sind notwendig und warum?

## Schritt 5: Parsen von C-Expr und bauen des AST

1.  Implementieren Sie für Ihre konkrete Grammatik (mit den gestuften Regeln) für
    **C-Expr einen Lexer**. Erweitern Sie dazu die Tokendefinitionen passend.
2.  Implementieren Sie einen **RD-Parser für C-Expr**, der als Ausgabe einen AST
    erzeugt. Ergänzen Sie dazu die AST-Klassen entsprechend Ihrer abstrakten Syntax.
3.  Lassen Sie sich von **ANTLR** für die beiden Grammatiken aus der vorigen Aufgabe
    je einen **Lexer, Parser und Visitor generieren**.
4.  Erstellen Sie **zwei AST-Builder**, die aus den beiden unterschiedlichen
    ANTLR-Parse-Trees je einen AST entsprechend Ihrer abstrakten Syntax erzeugen.
    Nutzen Sie das **Visitor-Pattern**. Diskutieren Sie:
    -   Welchen generischen Typ brauchen Sie für das Ableiten des generierten
        `XyzBaseVisitor`?
    -   Welche der `visitXYZ()`-Methoden sollten Sie überschreiben, welche nicht?
        Begründen Sie Ihre Aussage.
5.  Implementieren Sie die **obigen Testfälle in JUnit** und führen Sie diese auf
    **allen drei Varianten** aus (RD-Parser, ANTLR mit gestuften Regeln, ANTLR mit
    linkrekursiven Alternativen). Was beobachten Sie?

::: tip
**Hinweis**: Sie können die Funktionalität aus dem Lexer und RD-Parser für C-Int als
Basis per Copy&Paste übernehmen und für C-Expr ergänzen/umbauen. Die gestuften
Regeln vertragen sich nicht gut mit dem sonst in diesem Kurs praktizierten Ableiten
`class RdParserCexpr extends RdParserCint`, weshalb wir hier an dieser Stelle darauf
verzichten.
:::

## Schritt 6: Interpreter-Pipeline für C-Expr

Implementieren Sie nun den **Interpreter für C-Expr** in einer Klasse
`InterpreterCexpr`. Dabei soll wie üblich in diesem Kurs gelten
`class InterpreterCexpr extends InterpreterCint`.

Ergänzen Sie die neuen Fälle für C-Expr durch Überschreiben von `eval()`. Rufen Sie
für die bisherigen C-Int-Fälle `super.eval(expr)` auf.

Testen Sie Ihren Interpreter mit JUnit mit den obigen Testfällen. Dabei soll wie bei
L-Expr gelten: `class InterpreterCexprTest extends InterpreterCintTest`. Spielt es
eine Rolle, ob Sie dafür den handgeschriebenen Lexer/RD-Parser oder einen der beiden
ANTLR-Parser plus den passenden AST-Builder einsetzen?

Vergleichen Sie die Resultate der Testfälle von `InterpreterCexpr` mit dem mit
g++/clang übersetzten nativen C++-Code. Gibt es Unterschiede? Woran liegt das?

# (\*\*\*) Vertiefung: ANTLR und Stolperfallen

Betrachten Sie die folgende ANTLR-Grammatik:

``` antlr
foo  :  (ID '(' ')' '=' '0' | ID | NUM) EOF ;

ID      : [a-z][a-zA-Z]* ;
NUM     : [0-9]+ ;
WS      : [ \t\n]+ -> skip ;
```

Was passiert bei der Eingabe von `10` und `01` und `a() = 0`, wie sieht der
Parse-Tree aus? Was passiert bei der Eingabe von `0`?

Erklären Sie die Resultate.

<!--
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
-->
