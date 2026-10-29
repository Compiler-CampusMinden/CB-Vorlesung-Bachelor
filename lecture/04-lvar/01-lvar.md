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

# Erinnerung L-Int / L-Expr: Nur Ausdrücke

``` clojure
(+ 1 (* 2 3))
(/ (- 10 4) 2)
```

\bigskip

::: slides
Bisher: reine Arithmetik, nur Expressions, kein Zustand
:::

::: notes
Bisher hatten wir in L-Int und darauf aufbauend in L-Expr nur Integer-Werte und
arithmetische Operationen betrachtet. Wir können damit prima Taschenrechner spielen,
aber für ernsthafte Programme fehlen uns noch Variablen und Blöcke (L-Var),
Kontrollstrukturen (L-If) und Funktionen (L-Fun) ...
:::

# L-Var: Variablen definieren

``` clojure
(def x : int 10)
(+ x 5)
```

\bigskip

::: slides
Neue Idee: Namen binden Werte
:::

::::: notes
Variablen haben einen **Namen**, einen **Typ** und einen **Wert**. Variablen sind
nach ihrer Definition über ihren Namen zugreifbar (sofern "sichtbar", vgl.
Scope-Diskussion weiter unten). In Lispy müssen Variablen bereits bei der
**Definition initialisiert** werden.

Die `def`-Form definiert Variablen in Lispy.

Variablen führen **Zustand** im Programm ein. In L-Int und L-Expr waren wir
zustandslos, wir mussten uns nichts merken und einfach nur den aktuellen
arithmetischen Ausdruck auswerten. Mit Variablen haben wir Zustand: Wir definieren
die Variable an einer (beliebigen) Stelle im Programm, und können später (unter
bestimmten Bedingungen - "Sichtbarkeit", "Scopes") wieder darauf zugreifen.

Zur Laufzeit müssen Variablen deshalb geeignet im Speicher abgelegt werden. Der Name
der Variablen ist für den Compiler eine Art "Adresse" für den Zugriff auf den
korrekten Speicherort. Wir werden darüber im Interpreter noch einmal sprechen und
"Environments" anlegen.

Im Beispiel definieren wir in unserem Lispy-Dialekt L-Var eine Variable `x` vom Typ
`int` und initialisieren sie mit dem Wert `5`. Dabei bedeutet der Typ `int` in L-Var
offensichtlich Integer-Werte. Wenn wir später auf diese Variable lesend zugreifen,
können wir diesen Wert abrufen.

::: tip
Nicht in allen Sprachen ist der Typ direkt sichtbar.

In vielen statisch typisierten Sprachen muss man ihn explizit angeben, etwa in Java.
Es gibt aber auch statisch typisierte Sprachen, die sehr elegante Programme erlauben
fast ohne explizite Typangaben, beispielsweise Haskell. Dies funktioniert dort über
mächtige Typ-Inferenz-Systeme. (Wir werden uns später im Semester die Typ-Prüfung
(*type checking*) ansehen, quasi der kleine Bruder oder die einfache Vorstufe für
echte Typ-Inferenz (*type inference*).) "Statisch typisiert" bedeutet dabei, dass
der Typ eines Names im Laufe des Programms fest ist.

In dynamisch typisierten Sprachen kann der Typ eines Namens im Laufe des Programms
wechseln (deshalb "dynamisch"). Hier sieht man den Typ in der konkreten Syntax in
der Regel nicht, vgl. Python oder Ruby oder PHP.

Unser Lispy in der Vorlesung ist wie das (Mini-) C++ in der Übung statisch
typisiert.
:::

::: important
Bisher hatten wir nur **Ausdrücke** (*expressions*) betrachtet. Alles in L-Int und
L-Expr ergab einen Wert, d.h. alle Programme in L-Int und L-Expr wurden durch
Ausdrücke gebildet.

**Welchen Wert hat eine Variablendefinition?**

In Lispy wie in vielen anderen Sprachen ergibt die Variablendefinition bei der
Auswertung keinen Wert. Zudem verändert sie den Zustand des Programms, weshalb man
eine Variablendefinition auch **Anweisung** (*statement*) nennt.

