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

# A5.1: L-Var: Scopes und Tiefenwerte verfolgen (\*)

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

# A5.2: L-Var: `NameResolverLvar#resolve()` ergänzen (\*)

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

# A5.3: L-Var: Von `depth` zum Laufzeitwert (\*\*)

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

# A5.4: L-Var: Fehlende Fälle im Interpreter ergänzen (\*)

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

# A5.5: C-Var: Variablen, State und nested Scopes (\*\*)

Wir erweitern **C-Expr aus dem letzten Übungsblatt zu C-Var**. Dabei ergänzen wir
u.a. Variablendeklarationen, Zuweisungen und Blöcke mit eigenen Scopes.

Nutzen Sie Ihre bestehende **ANTLR-Pipeline** aus C-Expr als Ausgangspunkt.
Erweitern Sie die ANTLR-Grammatik, leiten Sie den AST-Builder und die übrigen
Komponenten von den entsprechenden C-Expr-Bausteinen ab und ergänzen Sie die neuen
Fälle. Ein handgeschriebener Lexer oder RD-Parser ist ab diesem Blatt nicht (mehr)
erforderlich.

::: important
## Waschzettel: In C++ sieht es so aus ...

| Zweck                                | L-Var (Lispy)                                              | C-Var (Mini-C++)                       |
|:-------------------------------------|:-----------------------------------------------------------|:---------------------------------------|
| Variable definieren                  | `(def x : int 10)`                                         | `int x = 10;`                          |
| Zuweisung an Variablen               | `(let x 2)`                                                | `x = 2;`                               |
| Variable lesen (Teil eines Ausdruck) | `x`                                                        | `x`                                    |
| Nested Scopes                        | `(def x : int 10) (let ((a : int 2) (x : int 3)) (+ a x))` | `int x=10; { int a=2; int x=3; a+x; }` |

Ein `let` kann in Lispy nicht nur eine Variable zuweisen, sondern auch einen neuen
lokalen Scope öffnen mit lokalen Variablen.

``` clojure
(def x : int 10)
(let ((a : int 2)
      (x : int 3))
  (+ a x))
```

In C++ nutzen wir dafür die geschweiften Klammern.

``` cpp
int x=10;
{
    int a=2;
    int x=3;
    a+x;
}
```

Für C-Var gelten die folgenden Festlegungen:

-   Variablen haben den Typ `int` und werden bei der Definition initialisiert.
-   Eine Variable darf in ihrer Initialisierung nicht auf sich selbst verweisen.
-   Eine Variable darf innerhalb desselben Scopes nur einmal definiert werden.
-   Eine Definition in einem inneren Scope darf eine Definition in einem äußeren
    Scope verdecken (*shadowing*).
-   Variablenzugriffe werden lexikalisch aufgelöst.
-   Es darf keine Zugriffe (lesend, schreibend) auf nicht sichtbare Variablen geben.
-   Zuweisungen dürfen in C-Var nur an Variablen erfolgen.
-   Der Name-Resolver speichert für jede Variablenreferenz die Tiefe, die der
    Interpreter später zum Zugriff auf das passende Environment verwendet.
-   Abweichungen vom "echten" C++:
    -   Zuweisungen sind in Mini-C++ Statements, keine Expressions.
    -   Der Wert des zuletzt ausgewerteten Expression-Statements ist der
        Rückgabewert des Interpreters.
:::

## Schritt 1: C-Var ausprobieren

Wir wollen Variablendeklarationen, Zuweisungen und Blockverhalten zunächst direkt in
C++ ausprobieren.

Schreiben Sie ein C++-Programm `var.cpp` mit den folgenden Statements:

``` cpp
int x = 10;
x = x + 1;
x + 2;
{
    int y = 3;
    x + y;
}
```

Ergänzen Sie an geeigneten Stellen `std::cout`-Ausgaben, sodass die Werte vor und
nach der Zuweisung sowie im und nach dem Block sichtbar werden.

Übersetzen Sie es mit g++/clang und prüfen Sie, ob jeweils das Ergebnis Ihren
Erwartungen entspricht.

## Schritt 2: C-Var-Grammatiken und AST ergänzen

Definieren Sie zunächst wieder die **konkrete** und die **abstrakte Grammatik** für
C-Var. Orientieren Sie dabei am Vorgehen im Skript.

C-Var soll mindestens die folgenden Konstrukte unterstützen:

``` cpp
int x = 10;
x = x + 1;
x + 2;
{
    int y = 3;
    x + y;
}
```

