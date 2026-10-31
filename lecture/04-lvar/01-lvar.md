---
author: Carsten Gips (HSBI)
title: "L-Var: Überblick, Syntax und AST"
---

::: tldr
In L-Var erweitern wir Lispy um Variablen und führen damit erstmals **Zustand** in
unsere Programme ein.

Neben den bereits aus L-Int und L-Expr bekannten **Ausdrücken** (*Expressions*), die
einen Wert liefern, führen wir nun **Anweisungen** (*Statements*) ein, die
typischerweise keinen Wert, aber einen Seiteneffekt haben.

L-Var kennt Variablen und Scopes: Variablen haben einen Namen, einen Typ und einen
Wert und müssen in Lispy bei der Definition mit `def` initialisiert werden. Mit
`let` können wir den Wert existierender Variablen ändern oder neue lokale Variablen
einführen und damit **lokale Scopes** aufspannen. Scopes bestimmen, welche Namen an
welcher Programmposition sichtbar sind; äußere Variablen sind in inneren Scopes
sichtbar, umgekehrt aber nicht.

Die konkrete Syntax von L-Var ergänzt L-Int/L-Expr um Variablennamen, `def`-, `let`-
und Block-Formen sowie einen einfachen Typ `int`. In der abstrakten Syntax
unterscheiden wir jetzt zwischen `Expr` und `Stmt` und führen neue AST-Knoten wie
`VarExpr`, `VarDecl`, `AssignStmt`, `ExprStmt` und `BlockStmt` ein. Unsere
ANTLR-Grammatik für Lispy wird modular erweitert, ohne die bisherigen Regeln zu
zerstören, sodass alte Tools (z.B. der AST-Builder für L-Expr) weiter funktionieren.
Ein spezialisierter AST-Builder für L-Var (`LispyAstBuilderLvar`) leitet vom
L-Expr-Builder ab und erzeugt aus den neuen Parse-Bäumen die erweiterten
AST-Klassen. Diese AST-Struktur bildet die Grundlage, um in den nächsten Schritten
Namensauflösung mit Scopes und einen Interpreter mit Environments und Statements zu
implementieren.
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
Nicht in allen Sprachen ist der Typ direkt in der konkreten Syntax sichtbar.

In vielen **statisch typisierten** Sprachen muss man ihn explizit angeben, etwa in
Java. Es gibt aber auch statisch typisierte Sprachen, die sehr elegante Programme
erlauben fast ohne explizite Typangaben, beispielsweise Haskell. Dies funktioniert
dort über mächtige Typ-Inferenz-Systeme. (Wir werden uns später im Semester die
Typ-Prüfung (*type checking*) ansehen, quasi der kleine Bruder oder die einfache
Vorstufe für echte Typ-Inferenz (*type inference*).) "Statisch typisiert" bedeutet
dabei, dass der Typ eines Names im Laufe des Programms fest ist.

In **dynamisch typisierten** Sprachen kann der Typ eines Bezeichners im Laufe des
Programms wechseln (deshalb "dynamisch"). Hier sieht man den Typ in der konkreten
Syntax in der Regel nicht, vgl. Python oder Ruby oder PHP.

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
In Lispy (wie auch in C++) können Variablen **verändert** werden. Das bedeutet, dass
ihr gespeicherter Wert per Zuweisung geändert werden kann. An der Stelle der
Zuweisung müssen die zu ändernden Variablen "sichtbar" sein. In Lispy ändert die
`let`-Form den Wert von Variablen. (Spoiler: Die `let`-Form taucht gleich noch
einmal mit einer etwas anderen Bedeutung auf, s.u.)

::: tip
Nicht in allen Sprachen ist der Wert und damit der Zustand von Variablen
veränderbar.

Viele Sprachen arbeiten mit **veränderbaren Variablen**, auch *mutable variables*
genannt. Java, Python und viele andere fallen in diese Kategorie. Das Arbeiten mit
einem veränderlichen Zustand fühlt sich oft angenehm an, kann aber bei komplexeren
Programmen schnell zu Problemen führen. Insbesondere bei paralleler Programmierung
läuft man sehr schnell in komplexe Synchronisationsaufgaben.

