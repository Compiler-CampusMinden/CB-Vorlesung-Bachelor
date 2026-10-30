---
author: Carsten Gips (HSBI)
title: "L-Var: Interpreter mit Environments und Statements"
---

::: tldr
TODO

-   Verständnis des `Environment`-Konzepts zur Laufzeit
-   Interpreter-Erweiterung für Statements (`exec`)
-   Variable-Lesen als Expression (`VarExpr`)
-   Scopes im Interpreter modellieren
:::

# Environments - Laufzeit-Sicht auf Scopes

Datenstruktur (vereinfacht):

``` java
public record Env(Env parent, Map values) {
    public Env() {
        this(null);
    }

    public Env(Env parent) {
        this(parent, new HashMap<>());
    }

    public void define(String name, Value value) {
        throwIf(values.containsKey(name), "(internal error) name already defined: " + name);
        values.put(name, value);
    }

    public void assign(String name, Value value) {
        throwIf(!values.containsKey(name), "(internal error) undefined name (cannot assign): " + name);
        values.put(name, value);
    }

    public void assign(String name, Value value, int depth) {
        Env env = envAtDepth(depth);
        env.assign(name, value);
    }

    public Value get(String name) {
        Value val = values.get(name);
        if (val != null) return val;
        if (parent != null) return parent.get(name);
        throw error("(internal error) undefined name: " + name);
    }

    public Value get(String name, int depth) {
        Env env = envAtDepth(depth);
        return env.getLocal(name);
    }

    public Value getLocal(String name) {
        return values.get(name);
    }

    private Env envAtDepth(int depth) {
        Env env = this;
        for (int i = 0; i < depth && env != null; i++) env = env.parent();
        throwIf(env == null, "(internal error) depth to high: " + depth);
        return env;
    }
}
```

-   `Env` bildet **lexikalische Scopes zur Laufzeit** ab:
    -   `parent` zeigt auf das "umgebende" Environment.
    -   `values` speichert Name $\to$ Wert für den aktuellen Scope.
-   Zugriffsmöglichkeiten:
    -   "naiv": `get(name)` - Suche in der Kette nach oben.
    -   "mit distance": `get(name, depth)` - später genutzt, wenn der Resolver uns
        `depth` vorgibt.

# Interpreter-Hierarchie (L-Int, L-Expr, L-Var)

Bisher (L-Int, L-Expr):

``` java
public class InterpreterLint {

    /** entry point */
    public Value interpret(Expr expr) {
        return eval(expr);
    }

    protected Value eval(Expr expr) {
        return switch (expr) {
            case IntLiteral(var v) -> new IntVal(v);
            case AddExpr(var l, var r) -> evalIntIntToInt(l, r, (a, b) -> a + b);
            case SubExpr(var l, var r) -> evalIntIntToInt(l, r, (a, b) -> a - b);
            default -> throw error("unexpected expression: " + expr);
        };
    }

    protected Value evalIntIntToInt(Expr l, Expr r, IntBinaryOperator op) {
        int a = asInt(eval(l));
        int b = asInt(eval(r));
        return new IntVal(op.applyAsInt(a, b));
    }
}
```

und

``` java
public class InterpreterLexpr extends InterpreterLint {
    @Override
    protected Value eval(Expr expr) {
        return switch (expr) {
            case MulExpr(var l, var r) -> evalIntIntToInt(l, r, (a, b) -> a * b);
            case DivExpr(var l, var r) -> evalIntIntToInt(l, r, (a, b) -> a / b);
            default -> super.eval(expr);
        };
    }
}
```

-   Nur Expressions, keine Statements, kein Environment.

# Interpreter für L-Var - Überblick

L-Var-Interpreter erweitert L-Expr um:

-   Environment (`Env env`)
-   Zugriff auf semantische Informationen (`SemaInfo sema`)
-   Statements + letztes Ergebnis (`Value last`)

Ausschnitt:

``` java
public class InterpreterLvar extends InterpreterLexpr {
    protected SemaInfo sema;
    protected Env env;
    protected Value last;

    /** entry point */
    public Value interpret(List stmts, SemaInfo semaInfo) {
        sema = semaInfo;
        env = sema.globalEnv;   // Start-Environment
        last = UNIT;

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

            case AssignStmt(var assignee, var expr) -> {
                if (!(assignee instanceof VarExpr v))
                    throw error("assignee should be a variable");
                Value value = eval(expr);
                int depth = sema.depths.get(v);
                env.assign(v.name(), value, depth);
            }

            case BlockStmt(var s) -> {
                env = new Env(env);  // neues Environment
                s.forEach(this::exec);
                env = env.parent();  // zurück zum umgebenden Scope
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
            default -> super.eval(expr);   // L-Int, L-Expr-Fälle
        };
    }
}
```

-   Zentral:
    -   `exec(Stmt)` führt Statements aus und updatet `env` und `last`.
    -   Block-Statements erzeugen neue Environments (Scopes).
    -   `eval(VarExpr)` liest Variablen aus dem passenden Environment.

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
**Nested Scopes**

Betrachten Sie folgendes Programm:

``` clojure
(def x : int 10)
(let ((x : int 1)
      (y : int 2))
  (+ x y)
  (let ((y : int 3))
        (+ x y))
    (+ x y))
```

-   Zeichnen Sie zu einigen ausgewählten Programmpunkten den Zustand des
    Environments:
    -   Nach `def x`
    -   Nach Eintritt in den ersten `let`-Block
    -   Nach Eintritt in den inneren `let`-Block
-   Welche Werte haben `x` und `y` jeweils an diesen Stellen?
-   Notieren Sie, wie `BlockStmt` im Interpreter diese Environments erzeugt und
    zurücksetzt.
:::
