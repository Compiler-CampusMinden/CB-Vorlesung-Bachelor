---
archetype: assignment
title: "Blatt 03: ANTLR"
author: "Carsten Gips, BC George (HSBI)"

hidden: true
---

<!--  pandoc -s -f markdown -t markdown+smart-grid_tables-multiline_tables-simple_tables --columns=94 sheet03.md -o xxx.md  -->

## Zusammenfassung

Ziel dieses Aufgabenblattes ist die Erstellung eines einfachen *Pretty Printers* für eine
fiktive Sprache. Dazu muss eine passende kontextfreie Grammatik definiert werden, für die mit
Hilfe von ANTLR ein Lexer und ein Parser erstellt werden. Aus dem Parse Tree soll ein AST
erstellt werden, und schließlich soll für den AST eine Traversierung zur Erzeugung einer
wohlformatierten Ausgabe definiert werden.

## Methodik

Erstellen Sie sich ein Java-Projekt mit einem Makefile oder Gradle-Skript und binden Sie ANTLR
ein. Testen Sie, ob Sie mit Hilfe einer minimalen ANTLR-Grammatik einen Lexer und Parser
automatisiert erzeugen können.

Bauen Sie die Grammatik für die Aufgabe schrittweise auf. Testen Sie mit Hilfe des
Beispielcodes und überlegen Sie sich selbst weitere Code-Schnipsel, die Sie mit Ihrem Parser
einlesen (bzw. die Ihr Parser zurückweist).[^1]

## Sprachdefinition

Ein Programm besteht aus einer oder mehreren Anweisungen (*Statements*).

### Anweisungen

Eine Anweisung ist eine einzeilige Befehlsfolge, beispielsweise eine Zuweisung, ein
Funktionsaufruf oder eine Operation. Sie muss immer mit einem Newline abgeschlossen werden.
Eine Anweisung hat keinen Wert.

``` python
a := 10 - 5  # Zuweisung des Ausdruckes 10-5 (Integer-Wert 5) an die Variable a
b := "foo"   # Zuweisung des Ausdrucks "foo" (String) an die Variable b
func1(a, b)  # Funktionsaufruf mit Variablen a und b
```

Kontrollstrukturen zählen ebenfalls als Anweisung.

### Ausdrücke (*Expression*)

Die einfachsten Ausdrücke sind Integer- oder String-Literale oder die Wahrheitswerte.
Variablen und Funktionsaufrufe sind ebenfalls Ausdrücke. Komplexere Ausdrücke werden mit Hilfe
von Operationen gebildet, dabei sind die Operanden jeweils auch wieder Ausdrücke. Ein Ausdruck
hat/ergibt immer einen Wert.

Die Operatoren besitzen eine Rangfolge, um verschachtelte Operationen aufzulösen. Sie dürfen
daher nicht einfach von links nach rechts aufgelöst werden. Die Rangfolge der Operatoren
entspricht der üblichen Semantik (vgl. Java, C, Python).

Es gibt in unserer Sprache folgende Operationen mit der üblichen Semantik:

#### Vergleichsoperatoren

| Operation    | Operator |
|:-------------|:--------:|
| Gleichheit   |   `==`   |
| Ungleichheit |   `!=`   |
| Größer       |   `>`    |
| Kleiner      |   `<`    |

#### Arithmetische Operatoren

| Operation                            | Operator |
|:-------------------------------------|:--------:|
| Addition / String-Literal-Verkettung |   `+`    |
| Subtraktion                          |   `-`    |
| Multiplikation                       |   `*`    |
| Division                             |   `/`    |

#### Beispiele für Ausdrücke

``` python
10 - 5       # Der Integer-Wert 5
"foo"        # Der String "foo"
a            # Wert der Variablen a
a + b        # Ergebnis der Addition der Variablen a und b
func1(a, b)  # Ergebnis des Funktionsaufrufs
```

### Bezeichner

