---
author: Carsten Gips (HSBI)
title: "L-Expr: ANTLR-Grammatik und Vorrangregeln"
---

::: tldr
ANTLR ist ein Parser-Generator, der aus einer Grammatik einen Lexer und einen LL(\*)-Parser sowie
Hilfsklassen für die Traversierung des Parse-Trees in
verschiedenen Zielsprachen (Java, Python, C++, ...) generieren kann.

In der ANTLR-Grammatik werden die Lexer-Regeln
werden mit **Großbuchstaben** geschrieben. Jede Lexer-Regel liefert ein Token
zurück, dabei ist der Tokenname die linke Seite der Regel. Der
längste Match gewinnt, und bei Gleichstand (mehrere längste Regeln matchen) gewinnt die
zuerst definierte Regel.

Die
Parser-Regeln in der Grammatik fangen dabei mit einem **Kleinbuchstaben** an.
Regeln haben einen Namen (linke Seite) und eine Produktion (rechte Seite). Dabei
können beliebige Abfolgen von Lexer- und Parser-Regeln auf der rechten Seite einer
Parser-Regel auftauchen. Die Token müssen jeweils matchen, die Parser-Regeln werden
in einen Aufruf der jeweiligen generierten Funktion übersetzt (wie bei einem RD-Parser).

Parser-Regeln können aus mehreren Alternativen bestehen, diese werden per `|`
separiert. Dabei hat bei Mehrdeutigkeiten die erste passende Regel bzw. Alternative Vorrang.
Wie bei Lexer-Regeln können Teile per `?` ein- oder keinmal vorkommen, per `*`
beliebig oft oder per `+` ein- oder mehrfach.

ANTLR erlaubt im Gegensatz zu allgemeinen LL-Parsern direkte Links-Rekursion.
(Indirekte Links-Rekursion funktioniert allerdings nicht.)
:::




# Von klassischer CFG zur ANTLR‑Grammatik

::: notes
Erinnerung an "Programmieren 2":
:::

-   ANTLR ist eine Java-Bibliothek
-   Generiert aus einer Grammatik einen Lexer und LL(\*)-Parser
-   Eingabe-String plus Lexer/Parser $\to$ Parse-Tree mit Kontextklassen
-   Zusätzlich: Klassen für Visitor-Pattern

