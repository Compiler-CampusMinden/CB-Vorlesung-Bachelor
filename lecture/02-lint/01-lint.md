---
author: Carsten Gips (HSBI)
title: L-Int -- Von Ausdrücken zum Interpreter (Sitzung 1)
---

::: tldr
TODO
:::

::: youtube
TODO
:::

# Problem: Wie verstehen wir `1 + 2 - 3`?

-   Eingabe: Text wie `1 + 2 - 3`
-   Ziel: Ergebnis berechnen
-   Frage:
    -   Wie modellieren wir die Struktur solcher Ausdrücke?
    -   Wie bringen wir den Rechner dazu, "richtig" zu rechnen?

:::: notes
Starten wir mit einem bewusst einfachen Beispiel: `1 + 2 - 3`. Das kennen alle, aber
wir tun jetzt so, als wüssten wir noch nicht, wie ein Rechner das versteht. Die
beiden Kernfragen sind: Wie sieht die Struktur dieses Ausdrucks aus? Und wie können
wir die Bedeutung so modellieren, dass wir sie programmatisch auswerten können?

Das wird uns durch die gesamte Vorlesung begleiten: **Vom Text (Eingabe) über
Struktur (Syntax) hin zur Bedeutung (Semantik)**.

::: important
**Lehrkonzept**

Wir werden im Laufe der Veranstaltung **inkrementell** vorgehen und mit einer
minimalen Sprache L-Int (nur Integer, Addition und Subtraktion) starten. Für diese
Sprache werden wir die Syntax in Form von Grammatiken festlegen, Lexer und Parser
bauen und aus einer Eingabe einen Syntax-Tree (Parse-Tree) und einen abstrakten
Syntax-Tree (AST) erzeugen und diesen schließlich mit einem Interpreter evaluieren.
In den Folgewochen werden wir darauf aufbauen und aufbauend auf L-Int weitere
Sprachen definieren, die zusätzliche Fähigkeiten und Konzepte mitbringen. Auf
Java-Ebene werden wir die Bausteine der jeweiligen Vorgängerversion erben und
passend überschreiben mit dem neuen Verhalten und mit `super.xyz()` die
Vorgängerversion "aufrufen" für die bisherige Funktionalität. Wir orientieren uns
damit grob an dem inkrementellen Vorgehen in [@Siek2023python].
Konzeptionell/didaktisch lassen wir uns bei der Modellierung der Bausteine in vielen
Fällen ungefähr von der Darstellung in [@Nystrom2021] inspirieren. Du wirst also
immer wieder den Hinweis auf diese beiden Werke als Vertiefung finden.
:::
::::

# S-Expressions als syntaktische Grundform

