---
author: Carsten Gips (HSBI)
title: "L-Int: Lexer - Handcodierte Implementierung"
---

::: tldr
Der Lexer (auch "Scanner") soll den Zeichenstrom in eine Folge von Token zerlegen.
Zur Spezifikation der Token werden reguläre Ausdrücke verwendet.

Von Hand implementierte Lexer arbeiten üblicherweise rekursiv und verarbeiten immer
das nächste Zeichen im Eingabestrom. Die Arbeitsweise erinnert an LL-Parser.

Lexer sollten sehr effizient sein, da sie noch direkt auf der niedrigsten
Abstraktionsstufe arbeiten und u.U. oft durchlaufen werden.

Die Palette an Fehlerbehandlungsstrategien im Lexer reichen von "aufgeben" über den
"Panic Mode" ("gobbeln" von Zeichen, bis wieder eines passt) und
Ein-Schritt-Transformationen bis hin zu speziellen Lexer-Regeln, die beispielsweise
besonders häufige Typos abfangen.
:::

::: youtube
TODO
:::

# Lexer: Erzeugen eines Token-Stroms aus einem Zeichenstrom

[Aus dem Eingabe(-quell-)text]{.notes}

``` clojure
;; demo
(+ 1 222 )
```

[erstellt der Lexer (oder auch Scanner genannt) eine Sequenz von Token:]{.notes}

\bigskip
\bigskip

    <LPAREN, "("> <PLUS, "+"> <INT, "1"> <INT, "222"> <RPAREN, ")">

::: notes
Wir wollen den Eingabetext in abstraktere Einheiten aufsplitten: die Token.

Jedes Token hat einen Typ und speichert ein Lexem - das ist der Teil der Eingabe,
der zu dem Token gematcht wurde.

Der Lexer versucht anhand von Regeln (reguläre Ausdrücke) zu erkennen, welche Token
in der Eingabe vorkommen. In der Regel geht man zeichenweise von links nach rechts
durch die Eingabe und versucht anhand des aktuellen Zeichens zu erkennen, welches
Token hier beginnt. Bei Mehrdeutigkeiten muss man entsprechend noch weitere folgende
Zeichen mit einbeziehen.
:::

# Modellierung der Token

``` ebnf
eform   ::= '(' '+' eform eform+ ')' | '(' '-' eform eform+ ')' | INT
INT     ::= [0-9]+
```

\bigskip

``` java
public enum TokenKind {
  PLUS, MINUS, LPAREN, RPAREN, SEMI,
  INT, // [0-9]+
  EOF
}

public record Token(TokenKind kind, String lexeme) {}
```

:::: notes
::: tip
**Design-Diskussion**: Es gibt verschiedene Möglichkeiten, Token zu modellieren.

Man könnte ein gemeinsames Interface schaffen und pro konkretem Token eine eigene
Klasse ableiten. Das hätte den Vorteil, dass man bei Token wie `LPAREN`, deren Lexem
bereits über den Tokentyp eindeutig definiert ist, kein extra Lexem speichern
müsste. Allerdings werden wir bereits in unserer kleinen Sprache Lispy um die 40
Tokenarten haben, wodurch die Anzahl der Klassen unangenehm unübersichtlich wird.

Aus der C-Welt stammt die gezeigte Modellierung: Man nutzt ein Enum, um die
Tokenarten zu modellieren. (Wir werden dieses Enum im Laufe des Semesters noch
deutlich ergänzen.) Für die Repräsentation der Token nutzt man dann eine gemeinsame
Daten-Klasse, die einfach die Tokenart und das Lexem kombiniert. Das ist
übersichtlich, allerdings muss man für Token wie `PLUS` das Lexem "+" dann nochmal
explizit mit speichern.
:::
::::

# Grundstruktur eines Lexers

