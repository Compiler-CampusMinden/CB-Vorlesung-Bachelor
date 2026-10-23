---
author: Carsten Gips (HSBI)
title: "L-Expr: ANTLR-Visitoren und Rückgabewerte"
---

::: tldr
Der von ANTLR generierte Parser erzeugt aus der Eingabe einen Parse-Tree, der die
Strukturen der Grammatik widerspiegelt: Die Token bilden die Blätter und jede
erfolgreich durchlaufene Parser-Regel bildet einen entsprechenden Knoten im Baum.

Für die Traversierung des Parse-Tree und zum Erzeugen des AST kann man die generierten
Visitor-Klassen nutzen.
Beim Visitor muss die Traversierung selbst erledigt werden, hier steht die aus der
Klassenhierarchie geerbte Methode `visit()` als Startpunkt zur Verfügung. In dieser
Methode wird basierend auf dem Knotentyp die in den Visitor-Klassen implementierte
`visitRegelName`-Methode aufgerufen und man muss darauf achten, die Kindknoten durch
passende Aufrufe zu traversieren.
Für den Zugriff auf die Regel-Elemente werden die sogenannten Kontextobjekte als
Parameter übergeben.

Label, also benannte Alternativen und Regel-Elemente, in der Grammatik sind nützlich, weil für die benannten
Alternativen zusätzliche Kontextklassen erzeugt werden, über die dann auf die
Bestandteile der Alternativen zugegriffen werden kann. Außerdem werden zusätzlich
passende `visitLabel`-Methoden
generiert.

Am Beispiel von L-Expr wiederholen wir die aus "Programmieren 2" bekannten ANTLR-Visitoren.

-   Generischer Rückgabetyp `T` (oft `Integer` oder passend)
-   Default-Implementierung in `BaseVisitor`: `visitChildren(ctx)`
-   Frage: Für welche Regeln ist der Default passend, für welche nicht?
:::





# Erinnerung: ANTLR-Toolchain: Von String zum Parse-Tree

```java
var source = "(+ 1 2)";

var input = CharStreams.fromString(source);
var lexer = new LispyLexer(input);
var tokens = new CommonTokenStream(lexer);

var parser = new LispyParser(tokens);
var tree = parser.lexpr();
```

\bigskip

Ergebnis: ein **Parse-Tree**, noch kein AST


# ANTLR: Generierte Klassen

-   Grammatik: `Lispy.g4`
    - mit Regel `eform : '(' '+' eform eform+ ')' ;`

\bigskip

-   ANTLR generiert:
    - `LispyLexer`, `LispyParser`
    - `LispyBaseVisitor<T>` mit

        ```java
        T visitAddExpr(LispyParser.AddExprContext ctx) {
            return visitChildren(ctx);
        }
        ```