::: notes
In [Prog2](https://github.com/Programmiermethoden-CampusMinden/Prog2-Lecture-S26/blob/master/lecture/tooling/antlr.md)
haben wir bereits ANTLR als Java-Bibliothek kennengelernt. Wir haben uns dort angeschaut, wie wir das Tool in einem
Java-Projekt über Gradle einbinden können, wie wir die generierten Lexer und Parser aufrufen, und wir haben sogar
die zu den Grammatik-Regeln generierten Kontextklassen betrachtet und das Visitor-Pattern zum Ablaufen der Parse-Trees
benutzt.

Wir benutzen hier ANTLR in der Version **4**, manchmal auch als "ANTLR4" geschrieben.

Jetzt wollen wir auf die ANTLR-Grammatik schauen.
:::



# Erinnerung: Konkrete Syntax für L-Expr


```ebnf
eform  ::= '(' '+' eform eform+ ')' | '(' '-' eform eform+ ')' | INT
INT    ::= [0-9]+
---

eform  ::= '(' '*' eform eform+ ')' | '(' '/' eform eform+ ')' | '(' '-' eform ')'

L_expr ::= eform EOF
```

::: notes
Im Prinzip sieht unsere konkrete Grammatik bereits der ANTLR-Grammatik recht ähnlich. Wir müssen
zunächst die `::=` durch einen einfachen Doppelpunkt `:` ersetzen. Zusätzlich muss jede Regel
mit einem Semikolon `;` abgeschlossen werden.

Darüber hinaus kommen noch Namenskonventionen, die die Art der Regel erkennen lassen: Kleingeschriebene
Regeln gelten für den Parser, großgeschriebene Regeln sind Lexer-Regeln. Die Reihenfolge der Regeln
ist relevant.
:::


# ANTLR-Grammatik für L-Expr (Parser-Teil)


```antlr
grammar Lispy;

lexpr       : eform EOF ;

eform       : atom                              #atomExpr
            | '(' '-' eform ')'                 #unaryMinusExpr
            | '(' '+' eform eform+ ')'          #addExpr
            | '(' '-' eform eform+ ')'          #subExpr
            | '(' '*' eform eform+ ')'          #mulExpr
            | '(' '/' eform eform+ ')'          #divExpr
            ;

atom        : INT ;
```

\bigskip

- `lexpr` ist der Einstiegspunkt
- `eform` entspricht unseren Ausdrücken

::: notes
Hier sehen Sie den Parser-Teil einer ANTLR-Grammatik für L-Expr.

Als erste Zeile findet man
immer die **Deklaration** `grammar <NAME>;`, wobei der Name `<NAME>` auch der Dateiname
ist (`NAME.g4`) und später den Präfix für die generierten
Lexer-/Parser-/Visitor-Klassen bildet. Unsere Grammatik würde also in der Datei `Lispy.g4` erwartet.

**Parser-Regeln** beginnen in ANTLR mit einem **Kleinbuchstaben** und können andere
Parser-Regeln "aufrufen" und auch Lexer-Regeln beinhalten. Jede Regel endet mit einem Semikolon.

Wir haben eine Parser-Regel `lexpr` als **Einstiegspunkt** (erste Regel), die genau eine `eform`
gefolgt vom Token `EOF` erwartet.

Die `eform`-Regel entspricht ziemlich direkt unserer konkreten EBNF-Grammatik. ANTLR4 kommt mit (direkter)
Linksrekursion zurecht, weshalb wir die Grammatik relativ intuitiv formulieren können. Eine `eform` kann also entweder
ein `atom` sein, oder eine `'(' '-' eform ')'` usw.

Nach den Parser-Regeln folgen üblicherweise die Lexer-Regeln (siehe nächste Folie).

## Formen der Subregeln

### Standardregeln

Jede Regel hat einen Kopf (Regelname) und nach dem ":" den Regelkörper. Darin können Token
wie `ID` oder `'='` und `';'` gematcht werden und andere Regeln "aufgerufen" werden wie `expr`.
Jede Regel wird mit einem Semikolon abgeschlossen.

``` antlr
stmt  : ID '=' expr ';' ;
```

Um die Regel `stmt` anwenden zu können, müssen alle Elemente auf der rechten Seite
der Regel erfüllt werden. Dabei müssen die Token wie `ID`, `'='` und `';'` in angegebenen Reihenfolge matchen und
die Subregel `expr` muss erfüllt werden können.

Das abschließende
Semikolon am Ende einer ANTLR-Regel markiert für  ANTLR das Ende der Regel und dient als Hilfe beim Parsen der
Grammatik und bezieht sich nicht auf den Input.

### Alternativen

Wie auch im RD-Parser können wir in ANTLR-Grammatiken Alternativen ausdrücken:

``` antlr
stmt  : ID '=' expr ';' | expr ';' ;
```

**Alternativen** werden durch ein `|` getrennt. Hier muss genau eine Alternative erfüllt
werden. Falls nötig, trennt man die Alternativen durch Einschließung in runden
Klammern vom Rest der Regel ab (Gruppierung): `r : a (b | c) d ;`.

### Wiederholungen (Multiplizitäten)

Teile der Regeln können wiederholt werden. Die Parser-Regeln nutzen  die aus regulären
Ausdrücken bekannten Operatoren
`+` (einmal oder öfter) und `*` (beliebig oft) bzw. `?` (einmal oder keinmal).

``` antlr
expr  : term ('+' term)* ;
```

Der durch den `*` gekennzeichnete Teil kann beliebig oft vorkommen oder auch fehlen.
Entsprechend würde eine `expr` dann erfüllt sein, wenn ein `term` vorliegt, oder auch
wenn ein `term` und ein `'+'` und ein weiterer `term` gematcht wurde, oder auch mit
mehrfachen Wiederholungen von `'+' term`.

Bei einem `+` müsste der Teil mind. einmal vorkommen, und bei einem `?` entsprechend
einmal oder gar nicht.

(vgl.
[github.com/antlr/antlr4/blob/master/doc/parser-rules.md](https://github.com/antlr/antlr4/blob/master/doc/parser-rules.md#subrules))

## Reihenfolge in Grammatik definiert Priorität

Falls mehr als eine Parser-Regel (oder Alternative) die selbe Input-Sequenz matcht, löst ANTLR diese
Mehrdeutigkeit auf, indem es die erste Regel/Alternative nimmt, die an der Entscheidung
beteiligt ist.

``` antlr
start : stmt ;

stmt  : expr | ID  ;
expr  : ID   | NUM ;
```

Bei der Eingabe "foo" würde die Alternative `ID` in der Regel `expr` "gewinnen",
weil sie in der Grammatik vor der Alternative `ID` in der Regel `stmt` kommt und
damit Vorrang hat.

## Benannte Alternativen (Label)

Man kann Alternativen in einer Produktionsregel auch individuell benennen über "`#...`". Das `#`
leitet dabei die Bennung ein, gefolgt vom Label: `#foo` wäre also das Label `foo` für eine Alternative.
Wenn man das nutzt, müssen immer
**alle** Alternativen einer Regel benannt werden.

Benannte Alternativen sind später recht praktisch, da ANTLR benannte Alternativen im generierten Visitor wie normale
Regeln behandelt und eigene `visitXYZ`-Methoden für die Label generiert.

Man kann die Label aber nicht in der Grammatik wie andere Regeln verwenden.
:::




# ANTLR-Grammatik für L-Expr (Lexer-Teil)


```antlr
...


INT         : [0-9]+ ;

COMMENT     : ';;' ~[\r\n]* -> skip ;
WS          : [ \t\r\n,]+ -> skip ;
```

\bigskip

- Token-Typen: `INT`, `'('`, `'-'`, ...
- Whitespace und Kommentare werden ignoriert

::: notes
Der Lexer-Teil der Grammatik definiert, wie ANTLR den Eingabetext in Tokens aufteilt. Üblicherweise findet man diese
Regeln nach den Parser-Regeln (siehe vorige Folie).

**Lexer-Regeln** beginnen mit einem **Grossbuchstaben** und definieren einen
regulären Ausdruck, der auf den Eingabetext angewendet wird.

``` antlr
INT : [0-9]+ ;
WS  : [ \t\n]+ -> skip ;
```

Jede Lexer-Regel entspricht einem (benannten) **Token**. Im Beispiel gibt es die Regel `INT`,
die den regulären Ausdruck `[0-9]+` anwendet. Damit matcht das Token `INT` auf
alle Zeichenfolgen, die aus einer oder mehreren Ziffern bestehen.

Zusätzlich
gibt es auch nicht benannte Token ("**implizite Token**", s.u.), das sind die in `'` eingeschlossenen
Zeichenketten, beispielsweise `'='` oder `';'`.

Die Whitespace-Token (`WS`)
werden im Beispiel zwar gematcht, aber danach **verworfen** (`-> skip`) - wir
müssen diese zwar erkennen und aus der Eingabe entfernen, brauchen sie aber
nicht für die weitere Prüfung der Strukturen.

Das Ergebnis ist ein Strom von Tokens, auf dem der Parser aufbaut.


## Implizite Token

Statt `PLUS` kann man in Parser-Regeln auch direkt `'+'` schreiben, d.h. das Lexem
direkt ausschreiben und in **einfache** Anführungszeichen einschließen.
ANTLR erzeugt dann automatisch ein unbenanntes Token (deshalb auch "implizites Token" genannt).

Die Länge der Zeichenkette spielt dabei keine Rolle, es werden hier immer einfache Anführungszeichen
verwendet.

## To EOF not to EOF?

Startregeln müssen nicht unbedingt den gesamten Input "konsumieren". Sie müssen per
Default nur eine der Alternativen in der Startregel erfüllen.


### Ohne EOF: Es darf ein Rest vom Input übrig bleiben

Betrachten wir noch einmal einen leicht modifizierten Ausschnitt aus der obigen
Grammatik:

``` antlr
start : stmt ;
```

Die Startregel wurde so geändert, dass sie nur noch genau ein Statement akzeptieren
soll.

In diesem Fall würde die Startregel bei der Eingabe "aa; bb;" nur den ersten Teil
"aa;" konsumieren (als Token `ID`) und das folgende "bb;" ignorieren. Das wäre in
diesem Fall aber auch kein Fehler.

### Mit EOF: Der gesamte Input muss passen

Wenn der gesamte Eingabestrom durch die Startregel erklärt werden soll, dann muss
das vordefinierte Token `EOF` am Ende der Startregel eingesetzt werden:

``` antlr
start : stmt EOF;
```

Hier würde die Eingabe "aa; bb;" zu einem Fehler führen, da nur der Teil "aa;" durch
die Startregel abgedeckt ist (Token `ID`), und der Rest "bb;" zwar sogar
gültige Token wären (ebenfalls `ID` und `;`), aber eben nicht mehr von der
Startregel akzeptiert. Durch das `EOF` soll die Startregel aber den gesamten Input
konsumieren und erklären, was hier nicht geht und entsprechend zum Fehler führt.

(vgl.
[github.com/antlr/antlr4/blob/master/doc/parser-rules.md](https://github.com/antlr/antlr4/blob/master/doc/parser-rules.md#start-rules-and-eof))


::: tip
## Reservierte Schlüsselwörter

Die folgenden Strings stellen reservierte Schlüsselwörter von ANTLR dar
und dürfen nicht als Token, Regel oder Label genutzt werden:

```
import, fragment, lexer, parser, grammar, returns, locals, throws, catch, finally, mode, options, tokens
```

`rule` ist zwar kein Schlüsselwort, wird aber als Methodenname bei
der Codegenerierung verwendet. =\> Wie ein Schlüsselwort behandeln!

(vgl.
[github.com/antlr/antlr4/blob/master/doc/lexicon.md](https://github.com/antlr/antlr4/blob/master/doc/lexicon.md))
:::

:::::::::


# Arbeitsweise von ANTLR

- ANTLR generiert aus der Grammatik: Lexer, Parser, Visitor, ...
- Lexer konsumiert Input und erzeugt Tokenstrom
- Parser konsumiert Tokenstrom und erzeugt Parse-Tree

\bigskip

```java
var source = "(+ 1 2)";

var input = CharStreams.fromString(source);
var lexer = new LispyLexer(input);
var tokens = new CommonTokenStream(lexer);

var parser = new LispyParser(tokens);
var tree = parser.lexpr();
```

[Web: Lispy (Grammatik und Regeln, Eingabe und Parse-Tree)]{.ex href="http://lab.antlr.org/"}


# Verhalten des Lexers

1. **Längster Match**

    ::: notes
    Primäres Ziel: Erkennen der längsten Zeichenkette
    :::

    ``` antlr
    INT  : [0-9]+ ;
    ID   : [a-zA-Z][a-zA-Z0-9]* ;
    ```

    Eingabe "foo42": Token `ID` (nicht `ID`, `INT`)

    ::: notes
    Die Regel, die den längsten Match für die aktuelle Eingabesequenz produziert,
    "gewinnt".
    :::

2. **Reihenfolge** in Grammatik definiert Priorität

    ``` antlr
    FOR : 'for' ;
    ID  : [a-z][a-zA-Z]* ;
    ```

    Eingabe "for": Token `FOR`

    ::: notes
    Falls mehr als eine Lexer-Regel die selbe Inputsequenz matcht, dann hat die in der
    Grammatik zuerst genannte Regel Priorität.
    :::

3. **Implizite Token**: haben höchste Priorität

    ``` antlr
    foo  : '0' | NUM EOF ;

    NUM  : [0-9]+ ;
    WS   : [ \t\r\n]+ -> skip ;
    ```

   Eingabe "0": Token `'0'` (nicht `NUM`)

   ::: notes
   Implizite Tokens (`'...'`) werden intern **vor** expliziten Lexer‑Regeln einsortiert und bekommen
   dadurch eine noch höhere Priorität.
   :::



# Berücksichtigung von Präzedenz im Parser

::: notes
Wir können die gestufte konkrete Grammatik, die die Operator-Präzedenz berücksichtigt,
direkt nach ANTLR übersetzen:
:::

- **konkrete Grammatik** (gestuft):

    ```ebnf
    expr  ::= term ('+' term)*
    term  ::= atom ('*' atom)*
    atom  ::= '-' atom
            | INT
    ```

\bigskip

- **ANTLR**-Grammatik:

    ```antlr
    expr  : term ('+' term)* ;
    term  : atom ('*' atom)* ;
    atom  : '-' atom
          | INT
          ;
    ```

::: notes
Die Präzedenz wird dabei durch die Struktur berücksichtigt: `expr` über `term` über `atom`.

Die gewünschte Linksassoziativität für die Operatoren `+`und `*`
wird durch die Formulierung `(...)*` berücksichtigt.
:::


# Direkte Linksrekursion und ANTLR - automatische Präzedenz

::: notes
ANTLR4 kann **direkte Linksrekursion** automatisch auflösen. Die Regel
`r : r T U | V ;` kann also in ANTLR4 verarbeitet werden.

ANTLR nutzt beim Auflösen der direkten Linksrekursion die Strategie des ["*precedence
climbing*"](https://www.antlr.org/papers/Clarke-expr-parsing-1986.pdf) und löst nach
der **Reihenfolge der linksrekursiven Alternativen** in einer Regel auf. Dies kann man ausnutzen, um
über die Reihenfolge der linksrekursiven Alternativen die Operator-Präzedenz abzubilden:
:::

:::::: columns
:::column
Aus der Grammatik mit gestuften Regeln zur Berücksichtigung von Präzedenz und (Links-)
Assoziativität ...

```antlr
expr  : term ('+' term)* ;
term  : atom ('*' atom)* ;
atom  : '-' atom
      | INT
      ;
```
:::
:::column
... wird eine Grammatik mit linksrekursiven Alternativen, wo sich der Vorrang über die
Reihenfolge der linksrekursiven Alternativen bestimmt (von oben nach unten):

```antlr
expr  : expr '*' expr
      | expr '+' expr
      | '-' atom
      | INT
      ;
```
:::
::::::

::: notes
Unter den beiden linksrekursiven Alternativen `expr '*' expr` und `expr '+' expr` hat die erste
Alternative die höhere Priorität und würde beim Parsen wie gewünscht weiter unten im Baum
landen.

Beide Varianten sind machbar. Entscheiden Sie selbst, was (für Sie) lesbarer ist.

::: caution
## Indirekte Linksrekursion

Mit **indirekter** Linksrekursion kann ANTLR (v4) **nicht** umgehen:

``` antlr
expr : expM | ... ;
expM : expr '*' expr ;
```

Hier würden sich die Regeln `expM` und `expr` gegenseitig aufrufen und kein Token aus dem
Tokenstrom entfernen, so dass der generierte LL-Parser hier in einer Endlosschleife
stecken bleiben würde. Mit indirekter Links-Rekursion kann ANTLR nicht umgehen.

**Indirekte Linksrekursion ist nicht erlaubt!**
:::

## Assoziativität

Per Default werden Operatoren wie `+` von ANTLR automatisch als **linksassoziativ** behandelt,
da bei Mehrdeutigkeiten in der Grammatik stets die erste passende Regel/Alternative genommen
wird. Dadurch wird die übliche Klammerung von `+` und `*` berücksichtigt, d.h. `1+2+3` wird
mit der gezeigten Grammatik wie erwartet als `(1+2)+3` geparst.

Die Eingabe `2^3^4` sollte aber als `2^(3^4)` geparst werden. Analog sollte `a=b=c` in C/C++
als `a=(b=c)` verstanden werden. Für *rechts-assoziative* Operatoren
muss man ANTLR dies explizit mit `<assoc=right>` in der Grammatik mitteilen:

``` antlr
expr : <assoc=right> expr '^' expr
     | INT
     ;
```

:::





::: notes
# Ausblick

Damit haben wir die sprichwörtliche "Spitze des Eisbergs" gesehen. Mit ANTLR sind
noch viele weitere Dinge möglich. Bitte nutzen Sie aktiv die Dokumentation auf
[github.com/antlr/antlr4](https://github.com/antlr/antlr4).
:::


# Wrap-up

- Lexer-Regeln beginnen mit **Großbuchstaben**
  -   Längster Match gewinnt, Gleichstand: zuerst definierte Regel

\smallskip

- Parser-Regeln beginnen mit **Kleinbuchstaben**
  -   Regeln können Lexer- und Parser-Regeln "aufrufen"
  -   Regeln können Alternativen haben
  -   Bei Mehrdeutigkeit: Vorrang für erste Alternative
  -   ANTLR erlaubt direkte Links-Rekursion

\smallskip

-   Vorrang und Assoziativität in ANTLR:
    -   gestufte Grammatik-Regeln (`expr`/`term`/`atom`)
    -   linksrekursive Regel mit geordneter Alternativenliste
    -   **Reihenfolge linksrekursiver Alternativen** steuert **Vorrang**






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
-   k3: Ich kann Lexer-Regeln in ANTLR formulieren und einsetzen
-   k2: Ich kann das Verhalten des Lexers erklären, insbesondere längste Matches und
    der Einfluss der Reihenfolge der Regeln
-   k2: Ich kann den Aufbau der Parser-Regeln an einem Beispiel erklären
-   k3: Ich kann Alternativen und optionale/mehrfache Regelteile in Parser-Regeln
    umsetzen
-   k3: Ich kann den Vorrang von Alternativen definieren
:::

::: challenges
**Token und Lexer-Regeln mit ANTLR**

Formulieren Sie für ANTLR Lexer-Regeln, mit denen folgende Token erkannt werden:

-   White-Space: Leerzeichen, Tabs, Zeilenumbrüche
-   Vergleichsoperatoren: `<`, `>`, `<=`, `>=`, `==`, `<>`
-   If: `if`
-   Then: `then`
-   Else: `else`
-   Namen: Ein Buchstabe, gefolgt von beliebig vielen weiteren Buchstaben und/oder
    Ziffern
-   Numerische Konstanten: Mindestens eine Ziffer, gefolgt von maximal einem Paar
    bestehend aus einem Punkt und mindestens einer Ziffer, gefolgt von maximal einem
    Paar bestehend aus dem Buchstaben "E" gefolgt von einem "+" oder "-" und
    mindestens einer Ziffer.

Formulieren Sie Hilfskonstrukte zur Verwendung in mehreren Lexer-Regeln als
ANTLR-Fragmente.

White-Spaces sollen entfernt werden und nicht als Token weitergereicht werden.

**Real-World-Lexer mit ANTLR: Programmiersprache Lox**

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

Erstellen Sie für diese fiktive Sprache einen Lexer mit ANTLR. Die genauere
Sprachdefinition finden Sie unter
[craftinginterpreters.com/the-lox-language.html](https://www.craftinginterpreters.com/the-lox-language.html).

**Pig-Latin mit ANTLR-Lexer**

Schreiben Sie eine Lexer-Grammatik mit eingebetteten Aktionen für ANTLR sowie ein
passendes Programm zur Einbindung des generierten Lexers, welches einen Text nach
[Pig Latin](https://de.wikipedia.org/wiki/Pig_Latin) übersetzt:

-   Ist der erste Buchstabe eines Wortes ein Konsonant, schiebe ihn ans Ende des
    Wortes und füge "ay" an.
-   Ist der erste Buchstabe eines Wortes ein Vokal, hänge an das Wort ein "ay" an.

**Lexing mit ANTLR**

In einem Telefonbuch sind zeilenweise Namen und Telefonnummern gespeichert.

Definieren Sie eine Lexer-Grammatik für ANTLR, mit der Sie die Zeilen einlesen
können. Können Sie dabei verschiedene Formate der Telefonnummern berücksichtigen?

    Heinz 030 5346 983
    Kalle +49 30 1234 567
    Lina +49.571.8385-255
    Rosi (0571) 8385-268

Können Sie die Grammatik so anpassen, dass Sie nur möglichst wenige verschiedene
Token an den Parser weitergeben?

Ergänzen Sie Ihre Grammatik um Lexer-Aktionen, so dass Sie die Zeilen, die Zeichen
(in den Namen) und die Ziffern (in den Telefonnummern) zählen können.

**Lexing mit ANTLR**

IBAN für Deutschland bestehen aus dem Kürzel "DE" sowie einer zweistelligen
Checksumme, gefolgt von 2x 4 Ziffern für die Bank (ehemalige Bankleitzahl) sowie 2x
4 Ziffern für die ehemalige Kontonummer sowie zwei weiteren Ziffern. Typisch sind
zwei Formate:

-   Menschenlesbares Format: `DEcc bbbb bbbb kkkk kkkk xx`
-   Maschinenlesbares Format: `DEccbbbbbbbbkkkkkkkkxx`

Definieren Sie eine Lexer-Grammatik für ANTLR, mit der Sie die verschiedenen
IBAN-Formate für Deutschland einlesen können.



---

CFG → ANTLR:„Geben Sie eine ANTLR‑Grammatik für Ausdrücke mit +, -, *, /, Klammern und unärem Minus an, so dass C‑Präzedenz und Linksassoziativität gelten.“

Kurze Erkläraufgabe:„Warum wird 0 in dieser Grammatik nicht als NUM erkannt?“ (mit einem minimalen Beispiel zu impliziten Tokens).

Verständnisfrage zu Präzedenz:„Welche Parse-Struktur erzeugt Ihre Grammatik für a + b * c? Zeichnen Sie den Parse‑Tree grob.“

---


**Linksrekursion und Vorrang**

Betrachten Sie die folgende typische ANTLR-Grammatik für Expressions:

``` antlr
program : expr EOF ;

expr
  : expr ('*'|'/') expr
  | expr ('+'|'-') expr
  | INT
  ;
```

Wie oben dargestellt, ist die Regel `expr` *direkt links-rekursiv*, womit ANTLR4
aber umgehen kann.

In der gezeigten Schreibweise wird implizit ein Vorrang unter den Alternativen
dieser direkt links-rekursiven Regel `expr` definiert und die Eingabe `2+3*4`
würde korrekt als `2+(3*4)` geparst.

Was passiert, wenn man nun versucht, die Operatoren auszuklammern und in eine
eigene Regel zu verlagern?
Betrachten Sie die folgende leicht geänderte Grammatik:

``` antlr
program : expr_ EOF ;

expr_
  : expr_ operator expr_
  | INT
  ;
operator
  : ('*'|'/')
  | ('+'|'-')
  ;
```

Was passiert hier bei der Eingabe von `2+3*4`?

<!--
Präzedenz entsteht in ANTLR4 nur durch die Reihenfolge der linksrekursiven
Alternativen in *derselben* Regel.
-->

:::