In der **funktionalen Programmierung** arbeitet man häufig mit *immutable state*.
Variablen können in Haskell (wie auch in der Mathematik) nicht mehr verändert
werden, wenn sie einmal gesetzt wurden. Dies erlaubt klare und elegante
Formulierungen, die an mathematische Notation erinnern können.

In C++ führt die dynamische Speicherverwaltung in Kombination mit veränderlichen
Variablen schnell zu Problemen. Moderne Sprachen wie Rust versuchen dies zu lösen,
indem sie per Default Variablen als *immutable* betrachten (wenn man veränderliche
Variablen möchte, muss man dies explizit deklarieren). Zusätzlich gibt es komplexe
Modelle, um die Ownership einer Variablen exakt zu bestimmen (*borrow checker*).

**In unserem (Mini-) C++ in der Übung werden wir Pointer und dynamische
Speicherverwaltung nicht betrachten.**
:::

::: important
In Lispy ergibt die **Zuweisung an eine Variable keinen Wert**. Damit wird die
Zuweisung in Lispy als **Statement** behandelt.

Es gibt Sprachen wie C oder C++, wo eine Zuweisung aber als Expression behandelt
wird. Damit erschließt sich eine komplett neue und faszinierende Welt von
potentiellen Fehlern:

``` c
int i;
if (i=0) {...}
```

wäre ein gültiges Programm in C/C++! Beim Auswerten der Bedingung im `if` wird eine
Zuweisung durchgeführt, das Ergebnis in C/C++ ist der zugewiesene Wert. Da in C/C++
zudem Integer im booleschen Kontext ausgewertet werden dürfen (`0` wirkt wie
`false`), würde der Bedingungsteil dieses `if` nie ausgeführt und `i` zudem auf `0`
gesetzt. ... Fehler dieser Art findet man in der Regel nur sehr schlecht!

**Wir werden in unserem Mini-C++ davon abweichen und Zuweisungen abweichend von C++
als Statements behandeln.**
:::
:::::

# L-Var: "let" mit Scopes

::::: columns
::: column
``` clojure
(def x : int 1)
(let ((a : int 2)
      (b : int 3))
  (+ a b)
  (let x (+ x b)))
```
:::

::: column
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
:::
:::::

\bigskip

::: slides
Neue Idee: Verschachtelung und Shadowing werden wichtig
:::

:::: notes
Die `let`-Form gibt es in zwei Varianten: (1) als Zuweisung an eine bereits
existierende Variable (s.o.) und (2) als `let`-mit-Scopes, das neue **lokale
Variablen** einführt und einen **Block (Scope)** aufspannt. Scopes sind
Sichtbarkeitsbereiche für Bezeichner.

Die Namen im **lokalen Scope** sind vom umgebenden (hier globalen) Scope aus nicht
sichtbar. Andersherum sind die Namen aus dem umgebenden Scope im lokalen Scope
sichtbar (rekursiv bis hoch zum globalen Scope).

::: important
## Scopes und Name Spaces

**Def.:** Unter dem *Gültigkeitsbereich* (Sichtbarkeitsbereich, Scope) eines
Bezeichners versteht man den Programmabschnitt, in dem der Bezeichner sichtbar und
nutzbar ist. Das ist oft der kleinste umgebende Block, außer darin enthaltene
Scopes, die ein eigenes Element dieses Namens benutzen.

Scopes sind fast immer hierarchisch angeordnet.

**Def.:** Unter einem *Namensraum* (name space) versteht man die Menge der zu einem
Zeitpunkt sichtbaren Bezeichner.

Es gibt Sprachen, in denen man eigene Namensräume explizit definieren kann (z.B.
C++).

Vorsicht: Diese Begriffe werden nicht immer gleich definiert und auch gerne
verwechselt.
:::

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