::: notes
Wir haben bereits in Prog2 darüber gesprochen: [Einführung in ANTLR](https://github.com/Programmiermethoden-CampusMinden/Prog2-Lecture-S26/blob/master/lecture/tooling/antlr.md)

Hier nur kurz zur Erinnerung: ANTLR generiert uns aus der Grammatik `Lispy.g4` einen Visitor `LispyVisitor<T>`
mit einer "leeren" Basisimplementierung `LispyBaseVisitor<T>`. Für jede Regel und benannte Alternative
finden wir da eine `visitName`-Methode, die in der Basisimplementierung einfach nur die Kinder der
Kontextklasse (also die Bestandteile der Grammatikregel) rekursiv besucht. Dabei wird das letzte Ergebnis dann zurückgegeben.

Wenn wir unseren AST-Builder schreiben wollen, können wir uns genau hier einhängen. Wir leiten von
`LispyBaseVisitor<T>` ab und überschreiben alle relevanten `visitName`-Methoden. Für jede Regel im Parser, die für unsere abstrakte Grammatik
relevant ist, überschreiben wir die passende `visit`-Methode und konstruieren dort den
entsprechenden AST-Knoten.

Der generische Parameter `T` sollte dem gewünschten Rückgabetyp der `visitName`-Methoden entsprechen. In unserem
Fall auf der Sprachstufe L-Expr wäre das ein `Expr`. Später wollen wir von unserem AST-Builder aber erneut ableiten
und die neuen
Regeln überschreiben und wir werden dann andere/weitere Rückgabetypen benötigen. Deshalb ist `Object` die passende Wahl
(auch  wenn wir dann explizit casten müssen).
:::


# AST-Builder: Beispiel Int-Literal und Addition

```java
public class LispyAstBuilderLexpr extends LispyBaseVisitor<Object> {

    @Override
    public Expr visitLexpr(LexprContext ctx) { return asExpr(visit(ctx.eform())); }

    @Override
    public Expr visitIntLit(IntLitContext ctx) {
        int value = Integer.parseInt(ctx.INT().getText());
        return new IntLiteral(value);
    }

    @Override
    public Expr visitAddExpr(AddExprContext ctx) {
        List<Expr> ops = ctx.eform().stream().map(this::visit).map(this::asExpr).toList();
        return ops.stream().reduce(AddExpr::new).orElseThrow();
    }
}
```

::: notes
Wir leiten von `LispyBaseVisitor` ab und setzten den generischen Parameter auf `Object`. Wie oben diskutiert,
wäre für L-Expr der Typ `Expr` die bessere Wahl - aber wir wollen später von diesem AST-Builder weiter ableiten
(`class LispyAstBuilderLvar extends LispyAstBuilderLexpr`) und brauchen noch weitere Rückgabetypen. Deshalb nehmen wir
in Kauf, dass wir entsprechend casten müssen. Im obigen Beispiel wurde dazu eine Hilfsmethode `Expr asExpr(Object o)`
definiert und eingesetzt. (Implementierung von `asExpr` siehe Challenge.)

Für jede Regel und für jedes Label haben wir eine `visitName`-Methode in `LispyBaseVisitor`. Wir überschreiben die
für uns relevanten Methoden, um den AST zu bauen.

Zu jeder Regel und jedem Label wird ein passendes Kontextobjekt generiert, mit dem man die Bestandteile der Regel
abfragen kann. Zur Regel `s : expr ;` würde also ein `SContext`-Objekt erzeugt bzw. der `visitS()`-Methode übergeben,
und man könnte darauf über `expr()` den `ExprContext` abfragen.

## Start: visitLexpr

Wir hatten die Startregel `lexpr : eform EOF ;`. In der zugehörigen Methode `visitLexpr` bekommen wir den Kontext
dieser Regel `LexprContext`. Auf das Element `eform` können wir hier mit `ctx.eform()` zugreifen.

Um die rekursive Traversierung anzustoßen, rufen wir die geerbte Methode `visit()` auf dieser `eform` auf und liefern
das Ergebnis als `Expr` zurück. Die geerbte Methode `visit()` erledigt den Dispatch für die Parse-Tree-Knoten
und sorgt dafür, dass jeweils die richtige `visitXYZ()`-Methode aufgerufen wird.

::: tip
### Stilfrage: kovariante Rückgabetypen

Eigentlich ist wg. `LispyBaseVisitor<Object>` der Rückgabetyp aller `visitXYZ()`-Methoden ebenfalls `Object`.
Wir liefern hier in der ableitenden Klasse `LispyAstBuilderLexpr` mit `Expr` etwas spezialisierteres zurück, und
Java erlaubt uns, dies auch in der Signatur der Methode  kenntlich zu machen. Das nennt man auch
"kovariante Rückgabetypen".
:::


## Blätter: Int-Literale

In `visitIntLit` bekommen wir ein `IntLitContext` für die Regel `atom : INT #intLit ;` (also für das Label).

Das einzige Kind in dieser Regel ist das Token `INT`, welches wir über `ctx.INT()` abfragen und das Lexem mit
`.getText()` holen. Dann müssen wir nur noch einen Java-Integer daraus machen, um ein neues `IntLiteral` für unseren
AST erzeugen zu können.

Eine weitere Traversierung ist hier nicht notwendig, die Int-Literale bilden die Blätter im Parse-Tree.

## Addition

Für die Addition überschreiben wir die Methode `visitAddExpr`. Die Regel war `eform : '(' '+' eform eform+ ')' #addExpr ;`,
weshalb im `AddExprContext` die Zugriffsmethode `eform()` vorhanden ist - allerdings haben wir mehrere `eform`-Kinder
in dieser Regel, entsprechend liefert `eform()` eine `List<EformContext>`.

Was müssen wir nun tun? Wir wollen für immer zwei Summanden ein neues `AddExpr` als AST-Knoten erzeugen (d.h. von links klammern).
Entsprechend machen wir eine Schleife über alle `eform`-Kinder der Regel/des Parse-Tree-Knotens, stoßen für diese
jeweils die rekursive Verarbeitung mit `visit()` an und bekommen so für jedes Kind einen AST, der in der Ergebnisliste
 `List<Expr>` gesammelt wird. In einem zweiten
Schritt iterieren wir über diese Liste und erzeugen von links her immer aus dem letzten `AddExpr` und dem aktuellen Eintrag ein neues
`AddExpr` - dies nennt man in der funktionalen Programmierung auch "reduce". Im ersten Schritt haben wir noch kein voriges `AddExpr`
und würden entsprechend die ersten beiden Listeneinträge in ein `AddExpr` verpacken. Falls es keine Kinder gegeben haben
sollte, würden wir hier einen Fehler werfen.
:::


# ANTLR-Pipeline komplett

```java
var source = "(+ 1 2)";

var input = CharStreams.fromString(source);
var lexer = new LispyLexer(input);
var tokens = new CommonTokenStream(lexer);

var parser = new LispyParser(tokens);
var tree = parser.lexpr();

var builder = new LispyAstBuilderLexpr();
var ast = builder.visitLexpr(tree);
```

::: notes
Ab hier sind wir jetzt synchron zu unserem AST, den wir manuell über den handgeschriebenen Lexer und unseren
RD-Parser erzeugt haben! D.h. wir könnten uns spontan aussuchen, welche dieser beiden Varianten wir nutzen möchten.

Für die Exploration von Sprachen und wachsende Grammatiken ist das Arbeiten mit ANTLR sehr angenehm, weil man
nur die Grammatik  und den AST-Builder anpassen muss.

Sobald die Sprache allerdings fix ist, gehen viele Projekte dazu über, ihre Lexer und Parser selbst zu implementieren.
:::


# Default-Implementierung: Wann reicht `visitChildren()`?

Default in `LispyBaseVisitor<T>`:

::: notes
**Hinweis**: Eigener Code, der die ursprüngliche Methode `visitChildren()` in ANTLR in der Wirkung zusammenfasst.
:::

``` java
public T visitChildren(RuleNode node) {
    return node.childs().stream()
            .map(c -> c.accept(this))
            .reduce((left, right) -> right)
            .orElse(null);
}
```

::: notes
Die Methode `visitChildren()` wird in der Defaultimplementierung in `LispyBaseVisitor` für alle `visitXYZ()`-Methoden
aufgerufen. Sie geht über alle Kinder des Knotens (Bestandteile der Grammatik-Regel), stößt jeweils die rekursive
Verarbeitung an und liefert das **letzte** Ergebnis (bzw. `null`) zurück.

Das ist einerseits sehr angenehm: Wir müssen nur noch diejenigen `visitXYZ()`-Methoden überschreiben, wo wir Dinge
aktiv bearbeiten wollen. Sobald uns die rekursive Traversierung und das Ergebnis des letzten Kindes reicht, müssen
wir diese `visitXYZ()`-Methode nicht überschreiben.

Andererseits ist dies auch gefährlich. Das letzte Kind kann ein Token sein. Die "Traversierung" eines Tokens liefert
oft nur `null` - und das wäre dann das Gesamtergebnis für den jeweiligen Knoten.

Konsequenz:
:::

- Überschreiben, wenn:

  - Semantik / Auswertung benötigt: Beispiel  `visitAddExpr`

    ::: notes
    ```java
    @Override
    public Expr visitAddExpr(AddExprContext ctx) {
        List<Expr> ops = ctx.eform().stream().map(this::visit).map(this::asExpr).toList();
        return ops.stream().reduce(AddExpr::new).orElseThrow();
    }
    ```
    :::

  - Standardlogik falsch: `parens : '(' expr ')' ;`

    ::: notes
    ```java
    @Override
    public T visitParens(ParensContext ctx) {
        return visit(ctx.expr());  // Klammern ignorieren
    }
    ```
    :::

\bigskip

- Defaultverhalten reicht, wenn

  - die Regel nur "durchgereicht" werden soll

    ```antlr
    expr    : addExpr ;
    addExpr : multExpr (('+' | '-') multExpr)* ;
    ```
    ::: notes
    Wenn wir hier `visitMultExpr` und `visitAddExpr` implementiert haben, reicht für `visitExpr` das Defaultverhalten.

    Das gilt auch, wenn eine Regel wie `expr` einfach nur mehrere Alternativen auflistet: `expr : foo | bar | wuppie | fluppie ;`
    und wir im Visitor einfach nur die passende Sub-Regel besuchen wollen, ohne für `expr` noch zusätzliche Verarbeitung
    zu benötigen.
    :::



# Wrap-up

-   ANTLR-Visitoren sind generisch: `<T>`
-   `BaseVisitor` implementiert `visitChildren()` als Default: Besuch aller Kinder,
    meist Rückgabe des letzten Kind-Ergebnisses.
-   Faustregel:
    -   Für **semantisch relevante** Regeln `visitXYZ()` überschreiben (Operatoren,
        Kontrollstrukturen, unäres Minus, ...).
    -   Für reine **Durchleitungs-/Klammer-Regeln** kann der Default genügen.



::: readings
Sie finden auf der [ANTLR-Homepage](https://www.antlr.org) Links zur Dokumentation
und auch zum [ANTLR-Projekt](https://github.com/antlr/antlr4) auf GitHub.

Eine ältere, aber dennoch interessante Quelle vom "Kopf" hinter ANTLR (Terence Parr)
ist [@Parr2014], die auch online verfügbar ist.

Die [ANTLR-Dokumentation](https://github.com/antlr/antlr4/blob/4.6/doc/index.md) und
die [ANTLR-FAQ](https://github.com/antlr/antlr4/blob/master/doc/faq/index.md) bieten
ebenfalls interessante Einstiegspunkte zur Vertiefung für Fortgeschrittene.
:::

::: outcomes
-   k3: Ich kann benannte Alternativen und Regel-Elemente zielgerichtet einsetzen
-   k2: Ich kann den Aufbau des Parse-Tree von ANTLR erklären
-   k3: Ich kann mit den Kontext-Objekten von ANTLR umgehen
-   k3: Ich kann den Parse-Tree mit den generierten Listenern oder Visitors
    traversieren und bearbeiten
:::

::: challenges
**Casten im AST-Builder**

Im Beispiel in der Vorlesung wurde die Hilfsmethode `Expr asExpr(Object o)` definiert, um nicht
manuell casten zu müssen. Wie sieht die passende Implementierung dazu aus?



**Lexer und Parser mit ANTLR**

Betrachten Sie den folgenden Programmschnipsel:

    result99 = acc_2*ACC_2 + spillover7 + bonus_1*3 + inc_0;
    calc_42 = __9 * zZ_1 + 5 + FooBar_42 * bar_7 + q0;
    _ExprLine + A_1 * bB_2 + cc3 * 7 +      11;

Erstellen Sie für diese fiktive Sprache einen Lexer+Parser mit ANTLR. Implementieren
Sie mit Hilfe des Parse-Trees und der Listener oder Visitoren einen einfachen
Pretty-Printer.

<!--
grammar MyLang;

start
  : stmt* EOF
  ;

stmt
  : id=ID '=' value=expr ';'    # Assign
  | expr ';'                    # ExprStmt
  ;

expr
  : lhs=expr '*' rhs=expr       # Mul
  | lhs=expr '+' rhs=expr       # Add
  | ID                          # Name
  | NUM                         # Number
  ;


ID  : [a-zA-Z_] [a-zA-Z_0-9]* ;
NUM : [0-9]+ ;

WS  : [ \t\r\n]+ -> skip ;
-->

**Lexer und Parser mit ANTLR: Programmiersprache Lox**

Betrachten Sie folgenden Code-Schnipsel in der Sprache
["Lox"](https://www.craftinginterpreters.com/the-lox-language.html):

    fun fib(x) {
        if (x == 0) {
            return 0;
        } else {
            if (x == 1) {
                return 1;
            } else {
                fib(x - 1) + fib(x - 2);
            }
        }
    }

    var wuppie = fib(4);

Erstellen Sie für diese fiktive Sprache einen Lexer+Parser mit ANTLR. Implementieren
Sie mit Hilfe des Parse-Trees und der Listener oder Visitoren einen einfachen
Pretty-Printer.

(Die genauere Sprachdefinition finden Sie bei Bedarf unter
[craftinginterpreters.com/the-lox-language.html](https://www.craftinginterpreters.com/the-lox-language.html).)

<!--
``` antlr
grammar MiniLox;

program: (functionDecl | statement)* EOF;

functionDecl: 'fun' IDENT '(' (IDENT (',' IDENT)*)? ')' '{' statement* '}';

statement
  : 'var' IDENT '=' expr ';'
  | 'if' '(' expr ')' statement ('else' statement)?
  | 'return' expr ';'
  | '{' statement* '}'
  | expr ';'
  ;

expr
  : expr '(' (expr (',' expr)*)? ')'
  | expr ('*'|'/') expr
  | expr ('+'|'-') expr
  | expr '==' expr
  | INT
  | IDENT
  | '(' expr ')'
  ;

IDENT: [a-zA-Z_] [a-zA-Z_0-9]*;
INT: [0-9]+;
WS: [ \t\r\n]+ -> skip;
```
-->
:::