``` java
public abstract class BaseLexer {
    protected String source;
    protected int current;

    /** entry point */
    public List<Token> scan(String input) {
        source = input;
        current = 0;
        List<Token> tokens = new ArrayList<>();

        while (!isAtEnd()) {
            while (skipIrrelevant()) {}
            if (!isAtEnd()) tokens.add(nextToken());
        }

        tokens.add(new Token(EOF, "<EOF>"));
        return tokens;
    }

    /** produce next token */
    protected abstract Token nextToken();
}
```

::::: notes
Der Lexer läuft über den Eingabestring und erzeugt eine vollständige Liste mit
Token. Irrelevante Zeichen wie Whitespace und Kommentare werden immer wieder
entfernt.

Die Einsprungsfunktion `scan()` stützt sich dabei auf der zentralen Hilfsmethode
`nextToken()` ab, die das nächste Token an der aktuellen Eingabeposition bildet. Die
Implementierung ist algorithmisch einfach: Wir schauen uns das aktuelle Zeichen an,
entscheiden, um welchen Token-Typ es sich handelt, und rücken den Positionszeiger
entsprechend vor. Falls nötig, ziehen wir weitere Zeichen in diese Entscheidung mit
ein.

::: tip
Der gezeigte Aufbau wirkt zunächst unnötig komplex, insbesondere die
`while`-Schleife in `scan()`. Dies liegt u.a. daran, dass wir für die nächsten
Sprachstufen jeweils eigene Klassen anlegen, die von den Klassen der Vorgängerstufe
erben. Für den Lexer wäre dies beispielsweise
`class LispyLexerLexpr extends LispyLexerLint` usw. Dabei wird das neue Verhalten
durch Überschreiben der entsprechenden Methoden erreicht und für das bisherige
Verhalten nur `super.xyz()` aufgerufen. Das orientiert sich am Vorgehen in
[@Siek2023python] und ist relativ elegant, kommt aber mit dem Preis, dass man bei
Zustandsveränderungen gut aufpassen muss - wenn die überschreibende Methode ein
`advance()` macht und dann ihre Basisimplementierung aufruft, dann fehlt dort das
bereits gelesene Zeichen ...
:::

::: tip
**Design-Diskussion**: In der gezeigten Variante verarbeitet der Lexer den
kompletten Input und erzeugt (falls möglich) eine vollständige Liste mit den zur
Eingabe gehörenden Token. Der nachfolgende Parser kann damit vom Lexer entkoppelt
werden und bekommt als Input einfach eine Liste mit Token und arbeitet auf dieser
Liste - die Parserimplementierung muss nicht wissen, dass es eine Klasse `Lexer`
gibt und wie diese aussieht. Der Preis ist dabei möglicher Mehrbedarf an Speicher
und möglicherweise schlechtere Fehlermeldungen.

In der Praxis sieht man häufig Lexer, deren Einsprungmethode `nextToken()` ist, also
immer nur das nächste Token zur Eingabe zurückliefert. Hier wird der Parser eng an
einen konkreten Lexer gekoppelt und ruft selbst immer wieder bei Bedarf
`lexer.nextToken()` auf. Das hat den Vorteil, dass Lexing und Parsing im Gleichtakt
arbeiten und das System aus Lexer und Parser nicht erst den kompletten Input in
Token zerlegt und dann ggf. beim ersten Token wegen Parsing-Fehlern stoppt.
Allerdings bekommt man Software-seitig eine enge Kopplung zwischen Lexer und Parser,
was sich auch in schlechterer Testbarkeit äußern kann.
:::
:::::

# Hand-Lexer: Beispielimplementierung

``` java
public class LispyLexerLint extends BaseLexer {

  protected Token nextToken() {
    return switch (peek()) {
      case '(' -> new Token(LPAREN, advance());
      case '+' -> new Token(PLUS, advance());
      default -> scanLiteral(); // Integer Literals
    };
  }

  protected Token scanLiteral() {
    if (Character.isDigit(peek())) {
      String lexeme = readWhile(Character::isDigit);
      return new Token(INT, lexeme);
    }

    throw new RuntimeException("unexpected character: '" + peek() + "'");
  }
}
```