Werden zur Bezeichnung von Variablen und Funktionsnamen verwendet. Sie bestehen aus einer
Zeichenkette der Zeichen `a-z`,`A-Z`, `0-9`, `_`. Bezeichner dürfen nicht mit einer Ziffer
`0-9` beginnen.

### Variablen

Variablen bestehen aus einem eindeutigen Bezeichner (Variablennamen). Den Variablen können
Werte zugewiesen werden und Variablen können als Werte verwendet werden. Die Zuweisung erfolgt
mithilfe des `:=`-Operators. Auf der rechten Seite der Zuweisung können auch einfache
Ausdrücke stehen.

``` python
a := 5      # Zuweisung des Wertes 5 an die Variable a
a := 2 + 3  # Zuweisung des Wertes 5 an die Variable a
print(a)    # Ausgabe des Wertes 5 auf der Standardausgabe
```

### Kommentare

Kommentare werden durch das Zeichen `#` eingeleitet und umfassen sämtliche Zeichen bis zum
nächsten Newline.

Es existiert ein spezielles Schlüsselwort `#end`, welches **keinen** Kommentar darstellt.

### *#end*

Das Schlüsselwort `#end` stellt eine Besonderheit dar und dient zum Schließen von Funktionen,
Methoden und Kontrollstrukturen. Durch die Verwendung dieses Schlüsselworts kann auf die
Auswertung der Einrückung verzichtet werden.

### Kontrollstrukturen

#### While-Schleife

While-Schleifen werden mit dem Schlüsselwort `while` eingeleitet. Sie bestehen im Weiteren aus
einer Bedingung, die durch ein `do` abgeschlossen wird, einer Folge von Anweisungen und werden
mit dem Schlüsselwort `#end` abgeschlossen.

Die Bedingung kann aus einem atomaren Boolean-Wert oder einem Vergleichsausdruck bestehen.

``` python
while <Bedingung> do
    <Anweisung_1>
    <Anweisung_2>
#end
```

``` python
a := 10
while (a >= 0) do
    print(a)
    a := a- 1
#end
```

#### Bedingte Anweisung (If-Else)

Eine bedingte Anweisung besteht immer aus genau einer `if`-Anweisung, und einer oder keiner
`else`-Anweisung. Die bedingte Anweisung muss mit dem Schlüsselwort `#end` abgeschlossen
werden.

Eine `if`-Anweisung wird mit dem Schlüsselwort `if` eingeleitet und besteht aus einer
Bedingung, die mit einem `do` abgeschlossen wird und einer Folge von Anweisungen.

Eine `else`-Anweisung wird mit dem Schlüsselwort `else` eingeleitet. Auf das Schlüsselwort
folgt ein `do` und eine Folge von Anweisungen.

``` python
if <Bedingung> do
    <Anweisung_1>
    <Anweisung_2>
#end
```

``` python
if <Bedingung> do
    <Anweisung>
else do
    <Anweisung>
#end
```

``` python
a := "abc"
if a < "adc" do
    print("a kleiner als ", "adc")
else do
    print("a passt nicht")
#end
```

### Funktionen

#### Funktionsdefinition

Funktionsdefinitionen werden mit dem Schlüsselwort `fun` eingeleitet. Sie besitzen einen
eindeutigen Bezeichner (Funktionsnamen), eine in Klammern angegebene Parameterliste, die auch
leer sein kann und eine Abfolge von Anweisungen. Der Anweisungsblock wird durch ein `do`
eingeleitet. Funktionsdefinitionen können eine Rückgabe besitzen, die über das Schlüsselwort
`return` eingeleitet wird. Eine Funktionsdefinition muss immer mit dem Schlüsselwort `#end`
geschlossen werden.

***Hinweis*: Verschachtelte Funktionsdefinitionen müssen nicht umgesetzt werden.**

``` python
fun bezeichner(param1, param2) do
    <Anweisung_1>
    <Anweisung_2>
    return <Bezeichner, Wert oder Operation>
#end
```

``` python
fun func1(a, b) do
    c := a + b
    return c == a + b
#end
```

