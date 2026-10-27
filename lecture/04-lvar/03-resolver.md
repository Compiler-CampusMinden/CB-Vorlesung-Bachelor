---
author: Carsten Gips (HSBI)
title: "L-Var: NameResolver - statische Namensauflösung"
---

::: tldr
TODO

-   Problem mit reiner Laufzeit-Namenssuche erkennen
-   Resolver als eigene semantische Phase verstehen
-   Verbindung Resolver ↔ Interpreter (Depth-Information)
-   Rolle von `SemaInfo` als Sidetable kennen lernen
:::

# Problem: Nur dynamische Namensauflösung

Mit reinem Environment-Ansatz (ohne Resolver) wäre das Muster:

-   Variablen lesen: `env.get(name)` läuft Kette nach oben.
-   Zuweisung: `env.assign(name, value)` sucht die passende Bindung.
-   Fehler wie "Variable nie deklariert" würden erst zur Laufzeit auftreten.

Nachteile:

-   Semantische Fehler werden spät entdeckt.
-   Interpreter trägt viel Verantwortung (Suche, Fehlerdiagnose).
-   Es gibt keine zentrale Sicht, welche Variablen wo gebunden sind.

# `Scope` - statische Sicht auf Symbole

Für die semantische Analyse definieren wir `Scope`:

``` java
public record Scope(Scope parent, HashMap symbols) {
    public Scope() {
        this(null);
    }

    public Scope(Scope enclosing) {
        this(enclosing, new HashMap<>());
    }

    // === basic functions ===
    public void bind(Decl symbol) {
        bind(symbol.name(), symbol);
    }

    public void bind(String name, Decl symbol) {
        throwIf(symbols.containsKey(name), "name already defined: " + name);
        symbols.put(name, symbol);
    }

    public Decl resolve(String name) {
        return resolve(name, 0).decl;
    }

    public Resolution resolve(String name, int depth) {
        Decl decl = symbols.get(name);
        if (decl != null) return new Resolution(decl, depth);
        if (parent != null) return parent.resolve(name, depth + 1);
        throw new RuntimeException("undefined name: " + name);
    }

    public Decl resolveLocal(String name) {
        return symbols.get(name);
    }

    // === helper ===
    public record Resolution(Decl decl, int depth) {
    }
}
```

-   `Scope` ist die **statische** Analogie zu `Env`:
    -   Resolved Deklarationen (`Decl`) statt Werte (`Value`).
    -   Liefert zusätzlich `depth` = Entfernung zum Scope der Deklaration.

# `SemaInfo` - zentrale Sidetable

`SemaInfo` sammelt alle Ergebnisse der semantischen Analyse:

``` java
public class SemaInfo {
    public Map<Stmt, Scope> symbols = new IdentityHashMap<>();
    public Map<VarExpr, Integer> depths = new IdentityHashMap<>();
    public Scope globalScope = new Scope();
    public Env globalEnv = new Env();
}
```

-   Für L-Var besonders relevant:
    -   `depths`: ordnet jede `VarExpr` einer Tiefe zu (Anzahl der Scopes nach oben
        zur Deklaration).
    -   `symbols`: ordnet jedem `Stmt` seinen Scope zu.
-   `globalScope`, `globalEnv` können mit Builtins aus einem Prelude vorbefüllt
    werden.

# NameResolverLvar - Überblick

Der Resolver läuft vor dem Interpreter einmal über den AST.

Entry-Point:

``` java
public class NameResolverLvar {
    protected SemaInfo sema;
    protected Scope scope;

    /** entry point */
    public SemaInfo resolve(List stmts, SemaInfo semaInfo) {
        sema = semaInfo;
        scope = sema.globalScope;

        stmts.forEach(this::resolve);

        return sema;
    }

    // ...
}
```

-   Start mit globalem Scope.
-   Für jeden `Stmt` wird `resolve(stmt)` aufgerufen.
-   Währenddessen:
    -   Neue Namen werden mit `scope.bind(...)` gebunden.
    -   Variable-Referenzen werden mit `scope.resolve(...)` aufgelöst und `depth`
        gespeichert.