Auf diesem Wege könnte man auch **Shadowing** erzeugen: Man könnte im globalen Scope
eine Variable `x` definieren, und dann im lokalen Scope erneut eine Variable `x`
anlegen. Wenn man im lokalen Scope ist, verdeckt diese lokale Variable `x` die
globale Variable `x`:

``` clojure
(def x : int 1)
(let ((x : int 2))
  (let x (+ x 2)))
```

Hier sollte das globale `x` von der Addition im Block unberührt bleiben, d.h. das
globale `x` sollte am Ende des Programms immer noch den ursprünglichen Wert `1`
haben, während im `let`-Block das lokale `x` mit `2` initialisiert wird und dann per
Zuweisung noch einmal im Wert auf `4` verändert wird.

Scopes können nahezu beliebig ineinander verschachtelt werden.
::::

# L-Var: Konkrete Grammatik

::: notes
Wir bauen auf L-Int und L-Expr auf und ergänzen L-Var. Im Stil von [@Siek2023python]
sind über den Trennern `---` die bisherigen Regeln für die konkrete Syntax (L-Int,
L-Expr) angegeben. Danach folgen die neuen Regeln für L-Var:
:::

``` ebnf
eform ::= '(' '+' eform eform+ ')' | '(' '-' eform eform+ ')' | INT
INT   ::= [0-9]+
---
eform ::= '(' '*' eform eform+ ')' | '(' '/' eform eform+ ')' | '(' '-' eform ')'
---

eform ::= ID
sform ::= eform
        | '(' 'def' ID ':' type eform? ')'
        | '(' 'let' ID eform ')'
        | '(' 'let' '(' ltBdg+ ')' sform+ ')'
ltBdg ::= '(' ID ':' type eform ')' ;
type  ::= 'int'
ID    ::= [a-zA-Z][a-zA-Z_0-9]*

lvar  ::= sform* EOF
```

::: notes
Mit L-Var ergänzen wir eine neue Expression in der `eform`: lesender Zugriff auf
eine Variable. D.h. ein Variablenname (hier als `ID`) stellt für sich eine
Expression dar.

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

::: notes
# L-Var: Abstrakte Syntax (AST)
:::

::: slides
# L-Var: Abstrakte Syntax (AST, Teil 1/2)
:::

::: notes
Im Stil von [@Siek2023python] sind über den Trennern `---` die bisherigen Regeln für
die abstrakte Syntax (L-Int, L-Expr) angegeben. Danach folgen die neuen Regeln für
L-Var:
:::

``` ebnf
Expr = IntLiteral(Int) | AddExpr(Expr, Expr) | SubExpr(Expr, Expr)
---
Expr = MulExpr(Expr, Expr) | DivExpr(Expr, Expr)
---

Expr = VarExpr(String)
Stmt = ExprStmt(Expr)
     | VarDecl(String, Type, Expr)
     | AssignStmt(Expr, Expr)
     | BlockStmt([Stmt])
Type = IntType

Lvar = [Stmt]
```

::: notes
Die Expressions bekommen eine neue `VarExpr` für den lesenden Zugriff auf
Variablennamen.

Die Statements sind komplett neu und modellieren die Variablendeklaration und die
Zuweisung an eine Variable. Dazu kommen ein `BlockStmt` für die `let`-Form mit
Scopes sowie der "Cast" einer Expression in ein Statement.

Das lässt sich wie bereits bei L-Int und L-Expr in die entsprechenden AST-Klassen
übersetzen:
:::

::: slides
# L-Var: Abstrakte Syntax (AST, Teil 2/2)
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
public record BlockStmt(List<Stmt> stmts) implements Stmt {}
```

:::: notes
Damit lassen sich dann die neuen Features aus L-Var im AST modellieren:

-   `VarExpr` - Lesen einer Variable
-   `VarDecl` - Einführung/Binden einer Variable
-   `AssignStmt` - Zuweisung an eine Variable (später wichtig für Resolver)
-   `BlockStmt` - Scope für mehrere Statements (aus der `let`-mit-Scopes-Form)

**Anmerkung**: `AssignStmt` verwendet als Ziel (`target`) eine `Expr`. In L-Var
werden wir hier nur einfache `VarExpr` zulassen; die allgemeinere Form wird erst in
späteren Sprachstufen interessant.

::: tip
## Exkurs: Definitionen und Deklarationen von Bezeichnern

In der Literatur wird teilweise zwischen **Deklaration** und **Definition**
unterschieden.

**Def.:** Die **Definition** eines (bisher nicht existenten) Bezeichners in einem
Programm generiert einen neuen Bezeichner und legt für ihn seinem Typ entsprechend
Speicherplatz an.

**Def.:** Unter der **Deklaration** eines (bereits existierenden) Bezeichners
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
letStmt     : ...
...

type        : 'int' ;
...
```

