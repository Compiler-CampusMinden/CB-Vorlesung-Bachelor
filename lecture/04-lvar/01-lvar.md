---
author: Carsten Gips (HSBI)
title: "L-Var: Überblick, Syntax und AST"
---

::: tldr
TODO

-   Erweiterung von Lispy um Variablen und Scopes (L-Var)
-   Unterschied Expressions vs. Statements
-   Konkrete und abstrakte Syntax für L-Var
-   Letzter Fokus auf ANTLR-Grammatik und AST-Builder
:::

# L-Var - Motivation: Beispiele (Lispy)

## Nur Ausdrücke (L-Int / L-Expr)

``` clojure
(+ 1 (* 2 3))
(/ (- 10 4) 2)
```

-   Bisher: reine Arithmetik, nur Expressions, kein Zustand.

## L-Var: Variablen definieren

``` clojure
(def x : int 10)
(+ x 5)
```

-   Neue Idee: Namen binden Werte.

## L-Var: Zuweisung / "let" mit Scopes

(Einfacher let mit einer Variable)

``` clojure
(def x : int 10)
(let x (+ x 1))   ;; neue Bindung im inneren Scope?
(+ x 5)
```

("Let-Block" mit mehreren Bindungen und Blockkörper)

``` clojure
(def x : int 1)
(let ((a : int 2)
      (b : int 3))
  (+ a b)
  (+ x b))
```

-   Verschachtelung und Shadowing werden wichtig.

# L-Var - Konkrete Grammatik (informell, EBNF)

Wir bauen auf L-Int und L-Expr auf und ergänzen L-Var:

``` ebnf
eform  ::= '(' '+' eform eform+ ')'
         | '(' '-' eform eform+ ')'
         | INT
INT    ::= [0-9]+
---
eform  ::= '(' '*' eform eform+ ')'
         | '(' '/' eform eform+ ')'
         | '(' '-' eform ')'
---

eform ::= ID
sform ::= eform
        | '(' 'def' ID ':' type eform? ')'
        | '(' 'let' ID eform ')'
        | '(' 'let' '(' ltBdg+ ')' sform+ ')'
ltBdg ::= '(' ID ':' type eform ')' ;
type  ::= 'int'
ID    ::= [a-zA-Z][a-zA-Z_0-9]*

L_var ::= sform* EOF
```

-   `sform` sind jetzt **Statements** (und Expressions als Statements).
-   `L_var`-Programme sind Listen von `sform`: also *Sequenzen von Statements*.

# L-Var - ANTLR-Grammatik (Ausschnitt)

Konkrete ANTLR-Grammatik (vereinfacht auf L-Var-relevante Teile):

``` antlr
grammar Lispy;

lvar        : sform* EOF ;

sform
            : exprStmt
            | varDecl
            | letStmt
            ;

eform
            : atom                              #atomExpr
            | '(' '-' eform ')'                 #unaryMinusExpr
            | '(' '+' eform eform+ ')'          #addExpr
            | '(' '-' eform eform+ ')'          #subExpr
            | '(' '*' eform eform+ ')'          #mulExpr
            | '(' '/' eform eform+ ')'          #divExpr
            ;

atom
            : INT               #intLit
            | ID                #varExpr
            ;

exprStmt    : eform ;

// (def x : int 0)
varDecl     : '(' 'def' ID ':' type eform? ')' ;

// (let x expr)
// (let ((a : int 1) (b : int 2)) body...)
letStmt
            : '(' 'let' ID eform ')'                        #letVar
            | '(' 'let' letBindings sform+ ')'              #letScope
            ;

letBindings : '(' letBinding+ ')' ;
letBinding  : '(' ID ':' type eform ')' ;

type
            : 'int'
            ;

INT         : [0-9]+ ;
ID          : [a-zA-Z_][a-zA-Z0-9_]* ;

COMMENT     : ';;' ~[\r\n]* -> skip ;
WS          : [ \t\r\n,]+ -> skip ;
```

Hinweis für die Studierenden:

-   Details zu `letThis`, `letMember`, weiteren Typen etc. kommen in späteren
    Stufen.
-   Für L-Var konzentrieren wir uns auf `letVar`, `letScope`, `int`.

# L-Var - Abstrakte Syntax (AST)

Im Siek-Stil (vereinfachte Sicht, nur L-Int, L-Expr, L-Var):

``` ebnf
Expr  = IntLiteral(Int) | AddExpr(Expr, Expr) | SubExpr(Expr, Expr)
---
Expr  = MulExpr(Expr, Expr) | DivExpr(Expr, Expr)
---

Expr  = VarExpr(String)

Stmt  = ExprStmt(Expr)
      | VarDecl(String, Type, Expr)    // name, type, init
      | AssignStmt(Expr, Expr)         // target, expr
      | BlockStmt([Stmt])

L_var = Stmt*
```

Zugehörige Java-Interfaces/-Records (vereinfacht):

