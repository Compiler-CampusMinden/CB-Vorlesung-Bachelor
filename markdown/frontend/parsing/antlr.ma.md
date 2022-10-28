---
archetype: lecture-cg
title: "ANTLR (Parsergenerator)"
author: "Carsten Gips (FH Bielefeld)"
weight: 5
readings:
  - key: "Aho2008"
    comment: " Abschnitt 2.6 und Kapitel 3"
tldr: |
  TODO
outcomes:
  - k2: "TODO"
  - k3: "TODO"
assignments:
  - topic: sheet01
youtube:
  - link: ""
    name: "VL Parsen mit ANTLR"
fhmedia:
  - link: ""
    name: "VL Parsen mit ANTLR"

sketch: true
---


## Hello World

TODO: Hello World mit Parser-Regeln, eine Slide mit vielen Formen von Regeln als Beispiel
https://github.com/antlr/antlr4/blob/master/doc/parser-rules.md

::::::::: notes
### Starten des Parsers

TODO: `grun Hello start -tree` und `grun Hello start -gui`

### Startregeln

TODO: Startregel (https://github.com/antlr/antlr4/blob/master/doc/parser-rules.md#start-rules-and-eof)

### Formen der Subregeln

TODO: Formen der Subregeln (https://github.com/antlr/antlr4/blob/master/doc/parser-rules.md#subrules)

### Parse-Tree

TODO: Beispiel: Grammatik, Eingabe, Parse-Tree

### EOF oder kein EOF?

TODO: EOF vs. kein EOF (https://github.com/antlr/antlr4/blob/master/doc/parser-rules.md#start-rules-and-eof)
:::::::::


## Expressions und Vorrang (Operatoren)

TODO: Beispiel von oben vereinfachen

::: notes
### Direkte vs. indirekte Linksrekursion

TODO: https://github.com/antlr/antlr4/blob/master/doc/left-recursion.md

### Konflikte in Regeln

TODO: Konflikte in Regeln (lexikalische Regeln in Parser-Regeln): S. 76
:::


## Kontext-Objekte für Parser-Regeln

TODO: Überblick, mit Verweis auf backend/interpretation/syntaxdriven: dort Kontextobjekte nur Skript!

```yacc
s    : expr         {List<EContext> x = $expr.ctx.e();} ;
expr : e '*' e ;
```

\bigskip
\bigskip

![](images/ParserRuleContext.png)

::: notes
Jede Regel liefert ein passend zu dieser Regel generiertes Kontext-Objekt
zurück. Darüber kann man das/die Kontextobjekt(e) der Sub-Regeln abfragen.

Die Regel `s()` liefert entsprechend ein `SContext`-Objekt und die Regel
`expr()` liefert ein `ExprContext`-Objekt zurück.

In der Aktion fragt man das Kontextobjekt über `ctx` ab.

Für einfache Regel-Aufrufe liefert die parameterlose Methode nur ein
einziges Kontextobjekt (statt einer Liste) zurück.

**Anmerkung**: ANTLR generiert nur dann Felder für die Regel-Elemente im
Kontextobjekt, wenn diese in irgendeiner Form referenziert werden. Dies
kann beispielsweise durch Benennung (Definition eines Labels, siehe nächste
Folie) oder durch Nutzung in einer Aktion (siehe obiges Beispiel) geschehen.
:::


## Benannte Regel-Elemente oder Alternativen

TODO: Label für Teilausdrücke und Alternativen (S.119, S.265) => Teil-Kopie aus backend/interpretation/syntaxdriven (dort nur Skript!)

```yacc
stat  : 'return' value=e ';'    # Return
      | 'break' ';'             # Break
      ;
```

\bigskip

```java
public static class StatContext extends ParserRuleContext { ... }
public static class ReturnContext extends StatContext {
    public EContext value;
    public EContext e() { ... }
}
public static class BreakContext extends StatContext { ... }
```

::: notes
Mit `value=e` wird der Aufruf der Regel `e` mit dem Label `value` belegt,
d.h. man kann mit `$e.text` oder `$value.text` auf das `text`-Attribut von
`e` zugreifen. Falls es in einer Produktion mehrere Aufrufe einer anderen
Regel gibt, **muss** man für den Zugriff auf die Attribute eindeutige Label
vergeben.

Analog wird für die beiden Alternativen je ein eigener Kontext erzeugt.
:::


## Arbeiten mit dem Listener-Pattern

TODO: Überblick, mit Verweis auf backend/interpretation/syntaxdriven: dort Kontextobjekte nur Skript!

::: notes
ANTLR (generiert auf Wunsch) zur Grammatik passende Listener (Interface und
leere Basisimplementierung). Beim Traversieren mit dem Default-`ParseTreeWalker`
wird der Parse-Tree mit Tiefensuche abgelaufen und jeweils beim Eintritt in
bzw. beim Austritt aus einen/m Knoten der passende Listener mit dem passenden
Kontext-Objekt aufgerufen.

Damit kann man die Grammatik "für sich" halten, d.h. unabhängig von einer
konkreten Zielsprache und die Aktionen über die Listener (oder Visitors, s.u.)
ausführen.
:::

```{.yacc size="footnotesize"}
expr : e1=expr '*' e2=expr      # MULT
     | e1=expr '+' e2=expr      # ADD
     | DIGIT                    # ZAHL
     ;
```

\smallskip

::: notes
ANTLR kann zu dieser Grammatik einen passenden Listener (Interface `calcListener`)
generieren. Weiterhin generiert ANTLR eine leere Basisimplementierung (Klasse
`calcBaseListener`):

![](images/ParseTreeListener.png)

Von dieser Basisklasse leitet man einen eigenen Listener ab und implementiert
die Methoden, die man benötigt.
:::

```{.java size="footnotesize"}
public static class MyListener extends calcBaseListener {
    Stack<Integer> stack = new Stack<Integer>();

    public void exitMULT(calcParser.MULTContext ctx) {
        int right = stack.pop();
        int left = stack.pop();
        stack.push(left * right);   // {$v = $e1.v * $e2.v;}
    }
    public void exitADD(calcParser.ADDContext ctx) {
        int right = stack.pop();
        int left = stack.pop();
        stack.push(left + right);   // {$v = $e1.v + $e2.v;}
    }
    public void exitZAHL(calcParser.ZAHLContext ctx) {
        stack.push(Integer.valueOf(ctx.DIGIT().getText()));
    }
}
```

::: notes
Anschließend baut man das alles in eine Traversierung des Parse-Trees ein:

```java
public class TestMyListener {
    public static class MyListener extends calcBaseListener {
        ...
    }

    public static void main(String[] args) throws Exception {
        calcLexer lexer = new calcLexer(CharStreams.fromStream(System.in));
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        calcParser parser = new calcParser(tokens);

        ParseTree tree = parser.s();    // Start-Regel
        System.out.println(tree.toStringTree(parser));

        ParseTreeWalker walker = new ParseTreeWalker();
        MyListener eval = new MyListener();
        walker.walk(eval, tree);
        System.out.println(eval.stack.pop());
    }
}
```

[Beispiel: [TestMyListener.java](https://github.com/Compiler-CampusMinden/CB-Vorlesung/blob/master/markdown/interpretation/src/TestMyListener.java) und [calc.g4](https://github.com/Compiler-CampusMinden/CB-Vorlesung/blob/master/markdown/interpretation/src/calc.g4)]{.bsp}
:::


## Arbeiten mit dem Visitor-Pattern

TODO: Überblick, mit Verweis auf backend/interpretation/syntaxdriven: dort Kontextobjekte nur Skript!

::: notes
ANTLR (generiert ebenfalls auf Wunsch) zur Grammatik passende Visitoren
(Interface und leere Basisimplementierung). Hier muss man allerdings selbst
für eine geeignete Traversierung des Parse-Trees sorgen. Dafür hat man mehr
Freiheiten im Vergleich zum Listener-Pattern, insbesondere im Hinblick auf
Rückgabewerte.
:::

```{.yacc size="footnotesize"}
expr : e1=expr '*' e2=expr      # MULT
     | e1=expr '+' e2=expr      # ADD
     | DIGIT                    # ZAHL
     ;
```

\bigskip

::: notes
ANTLR kann zu dieser Grammatik einen passenden Visitor (Interface `calcVisitor<T>`)
generieren. Weiterhin generiert ANTLR eine leere Basisimplementierung (Klasse
`calcBaseVisitor<T>`):

![](images/ParseTreeVisitor.png)

Von dieser Basisklasse leitet man einen eigenen Visitor ab und überschreibt
die Methoden, die man benötigt. Wichtig ist, dass man selbst für das "Besuchen"
der Kindknoten sorgen muss (rekursiver Aufruf der geerbten Methode `visit()`).
:::

```{.java size="footnotesize"}
public static class MyVisitor extends calcBaseVisitor<Integer> {
    public Integer visitMULT(calcParser.MULTContext ctx) {
        return visit(ctx.e1) * visit(ctx.e2);   // {$v = $e1.v * $e2.v;}
    }
    public Integer visitADD(calcParser.ADDContext ctx) {
        return visit(ctx.e1) + visit(ctx.e2);   // {$v = $e1.v + $e2.v;}
    }
    public Integer visitZAHL(calcParser.ZAHLContext ctx) {
        return Integer.valueOf(ctx.DIGIT().getText());
    }
}
```

::: notes
Anschließend baut man das alles in eine manuelle Traversierung des Parse-Trees ein:

```java
public class TestMyVisitor {
    public static class MyVisitor extends calcBaseVisitor<Integer> {
        ...
    }

    public static void main(String[] args) throws Exception {
        calcLexer lexer = new calcLexer(CharStreams.fromStream(System.in));
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        calcParser parser = new calcParser(tokens);

        ParseTree tree = parser.s();    // Start-Regel
        System.out.println(tree.toStringTree(parser));

        MyVisitor eval = new MyVisitor();
        System.out.println(eval.visit(tree));
    }
}
```

[Beispiel: [TestMyVisitor.java](https://github.com/Compiler-CampusMinden/CB-Vorlesung/blob/master/markdown/interpretation/src/TestMyVisitor.java) und [calc.g4](https://github.com/Compiler-CampusMinden/CB-Vorlesung/blob/master/markdown/interpretation/src/calc.g4)]{.bsp}
:::


::: notes
## Eingebettete Aktionen und Attribute

TODO: Beispiel und Verweis auf backend/interpretation/syntaxdriven
:::


::: notes
## Semantische Prädikate

TODO: Beispiel und Verweis auf frontend/parsing/ll-advanced
TODO: NUR MASTER
:::


::: notes
## Exceptions

TODO: Beispiel und Verweis auf frontend/parsing/recovery
:::


## Wrap-Up

TODO







<!-- DO NOT REMOVE - THIS IS A LAST SLIDE TO INDICATE THE LICENSE AND POSSIBLE EXCEPTIONS (IMAGES, ...). -->
::: slides
## LICENSE
![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)

Unless otherwise noted, this work is licensed under CC BY-SA 4.0.
:::
