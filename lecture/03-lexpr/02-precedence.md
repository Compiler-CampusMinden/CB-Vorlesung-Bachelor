---
author: Carsten Gips (HSBI)
title: "L-Expr: Vorrang und Assoziativität"
---

::: tldr
In Lispy mit Präfix-Notation und vielen Klammern gibt es keine Mehrdeutigkeit: Die
Struktur des Ausdrucks ist durch die Klammerung eindeutig vorgegeben.

In einer Java- oder C++-ähnlichen Infix-Notation dagegen brauchen wir
**Vorrangregeln** und **Assoziativität**, damit Ausdrücke wie `1+2*3` eindeutig
interpretiert werden. Multiplikation und Division sollen stärker binden als Addition
und Subtraktion, und alle diese Operatoren verhalten sich in unseren Beispielen
**linksassoziativ** (also `1-2-3 = (1-2)-3`).

Diese Informationen kodieren wir nicht "irgendwo im Parser", sondern **direkt in der
konkreten Grammatik**. Dazu verwenden wir eine **gestufte Grammatik** mit mehreren
Ebenen wie `expr`, `term` und `atom`, wobei `expr` die Operatoren mit der
niedrigsten Priorität und `atom` die mit der höchsten Priorität beschreibt. Die
Wiederholung `(...)*` in diesen Regeln erzeugt dabei automatisch
**linksassoziative** Parse-Bäume. So erreichen wir, dass z.B. `1+2*3` immer als
`1+(2*3)` und nicht als `(1+2)*3` geparst wird.
:::

# Java-artige Infix-Syntax: Vorrangregeln

::: notes
In Lispy gibt es durch die Präfix-Notation und die Klammern **keine
Vorrangprobleme**:
:::

-   `(* (+ 1 2) 3)` ist immer eindeutig

\bigskip

::: notes
In Java-ähnlicher Infix-Syntax:
:::

-   `1+2*3   ==   1+(2*3)   !=   (1+2)*3`

\bigskip
\smallskip

-   Multiplikation/Division binden **stärker** als Addition/Subtraktion.

[Die Eingabe `1+2*3` muss als `1+(2*3)` interpretiert werden, da `*` Vorrang vor `+`
hat.]{.notes}

[[Tafel: Unterschiede im AST]{.ex}]{.slides}

# Assoziativität (Klammerung)

::: notes
Nicht nur der **Vorrang** (Multiplikation/Division vor Addition/Subtraktion) ist
wichtig, sondern auch die **Assoziativität** der Operatoren.

Für unsere Infix-Ausdrücke gilt:
:::

`+`, `-`, `*`, `/` sind **linksassoziativ**: [(werden von **links**
geklammert)]{.notes}

    1 - 2 - 3   =   (1 - 2) - 3
    8 / 4 / 2   =   (8 / 4) / 2
    1 + 2 + 3   =   (1 + 2) + 3

# Vorrang und Assoziativität: Gestufte Grammatik-Regeln

::: notes
Um Vorrang und Assoziativität zu berücksichtigen, formuliert man traditionell in der
konkreten Grammatik "gestufte" Regeln. Dabei tauchen die Operatoren mit der
kleinsten Priorität ganz oben auf, und die Operatoren mit höherer Priorität folgen
in den tieferen Stufen, und ganz unten kommen die Operatoren mit der höchsten
Priorität. Diese letzte Regel nennt man oft `atom` oder `primary` oder auch
`factor`.
:::

``` ebnf
expr  ::= term ('+' term)*
term  ::= atom ('*' atom)*
atom  ::= '-' atom
        | INT
```

::::: notes
::: tip
**Hinweis**: Das Einbauen von Subtraktion und Division sind aus Gründen der
Übersichtlichkeit hier nicht gezeigt. Wir betrachten das als Teil der Challenges
und/oder des L-Expr-Übungsblattes.
:::

::: tip
**Hinweis**: Geklammerte Ausdrücke haben ebenfalls wie das unäre Minus die höchste
Priorität. Wir werden das als Teil der Challenges und/oder des L-Expr-Übungsblattes
einbauen.
:::
:::::

[Beispiel Parsen "1+2\*3" und "1+2+3"]{.ex}

::: notes
Diese etwas komplex anmutende Struktur ist ein Standardmuster, das Sie in vielen
Parsern wiederfinden werden, und soll sicherstellen, dass die Vorrangregeln für
Addition und Multiplikation korrekt beachtet werden, d.h. dass `2+3*4` als `2+(3*4)`
geparst wird und nicht fälschlicherweise als `(2+3)*4` erkannt wird.

Zusätzlich muss bei LL-Parsern Links-Rekursion vermieden werden: Die Parser-Regeln
werden in Funktionsaufrufe übersetzt, d.h. bei einer Links-Rekursion würde man
dieselbe Regel immer wieder aufrufen, ohne ein Token aus dem Token-Strom zu
entnehmen.

Eigenschaften:

