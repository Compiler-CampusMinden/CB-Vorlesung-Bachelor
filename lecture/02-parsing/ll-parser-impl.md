---
author: Carsten Gips (HSBI)
title: LL-Parser selbst implementiert
---

::: tldr
Zur Beachtung der Vorrang- und Assoziativitätsregeln muss die Grammatik entsprechend
umgebaut werden.
:::


# Vorrangregeln

    1+2*3 == 1+(2*3) != (1+2)*3

[Die Eingabe `1+2*3` muss als `1+(2*3)` interpretiert werden, da `*` Vorrang vor `+`
hat.]{.notes}

[[Tafel: Unterschiede im AST]{.ex}]{.slides}

\pause

[Dies formuliert man üblicherweise in der Grammatik:]{.notes}

``` antlr
expr : expr '+' term
     | term
     ;
term : term '*' INT
     | INT
     ;
```

::: notes
ANTLR nutzt die Strategie des ["*precedence
climbing*"](https://www.antlr.org/papers/Clarke-expr-parsing-1986.pdf) und löst nach
der *Reihenfolge der Alternativen* in einer Regel auf. Entsprechend könnte man die
obige Grammatik unter Beibehaltung der Vorrangregeln so in ANTLR (v4) formulieren:
:::

\pause
\bigskip

``` antlr
expr : expr '*' expr
     | expr '+' expr
     | INT
     ;
```

# Linksrekursion

::: notes
Normalerweise sind linksrekursive Grammatiken nicht mit einem LL-Parser behandelbar.
Man muss die Linksrekursion manuell auflösen und die Grammatik umschreiben.

**Beispiel**:
:::

``` antlr
expr : expr '*' expr | expr '+' expr | INT ;
```

\bigskip

[Diese linksrekursive Grammatik könnte man (unter Beachtung der Vorrangregeln) etwa
so umformulieren:]{.notes}

``` antlr
expr     : addExpr ;
addExpr  : multExpr ('+' multExpr)* ;
multExpr : INT ('*' INT)* ;
```

::: notes
ANTLR (v4) kann Grammatiken mit *direkter* Linksrekursion auflösen. Für frühere
Versionen von ANTLR muss man die Rekursion manuell beseitigen.

Vergleiche ["ALL(\*)" bzw. "Adaptive
LL(\*)"](https://www.antlr.org/papers/allstar-techreport.pdf).
:::

\bigskip
\bigskip
\bigskip
\pause

**Achtung**: Mit *indirekter* Linksrekursion kann ANTLR (v4) *nicht* umgehen:

``` antlr
expr : expM | ... ;
expM : expr '*' expr ;
```

[=\> *Nicht* erlaubt!]{.notes}

::: notes
# Assoziativität

Die Eingabe `2^3^4` sollte als `2^(3^4)` geparst werden. [Analog sollte `a=b=c` in C
als `a=(b=c)` verstanden werden.]{.notes}

\bigskip

Per Default werden Operatoren wie `+` in ANTLR *links-assoziativ* behandelt, d.h.
die Eingabe `1+2+3` wird als `(1+2)+3` gelesen. Für *rechts-assoziative* Operatoren
muss man ANTLR dies in der Grammatik mitteilen:

``` antlr
expr : expr '^'<assoc=right> expr
     | INT
     ;
```

*Anmerkung*: Laut
[Doku](https://github.com/antlr/antlr4/blob/master/doc/left-recursion.md) gilt die
Angabe `<assoc=right>` immer für die jeweilige Alternative und muss seit Version 4.2
an den Alternativen-Operator `|` geschrieben werden. In der Übergangsphase sei die
Annotation an Tokenreferenzen noch zulässig, würde aber ignoriert?!
:::






::: outcomes
-   k3: Ich kann Vorrang und Assoziativität bei der Implementierung korrekt umsetzen
:::

::: challenges
**Quizzfragen**:

-   Wie kann man Vorrangregeln implementieren?
:::