Wir führen also in L-Var nun Statements zu den Expressions von L-Int und L-Expr
hinzu.
:::
:::::

# L-Var: "let" - Zuweisung an Variablen

``` clojure
(def x : int 10)
(let x (+ x 1))
(+ x 5)
```

\bigskip

::: slides
Neue Idee: Variablen können verändert werden
:::

::::: notes
In Lispy (wie auch in C++) können Variablen verändert werden. Das bedeutet, dass ihr
gespeicherter Wert per Zuweisung geändert werden kann. An der Stelle der Zuweisung
müssen zu ändernden Variablen "sichtbar" sein. In Lispy ändert die `let`-Form den
Wert von Variablen.

::: tip
Nicht in allen Sprachen ist der Wert und damit der Zustand von Variablen
veränderbar.

Viele Sprachen arbeiten mit veränderbaren Variablen, auch *mutable variables*
genannt. Java, Python und viele andere fallen in diese Kategorie. Das Arbeiten mit
einem veränderlichen Zustand fühlt sich oft angenehm an, kann aber bei komplexeren
Programmen schnell zu Problemen führen. Insbesondere bei paralleler Programmierung
läuft man sehr schnell in komplexe Synchronisationsaufgaben.

In der funktionalen Programmierung arbeitet man häufig mit *immutable state*.
Variablen können in Haskell (wie auch in der Mathematik) nicht mehr verändert
werden, wenn sie einmal gesetzt wurden. Dies erlaubt klare und elegante
Formulierungen, die an mathematische Notation erinnern können.

In C++ führt die dynamische Speicherverwaltung in Kombination mit veränderlichen
Variablen schnell zu Problemen. Moderne Sprachen wie Rust versuchen dies zu lösen,
indem sie per Default Variablen als *immutable* betrachten (wenn man veränderliche
Variablen möchte, muss man dies explizit deklarieren). Zusätzlich gibt es komplexe
Modelle, um die Ownership einer Variablen exakt zu bestimmen (*borrow checker*).

In unserem (Mini-) C++ in der Übung werden wir Pointer und dynamische
Speicherverwaltung nicht betrachten.
:::

::: important
In Lispy ergibt die Zuweisung an eine Variable keinen Wert. Damit wird die Zuweisung
in Lispy als Statement behandelt.

Es gibt Sprachen wie C oder C++, wo eine Zuweisung aber als Expression behandelt
wird. Damit erschließt sich eine komplett neue und faszinierende Welt von
potentiellen Fehlern:

``` c
int i;
if (i=0) {...}
```

wäre ein gültiges Programm! Beim Auswerten der Bedingung im `if` wird eine Zuweisung
durchgeführt, das Ergebnis in C/C++ ist der zugewiesene Wert. Da in C/C++ zudem
Integer im booleschen Kontext ausgewertet werden dürfen (`0` ist `false`), würde der
Bedingungsteil dieses `if` nie ausgeführt und `i` zudem auf `0` gesetzt. ... Fehler
dieser Art findet man in der Regel nur sehr schlecht!

Wir werden in unserem Mini-C++ davon abweichen und Zuweisungen abweichend von C++
als Statements behandeln.
:::
:::::

# L-Var: "let" mit Scopes

``` clojure
(def x : int 1)
(let ((a : int 2)
      (b : int 3))
  (+ a b)
  (let x (+ x b)))
```

::: slides
Neue Idee: Verschachtelung und Shadowing werden wichtig
:::

::: notes
Die `let`-Form gibt es in zwei Varianten: (1) als Zuweisung an eine bereits existierende
Variable (s.o.) und (2) als `let`-mit-Scopes, das neue lokale Variablen einführt und einen Block (Scope)
aufspannt.

Die Namen im **lokalen
Scope** sind vom umgebenden Scope aus nicht sichtbar.
Andersherum sind die Namen aus dem umgebenen Scope im lokalen Scope sichtbar
(rekursiv bis hoch zum globalen Scope).