-   Vorrang über die **Struktur**:

    -   `expr` = schwächste Ebene (`+`, `-`)
    -   `term` = mittlere Ebene (`*`, `/`)
    -   `atom` = stärkste Ebene (`INT`, unäres Minus)

-   Assoziativität über das `(...)*`: Wiederholung nach rechts $\to$
    linksassoziative Bäume. Jede Wiederholung von rechts hängt einen neuen Operator
    rechts an den bereits aufgebauten Teilausdruck - dadurch landen die früheren
    Operatoren weiter oben im Baum, und der Baum wird links-astig: `((1+2)+3)`.
:::

# Wrap-up

-   In Infix-Notation brauchen wir:
    -   **Vorrang**: `*` und `/` binden stärker als `+` und `-`
    -   **Assoziativität**: `+`, `-`, `*`, `/` sind linksassoziativ, z.B.
        `1-2-3 = (1-2)-3`

\smallskip

-   **Gestufte konkrete Grammatik** (`expr -> term -> atom`) modelliert Vorrang:
    -   `expr`: Ebene mit `+` und `-`
    -   `term`: Ebene mit `*` und `/`
    -   `atom`: Ebene mit Literalen, Klammern und unärem Minus

\smallskip

-   Muster `X ::= Y (op Y)*` erzeugt **linksassoziative** Bäume

::: readings
Im [@Nystrom2021] kann man in Kapitel 6 "Parsing Expressions" und Kapitel 7
"Evaluation Expressions" nachlesen.
:::

::: outcomes
-   k2: Ich kann erklären, warum Infix-Notation ohne Vorrangregeln und
    Assoziativität mehrdeutig ist.
-   k2: Ich kann beschreiben, wie eine gestufte Grammatik (`expr`/`term`/`atom`)
    Operatorvorrang modelliert.
-   k3: Ich kann eine gegebene flache Grammatik für arithmetische Ausdrücke so
    umschreiben, dass Vorrang und Linksassoziativität korrekt berücksichtigt werden.
-   k3: Ich kann zu einem Ausdruck wie `1+2*3-4` anhand der Grammatik die zugehörige
    Klammerung und den Parse-Tree konstruieren.
-   k2: Ich kann erläutern, wie das Wiederholungsmuster `(...)*` in Grammatikregeln
    zu linksassoziativen Parse-Bäumen führt.
-   k4: Ich kann verschiedene Varianten einer Expression-Grammatik vergleichen und
    begründen, ob sie mehrdeutig sind oder nicht.
:::

::: challenges
**Ambiguität der "flachen" Grammatik**

Gegeben sei:

``` ebnf
expr ::= expr '+' expr
       | expr '*' expr
       | INT
```

1.  Zeigen Sie, dass diese Grammatik für den Ausdruck `1+2*3` mehrdeutig ist.
2.  Zeichnen Sie zwei verschiedene Parse-Trees für `1+2*3`, die aus dieser Grammatik
    entstehen können.
3.  Welche der beiden Klammerungen entspricht der gewünschten Interpretation in
    Java/C++? Welche nicht?
4.  Formulieren Sie in Worten, welches Problem hier auftritt und wie eine gestufte
    Grammatik dieses Problem löst.

**Assoziativität sichtbar machen**

Betrachten Sie erneut die Grammatik aus dem Beispiel:

``` ebnf
expr  ::= term ('+' term)*
term  ::= atom ('*' atom)*
atom  ::= '-' atom
        | INT
```

1.  Zeichnen Sie die Parse-Trees für die folgenden Eingaben nach dieser Grammatik:
    -   `1 + 2 + 3`
    -   `2 * 3 * 4`
    -   `1 + 2 * 3`
    -   `8 * 4 * 2`
    -   `-3 * 4`
2.  Schreiben Sie zu jedem Parse-Tree die explizite Klammerung des Ausdrucks dazu,
    z.B. `(1 + 2) + 3`.
3.  Diskutieren Sie in der Gruppe:
    -   Warum sind die Bäume links-astig?
    -   Wie würde eine Grammatik aussehen, die `+` (oder `*`) **rechtsassoziativ**
        parst?

**Vorrang durch Umformung der Grammatik**

Starten Sie erneut mit der folgenden Grammatik:

``` ebnf
expr ::= expr '+' expr
       | expr '*' expr
       | INT
```

1.  Formulieren Sie eine neue Grammatik, die:

    -   Multiplikation und Division stärker bindet als Addition und Subtraktion (wie
        in Java/C++),
    -   alle vier Operatoren linksassoziativ macht, und
    -   geklammerte Ausdrücke erlaubt.

2.  Verwenden Sie dazu die drei Stufen `expr`, `term`, `atom`.

3.  Testen Sie Ihre Grammatik gedanklich an den Ausdrücken:

        1 + 2 * 3
        4 * 5 + 6
        7 + 8 + 9

4.  Notieren Sie für jeden Ausdruck die Klammerung, die Ihre Grammatik erzwingt.
:::