``` java
public interface Expr {}
public interface Stmt {}

public record IntLiteral(int value) implements Expr {}
public record AddExpr(Expr left, Expr right) implements Expr {}
public record SubExpr(Expr left, Expr right) implements Expr {}

public record MulExpr(Expr left, Expr right) implements Expr {}
public record DivExpr(Expr left, Expr right) implements Expr {}

public record VarExpr(String name) implements Expr {}
public record VarDecl(String name, Type type, Expr init) implements Stmt, Decl {}
public record AssignStmt(Expr target, Expr expr) implements Stmt {}
public record ExprStmt(Expr expr) implements Stmt {}
public record BlockStmt(List stmts) implements Stmt {}
```

-   Wichtige neue AST-Knoten:
    -   `VarExpr` - Lesen einer Variable
    -   `VarDecl` - Einführung/Binden einer Variable
    -   `AssignStmt` - Zuweisung an eine Variable (später wichtig für Resolver)
    -   `BlockStmt` - Scope für mehrere Statements

# L-Var - AST-Builder: Vom Parse-Tree zum AST

Letzter Fokus auf ANTLR-Visitor und AST-Builder:

-   Idee: Wir wollen **abstrakte** Knoten (wie oben), keine direkten
    Parse-Tree-Strukturen.
-   Vorgehen:
    -   Bestehenden AST-Builder aus L-Expr erben.
    -   Neue Visitor-Methoden für `exprStmt`, `varDecl`, `letStmt` überschreiben
        oder ergänzen.

Skizze (sehr vereinfacht):

``` java
public class LispyAstBuilderLvar extends LispyAstBuilderLexpr {

    @Override
    public List<Stmt> visitLvar(LvarContext ctx) {
        return ctx.sform().stream().map(this::visit).map(Stmt.class::cast).toList();
    }

    // ---------------------------
    // Expressions
    // ---------------------------

    @Override
    public Expr visitVarExpr(VarExprContext ctx) {
        return new VarExpr(ctx.ID().getText());
    }

    // ---------------------------
    // Statements
    // ---------------------------

    @Override
    public Stmt visitExprStmt(ExprStmtContext ctx) {
        Expr expr = asExpr(visit(ctx.eform()));
        return new ExprStmt(expr);
    }

    // (def x : int initExpr)
    @Override
    public Stmt visitVarDecl(VarDeclContext ctx) {
        return parseVarDef(ctx, true);
    }

    // (let x expr)
    @Override
    public Stmt visitLetVar(LetVarContext ctx) {
        Expr target = new VarExpr(ctx.ID().getText());
        Expr value = asExpr(visit(ctx.eform()));
        return new AssignStmt(target, value);
    }

    // (let ((a : int 1) (b : int 2)) body...)
    @Override
    public Stmt visitLetScope(LetScopeContext ctx) {
        List<Stmt> stmts = new ArrayList<>();

        for (var b : ctx.letBindings().letBinding()) {
            String name = b.ID().getText();
            Type type = Type.from(b.type().getText());
            Expr init = asExpr(visit(b.eform()));

            VarDecl vd = new VarDecl(name, type, init);
            stmts.add(vd);
        }

        for (var sf : ctx.sform()) {
            Stmt s = asStmt(visit(sf));
            stmts.add(s);
        }

        return new BlockStmt(stmts);
    }

    // ---------------------------
    // Types
    // ---------------------------

    @Override
    public Type visitType(TypeContext ctx) {
        return Type.from(ctx.getText());
    }

    // ---------------------------
    // Helpers
    // ---------------------------

    protected Stmt asStmt(Object o) {
        if (o instanceof Stmt s) return s;
        if (o instanceof Expr e) return new ExprStmt(e);
        throw error("statement or expression expected, got: " + o);
    }

    protected VarDecl parseVarDef(VarDeclContext ctx, boolean expectInit) {
        String name = ctx.ID().getText();
        Type type = Type.from(ctx.type().getText());

        Expr init = (ctx.eform() != null) ? asExpr(visit(ctx.eform())) : null;
        if (expectInit && init == null) throw error("variable '" + name + "' must have an initializer");

        return new VarDecl(name, type, init);
    }
}
```

-   **Konkrete Syntax** vs. **Abstrakte Syntax**:
    -   `letScope`-Parse-Tree $\to$ `BlockStmt` mit einer Folge von `VarDecl` und
        `Stmt`.
-   Wir wollen nur noch AST in weiteren Phasen (Resolver, Interpreter) sehen.

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
**Statemens vs. Expressions**

1.  Geben Sie den folgenden Lispy-Code in **L-Var**-Syntax eine AST-Struktur:

    ``` clojure
    (def x : int 10)
    (let ((y : int 1)
          (z : int 2))
      (+ x y)
      (+ y z))
    ```

    -   Welche `Stmt`-Knoten entstehen?
    -   Welche `Expr`-Knoten entstehen?

2.  Zeichnen Sie den **Scope-Baum**:

    -   Welcher Scope enthält welche Variablen?
    -   Welche Referenz (`VarExpr`) bezieht sich auf welche Deklaration (`VarDecl`)?
:::
