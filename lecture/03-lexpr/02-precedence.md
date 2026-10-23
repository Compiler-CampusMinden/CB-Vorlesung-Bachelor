---
author: Carsten Gips (HSBI)
title: "L-Expr: Vorrang und Assoziativität"
---

::: tldr
Für eine Java-artige Infix-Notation sind Vorrangregeln und Assoziativität wichtig:
Multiplikation/Division binden stärker als Addition/Subtraktion, alle vier
Operatoren sind linksassoziativ. Wir modellieren das in einer **gestuften konkreten
Grammatik** (`expr`/`term`/`factor`).
:::





# Java-artige Infix-Syntax: Vorrangregeln

::: notes
In Lispy gibt es durch die Präfix-Notation und Klammern **keine Vorrangprobleme**:
:::

-   `(* (+ 1 2) 3)` ist immer eindeutig

\bigskip

::: notes
In Java-ähnlicher Infix-Schreibweise:
:::

    1+2*3   ==   1+(2*3)   !=   (1+2)*3

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

`+`, `-`, `*`, `/` sind **linksassoziativ**: [(werden von **links** geklammert)]{.notes}

    1 - 2 - 3   =   (1 - 2) - 3
    8 / 4 / 2   =   (8 / 4) / 2
    1 + 2 + 3   =   (1 + 2) + 3



# Vorrang und Assoziativität: Gestufte Grammatik-Regeln

::: notes
Um Vorrang und Assoziativität zu berücksichtigen, formuliert man traditionell in der
konkreten Grammatik "gestufte" Regeln. Dabei tauchen die Operatoren mit der kleinsten
Priorität ganz oben auf, und die Operatoren mit höherer Priorität folgen in den tieferen
Stufen, und ganz unten kommen die Operatoren mit der höchsten Priorität. Diese letzte Regel nennt
man oft `atom` oder `primary`.
:::

```ebnf
expr  ::= term ('+' term)*
term  ::= atom ('*' atom)*
atom  ::= '-' atom
        | INT
```

[Beispiel Parsen "1+2*3" und "1-2-3"]{.ex}

::: notes
Diese typische, etwas komplex anmutende Struktur soll sicherstellen, dass die
Vorrangregeln für Addition und Multiplikation korrekt beachtet werden, d.h. dass
`2+3*4` als `2+(3*4)` geparst wird und nicht fälschlicherweise als `(2+3)*4` erkannt
wird.

Zusätzlich muss bei LL-Parsern Links-Rekursion vermieden werden: Die Parser-Regeln
werden in Funktionsaufrufe übersetzt, d.h. bei einer Links-Rekursion würde man die
selbe Regel immer wieder aufrufen, ohne ein Token aus dem Token-Strom zu entnehmen.


Eigenschaften:

-   Vorrang über die **Struktur**:

    -   `expr` = schwächste Ebene (`+`, `-`)
    -   `term` = mittlere Ebene (`*`, `/`)
    -   `atom` = stärkste Ebene (`INT`, unäres Minus)

-   Assoziativität über das `(...)*`: Wiederholung nach rechts $\to$
    linksassoziative Bäume.
:::


# Wrap-up

-   In Infix-Notation brauchen wir:
    -   Vorrang: `*` und `/` binden stärker als `+` und `-`
    -   Linksassoziativität aller vier Operatoren
-   Vorrang: [modellieren wir klassisch über eine]{.notes} **gestufte Grammatik** mit `expr`, `term`,
    `atom`



::: readings
TODO

Einen schönen Überblick über das, was uns in diesem Semester erwartet, gibt
@Nystrom2021 in Kapitel 2 "A Map of the Territory".
:::

::: outcomes
:::

::: challenges
**Vorrang und Assoziativität**

Betrachten Sie erneut die Grammatik aus dem Beispiel:


```ebnf
expr  ::= term ('+' term)*
term  ::= atom ('*' atom)*
atom  ::= '-' atom
        | INT
```

Welche Klammerung wird beim Parsen der folgenden Eingaben erzwungen:

-   `1 + 2 * 3`
-   `8 * 4 * 2`
-   `-3 * 4`

Geben Sie jeweils die resultierenden Parse-Trees an.


:::