::: notes
Hier ist eine mögliche Implementierung von `nextToken()`. In der aufrufenden Methode
`scan()` hatten wir Whitespaces und Kommentare übersprungen und geprüft, ob wir am
Ende der Eingabe sind. Wir können hier also unbesorgt das aktuelle Zeichen lesen und
entscheiden, welches Token hier vorliegt (oder beginnt). Gelesene Zeichen werden aus
der Eingabe "entfernt": Beim Aufruf von `advance()` wird der Index `current`
inkrementiert (falls möglich).

Wenn das aktuelle Zeichen eine Ziffer ist, lesen wir so lange weiter, bis keine
Ziffer mehr folgt, und erzeugen ein `INT`-Token. Andernfalls unterscheiden wir
anhand des Zeichens die Operatoren und Klammern. Unbekannte Zeichen führen zu einem
Fehler. Das ist im Kern das, was auch generierte Lexer tun.

*Anmerkung*: Häufig findet man im Lexer keinen "schönen" objektorientierten Ansatz.
Dies ist oft Geschwindigkeitsgründen geschuldet ...
:::

# Hilfsfunktionen im Lexer I: Zeichenhandling

``` java
public abstract class BaseLexer {

    protected final boolean isAtEnd() { return current >= source.length(); }

    protected final char peek() { return peek(0); }
    protected final char peek(int la) {
        if (la < 0 || current + la >= source.length()) return '\0';
        return source.charAt(current + la);
    }

    protected final char advance() {
        if (isAtEnd()) return '\0';
        return source.charAt(current++);
    }
}
```

:::: notes
Wir müssen im Lexer immer wieder erkennen, ob bereits alle Zeichen im Input
abgearbeitet sind. Um nicht immer wieder den Index `current` mit der Länge des
Inputs `source` vergleichen zu müssen, kapselt man die in der Hilfsmethode
`isAtEnd()`. Diese liefert `true`, sobald wir alle Zeichen im Input-String `source`
bearbeitet haben.

In der Hauptschleife `nextToken()` müssen wir auf das aktuelle Zeichen schauen. Auch
hier bietet es sich an, dies nicht immer wieder manuell über
`source.charAt(current)` zu tun, sondern dies über eine Hilfsmethode `peek()` zu
tun. Im obigen Beispiel ist auch gleich eine Implementierung für ein `peek()` mit
Lookahead gezeigt - wir werden später auch das nächste und übernächste Zeichen nach
dem  aktuellen Zeichen benötigen.

Für das Weiterschalten gibt es die Methode `advance()`. Diese gibt das aktuelle
Zeichen zurück und schaltet auf das nächste Zeichen, d.h. ein nachfolgendes `peek()`
liefert dann das nächste Zeichen. Damit wir nicht über den Input-String hinaus
laufen, wird die Weiterschaltung nur gemacht, wenn wir noch nicht am Ende des Inputs
sind. Anderenfalls liefern wir ein Null-Zeichen (`\0`) zurück.

::: tip
**Design-Diskussion**: Das Hantieren mit dem Index und dem Weiterschalten muss gut
aufeinander abgestimmt sein - der Lexer sollte hier nicht in einen ungültigen
Zustand geraten können.

Grundsätzlich könnte man es den Usern überlassen, die Aufrufe immer korrekt zu
machen und damit nie über das Ende des Inputs hinaus zu lesen. In der Praxis lohnt
es sich aber, etwas mehr Robustheit einzubauen.

Im obigen Beispiel habe ich die Rückgabe eines besonderen Null-Zeichens gewählt,
dies stammt aus der C-Welt und bedeutet dort "wir sind am Ende des Strings
angekommen".

Alternativ könnte man auch eine Exception auslösen beim Versuch, am Ende des Strings
noch ein `advance()` zu machen. Dies zieht aber schnell eine relativ umständliche
Fehlerbehandlung nach sich, zumal wir unsere Lexer schichtweise aufbauen und
voneinander ableiten werden.
:::
::::

