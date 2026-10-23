---
author: Carsten Gips (HSBI)
title: "L-Expr: Multiplikation/Division und unäres Minus"
---

::: tldr
Wir erweitern L-Int zu L-Expr um Multiplikation und Division. In Lispy ist die
Erweiterung der Grammatik und des Interpreters relativ mechanisch.

Jede Sprachstufe fügt der vorherigen neue Features hinzu: L-Expr *erweitert* L-Int. Analog
halten wir es bei der Implementierung: Die Bausteine der Sprachstufe erben von den Bausteinen
der vorigen Stufe, überschreiben bei Bedarf Methoden und rufen für bisheriges Verhalten
`super.XYZ()` auf. Entsprechend ist `class InterpreterLexpr extends InterpreterLint`.

Die Semantik der Division ist **ganzzahlige Division wie in Java**.
:::




# Rückblick: L-Int

-   Konkrete Syntax:

    ```ebnf
    eform ::= '(' '+' eform eform+ ')' | '(' '-' eform eform+ ')' | INT
    INT   ::= [0-9]+

    L_int ::= eform EOF
    ```

-   Abstrakte Syntax:

    ```ebnf
    Expr  = IntLiteral(Int) | AddExpr(Expr, Expr) | SubExpr(Expr, Expr)

    L_int = Expr
    ```

-   AST:

    ``` java
    public interface Expr {}

    public record AddExpr(Expr left, Expr right) implements Expr {}
    public record SubExpr(Expr left, Expr right) implements Expr {}
    public record IntLiteral(int value) implements Expr {}
    ```


# Erweiterung zu L-Expr: Multiplikation und Division

::: notes
Wir bleiben bei **Integer-Ausdrücken**, fügen aber Multiplikation und Division
hinzu.
:::

-   Beispiel:

    ```
    (* 2 (+ 3 4))
    ```

\bigskip

-   **Neue konkrete Syntax in Lispy**:

    ```ebnf
    eform  ::= '(' '+' eform eform+ ')' | '(' '-' eform eform+ ')' | INT
    INT    ::= [0-9]+
    ---

    eform  ::= '(' '*' eform eform+ ')'
             | '(' '/' eform eform+ ')'
             | '(' '-' eform ')'

    L_expr ::= eform EOF
    ```

::: notes
Die Grundidee in Lispy ist: Wir fügen einfach zwei weitere Alternativen für die
Operatoren hinzu. Semantisch bleiben wir bei Integer-Werten und mehrstelligen Operationen.

::: tip
## Hinweis zum Lesen der Regeln

In dem obigen Beispiel wurden über den `---` die bisherigen Regeln aus L-Int übernommen. Unter
dem  `---` sehen wir die neuen Regeln, die in L-Expr hinzukommen. Dies soll zum einen die Features der
neuen Sprachstufe hervorheben.
Zum anderen soll es auch deutlich machen, dass L-Expr tatsächlich L-Int plus ein paar neue Fähigkeiten ist.

Für eine formale Grammatik wären normalerweise zwei Regeln mit dem selben Namen nicht erlaubt.
Man muss also die beiden `eform`-Regeln (eine aus L-Int, eine neu in L-Expr) gedanklich mergen:

```ebnf
eform  ::= '(' '+' eform eform+ ')'
         | '(' '-' eform eform+ ')'
         | '(' '*' eform eform+ ')'
         | '(' '/' eform eform+ ')'
         | '(' '-' eform ')'
         | INT

INT    ::= [0-9]+

L_expr ::= eform EOF
```
:::

Dieses Prinzip werden wir für die folgenden konkreten und abstrakten Grammatiken anwenden.
Aus Platzgründen werden wir aber irgendwann darauf verzichten, die bisherigen Regeln erneut
über den  `---` aufzuschreiben.
:::

# Abstrakte Syntax für L-Expr

```ebnf
Expr   = IntLiteral(Int) | AddExpr(Expr, Expr) | SubExpr(Expr, Expr)
---

Expr   = MulExpr(Expr, Expr) | DivExpr(Expr, Expr)

L_expr = Expr
```

\bigskip

``` java
public interface Expr {}
```

::: notes
Zusätzlich zu den Klassen aus L-Int

``` java
public record AddExpr(Expr left, Expr right) implements Expr {}
public record SubExpr(Expr left, Expr right) implements Expr {}
public record IntLiteral(int value) implements Expr {}
```

bekommen wir durch/in L-Expr:
:::


\smallskip

``` java
public record MulExpr(Expr left, Expr right) implements Expr {}
public record DivExpr(Expr left, Expr right) implements Expr {}
```


::: notes
::: tip
## Hinweis zu den AST-Klassen

Jede Sprachstufe wird auf der Vorgängersprachstufe aufbauen, d.h. jede Stufe übernimmt
die Regeln und fügt neue hinzu. Wir haben also eine Art Vererbungsbeziehung: die aktuelle
Stufe erbt von der Vorgängerstufe und fügt neue Features hinzu.