::: notes
Hier ist ein Teil der ANTLR-Grammatik für L-Var, resultierend aus der konkreten
Grammatik, gezeigt.

Wir verwenden für L-Var die bereits für L-Expr erstellte Grammatik `Lispy.g4` weiter
und ergänzen nur die neuen Regeln.

Per Konvention ist die erste Regel die Startregel, hier wäre das
`lvar : sform* EOF ;`. Aber man kann auf dem von ANTLR generierten Parser auch
andere Regeln aufrufen. Deshalb bleibt die alte Startregel aus L-Expr
`lexpr : eform EOF ;` mit drin, wodurch unser Tooling auf L-Expr-Ebene weiterhin
funktioniert (insbesondere der AST-Builder).

Wie in der konkreten Grammatik bereits angemerkt, besteht ein L-Var-Programm aus
einer Liste von `sform`-Forms, also einer Sequenz von Statements. Die `eform`-Formen
sind Teil von `sform`-Formen, insbesondere gibt es in Lispy die Regel
`exprStmt : eform ;` - eine Expression kann überall verwendet werden, wo ein
Statement erwartet wird. Dies ist nicht in allen Sprachen so, insbesondere ist in
C++ eine Expression erst dann ein Statement, wenn sie von einem Semikolon
abgeschlossen wird.

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
Dazu brauchen wir noch ein Interface `Type` und ein initiales Enum `BuiltinType`
o.ä. zur Repräsentation der eingebauten Typen, etwa so:

``` java
public interface Type {}

enum BuiltinType implements Type {
    INT
}
```
:::

# Wrap-up

-   L-Var: Variablen, Scopes und **Zustand**
    -   **Expressions** (liefern Wert)
    -   **Statements** (ändern Zustand, liefern keinen Wert)

\smallskip

-   Scopes bestimmen die **Sichtbarkeit** von Variablen
    -   innere Scopes sehen äußere Variablen, umgekehrt nicht

\smallskip

-   Sprachfeatures in L-Var:
    -   `def`: definiert neue Variablen mit Typ und Initialwert
    -   `let`:
        -   Zuweisung für Variablen, oder‚
        -   neue **lokale Variablen** mit eigenem lokalem Scope

::: readings
In [@Nystrom2021] kann man in Kapitel 8 "Statements and State" nachlesen. Auch die
Darstellung im [@Siek2023python] in Kapitel 2 "Integers and Variables" ist sehr
hilfreich.
:::

::: outcomes
-   k1: Ich kann die Begriffe *Expression*, *Statement*, *Scope* und *Variable*
    definieren.
-   k2: Ich kann anhand von Beispielen erklären, warum Variablendefinitionen und
    Zuweisungen in L-Var als Statements und nicht als Expressions behandelt werden.
-   k2: Ich kann erläutern, wie Scopes die Sichtbarkeit von Variablen beeinflussen
    und wie globale und lokale Variablen sich unterscheiden.
-   k3: Ich kann Lispy-L-Var-Programme in *konkrete* und *abstrakte* Syntax
    (AST-Bäume mit `Expr`- und `Stmt`-Knoten) übersetzen.
-   k3: Ich kann eine bestehende ANTLR-Grammatik (L-Expr) um Variablen, Statements
    und Scopes zu L-Var erweitern und den AST-Builder entsprechend anpassen.