# Read-Ahead: Unterscheiden von "=" und "\=="

``` python
protected Token nextToken() {
    return switch (peek()) {

        case '=' -> {
            advance();  // consume first '='
            if (peek('=')) {
                advance();  // consume second '='
                yield new Token(EQEQ, "==");
            }
            else yield new Token(EQUAL, "=");
        }

        default -> super.nextToken();
    };
}
```

::: notes
Um die Token "`=`" und "`==`" unterscheiden zu können, müssen wir ein Zeichen
vorausschauen: Wenn nach dem "`=`" noch ein "`=`" kommt, ist es "`==`", sonst "`=`".

Erinnerung: Die Funktion `advance()` liefert das aktuelle Zeichen aus der Eingabe
zurück und schaltet zum nächsten Zeichen.
:::

# Hilfsfunktionen im Lexer II: Lese solange ...

``` java
public abstract class BaseLexer {

    protected final boolean skipIrrelevant() {}  // Homework

    protected final String readWhile(Predicate<Character> pred) {
        StringBuilder sb = new StringBuilder();
        while (!isAtEnd() && pred.test(peek())) sb.append(advance());
        return sb.toString();
    }
}
```

::: notes
Wir brauchen noch zwei weitere komplexere Hilfsfunktionen im Lexer:
`skipIrrelevant()` und `readWhile()`.

Der Aufruf von `skipIrrelevant()` entfernt vom aktuellen Zeichen an alle nicht
benötigten Zeichen wie Whitespace und Kommentare und stoppt, sobald ein benötigtes
Zeichen auftaucht. Dabei muss die Funktion selbst prüfen, ob überhaupt noch gelesen
werden darf, oder ob bereits das Ende des Inputs erreicht ist. Falls Zeichen
entfernt wurden, wird `true` zurückgegeben.

Die Funktion `readWhile()` bekommt einen Test `pred` als Argument und liest so
lange, wie das aktuelle Zeichen diesen Test erfüllt und das Ende vom Input nicht
erreicht ist. Jedes gelesene Zeichen wird an einen Stringbuffer angehängt und am
Ende als String zurückgeliefert. Diese Funktion ist sehr praktisch, wenn man
beispielsweise aufeinander folgende Ziffern einlesen will:
`String lexeme = readWhile(Character::isDigit);` liest so lange, wie Ziffern in der
Eingabe vorkommen und liefert diese zunächst als String zurück.
:::

# Typische Muster für Erstellung von Token

1.  Schlüsselwörter

    -   Ein eigenes Token für jedes Schlüsselwort, oder
    -   Erkennung als Name (`ID`) und nachträglich Vergleich mit Wörterbuch [sowie
        Korrektur des Tokentyps]{.notes}

    ::: notes
    Wenn Schlüsselwörter über je ein eigenes Token abgebildet werden, benötigt man
    für jedes Schlüsselwort einen eigenen RE bzw. DFA. Die Erkennung als Bezeichner
    und das Nachschlagen in einem Wörterbuch (geeignete Hashtabelle) sowie die
    entsprechende nachträgliche Korrektur des Tokentyps kann die Anzahl der Zustände
    im Lexer signifikant reduzieren! Wir werden dies später in der Sprachvariante
    L-Var sehen.
    :::

2.  Operatoren

    -   Ein eigenes Token für jeden Operator, oder
    -   Gemeinsames Token für jede Operatoren-Klasse

3.  Bezeichner: Ein gemeinsames Token für alle Namen

4.  Zahlen: Ein gemeinsames Token für alle numerischen Konstante [(ggf. Integer und
    Float unterscheiden)]{.notes}

    ::: notes
    Für Zahlen führt man oft ein Token "`NUM`" oder "`INT`"ein. Als Attribut
    speichert man das Lexem als String. Alternativ kann man das Lexem bereits in
    eine Zahl konvertieren und als (zusätzliches) Attribut speichern. Dies kann in
    späteren Stufen viel Arbeit sparen.
    :::