```
+----------------------+
|     GLOBAL SCOPE     |
+----------------------+
| symbols = [x : int]  |
+----------------------+
           ^
           |
           |
+----------------------+
|     LOCAL SCOPE      |
+----------------------+
| symbols = [a : int,  |
|            b : int]  |
+----------------------+
```

Im Beispiel ist `x` eine **globale** Variable, die im gesamten Programm sichtbar
ist. Dagegen sind `a` und `b` **lokale** Variablen, deren Gültigkeitsbereich sich
auf den Körper der `let`-Form beschränkt. D.h. im Inneren der `let`-Form ist
`(+ a b)` erlaubt - außerhalb nicht, weil dort `a` und `b` nicht existieren. `x` ist
dagegen auch in dem durch die `let`-Form aufgespannten Scope sichtbar: Wir finden
`x` nicht direkt im **lokalen Scope** der `let`-Form, aber im umgebenden Scope (hier
der **globale Scope**).

In Java würde das Snippet ungefähr so aussehen:

``` java
int x = 1;
{
    int a = 2;
    int b = 3;
    a + b;
    x = x + b;
}
```
:::

# L-Var: Konkrete Grammatik

::: notes
Wir bauen auf L-Int und L-Expr auf und ergänzen L-Var. Im Stil von [@Siek2023python]
sind über den Trennern `---` die bisherigen Regeln für die konkrete Syntax (L-Int,
L-Expr) angegeben. Danach folgen die neuen Regeln für L-Var:
:::

``` ebnf
eform  ::= '(' '+' eform eform+ ')' | '(' '-' eform eform+ ')' | INT
INT    ::= [0-9]+
---
eform  ::= '(' '*' eform eform+ ')' | '(' '/' eform eform+ ')' | '(' '-' eform ')'
---

eform ::= ID
sform ::= eform
        | '(' 'def' ID ':' type eform? ')'
        | '(' 'let' ID eform ')'
        | '(' 'let' '(' ltBdg+ ')' sform+ ')'
ltBdg ::= '(' ID ':' type eform ')' ;
type  ::= 'int'
ID    ::= [a-zA-Z][a-zA-Z_0-9]*

Lvar  ::= sform* EOF
```

::: notes
Mit L-Var ergänzen wir neue Expressions in der `eform`: lesender Zugriff auf eine
Variable. D.h. ein Variablenname (hier als `ID`) stellt für sich eine Expression
dar.

Zusätzlich haben wir aber nun auch Statements: Variablendefinition und Zuweisung
sowie `let` mit lokalen Bindungen und einem lokalen Scope.

Außerdem taucht zum ersten Mal ein expliziter Typ auf: Integer-Werte werden mit dem
Typnamen `int` bezeichnet.

Unser Programm besteht ab jetzt aus einer Menge von Statements, d.h. wir betrachten
Listen von `sform`, also *Sequenzen von Statements*. Expressions (`eform`) sind
i.d.R. **Teile** von Statements (`sform`).

Diese Definition wird uns zur Laufzeit im Interpreter noch etwas Kopfzerbrechen
bereiten: Was genau liefert ein Programm zurück?
:::

# L-Var: Abstrakte Syntax (AST)

::: notes
Im Stil von [@Siek2023python] sind über den Trennern `---` die bisherigen Regeln für
die abstrakte Syntax (L-Int, L-Expr) angegeben. Danach folgen die neuen Regeln für
L-Var:
:::

``` ebnf
Expr  = IntLiteral(Int) | AddExpr(Expr, Expr) | SubExpr(Expr, Expr)
---
Expr  = MulExpr(Expr, Expr) | DivExpr(Expr, Expr)
---

Expr  = VarExpr(String)
Stmt  = ExprStmt(Expr)
      | VarDecl(String, Type, Expr)
      | AssignStmt(Expr, Expr)
      | BlockStmt([Stmt])
Type  = IntType

Lvar  = [Stmt]
```

::: notes
Die Expressions bekommen eine neue `VarExpr` für den lesenden Zugriff auf
Variablennamen.

