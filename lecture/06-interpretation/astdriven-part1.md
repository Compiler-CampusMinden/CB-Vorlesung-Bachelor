
# Kontrollstrukturen

``` antlr
ifstat: 'if' expr 'then' s1=stat ('else' s2=stat)? ;
```

\bigskip

``` python
def ifstat(self, AST t):
    if eval(t.expr()): eval(t.s1())
    else:
        if t.s2(): eval(t.s2())
```

::: notes
Analog können die anderen bekannten Kontrollstrukturen umgesetzt werden, etwa
`switch/case`, `while` oder `for`.

Dabei können erste Optimierungen vorgenommen werden: Beispielsweise könnten
`for`-Schleifen im Interpreter in `while`-Schleifen transformiert werden, wodurch im
Interpreter nur ein Schleifenkonstrukt implementiert werden müsste.
:::