5.  String-Literale: Ein gemeinsames Token

6.  Komma, Semikolon, Klammern, ...: Je ein eigenes Token

    \bigskip

7.  Regeln für White-Space und Kommentare etc. ...

    ::: notes
    Normalerweise benötigt man Kommentare und White-Spaces in den folgenden Stufen
    nicht und entfernt diese deshalb aus dem Eingabestrom. Dabei könnte man etwa
    White-Spaces in den Pattern der restlichen Token berücksichtigen, was die
    Pattern aber sehr komplex macht. Die Alternative sind zusätzliche Pattern, die
    auf die White-Space und anderen nicht benötigten Inhalt matchen und diesen
    "geräuschlos" entfernen. Mit diesen Pattern werden keine Token erzeugt, d.h. der
    Parser und die anderen Stufen bemerken nichts von diesem Inhalt.

    Gelegentlich benötigt man aber auch Informationen über White-Spaces,
    beispielsweise in Python. Dann müssen diese Token wie normale Token an den
    Parser weitergereicht werden.
    :::

:::: notes
Jedes Token hat üblicherweise ein Attribut, in dem das Lexem gespeichert wird. Bei
eindeutigen Token (etwa bei eigenen Token je Schlüsselwort oder bei den
Interpunktions-Token) kann man sich das Attribut auch sparen, da das Lexem durch den
Tokennamen eindeutig rekonstruierbar ist. Bei unserer Implementierung in Java müsste
man dann entweder zwei verschiedene Klassen zur Modellierung der Token nutzen (was
eher umständlich ist), oder man spendiert der `Token`-Klasse Hilfsfunktionen, die
ein Token bauen: einmal vollständig (mit Token-Typ und Lexem) und einmal nur mit dem
Token-Typ:

``` java
public record Token(TokenKind kind, String lexeme) {
  public static Token from(TokenKind kind) {
    return from(kind, kind.toString());
  }

  public static Token from(TokenKind kind, char lexeme) {
    return from(kind, String.valueOf(lexeme));
  }

  public static Token from(TokenKind kind, String lexeme) {
    return new Token(kind, lexeme);
  }
}
```

::: tip
*Anmerkung*: Wenn es mehrere matchende Tokenregeln gibt, wird in der Regel das
längste Lexem bevorzugt. Wenn es mehrere gleich lange Alternativen gibt, muss man
mit Vorrangregeln bzgl. der Token arbeiten.
:::
::::

# Fehler bei der Lexikalischen Analyse

[Problem: Eingabestrom sieht so aus:]{.notes} `(fi (== a 42) ...)`

::: notes
Der Lexer kann nicht erkennen, ob es sich bei `fi` um ein vertipptes Schlüsselwort
handelt oder um einen Bezeichner: Es könnte sich um einen Funktionsaufruf der
Funktion `fi()` handeln ... Dieses Problem kann erst in der nächsten Stufe (Parser)
sinnvoll erkannt und behoben werden.
:::

\smallskip

=\> Was tun, wenn keines der Pattern auf den Anfang des Eingabestroms passt?

\bigskip
\bigskip
\pause

::: notes
Optionen:
:::

-   Aufgeben ...

    ::: notes
    Eventuell vielleicht sogar die beste und einfachste Variante :-)
    :::

\smallskip

-   "Panic Mode": Entferne so lange Zeichen, bis ein Pattern passt.

    ::: notes
    Das verwirrt u.U. den Parser, kann aber insbesondere in interaktiven Umgebungen
    hilfreich sein. Ggf. kann man dem Parser auch signalisieren, dass hier ein
    Problem vorlag.
    :::

\smallskip