Bei den AST-Klassen bedeutet die, dass wir weitere Klassen ergänzen, um die neuen Features
im Baum repräsentieren zu können. D.h. wir bleiben zunächst bei `Expr` als Obertyp für
die AST-Knoten und fügen nur die neu benötigten Knoten `MulExpr` und `DivExpr` hinzu.
:::




# Interpreter: Erinnerung an L-Int


``` java
public class InterpreterLint {

    public Value eval(Expr expr) {
        return switch (expr) {
            case IntLiteral(var v) -> new IntVal(v);

            case AddExpr(var l, var r) -> {
                int a = Value.asInt(eval(l));
                int b = Value.asInt(eval(r));
                yield new IntVal(a + b);
            }

            default -> throw new RuntimeException("unexpected expression: " + expr);
        };
    }
}
```


# Interpreter L-Expr: Erben von L-Int und Ergänzen der neuen Funktionalität

``` java
public class InterpreterLexpr extends InterpreterLint {

    @Override
    public Value eval(Expr expr) {
        return switch (expr) {
            case MulExpr(var l, var r) -> {
                int a = Value.asInt(eval(l));
                int b = Value.asInt(eval(r));
                yield new IntVal(a * b);
            }

            default -> super.eval(expr);
        };
    }
}
```

::: notes
::: tip
## Hinweis zur Vererbung der Bausteine

L-Expr *ist* L-Int plus Multiplikation, Division und ein unäres Minus.

Unser Interpreter für L-Expr braucht also die Fähigkeiten des L-Int-Interpreters und muss
Multiplikation und Division *ergänzen. Dies können wir in objektorientierten Sprachen wie
Java leicht erreichen, indem der L-Expr-Interpreter vom L-Int-Interpreter ableitet:
`class InterpreterLexpr extends InterpreterLint`. In der Methode `eval()` wollen wir die neuen
Fälle ergänzen, deshalb überschreiben wir die geerbte Methode und fügen die neuen Fälle hinzu. Damit
die alten Fälle weiterhin funktionieren, rufen wir im `default`-Zweig einfach `super.eval(expr);` auf und bekommen
damit das in `InterpreterLint` implementierte bisherige Verhalten.

Das werden wir von nun an in allen Bausteinen unserer Interpreter-Pipeline so machen!
Jede neue Sprachstufe "erbt" von der Vorgängersprachstufe:
- In den Grammatiken nutzen wir die alten Regeln weiter und ergänzen neue Regeln/Alternativen
- In den Java-Bausteinen (Klassen) leiten die Klassen der aktuellen Sprachstufe jeweils von den Klassen der Vorgängersprachstufe ab und erweitern das Verhalten durch Überschreiben und `super.XYZ()` für das bisherige Verhalten
- Die JUnit-Tests leiten ebenfalls von den Tests der Vorgängerstufe ab, um das bisherige Verhalten immer mitzutesten
:::

::: tip
## Unäres Minus

Das unäre Minus taucht nicht im AST auf.

Das ist eine Design-Entscheidung, um die Anzahl der AST-Typen möglichst klein zu halten.

Beim Parsen oder beim Erzeugen des AST aus dem Parse-Tree kann man ein unäres Minus auf den bereits
vorhandenen Subtraktionsknoten `SubExpr` "reduzieren". ... Ein weiterer Fall von *Desugaring* ...
:::



## Semantik der Division: Integer-Division wie in Java

Wir bleiben in allen Sprachstufen bei **Ganzzahlen** und nutzen überall dieselbe
Divisions-Semantik wie in Java:

-   Operanden: `int`
-   Ergebnis: `int`
-   Rest wird **abgeschnitten** (Division mit Abrunden Richtung 0)

Beispiele:

    (/ 7 3)         ;; => 2
    (/ (-7) 3)      ;; => -2
    (/ 7 (-3))      ;; => -2
    (/ (-7) (-3))   ;; => 2

**Wichtig:**

-   In Lispy-Formen (`(/ 7 3)`) und in Java-ähnlichen Ausdrücken (`7 / 3`) verwenden wir dieselbe
    Integer-basierte Semantik wie in Java.
-   Division durch 0 führt zu einem **Laufzeitfehler** (in Java
    `ArithmeticException`). Wir behandeln diesen Fall nicht besonders in der
    Sprache.

:::


# Wrap-up

-   L-Expr = L-Int + Multiplikation/Division (in Lispy leicht zu ergänzen)
-   Sprachstufen "erben" voneinander:
    - Grammatiken ergänzen
    - Klassen leiten ab und überschreiben und rufen `super.XYZ()`

::: readings
TODO

Einen schönen Überblick über das, was uns in diesem Semester erwartet, gibt
@Nystrom2021 in Kapitel 2 "A Map of the Territory".
:::

::: outcomes
:::

::: challenges
**Unäres Minus**

Das unäre Minus taucht nicht als eigener Knoten im AST auf. Zeigen Sie, wie man es trotzdem
im AST modellieren kann (mit den bereits vorhandenen Knoten).


:::
