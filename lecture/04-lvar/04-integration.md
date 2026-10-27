---
author: Carsten Gips (HSBI)
title: "L-Var: Integration & Pipeline-Gesamtbild"
---

::: tldr
TODO

-   Gesamtbild: Quelltext $\to$ Parser $\to$ AST $\to$ Resolver $\to$ Interpreter
-   Interpreter+Resolver-Interaktion als wiederverwendbares Muster
-   Ausblick auf spätere Sprachstufen
:::

# Pipeline-Gesamtbild für L-Var

1.  **Lexing & Parsing** (ANTLR):
    -   Quelltext $\to$ Parse-Tree (`LispyParser.lvar()`).
2.  **AST-Builder**:
    -   Parse-Tree $\to$ unsere AST-Klassen (`Expr`, `Stmt`, `VarDecl`, `BlockStmt`,
        ...).
3.  **NameResolverLvar**:
    -   AST $\to$ `SemaInfo`, gefüllt mit:
        -   `symbols`: Statement $\to$ Scope
        -   `depths`: VarExpr $\to$ Entfernungszahl
        -   `globalScope`, `globalEnv` mit Prelude vorbelegt
4.  **InterpreterLvar**:
    -   AST + `SemaInfo` $\to$ Ausführung:
        -   `Env env` für Werte zur Laufzeit
        -   `eval(Expr)` und `exec(Stmt)` nutzen `depths` für direkte
            Environment-Zugriffe.

Skizze im Code:

``` java
var input = CharStreams.fromString(source);
var lexer = new LispyLexer(input);
var tokens = new CommonTokenStream(lexer);
var parser = new LispyParser(tokens);
var tree = parser.lvar();

var astBuilder = new LispyAstBuilderLvar();
var ast = astBuilder.visitLvar(tree);

SemaInfo sema = new SemaInfo();
new NameResolverLvar().resolve(ast, sema);

Value result = new InterpreterLvar().interpret(ast, sema);
```

# InterpreterLvar - Rolle von `interpret(...)`

Nochmal der Einstiegspunkt:

``` java
public Value interpret(List stmts, SemaInfo semaInfo) {
    sema = semaInfo;
    env = sema.globalEnv;
    last = UNIT;

    stmts.forEach(this::exec);

    return last;
}
```

-   `sema.globalEnv` kann bereits Prelude-Funktionen/Variablen enthalten.
-   `exec(stmt)`:
    -   Deklarationen binden Werte in `env`.
    -   Blocks erzeugen neue `Env`-Instanzen.
    -   `VarExpr`/`AssignStmt` nutzen `sema.depths` zur Navigation.

# Reflexion: Muster für spätere Sprachstufen

Das folgende Muster wird uns in L-If, L-Fun, L-Class usw. begleiten:

-   **Konkrete Syntax** erweitern (ANTLR).
-   **Abstrakte Syntax** (AST-Klassen) erweitern.
-   **Resolver**:
    -   neue Scopes (z.B. Funktions-Scopes, Klassenscopes),
    -   zusätzliche Einträge in `SemaInfo` (z.B. Funktions-Typen, Klasseninfos).
-   **Interpreter**:
    -   nutzt `SemaInfo`, um zur Laufzeit nicht mehr suchen zu müssen, sondern
        direkt zu springen.

Beispiele:

-   Funktionen:
    -   Resolver merkt sich, in welchem Scope eine Funktion deklariert wurde.
    -   Interpreter benutzt das für Closures und Environment-Capturing.
-   Klassen:
    -   Resolver legt `staticTargets` für Memberzugriffe fest.
    -   Interpreter ruft genau die richtige Methode / liest das richtige Feld.

# Wrap-up

TODO

::: readings
TODO

In [@Nystrom2021] kann man in Kapitel 6 "Parsing Expressions" und Kapitel 7
"Evaluation Expressions" nachlesen.
:::

::: outcomes
TODO
:::

::: challenges
**Pipeline für L-Var**

1.  Zeichnen Sie für ein kleines L-Var-Programm (eigene Wahl mit `def`, `let`,
    Block) die gesamte Pipeline als Kette von Kästen:
    -   Quelltext
    -   Parse-Tree
    -   AST
    -   Resolver (`Scope`, `SemaInfo.depths`)
    -   Interpreter (`Env`, `Value`)
2.  Markieren Sie:
    -   Wo werden **Namen gebunden**? (Resolver, `Scope.bind`)
    -   Wo werden **Werte gespeichert**? (Interpreter, `Env.define`)
    -   Wo werden **depth-Werte benutzt**?
3.  Diskutieren Sie:
    -   Welche Teile würden Sie gerne testen, ohne den Rest?
        -   z.B. nur Resolver testen, nur Interpreter mit vorbereiteten `SemaInfo`,
            etc.
:::