-   Ein-Schritt-Transformationen:
    -   Füge fehlendes Zeichen in Eingabestrom ein.
    -   Entferne ein Zeichen aus Eingabestrom.
    -   Vertausche ein Zeichen:
        -   Ersetze ein Zeichen durch ein anderes.
        -   Vertausche zwei benachbarte Zeichen.

    ::: notes
    Diese Transformationen versuchen, den Input in einem Schritt zu reparieren. Das
    ist durchaus sinnvoll, da in der Praxis die meisten Fehler in dieser Stufe durch
    ein einzelnes Zeichen hervorgerufen werden: Es fehlt ein Zeichen oder es ist
    eines zuviel im Input. Es liegt ein falsches Zeichen vor (Tippfehler) oder zwei
    benachbarte Zeichen wurden verdreht ...

    Im Prinzip könnte man auch eine allgemeinere Strategie versuchen, indem man
    diejenige Transformation mit der *kleinsten Anzahl von Schritten* zur
    Fehlerbehebung bestimmt. Beispiele dafür finden sich im Bereich Natural Language
    Processing (*NLP*), etwa die Levenshtein-Distanz oder der SoundEx-Algorithmus
    oder sogar Hidden-Markov-Modelle. Allerdings muss man sich in Erinnerung rufen,
    dass gerade in dieser ersten Phase eines Compilers die Geschwindigkeit stark im
    Fokus steht und eine ausgefeilte Fehlerkorrekturstrategie die vielen kleinen
    Optimierungen schnell wieder zunichte machen kann.
    :::

\smallskip

-   Fehler-Regeln: Matche typische Typos

    ::: notes
    Gelegentlich findet man in den Grammatiken für den Lexer extra Regeln, die
    häufige bzw. typische Typos matchen und dann passend darauf reagieren.
    :::

# Wrap-up

-   Zusammenhang DFA, RE und Lexer

\smallskip

-   Implementierungsansatz: Manuell codiert (rekursiver Abstieg)

\smallskip

-   Read-Ahead
-   Puffern mit Doppel-Puffer-Strategie

\smallskip

-   Typische Fehler beim Scannen

::: notes
Heute haben wir den Einstieg in das "Frontend" einer Sprache gemacht. Wir haben
gesehen, wie ANTLR aus einer konkreten Grammatik Lexer und Parser generiert und wie
wir aus dem Parse Tree unseren AST gewinnen. Parallel dazu haben wir einen eigenen
Lexer und einen Recursive-Descent-Parser implementiert. Beide Ansätze führen zum
gleichen AST, den unser Interpreter aus Sitzung 1 auswertet. Das ist das
Grundmuster, das wir in den kommenden Sprachstufen inkrementell erweitern werden.
:::

::: readings
TODO

-   @Nystrom2021: Kapitel 4: A Tree-Walk Interpreter, insb. 8. Statements and State
-   @Mogensen2017: Kapitel 4
:::

::: outcomes
-   k1: Ich kenne die Aufgaben eines Lexers
-   k2: Ich kann typische Fehler und Lösungsansätze in der lexikalischen Analyse
    erklären
-   k3: Ich kann für ein Problem eine typische Einteilung von Token vornehmen
-   k3: Ich kann einen Top-Down-Lexer mit Read-Ahead implementieren
:::

::: challenges
**Manuell implementierter Lexer**

Betrachten Sie die folgende einfache Sprache:

TODO

    a = 10 - 5     # Zuweisung des Ausdruckes 10-5 (Integer-Wert 5) an Variable a
    b = a + 2 * 3  # Zuweisung von 16 an Variable b
    c = a != b     # Zuweisung eines boolschen Werts an c

Es gibt nur Statements und Expressions:

-   Statement: Zuweisung; jedes Statement endet mit einem NL
-   Expression: Zahl, Variable, Addition, Subtraktion, Multiplikation (mit üblichem
    Vorrang), Vergleich

**Aufgaben**:

-   Geben Sie eine ANTLR-Grammatik für diese Sprache an.
-   Implementieren Sie analog zum Vorgehen in der Vorlesung einen Lexer für diese
    Sprache. (Nur den Lexer, den Parser besprechen wir in einer anderen
    [Sitzung](../02-parsing/ll-parser-impl.md).)
:::