#### Funktionsaufrufe

Funktionsaufrufe bestehen aus einem Bezeichner (Funktionsname) gefolgt von einer in Klammern
angegebenen Parameterliste, die auch leer sein kann. Als Parameter können Variablen, Werte der
Datentypen, weitere Funktionsaufrufe und Ausdrücke wie z.B. `1 + 1` dienen.

``` python
func1(var1, 5)
func1(func2(), 1 + 1)
```

#### Eingebaute Funktionen

Die Funktion `print` ist in der Sprache eingebaut. Sie nimmt einen Ausdruck als Parameter
entgegen, wertet diesen aus und gibt das Ergebnis auf der Standardausgabe aus.

### Datentypen

Unsere Sprache hat drei eingebaute Datentypen:

| Datentyp | Definition |
|:-------|:-------------------------------------------------------------------------------------|
| `Integer` | Integer-Literale bestehen aus einer beliebigen Folge der Ziffern `0-9`. |
| `String` | String-Literale bestehen aus einer beliebigen Folge an ASCII-Zeichen, die von `"` eingeschlossen sind. Sie müssen keine Unicode-Zeichen unterstützen. |
| `Boolean` | Bestehen aus einem der beiden Schlüsselwörter `True` oder `False` |

Die Sprache ist dynamisch typisiert, d.h. beim Parsen werden Ihnen keine Typ-Angaben begegnen.
Aber Sie müssen die entsprechenden Werte parsen können.

## Aufgaben

### A3.1: Beispielprogramme

Sie finden unten einige Beispielprogramme.

Erstellen Sie selbst weitere Programme in der Zielsprache. Diese sollten von einfachsten
Ausdrücken bis hin zu komplexeren Programmen reichen.

### A3.2: Grammatik

Definieren Sie für die obige Sprache eine geeignete ANTLR-Grammatik.

### A3.3: ANTLR

Erzeugen Sie mithilfe der Grammatik und ANTLR einen Lexer und Parser, den Sie für die
folgenden Aufgaben nutzen.

### A3.4: AST

Beim Parsen bekommen Sie von ANTLR einen Parse-Tree zurück, der die Struktur Ihrer Grammatik
widerspiegelt. Die einzelnen Zweige sind damit aber auch viel zu tief verschachtelt.

Überlegen Sie sich, welche Informationen/Knoten Sie für die formatierte Ausgabe wirklich
benötigen (das ist Ihr AST). Programmieren Sie eine Transformation des Parse-Tree in die von
Ihnen hier formulierten AST-Strukturen.

### A3.5: Pretty Printer

Programmieren Sie eine Traversierung Ihres AST, so dass das geparste Programm korrekt
eingerückt ausgegeben wird.

Jede Anweisung soll auf einer eigenen Zeile stehen. Die Einrückung soll mit Leerzeichen
erfolgen und konsistent sein. Sie brauchen keine Begrenzung der Zeilenlänge implementieren.

Beispiel:

Aus

``` python
a := 0
    if 10<1 do
print("10<1")
a := 42
else do
        print("kaputt")
  #end
```

soll

``` python
a := 0
if 10<1 do
    print("10<1")
    a := 42
else do
    print("kaputt")
#end
```

werden.

## Beispiele

``` python
print("Hello World")
```

``` python
a := "wuppie fluppie"
```

``` python
a := 0
if 10<1 do
    print("10<1")
    a := 42
else do
    print("kaputt")
#end
```

``` python
fun f95(n) do
    if n == 0 do
        return 1
    else do
        if n == 1 do
            return 1
        else do
            return f95(n - 1) + f95(n - 2) + f95(n - 3) + f95(n - 4) + f95(n - 5)
        #end
    #end
#end

n := 10
r := f95(n)
print(r)
```

[^1]: Um den Text lesbar zu halten, wird hier oft nur von "Parser" gesprochen - gemeint ist
    aber die gesamte auf diesem Blatt zu erstellende Toolchain: Lexer - Parser - AST -
    Ausgabe.
