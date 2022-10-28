---
archetype: lecture-cg
title: "Parser mit ANTLR generieren"
author: "Carsten Gips (FH Bielefeld)"
weight: 5
readings:
  - key: "@Parr2014"
tldr: |
  TODO
outcomes:
  - k2: "TODO"
  - k3: "TODO"
assignments:
  - topic: sheet01
youtube:
  - link: ""
    name: "VL Parser mit ANTLR"
fhmedia:
  - link: ""
    name: "VL Parser mit ANTLR"
---


## Hello World

```antlr
grammar Hello;

start : stmt* ;

stmt  : ID '=' expr ';' | expr ';' ;

expr  : term ('+' term)* ;
term  : atom ('*' atom)* ;

atom  : ID | NUM ;

ID    : [a-z][a-zA-Z]* ;
NUM   : [0-9]+ ;
WS    : [ \t\n]+ -> skip ;
```

[Konsole: Hello (grun, Parse-Tree)]{.bsp}

::::::::: notes
### Starten des Parsers

1.  Grammatik übersetzen und Code generieren: `antlr Hello.g4`
2.  Java-Code kompilieren: `javac *.java`
3.  Parser ausführen:
    *   `grun Hello start -tree` oder `grun Hello start -gui` (Grammatik "Hello", Startregel "start")
    *   Alternativ mit kleinem Java-Programm:
        ```java
        import org.antlr.v4.runtime.CharStreams;
        import org.antlr.v4.runtime.CommonTokenStream;
        import org.antlr.v4.runtime.tree.ParseTree;

        public class Main {
            public static void main(String[] args) throws Exception {
                HelloLexer lexer = new HelloLexer(CharStreams.fromStream(System.in));
                CommonTokenStream tokens = new CommonTokenStream(lexer);
                HelloParser parser = new HelloParser(tokens);

                ParseTree tree = parser.start();  // Start-Regel
                System.out.println(tree.toStringTree(parser));
            }
        }
        ```

### Startregeln

*   `start` ist eine [Parser-Regel]{.alert}
    => Eine Parser-Regel pro Grammatik wird benötigt, damit man den generierten
    Parser am Ende auch starten kann ...
*   Alle Regeln mit kleinem Anfangsbuchstaben sind Parser-Regeln
*   Alle Regeln mit großem Anfangsbuchstaben sind Lexer-Regeln

### Formen der Subregeln

```antlr
stmt  : ID '=' expr ';' ;
```

Um die Regel `stmt` anwenden zu können, müssen alle Elemente auf der rechten
Seite der Regel erfüllt werden. Dabei müssen die Token wie `ID`, `=` und `;`
matchen und die Subregel `expr` muss erfüllt werden können. Beachten Sie das
abschließende Semikolon am Ende einer ANTLR-Regel!

```antlr
stmt  : ID '=' expr ';' | expr ';' ;
```

Alternativen werden durch ein `|` getrennt. Hier muss genau eine Alternative
erfüllt werden. Falls nötig, trennt man die Alternativen durch Einschließung
in runden Klammern vom Rest der Regel ab: `r : a (b | c) d ;`.

```antlr
expr  : term ('+' term)* ;
```

Der durch den `*` gekennzeichnete Teil kann beliebig oft vorkommen oder auch
fehlen. Bei einem `+` müsste der Teil mind. einmal vorkommen und bei einem
`?` entsprechend einmal oder keinmal.

Auch hier kann man die Operatoren durch ein zusätzliches `?` auf non-greedy
umschalten (analog zu den Lexer-Regeln).

(vgl. [github.com/antlr/antlr4/blob/master/doc/parser-rules.md](https://github.com/antlr/antlr4/blob/master/doc/parser-rules.md#subrules))

### Reihenfolge in Grammatik definiert Priorität

Falls mehr als eine Parser-Regel die selbe Inputsequenz matcht, löst ANTLR
diese Mehrdeutigkeit auf, indem es die erste Alternative nimmt, die an der
Entscheidung beteiligt ist.

```antlr
start : stmt ;

stmt  : expr | ID  ;
expr  : ID   | NUM ;
```

Bei der Eingabe "foo" würde die Alternative `ID` in der Regel `expr` "gewinnen",
weil sie in der Grammatik vor der Alternative `ID` in der Regel `stmt` kommt und
damit Vorrang hat.

### Parse-Tree

TODO: Beispiel: Grammatik, Eingabe, Parse-Tree

### To EOF not to EOF?

Startregeln müssen nicht unbedingt den gesamten Input "konsumieren". Sie müssen
per Default nur eine der Alternativen in der Startregel erfüllen.

Betrachten wir noch einmal einen leicht modifizierten Ausschnitt aus der obigen
Grammatik:

```antlr
start : stmt ;

stmt  : ID '=' expr ';' | expr ';' ;
expr  : term ('+' term)* ;
term  : atom ('*' atom)* ;
atom  : ID | NUM ;
```

Die Startregel wurde so geändert, dass sie nur noch genau ein Statement
akzeptieren soll.

In diesem Fall würde die Startregel bei der Eingabe "aa; bb;" nur den ersten
Teil "aa;" konsumieren (als Token `ID`) und das folgende "bb;" ignorieren.
Das wäre in diesem Fall aber auch kein Fehler.

Wenn der gesamte Eingabestrom durch die Startregel erklärt werden soll,
dann muss das vordefinierte Token `EOF` am Ende der Startregel eingesetzt
werden:

```antlr
start : stmt EOF;
```

Hier würde die Eingabe "aa; bb;" zu einem Fehler führen, da nur der Teil "aa;"
durch die Startregel abgedeckt ist (Token `ID`), und der Rest "bb;" zwar sogar
ein gültiges Token wären (ebenfalls `ID` und `;`), aber eben nicht mehr von der
Startregel akzeptiert. Durch das `EOF` soll die Startregel aber den gesamten
Input konsumieren und erklären, was hier nicht geht und entsprechend zum Fehler
führt.

(vgl. [github.com/antlr/antlr4/blob/master/doc/parser-rules.md](https://github.com/antlr/antlr4/blob/master/doc/parser-rules.md#start-rules-and-eof))
:::::::::


## Expressions und Vorrang (Operatoren)

```antlr
expr  : term ('+' term)* ;
term  : atom ('*' atom)* ;
atom  : ID | NUM ;
```

\pause
\bigskip

```antlr
expr  : expr '*' expr
      | expr '+' expr
      | ID
      | NUM
      ;
```

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