Die Statements sind komplett neu und modellieren eine Variablendeklaration und eine
Zuweisung an eine Variable. Dazu kommen ein `BlockStmt` für die `let`-Form mit
Scopes sowie der "Cast" einer Expression in ein Statement.

Das lässt sich wie bereits bei L-Int und L-Expr in die entsprechenden AST-Klassen
übersetzen:
:::

``` java
public interface Expr {}
public interface Stmt {}
```

::: notes
Wir haben einen neuen Obertyp `Stmt` zur Repräsentation von Statements:
`interface Stmt`.

Die bisherigen Klassen aus L-Int und L-Expr gelten weiterhin:

``` java
public record IntLiteral(int value) implements Expr {}
public record AddExpr(Expr left, Expr right) implements Expr {}
public record SubExpr(Expr left, Expr right) implements Expr {}

public record MulExpr(Expr left, Expr right) implements Expr {}
public record DivExpr(Expr left, Expr right) implements Expr {}
```

Dazu kommen nun die neuen Klassen für L-Var:
:::

``` java
public record VarExpr(String name) implements Expr {}
public record VarDecl(String name, Type type, Expr init) implements Stmt, Decl {}
public record AssignStmt(Expr target, Expr expr) implements Stmt {}
public record ExprStmt(Expr expr) implements Stmt {}
public record BlockStmt(List stmts) implements Stmt {}
```

:::: notes
Damit lassen sich dann die neuen Features aus L-Var im AST modellieren:

-   `VarExpr` - Lesen einer Variable
-   `VarDecl` - Einführung/Binden einer Variable
-   `AssignStmt` - Zuweisung an eine Variable (später wichtig für Resolver)
-   `BlockStmt` - Scope für mehrere Statements (aus der `let`-mit-Scopes-Form)

**Anmerkung**: `AssignStmt` verwendet als Ziel (`target`) eine `Expr`. In L-Var werden wir
hier nur einfache `VarExpr` zulassen; die allgemeinere Form wird erst in späteren Sprachstufen interessant.

::: tip
## Definitionen und Deklarationen von Bezeichnern

In der Literatur wird teilweise zwischen **Deklaration** und **Definition**
unterschieden.

**Def.:** Die *Definition* eines (bisher nicht existenten) Bezeichners in einem
Programm generiert einen neuen Bezeichner und legt für ihn seinem Typ entsprechend
Speicherplatz an.

**Def.:** Unter der *Deklaration* eines (bereits existierenden) Bezeichners
verstehen wir seine Bekanntmachung, damit er benutzt werden kann. Er ist oft in
einem anderen Scope definiert und bekommt dort Speicherplatz zugeteilt.

Insbesondere werden Typen *deklariert*. Hier gibt es in der Regel gar keine
Speicherplatzzuweisung.

Ein Bezeichner kann in C/C++ beliebig oft deklariert werden, während er in einem
Programm nur einmal definiert werden kann. Oft wird bei der Deklarationen eines
Elements sein Namensraum mit angegeben. Wir werden in unserem Mini-C++ zur
Vereinfachung diese Feinheit nicht ausnutzen.

**Vorsicht**: Die Begriffe werden oft auch anders verwendet, beispielsweise findet
sich in der Java-Literatur der Begriff *Deklaration* anstelle von *Definition*.
**Wir folgen in Lispy diesem unscharfen Sprachgebrauch: `def` in der konkreten
Syntax kommt von "Definieren einer Variablen", in der abstrakten Syntax nutzen wir
dafür dann aber `VarDecl` von "Deklarieren einer Variablen".**
:::
::::

# Implementierungsdetails: ANTLR-Grammatik L-Var

::: notes
Konkrete ANTLR-Grammatik (Ausschnitte):
:::

``` antlr
grammar Lispy;

lvar        : sform* EOF ;
lexpr       : eform EOF ;

sform       : exprStmt | varDecl | letStmt ;
eform       : ...

exprStmt    : eform ;
varDecl     : '(' 'def' ID ':' type eform? ')' ;
...

type        : 'int' ;

...
```

