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

-   L-Var: Überblick, Syntax und AST
-   L-Var: Scopes, Name-Resolver und Symboltabellen
-   L-Var: Interpreter mit Environments und Statements
-   L-Var: Integration & Pipeline-Gesamtbild

# A5.1: L-Var: `NameResolverLvar#resolve()` ergänzen (\*)

Sie haben im Skript für L-Var den Name-Resolver `NameResolverLvar` kennengelernt.
Dabei wurde die Implementierung für die AST-Knoten `ExprStmt` und `AssignStmt`
(beides `Stmt`) sowie `SubExpr`, `MulExpr` und `DivExpr` (alle drei `Expr`) nicht
gezeigt.

::: details
``` java
public class NameResolverLvar {
    protected SemaInfo sema;
    protected Scope scope;

    public SemaInfo resolve(List<Stmt> stmts, SemaInfo semaInfo) {
        sema = semaInfo;  scope = sema.globalScope;
        stmts.forEach(this::resolve);
        return sema;
    }

    protected void resolve(Stmt stmt) {
        sema.symbols.put(stmt, scope);

        switch (stmt) {
            case VarDecl(var name, var type, var init) -> {
                resolve(init);
                resolveType(type);
                scope.bind((VarDecl) stmt);
            }
            case BlockStmt(var s) -> {
                scope = new Scope(scope);
                s.forEach(this::resolve);
                scope = scope.parent();
            }
            default -> throw new RuntimeException("unexpected statement: " + stmt);
        }
    }

    protected void resolve(Expr expr) {
        switch (expr) {
            case IntLiteral _ -> { } // nothing to do
            case AddExpr(var l, var r) -> List.of(l, r).forEach(this::resolve);
            case VarExpr e -> {
                var res = scope.resolve(e.name(), 0);
                sema.depths.put(e, res.depth());
            }
            default -> throw new RuntimeException("unexpected expression: " + expr);
        }
    }
}
```
:::

Skizzieren Sie die fehlenden Fälle in `resolve(stmt)` und `resolve(expr)` für
`ExprStmt`, `AssignStmt`, `SubExpr`, `MulExpr` und `DivExpr`.

Geben Sie für jeden Fall an:

-   welche Kindknoten rekursiv besucht werden
-   ob ein Name über `scope.resolve()` aufgelöst wird
-   ob und welche Information in `SemaInfo` gespeichert wird

In L-Var ist das Ziel eines `AssignStmt` eine `VarExpr`. In der abstrakten Syntax
haben wir hier nur `Expr` - wie stellen Sie im Resolver sicher, dass wir hier
tatsächlich nur eine Variable betrachten? Skizzieren Sie, wie der Resolver diese
Zielvariable auflöst und wie er anschließend den rechten Ausdruck verarbeitet.

# A5.2: L-Var: Scopes und Tiefenwerte verfolgen (\*)

Betrachten Sie das folgende L-Var-Programm:

``` clojure
(def x : int 10)

(let ((y : int 2))
  (+ x y)
  (let ((x : int 5))
    (+ x y))
  (+ x y))
```

Skizzieren Sie die Arbeit des Name-Resolvers:

1.  Zeichnen Sie den Scope-Baum und tragen Sie in jeden Scope die dort definierten
    Variablen ein.
2.  Gehen Sie die Statements und Expressions in der Reihenfolge durch, in der der
    Resolver sie besucht. Notieren Sie dabei, wann ein neuer Scope betreten und
    wieder verlassen wird.
3.  Ordnen Sie jede `VarExpr` der passenden `VarDecl` zu.
4.  Geben Sie für jede `VarExpr` den von `scope.resolve(name, 0)` gelieferten
    `depth`-Wert an.

# A5.3: L-Var: Fehlende Fälle im Interpreter ergänzen (\*)

Im Skript wurde die Implementierung von `InterpreterLvar` für `AssignStmt` nicht
gezeigt.

::: details
``` java
public class InterpreterLvar extends InterpreterLexpr {
    protected SemaInfo sema;
    protected Env env;
    protected Value last;

    public Value interpret(List<Stmt> stmts, SemaInfo semaInfo) {
        sema = semaInfo;  env = sema.globalEnv;  last = UNIT;
        stmts.forEach(this::exec);
        return last;
    }

    protected void exec(Stmt stmt) {
        switch (stmt) {
            case ExprStmt(var expr) -> last = eval(expr);
            case VarDecl(var name, var type, var init) -> {
                Value i = eval(init);
                env.define(name, i);
            }
            case BlockStmt(var s) -> {
                env = new Env(env);
                s.forEach(this::exec);
                env = env.parent();
            }
            default -> throw error("unexpected statement: " + stmt);
        }
    }

    @Override
    protected Value eval(Expr expr) {
        return switch (expr) {
            case VarExpr v -> {
                int depth = sema.depths.get(v);
                yield env.get(v.name(), depth);
            }
            default -> super.eval(expr);
        };
    }
}
```
:::

Skizzieren Sie den fehlenden Fall und erklären Sie die Arbeitsweise:

-   Welche Kindknoten werden ausgewertet?
-   Welche Werte werden aus den Kindknoten benötigt?
-   Welche Aktion führt der Interpreter aus beziehungsweise welchen Wert liefert er
    zurück?

# A5.4: L-Var: Von `depth` zum Laufzeitwert (\*\*)

Betrachten Sie erneut das Programm von oben:

``` clojure
(def x : int 10)

(let ((y : int 2))
  (+ x y)
  (let ((x : int 5))
    (+ x y))
  (+ x y))
```

Der Name-Resolver hat für jede `VarExpr` eine Tiefe berechnet. Der Interpreter
verwendet diese Tiefe, um vom aktuellen `Env` aus das passende Environment
auszuwählen.

1.  Skizzieren Sie die Environments während der Ausführung:

    -   nach der globalen Definition von `x`
    -   im äußeren `let`-Block nach der Definition von `y`
    -   im inneren `let`-Block nach der Definition des lokalen `x`

2.  Erstellen Sie eine Tabelle und tragen Sie für jedes Variablenvorkommen ein:

    -   das aktuelle Environment
    -   den `depth`-Wert
    -   das Environment, auf das der Interpreter zugreift
    -   den dort gespeicherten Wert

3.  Erklären Sie anhand des inneren `(+ x y)`, warum `x` und `y` über
    unterschiedliche Tiefen aufgelöst werden.

4.  Was würde im Interpreter schiefgehen, wenn für das innere Vorkommen von `x`
    fälschlich die Tiefe des globalen `x` gespeichert wäre?

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