::: notes
Ein Programm in L-Int besteht aus einem Ausdruck (*Expression*). Die Ausdrücke haben
eine spezielle Form: Sie sind sogenannte
[**S-Expressions**](https://en.wikipedia.org/wiki/S-expression).

Eine S-Expression ist:
:::

-   ein Atom der Form `x`, oder
-   ein Ausdruck der Form `(. x y)` [(mit `x` u. `y` S-Expression, `.` eine
    Operation oder Funktion oder ein Keyword)]{.notes}.

:::: notes
::: tip
**Anmerkung**: Die Anzahl der S-Expressions in einem Klammer-Ausdruck ist nicht
näher definiert - `x` und `y` sind nur Beispiele. Es könnten auch mehr oder weniger
S-Expressions nach der Operation/Funktion/Keyword auftauchen (vgl. nachfolgende
Sprachdefinition).
:::

In der *Vorlesung* werden wir für unsere aufeinander aufbauenden Sprachfamilien
**S-Expressions** nutzen in Anlehnung an Clojure und Lisp. Das vereinfacht das
Parsing deutlich und lässt die Konzepte im Skript und den Folien deutlicher
hervortreten. Im Praktikum wirst Du diese Konzepte auf einen Subdialekt von C++
anwenden und über das Semester hinweg in modernem Java einen Interpreter für C++
schreiben.

Lisp ist eine alte Sprache (Sprachfamilie), die aus dem KI-Umfeld stammt, und ist
eine Abkürzung für "*list processing*". In Lisp wird fast alles über Listen
dargestellt, dabei werden sowohl für Programme wie auch für Daten dieselbe Form
([S-Expressions](https://en.wikipedia.org/wiki/S-expression)) genutzt
("Homoikonizität", "*code as data*") - einfach zu merken und gleichzeitig sehr
mächtig.

Clojure ist ein moderner Lisp-Dialekt und läuft auf der Java-VM. Der Legende nach
stammt der Name "Clojure" von "*closure*" (Programmierkonzept) sowie von "C" für C
bzw. C#, "L" für Lisp und "J" für Java (Sprachen, bei denen Konzepte entlehnt
wurden). ([[Hickey, Rich (2009-01-05). "meaning and pronunciation of
Clojure"](https://groups.google.com/g/clojure/c/4uDxeOS8pwY/m/UHiYp7p1a3YJ)]{.credits
nolist="true"})

Clojure und Lisp nutzen die "*prefix notation*": `(. x y)`
::::

\bigskip
\bigskip

::: center
![](https://clojure.org/images/content/guides/learn/syntax/structure-and-semantics.png){width="60%"
web_width="85%"}

[[Clojure.org: Learn
Clojure](https://clojure.org/guides/learn/syntax#_structure_vs_semantics)]{.credits}
:::

:::: notes
In grüner Beschriftung ist die Syntax markiert, also die Datenstruktur, die nach dem
Einlesen des Codeschnipsels entsteht. Eine S-Expression ist also einfach eine Liste
mit einem Symbol und hier im Beispiel zwei Zahlen.

In blauer Schrift ist die Semantik markiert, also das, was die Clojure Runtime dann
ausführt. Dabei wird die Liste als Funktionsaufruf interpretiert, das Symbol zu
einer Funktion aufgelöst und die beiden Zahlen werden als Argumente übergeben.

Die Verwendung von S-Expressions spielt direkt eine Rolle, warum Lisp und die
modernen Varianten wie Clojure und Racket so beliebt sind.

S-Expressions werden in Clojure und Lisp oft auch "*form*" genannt.

::: tip
Wir ignorieren die Aspekte "Liste" und "Funktion" vorerst und stellen das für später
zurück. Ein `(+ 1 2)` ist einfach eine andere Schreibweise für `1 + 2`.
:::
::::

# L-Int: Erste Sprachstufe

::: notes
Die Sprache L-Int ist bewusst sehr eingeschränkt, damit wir schnell die
Interpreter-Pipeline aufbauen können. Wir werden dann schrittweise weitere
Sprachinkremente darauf aufbauen.

In L-Int haben wir:

-   Ganzzahlen (z.B. `0`, `42`, `1337`)
-   Binäre Operatoren: `+`, `-`
-   Klammern: `(`, `)`
-   Zeilen-Kommentar: `;;`

Beispiele:
:::

``` clojure
1                       ;; 1 (Integer)
(+ 1 2)                 ;; 1 + 2
(+ 1 2 3 4)             ;; 1 + 2 + 3 + 4
(- 10 (+ 3 5))          ;; 10 - (3 + 5)
(- (+ 1 2) (- 3 4))     ;; (1 + 2) - (3 + 4)
```

:::: notes
L-Int ist unsere minimalistische Basissprache für die folgenden Sitzungen. Sie
enthält nur das Nötigste: Integer-Literale, Addition und Subtraktion, sowie
Klammern. Das ist bewusst klein gehalten, damit wir uns auf die Architektur
konzentrieren können: Grammatik, AST, Interpreter. Alles, was wir hier aufbauen,
lässt sich (und wird) später systematisch erweitern.

Die einfachste Form sind dabei Literale mit konkreten Werten des Datentypen
`Integer`.

In der listenartigen Form ist der erste Eintrag der Liste immer eine Operation (oder
ein Funktionsname), danach kommen je nach Operation/Funktion (die Arität muss
passen!) entsprechende Einträge, die als Parameter für die Operation oder Funktion
zu verstehen sind.

Der Ausdruck `(+ 1 1)` ist eine S-Expression, gebildet aus den atomaren Ausdrücken
`+` und `1`. Bei der Evaluierung wird das `+`-Symbol zu einer Additionsfunktion
evaluiert, und die `1` steht für sich, also für eine Integerzahl mit dem Wert $1$.
Bei der Evaluierung der Liste wird die Additionsfunktion mit den beiden Integerzahl
als Argument aufrufen.

Die Ausdrücke sind implizit von links nach rechts geklammert, d.h. der Ausdruck
`(+ 1 2 3 4)` ist [*syntactic sugar*](https://en.wikipedia.org/wiki/Syntactic_sugar)
für `(+ (+ (+ 1 2) 3) 4)`.

::: tip
In vielen Sprachen unterscheidet man zwischen **Statements** und **Expressions**
(Anweisungen und Ausdrücke). Dabei haben Statements üblicherweise keinen (Rückgabe-)
Wert und verändern den Zustand des laufenden Programms (*state*), während
Expressions immer einen Wert ergeben. In unserem L-Int ist zunächst alles eine
Expression, d.h. Ausdrücke ergeben bei der Auswertung immer einen Wert. In späteren
Sprachstufen werden wir komplexere Ausdrücke und auch Statements über die Listenform
bilden.
:::

Über `;;` wird ein Kommentar eingeleitet, der bis zum Ende der Zeile geht.
::::

# Wrap-up

-   L-Int besteht aus S-Expressions
-   Formen:
    -   Integer-Literal als Atom
    -   S-Expression mit `+` und `-` als Operatoren

::: readings
TODO

-   @Nystrom2021: Kapitel 4: A Tree-Walk Interpreter, insb. 8. Statements and State
-   @Mogensen2017: Kapitel 4
:::

::: outcomes
-   k3: Ich kann TODO
:::