::: notes
Hier ist ein Teil der ANTLR-Grammatik für L-Var, resultierend aus der konkreten
Grammatik, gezeigt.

Wir verwenden für L-Var die bereits für L-Expr erstellte Grammatik weiter und
ergänzen nur die neuen Regeln.

Per Konvention ist die erste Regel die Startregel, hier wäre das
`lvar : sform* EOF ;`. Aber man kann auf dem von ANTLR generierten Parser auch
andere Regeln aufrufen. Deshalb bleibt die alte Startregel aus L-Expr
`lexpr : eform EOF ;` mit drin, wodurch unser Tooling auf L-Expr-Ebene weiterhin
funktioniert (insbesondere der AST-Builder).

Wie in der konkreten Grammatik bereits angemerkt, besteht ein L-Var-Programm aus
einer Liste von `sform`-Forms, also einer Sequenz von Statements. Die `eform`-Formen
sind Teil von `sform`-Formen, insbesondere gibt es in Lispy die Regel
`exprStmt : eform ;` - eine Expression kann überall verwendet werden, wo ein
Statement erwartet wird. Dies ist nicht in allen Sprachen so, inbesondere ist in C++
eine Expression erst dann ein Statement, wenn sie von einem Semikolon abgeschlossen
wird.

Ansonsten werden wie gewohnt die Regeln aus der konkreten Syntax in die
ANTLR-Grammatik übersetzt. Dabei ist es hilfreich, für die Regeln und die Label auf
"sprechende" Namen zu achten. Dies unterstützt die Lesbarkeit der Grammatik, und da
zu jeder Regel und jedem Label eine `visitXYZ()`-Methode generiert wird, erleichtert
uns das auch das Zurechtfinden im AST-Builder.
:::

# Implementierungsdetails: AST-Builder L-Var

::: notes
Wir hatten für `Lispy.g4` auf dem L-Expr-Level bereits einen Visitor zum Bauen des
AST aus dem ANTLR-Parse-Tree definiert:
`class LispyAstBuilderLexpr extends LispyBaseVisitor<Object>`.

Wir ergänzen diese Grammatik nun mit einer neuen Startregel und den für Lispy L-Var
notwendigen neuen Regeln für die konkrete Syntax. Damit funktioniert der
`LispyAstBuilderLexpr` immer noch (so lange wir nicht benutzte Regeln umbenennen
oder relevante Elemente in den L-Expr-Regeln ändern o.ä.).

In L-Var generiert ANTLR nun für die neuen Regeln und Labels entsprechende
zusätzliche `visitXYZ()`-Methoden und bietet in `LispyBaseVisitor` die
Defaultimplementierung an. Das nutzen wir aus und leiten den Visitor für L-Var
einfach vom Visitor für L-Expr ab und ergänzen die notwendigen Implementierungen
beispielsweise für `exprStmt`, `varDecl`, `letStmt`:
:::

``` java
public class LispyAstBuilderLvar extends LispyAstBuilderLexpr {
    @Override
    public List<Stmt> visitLvar(LvarContext ctx) {
        return ctx.sform().stream().map(this::visit).map(Stmt.class::cast).toList();
    }
    @Override
    public Expr visitVarExpr(VarExprContext ctx) {
        return new VarExpr(ctx.ID().getText());
    }
    @Override
    public Stmt visitExprStmt(ExprStmtContext ctx) {
        Expr expr = asExpr(visit(ctx.eform()));
        return new ExprStmt(expr);
    }
    @Override
    public Type visitType(TypeContext ctx) {
        if (ctx.getText().equals("int")) return BuiltinType.INT;
        throw new RuntimeException("'int' type expected");
    }
...
}
```

::: notes
Dazu brauchen wir ein Interface `Type` und ein initiales Enum `BuiltinType` zur
Repräsentation der eingebauten Typen, etwa so:

``` java
public interface Type {}

enum BuiltinType implements Type {
    INT
}
```
:::

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