# NameResolverLvar - Statements

Ausschnitt aus `resolve(Stmt)`:

``` java
protected void resolve(Stmt stmt) {
    sema.symbols.put(stmt, scope);

    switch (stmt) {
        // === L_Var ===
        case ExprStmt(var e) -> resolve(e);

        case VarDecl(var name, Type type, var init) -> {
            resolve(init); // resolve rhs first

            resolveType(type);
            scope.bind(name, (VarDecl) stmt);
        }

        case AssignStmt(var target, var expr) -> {
            if (!(target instanceof VarExpr))
                throw error("lhs of assignment, expected variable, got " + target);
            resolve(expr);
            resolve(target);
        }

        case BlockStmt(var s) -> {
            beginScope();
            s.forEach(this::resolve);
            endScope();
        }

        default -> throw error("unexpected statement: " + stmt);
    }
}
```

-   Wichtige Punkte:
    -   Jeder `Stmt` erhält in `symbols` seinen aktuellen `Scope`.
    -   `VarDecl` bindet einen neuen Namen im aktuellen Scope.
    -   `BlockStmt` erzeugt bzw. beendet einen statischen Scope.

# NameResolverLvar - Expressions

Ausschnitt aus `resolve(Expr)`:

``` java
protected void resolve(Expr expr) {
    switch (expr) {
        // === L_Int ===
        case IntLiteral _ -> {} // nothing to do
        case AddExpr(var l, var r) -> List.of(l, r).forEach(this::resolve);
        case SubExpr(var l, var r) -> List.of(l, r).forEach(this::resolve);

        // === L_Expr ===
        case MulExpr(var l, var r) -> List.of(l, r).forEach(this::resolve);
        case DivExpr(var l, var r) -> List.of(l, r).forEach(this::resolve);

        // === L_Var ===
        case VarExpr e -> {
            var res = scope.resolve(e.name(), 0);
            sema.depths.put(e, res.depth());
        }

        default -> throw error("unexpected expression: " + expr);
    }
}
```

-   `VarExpr e`:
    -   Resolver ruft `scope.resolve(e.name(), 0)` auf.
    -   Ergebnis: Deklaration + `depth`.
    -   `depth` wird in `sema.depths` abgelegt.
-   Der Interpreter nutzt diese `depth` später zur direkten Environment-Navigation.

# Resolver ↔ Interpreter - Verbindung

-   **Resolver**:
    -   speichert für jede `VarExpr` einen `depth`-Wert in `sema.depths`.
-   **Interpreter**:
    -   benutzt diesen `depth`, um direkt das passende Environment anzuspringen:

        ``` java
        case VarExpr v -> {
            int depth = sema.depths.get(v);
            yield env.get(v.name(), depth);
        }

        case AssignStmt(var assignee, var expr) -> {
            if (!(assignee instanceof VarExpr v)) throw error("assignee should be a variable");
            Value value = eval(expr);
            int depth = sema.depths.get(v);
            env.assign(v.name(), value, depth);
        }
        ```
-   Wichtiger Punkt:
    -   **Semantik bleibt identisch** zu einer reinen Environment-Ketten-Suche.
    -   Wir verschieben nur die Sucharbeit in eine vorherige, statische Phase.

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
**Lexikalisches Auflösen von Namen**

Betrachten Sie dieses L-Var-Programm:

``` clojure
(def x : int 10)
(def y : int 20)
(let ((x : int 1))
  (+ x y)
(let ((y : int 2))
  (+ x y))
```

-   Zeichnen Sie den **Scope-Baum** (statisch).
-   Notieren Sie für jede `VarExpr` (`x` und `y`):
    -   Auf welche `VarDecl` zeigt sie?
    -   Welchen `depth`-Wert würde der Resolver berechnen?
-   Skizzieren Sie, wie `sema.depths` für diese Variable-Expressions aussehen
    würde.
:::
