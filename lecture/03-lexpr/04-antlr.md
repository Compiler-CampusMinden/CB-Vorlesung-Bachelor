---
title: L-Int - Vom Text zum AST (Sitzung 2)
---

# Ausgangspunkt: Wir können ASTs auswerten

- Bekannt aus Sitzung 1:
  - Abstrakte Grammatik für L-Int
  - AST-Typen in Java
  - Tree-Walking-Interpreter `eval(Expr)`
- Offene Frage:
  - Wie kommen wir von `"1 + 2 - 3"` zu einem `Expr`-AST?

::: notes
Wir knüpfen direkt an die letzte Sitzung an: Wir können ASTs bauen und auswerten. Was uns fehlt, ist der Schritt vom Text zum AST. Genau darum geht es heute: Wir schauen uns zwei Ansätze an, um aus einem String wie `"1 + 2 - 3"` unseren bekannten `Expr`-Baum zu machen - einmal mit ANTLR, einmal komplett handgeschrieben.
:::


# Überblick: Der Kompilationsweg

- Gesamtpipeline:
  - Text → Lexer → Tokens
  - Tokens → Parser → AST
  - AST → Interpreter → Wert
- Heute:
  - Fokus auf: **Lexer** und **Parser**

::: notes
Das große Bild: Ein Compiler oder Interpreter besteht typischerweise aus mehreren Stufen. Heute betrachten wir insbesondere die vorderen beiden, Lexer und Parser. Der Lexer wandelt den Rohtext in Tokens um, der Parser baut daraus den AST. Unser Interpreter aus Sitzung 1 bleibt unverändert und arbeitet dann wie gehabt weiter.
:::


# ANTLR: Idee

- Ein Werkzeug für:
  - Lexer- und Parsergenerierung aus einer Grammatik
- Wir beschreiben:
  - konkrete Grammatik in einer `.g4`-Datei
- ANTLR erzeugt:
  - Java-Klassen für Lexer, Parser, Parse Tree

::: notes
ANTLR ist ein Generator: Wir beschreiben die konkrete Grammatik unserer Sprache in einer eigenen Notation und bekommen als Output u. a. Java-Klassen, die lexen und parsen können. Das spart uns sehr viel Boilerplate und erlaubt es uns, uns auf die Grammatik selbst zu konzentrieren. Trotzdem schauen wir uns später an, wie man das von Hand machen würde.
:::


# ANTLR-Grammatik für L-Int (Parser-Teil)

    grammar LInt;

    prog  : expr EOF ;

    expr  : expr '+' expr
          | expr '-' expr
          | INT
          | '(' expr ')'
          ;

- `prog` ist der Einstiegspunkt
- `expr` entspricht unseren Ausdrücken

::: notes
Hier sehen Sie den Parser-Teil einer ANTLR-Grammatik für L-Int. Wir haben eine Regel `prog` als Einstiegspunkt, die genau eine `expr` gefolgt von EOF erwartet. Die `expr`-Regel entspricht ziemlich direkt unserer konkreten EBNF-Grammatik. ANTLR4 kommt mit Linksrekursion zurecht, weshalb wir die Grammatik relativ natürlich formulieren können.
:::


# ANTLR-Grammatik für L-Int (Lexer-Teil)

    INT   : [0-9]+ ;
    PLUS  : '+' ;
    MINUS : '-' ;
    LPAREN: '(' ;
    RPAREN: ')' ;

    WS    : [ \t\r\n]+ -> skip ;

- Token-Typen:
  - `INT`, `PLUS`, `MINUS`, `LPAREN`, `RPAREN`
- Whitespace wird ignoriert

::: notes
Der Lexer-Teil der Grammatik definiert, wie ANTLR den Eingabetext in Tokens aufteilt. Jede Großbuchstabenregel ist ein Token-Typ. `INT` erfasst eine oder mehr Ziffern, die Operatoren und Klammern jeweils ein einzelnes Zeichen. Whitespace wird mit der `skip`-Aktion verworfen. Das Ergebnis ist ein Strom von Tokens, auf dem der Parser aufbaut.
:::


# ANTLR-Toolchain: Von String zum Parse Tree

    CharStream input = CharStreams.fromString("1 + 2 - 3");
    LIntLexer lexer = new LIntLexer(input);
    CommonTokenStream tokens = new CommonTokenStream(lexer);
    LIntParser parser = new LIntParser(tokens);

    // Einstiegspunkt:
    ParseTree tree = parser.expr();

- Ergebnis:
  - ein **Parse Tree**, noch kein AST

::: notes
So verwenden wir die von ANTLR generierten Klassen. Wir erzeugen einen `LIntLexer` für unseren Eingabestring, sammeln die Tokens in einem `CommonTokenStream` und übergeben sie an den `LIntParser`. Dann rufen wir z. B. `parser.expr()` auf und erhalten einen `ParseTree`. Dieser Baum entspricht der konkreten Grammatik - er enthält mehr Details, als wir später im AST brauchen.
:::


# Parse Tree vs. AST

- Parse Tree:
  - Vollständig, direkt aus Grammatik
  - Spiegelt alle Regeln 1:1 wider
- AST:
  - Aufgeräumt, nur relevante Knoten
  - Entspricht der **abstrakten** Grammatik