1.  Ergänzen Sie die **konkrete Grammatik** um passende Regeln für die neuen
    Sprachkonstrukte.

2.  Leiten Sie aus der konkreten Grammatik die notwendigen Ergänzungen Ihrer
    **ANTLR-Grammatik** vom letzten Blatt ab. Sie können die von Ihnen bevorzugte
    Variante nutzen (gestufte Regeln vs. Auflösung der linksrekursiven Alternativen
    in ANTLR4).

3.  Nutzen Sie die Definitionen in Ihrer **abstrakten Grammatik**, um den AST um die
    benötigten neuen Knotentypen zu erweitern. Halten Sie dabei die Unterscheidung
    zwischen Expressions und Statements aufrecht.

4.  Leiten Sie Ihren C-Expr-AST-Builder zu einem **C-Var-AST-Builder** ab.
    Überschreiben Sie die benötigten `visitXYZ()`-Methoden und erläutern Sie kurz,
    welche bisherigen Methoden Sie weiterverwenden können.

5.  Stellen Sie sicher, dass ein C-Var-Programm aus einer **Folge von Statements**
    besteht.

## Schritt 3: Name-Resolver und Scopes

Implementieren Sie einen `NameResolverCvar`. Orientieren Sie sich am Vorgehen im
Skript.

Testen Sie den Resolver mindestens mit diesen Fällen:

``` cpp
int x = 1;
x + 2;
```

``` cpp
int x = 1;
{
    int y = x + 2;
    y + x;
}
```

``` cpp
int x = 1;
{
    int x = 2;
    x + 1;
}
```

Prüfen Sie für diese Tests, ob die richtigen Namen im richtigen Scope gebunden
wurden und die korrekte Tiefeninformation berechnet wurde.

Erstellen Sie außerdem noch **Negativtests**: Welche Eingaben sollte der
Name-Resolver zurückweisen?

## Schritt 4: Interpreter und Environments

Erweitern Sie Ihren C-Expr-Interpreter zu einem `InterpreterCvar`. Ergänzen Sie eine
`Env`-Struktur, die Variablennamen und Laufzeitwerte speichert und auf das
Eltern-Environment verweist.

Erläutern Sie, welche Informationen der Interpreter aus der Sidetable benötigt.

Legen Sie fest, welchen Wert Ihr Interpreter für ein Programm zurückgibt.
Orientieren Sie sich dabei an der L-Var-Semantik: Der Wert des letzten ausgewerteten
Expression-Statements wird zurückgegeben; falls keines vorkommt, wird ein
Einheitswert zurückgegeben.

Ergänzen Sie Ihre JUnit-Tests so, dass die neuen Sprachkonstrukte in der Pipeline
getestet werden. Testen Sie insbesondere syntaktische Konstruktion, Namensauflösung
und Laufzeitverhalten.

Vergleichen Sie das beobachtbare Verhalten Ihres Interpreters mit einem
entsprechenden C++-Programm (clang/g++). Welche Unterschiede ergeben sich durch die
Festlegungen von Mini-C++?

# A5.6: C-Var: Scopes, Tiefenwerte und Laufzeitwerte (\*\*)

Betrachten Sie das folgende C-Var-Programm:

``` cpp
int x = 10;

{
    int y = 2;
    x + y;

    {
        int x = 5;
        x + y;
    }

    x + y;
}
```

1.  Zeichnen Sie den Scope-Baum und notieren Sie, welche Variablen in jedem Scope
    definiert werden.
2.  Ordnen Sie jede Variablenreferenz ihrer Deklaration zu und geben Sie ihre
    `depth`-Werte an.
3.  Skizzieren Sie die Environments während der Ausführung:
    -   nach der globalen Deklaration von `x`;
    -   im äußeren Block nach der Deklaration von `y`;
    -   im inneren Block nach der lokalen Deklaration von `x`.
4.  Wählen Sie für jede Variablenreferenz ein Beispiel aus und beschreiben Sie, wie
    der Interpreter mit dem `depth`-Wert das passende Environment findet.
5.  Erklären Sie, warum die statische Auflösung im Resolver nicht von den
    Laufzeitwerten abhängt, obwohl der Interpreter später mit Environments arbeitet.

# A5.7: Vertiefung: Namensauflösung (\*\*\*)

Betrachten Sie:

``` cpp
int x = 1;
{
    int x = x + 1;
}
```

Was passiert bei der Namensauflösung des `x` im Initialisierungsausdruck?