-   k4: Ich kann für ein gegebenes L-Var-Programm den Scope-Baum bestimmen und jede
    Variablenreferenz (`VarExpr`) der zugehörigen Deklaration (`VarDecl`) zuordnen.
:::

::: challenges
**Statements vs. Expressions**

1.  Geben Sie für den folgenden Lispy-Code in **L-Var**-Syntax eine AST-Struktur an:

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

**Konkrete vs. abstrakte Syntax für `let`-mit-Scope**

Gegeben ist folgender Lispy-L-Var-Code:

``` clojure
(def x : int 1)
(def y : int 2)
(let ((x : int 3)
      (z : int 4))
  (+ x y)
  (+ x z))
(+ x y)
```

1.  Schreiben Sie die konkrete Grammatikableitung (Parse-Tree) in Form der
    verwendeten Nonterminals (z.B. `sform`, `eform`, ...) für die äußere `let`-Form
    (nicht das gesamte Programm, nur das `let`-Statement).
2.  Geben Sie den zugehörigen abstrakten Syntaxbaum (AST) für das `let`-Statement
    an:
    -   Welche `Stmt`-Knoten entstehen (`VarDecl`, `BlockStmt`, `ExprStmt`, ...)?
    -   Welche `Expr`-Knoten entstehen (`VarExpr`, `AddExpr`, `IntLiteral`, ...)?
    -   Markieren Sie im AST, welche `VarExpr`-Knoten sich auf das innere `x` und
        welche sich auf das äußere `y` beziehen.

Diskussion im Plenum: Wo wäre Shadowing möglich, und warum ist das im AST allein
noch nicht aufgelöst?

**Statements aus Expressions bauen**

Betrachten Sie die folgenden Lispy-Fragmente (L-Var):

``` clojure
(+ 1 2)
(def a : int (+ 1 2))
(let a (+ a 1))
(let ((b : int 10))
  (+ b 1)
  (let b (+ b 2)))
```

1.  Ordnen Sie jede Zeile bzw. jeden Block ein als:
    -   reine Expression,
    -   Statement,
    -   Block mit mehreren Statements.
2.  Bestimmen Sie für jede Zeile/jeden Block:
    -   Welche `Stmt`-Knoten entstehen (z.B. `ExprStmt`, `VarDecl`, `AssignStmt`,
        `BlockStmt`)?
    -   Welche `Expr`-Knoten entstehen?
3.  Diskutieren Sie kurz:
    -   Warum ist `(+ 1 2)` in L-Var alleine als Zeile ein Statement, obwohl es
        syntaktisch wie eine Expression aussieht?
    -   Welche Sprache(n), die Sie kennen, erlauben ebenfalls "nackte" Expressions
        als Statements?

**ANTLR-Regel-Design für `let`**

Sie möchten die beiden `let`-Varianten in ANTLR so modellieren, dass der AST-Builder
sie leicht unterscheiden kann:

``` clojure
(let x (+ x 1))                         ;; Zuweisung
(let ((a : int 2) (b : int 3)) ... )    ;; lokaler Scope mit Bindungen
```

1.  Entwerfen Sie eine ANTLR-Regel `letStmt`, die beide Varianten unterscheidbar
    macht, z.B. mit zwei Alternativen und Labels.
2.  Skizzieren Sie (in Pseudocode oder Java-ähnlich), wie die entsprechenden
    `visitXYZ()`-Methoden im `LispyAstBuilderLvar` aussehen könnten, um:
    -   im ersten Fall einen `AssignStmt` zu erzeugen,
    -   im zweiten Fall einen `BlockStmt` mit passenden `VarDecl`-Knoten und
        Body-Statements zu erzeugen.
3.  Diskutieren Sie in der Gruppe:
    -   Welche Vor- und Nachteile hat es, eine `letStmt`-Regel mit zwei Alternativen
        zu haben, im Vergleich zu zwei getrennten Regeln (z.B. `assignLet` und
        `scopedLet`)?
    -   Könnte man die `def`-Form auch noch zu einer `let`-Form (also einer dritten
        Alternative) machen? Was spräche dafür, was spräche dagegen?
:::
