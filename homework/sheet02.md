---
archetype: assignment
title: "Blatt 02: CFG"
author: "BC George, Carsten Gips (HSBI)"

hidden: true

sketch: true
---


## A2.1: Grammatik für Mini-Python

Erstellen Sie eine Grammatik für [**Mini-Python**].

Der in der [Dokumentation] definierte [syntaktische] und [semantische]
Sprachumfang soll mit Ihrer Grammatik mindestens unterstützt werden.
Dabei ist die Funktionalität wie in Python mit folgenden Ausnahmen:

*   Einrückung ist für die Funktionalität irrelevant
*   Schleifen, Funktionen und Klassen werden mit `#end` beendet

Nachfolgend einige Beispiele in Ergänzung zur [Dokumentation]:

1.  Beispiele für IF-Statements:

    ```python
    a= 2
    if a == 2:
        print("a is ", a)
    #end
    ```

    ```python
    if a == 2:
    print("a is ", a)
    elif a == 3:
    print("a is ", a)
    else:
    print("a is neither 2 and 3")
    #end
    ```

2.  Beispiel für Schleifen:

    ```python
    while(x>y):
        print(x ,"is bigger than ",y)
        x=x-1
    #end
    ```

3.  Beispiel für Funktionen:

    ```python
    def foo():
    print("ich bin eine Funktion")
    #end
    ```

4.  Beispiele für Klassen:

    ```python
    class A:
    def foo(self):
        print("Ich bin eine Methode von A")
    #end
    #end
    ```

    ```python
    class B(A): #Vererbung B erbt von A
    def foo(self):
        print("Ich bin eine Methode von B")
    #end
    #end
    ```

[**Mini-Python**]: https://github.com/Compiler-CampusMinden/Mini-Python-Builder
[Dokumentation]: https://github.com/Compiler-CampusMinden/Mini-Python-Builder/tree/master/docs
[syntaktische]: https://github.com/Compiler-CampusMinden/Mini-Python-Builder/blob/master/docs/syntax_definition.md
[semantische]: https://github.com/Compiler-CampusMinden/Mini-Python-Builder/blob/master/docs/semantic_definition.md


## A2.2: TODO

TODO