::: notes
Der von ANTLR gelieferte Parse Tree kennt alle Nichtterminale und spiegelt die konkrete Grammatik exakt wider. Im AST möchten wir aber eine reduzierte Darstellung, die nur die semantisch relevanten Konstrukte enthält. Deshalb definieren wir einen Schritt Parse Tree → AST, typischerweise mit dem Visitor-Pattern.
:::


# Parse Tree → AST mit Visitor (Prinzip)

- ANTLR erzeugt:
  - `LIntBaseVisitor<T>`
- Wir implementieren:
  - `ASTBuilder extends LIntBaseVisitor<Expr>`
- Idee:
  - Pro relevanter Regel: AST-Knoten erzeugen

::: notes
ANTLR generiert für uns eine Basisklasse `LIntBaseVisitor<T>`, die alle Besucher-Methoden bereitstellt. Wir leiten davon eine Klasse `ASTBuilder` ab, die als Rückgabetyp unseren AST-Basistyp `Expr` verwendet. Für jede Regel im Parser, die für unsere abstrakte Grammatik relevant ist, überschreiben wir die passende `visit`-Methode und konstruieren dort den entsprechenden AST-Knoten.
:::


# ASTBuilder: Beispiel (Int-Literal)

    public class ASTBuilder extends LIntBaseVisitor<Expr> {

        @Override
        public Expr visitInt(LIntParser.IntContext ctx) {
            int value = Integer.parseInt(ctx.INT().getText());
            return new IntLit(value);
        }

        // weitere visit-Methoden ...
    }

- Annahme:
  - Parser-Regel `expr` hat eine Alternative `INT` mit Label `#int`

::: notes
Dieses Beispiel zeigt eine `visit`-Methode, die einen Integer-Literal-Knoten im Parse Tree in unseren `IntLit`-AST-Knoten überführt. `ctx.INT().getText()` gibt uns die Zeichenfolge der Zahl, die wir parsen. Wichtig ist, dass der Name der Context-Klasse (`IntContext`) und die Methode (`visitInt`) von der Grammatik-Alternative abhängen. Oft versieht man diese Alternativen explizit mit Labels.
:::


# ASTBuilder: Beispiel (Addition/Subtraktion)

    @Override
    public Expr visitAddSub(LIntParser.AddSubContext ctx) {
        Expr left  = visit(ctx.left);
        Expr right = visit(ctx.right);

        if (ctx.op.getType() == LIntParser.PLUS) {
            return new Add(left, right);
        } else {
            return new Sub(left, right);
        }
    }

- Annahme:
  - Grammatik-Alternative mit Labeln `left`, `right`, `op`

::: notes
Für binäre Operatoren wie `+` und `-` ist das Muster ähnlich. Wir besuchen zunächst rekursiv die Operanden im Parse Tree und konstruieren dann entweder einen `Add`- oder `Sub`-AST-Knoten, abhängig vom Operator-Token. Das ist genau die Stelle, wo wir konkrete Grammatik in abstrakte Grammatik "übersetzen".
:::


# ANTLR-Pipeline komplett

    CharStream input = CharStreams.fromString("1 + 2 - 3");

    LIntLexer lexer = new LIntLexer(input);
    CommonTokenStream tokens = new CommonTokenStream(lexer);
    LIntParser parser = new LIntParser(tokens);

    ParseTree tree = parser.expr();
    ASTBuilder builder = new ASTBuilder();
    Expr ast = builder.visit(tree);

    Interpreter interp = new Interpreter();
    Value result = interp.eval(ast);

- Ergebnis:
  - `result` ist ein `IntValue` mit dem berechneten Wert

::: notes
Hier sehen Sie die komplette ANTLR-basierte Pipeline für L-Int. Ausgehend vom Rohstring erzeugen wir Tokens, bauen einen Parse Tree, wandeln diesen mittels `ASTBuilder` in unseren AST um und übergeben diesen an den Interpreter. Ohne dass wir den Interpreter ändern mussten, können wir jetzt beliebige Texte auswerten, solange sie der Grammatik entsprechen.
:::


# Wrap-up - Sitzung 2

- Wir haben den vorderen Teil der Pipeline gebaut:
  - ANTLR-Grammatik für L-Int
  - ANTLR-Toolchain: Text → Parse Tree → AST
  - Hand-Lexer: Text → Tokens
  - Recursive-Descent-Parser: Tokens → AST
- Insgesamt:
  - Zwei Wege, derselbe AST, derselbe Interpreter
- Ausblick:
  - Erweiterung der Sprache:
    - Vorrangregeln, weitere Operatoren
    - Variablen, Typen, Scopes, Funktionen …

::: notes
Heute haben wir den Einstieg in das "Frontend" einer Sprache gemacht. Sie haben gesehen, wie ANTLR aus einer konkreten Grammatik Lexer und Parser generiert und wie wir aus dem Parse Tree unseren AST gewinnen. Parallel dazu haben wir einen eigenen Lexer und einen Recursive-Descent-Parser implementiert. Beide Ansätze führen zum gleichen AST, den unser Interpreter aus Sitzung 1 auswertet. Das ist das Grundmuster, das wir in den kommenden Sprachstufen inkrementell erweitern werden.
:::
