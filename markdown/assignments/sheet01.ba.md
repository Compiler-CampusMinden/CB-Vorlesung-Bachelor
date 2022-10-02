---
archetype: assignment
title: "Meilenstein 01: Grammatik, ANTLR, AST (Mini-Python)"
author: "BC George, Carsten Gips (FH Bielefeld)"
weight: 1

hidden: true

sketch: true
---


## A1.1: Grammatik

Erstellen Sie eine Grammatik für **Mini-Python**. An folgenden Code-Beispielen können
Sie den minimalen Funktionsumfang ablesen.

Folgender Sprachumfang soll mit Ihrer Grammatik mindestens unterstützt werden:
* [Sprachumfang](https://github.com/Compiler-CampusMinden/Mini-Python)
* Funktionalität soll wie in Python erfolgen. Folgende Ausnahmen gelten:
  * Einrückung für die Funktionalität irrelevant
  * Schleifen, Funktionen und Klassen werden mit #end beendet!

```python3
# IF-Statement BSP 1
a= 2
if a == 2:
    print("a is ", a)
#end

# IF-Statement BSP 2
if a == 2:
  print("a is ", a)  
elif a == 3:
  print("a is ", a)  
else:
  print("a is not 2 and not 3")
#end
```

```python3
#Schleifen
while(x>y):
	print(x ,"is bigger than ",y)
	x=x-1
#end
```

```python3
#Funktionen
def foo():
  print("ich bin eine Funktion")
#end
```

```python3
#Klassen BSP1

class A:
  def foo():
    print("Ich bin eine Methode von A")
  #end
#end

class B(A): #Vererbung B erbt von A
  def foo():
    print("Ich bin eine Methode von B")
  #end
#end
```

<!-- TODO Abstimmung mit Florian/Sebastian/Michael -->


## A1.2: ANTLR

Erzeugen Sie mithilfe der Grammatik und ANTLR einen Scanner und Parser, den Sie für
die folgenden Aufgaben nutzen.


## A1.3: AST

Entwickeln Sie ein Konzept für einen AST.

Begründen und diskutieren Sie im Praktikum Ihre Entscheidungen: Warum haben Sie
welche Elemente weggelassen, warum sieht Ihr AST so aus, wie er aussieht? Wie
kommen Sie vom Parse-Tree zum AST?
