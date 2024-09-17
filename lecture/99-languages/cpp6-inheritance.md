---
archetype: lecture-cg
title: "C++: Vererbung und Polymorphie"
author: "Carsten Gips (HSBI)"
readings:
  - key: "Breymann2011"
  - key: "cppreference.com"
  - key: "cprogramming.com"
tldr: |
    Vererbung analog zu Java passiert in C++ über die "`public`-Vererbung": `Subklasse : public Superklasse`.
    Dabei gibt es in C++ **keine** gemeinsame Oberklasse wie `Object` und entsprechend kein `super`. (Es
    kann auch private Vererbung geben.)

    Operatoren und *struktoren werden in den vom Compiler erzeugten Defaults richtig verkettet. Bei der
    eigenen Implementierung von Operatoren und Konstruktoren muss zunächst der Operator/Konstruktor der
    Basisklasse aufgerufen werden (Basisklassen-Konstruktoren dabei in der Initialisierungsliste!), danach
    erfolgt die Implementierung für die eigenen Attribute der abgeleiteten Klasse. Der Zugriff auf die
    Elemente der Elternklasse erfolgt dabei über den Namen der Elternklasse und den Scope-Operator (nicht
    mit `super`!). Destruktoren von abgeleiteten Klassen müssen sich dagegen nur um die zusätzlichen
    Attribute der abgeleiteten Klasse kümmern, der Basisklassendestruktor wird automatisch verkettet bzw.
    aufgerufen.

    Abstrakte Klassen in C++ haben mindestens eine abstrakte Methode. Eine Methode ist abstrakt, wenn sie
    als "`virtual`" deklariert ist **und** der Deklaration ein "`=0`" folgt.

    In C++ hat man aus Effizienzgründen per Default statische Polymorphie. Bei der Zuweisung eines Objekts
    einer abgeleiteten Klasse (rechte Seite) an ein Objekt vom Typ der Oberklasse (linke Seite) erfolgt
    dabei "Slicing", d.h. alle zusätzlichen Eigenschaften der abgeleiteten Klasse gehen dabei verloren.
    Dynamische Polymorphie kann man in C++ nutzen, indem man (a) die gewünschten Methoden in der Basisklasse
    als `virtual` deklariert und (b) für den Zugriff auf die Objekte der abgeleiteten Klasse Pointer oder
    Referenzen vom Basisklassen-Typ benutzt.

    In C++ ist Mehrfachvererbung möglich, d.h. eine Klasse kann von mehreren anderen Klassen erben. Damit
    erbt sie auch das Objekt-Layout aller Elternklassen.

    Bei rautenförmigen Vererbungsbeziehung führt dies zu Problemen, da Attribute und Methoden der gemeinsamen
    Basisklasse mehrfach vorhanden (über jeden Zweig der Raute).

    Zur Umgehung des Problems kann man die gemeinsam genutzten Basisklassen "`virtual`" deklarieren. Dadurch
    sind gemeinsam genutzte Attribute und Methoden nur noch einfach vorhanden. Da die Klassen "in der Raute"
    ihrerseits den Konstruktor der Basisklasse aufrufen (könnten) und es dadurch zu Konflikten beim Setzen
    der Attribute der Basisklasse kommen kann, gelten bei virtueller Ableitung Sonderregeln: Für die virtuelle
    Basisklasse wird die Weiterleitung der Werte aufgehoben (es muss also ein parameterloser Konstruktor existieren,
    der durch die direkten Unterklassen aufgerufen wird) und die Klasse am "unteren Ende der Raute" kann direkt
    den Konstruktor der virtuellen Basisklasse am "oberen Ende der Raute" aufrufen.
outcomes:
    - k2: "Unterschied zwischen `public`- und `private`-Vererbung"
    - k2: "Unterschied Überladen und Überschreiben"
    - k2: "Slicing in C++"
    - k2: "Probleme bei Mehrfachvererbung und Einsatz virtueller Basisklassen"
    - k3: "`public`-Vererbung in C++"
    - k3: "Verkettung von Operatoren und *struktoren"
    - k3: "Statische und dynamische Polymorphie in C++"
    - k3: "Abstrakte Klassen in C++"
    - k2: "Probleme bei Mehrfachvererbung und Einsatz virtueller Basisklassen"
    - k3: "Praktischer Umgang mit Mehrfachvererbung"
youtube:
  - link: "TODO"
    name: "VL C++: Vererbung und Polymorphie"
challenges: |
    **Destruktoren und Vererbung**

    Welcher Destruktor würde im folgenden Beispiel aufgerufen?!

    ```cpp
    Student *s3 = new Student("Holger", 1.0);
    Person  *p  = s3;

    delete p;
    ```

    **Vererbung**

    *   Welche Formen der (einfachen) Vererbung gibt es in C++ neben der
        `public`-Form noch? Was bewirken diese Formen?
    *   Warum wird in C++ die `public`-Form der Vererbung vorgezogen
        (zumindest, wenn man dynamische Polymorphie nutzen will)?
    *   Wie müssen Konstruktoren/Destruktoren richtig verkettet werden?
    *   Arbeiten Sie das Beispiel auf S. 274 im @Breymann2011:
        "Der C++ Programmierer" durch.

    **Virtuelle Methoden, Dynamische Polymorphie in C++**

    1.  Was sind virtuelle Methoden und wie setze ich diese ein?
    2.  Wozu brauche ich in C++ virtuelle Klassen? Was muss beachtet werden?
    3.  Was passiert in C++, wenn eine virtuelle Methode innerhalb von Konstruktoren
        verwendet wird? Schreiben Sie ein kurzes Programm zur Verdeutlichung.
    4.  Wie verhält es sich mit der Problematik aus (a) in Java?
    5.  Wie unterscheiden sich in C++ virtuelle und nicht virtuelle Destruktoren?
        Schreiben Sie ein kurzes Programm zur Verdeutlichung.
    6.  Was passiert, wenn in C++ aus einem Destruktor heraus eine virtuelle
        Methode aufgerufen wird?

    *Hinweis:*
    Möglicherweise müssen jeweils mehrere Fälle betrachtet werden!

    <!-- XXX
    a) C++, Konstruktor, Aufruf virtueller Methode:
        * es wird die jeweilige Methode der Klasse des aktuell genutzten Konstruktors genommen
        * unabhängig von virtual oder nicht!
        * Grund: Speicherlayout! Basisklasse kennt evtl. zusätzliche Felder nicht ...
    b) Java, Konstruktor, überschriebene Methode:
        * es wird immer die **tiefste** implementierte Methode genommen (bezogen auf den polymorphen Typ)
    c) C++, Destruktor:
        * bei nicht-virtuellem Destruktor klappt die polymorphe Zerstörung nicht (zerstört nur die Basisklasse)
        * bei virtuellem Destruktor wird erst die abgeleitete Klasse zerstört, danach die Basisklasse
    d) C++, Destruktor, Aufruf virtueller Methode:
        * es wird die jeweilige Methode der Klasse des aktuell genutzten Destruktors genommen
        * unabhängig von virtual oder nicht!
        * Grund: Speicherlayout! Basisklasse kennt evtl. zusätzliche Felder nicht ...

    * C++
        vor VolkswagenVirtuell
            brummm (virtual)!
            quietsch (nonvirtual)!
        nach Basis
            brummm brumm (virtual)
            quietsch quietsch (nonvirtual)

            brummm brumm (virtual)

            Destruktor VW (virtual):    brummm brumm (virtual)  quietsch quietsch (nonvirtual)
            Destruktor Auto (virtual):  brummm (virtual)!   quietsch (nonvirtual)!
        nach VolkswagenVirtuell

        vor VolkswagenNonVirtuell
            brummm (nonvirtual)!
            quietsch (nonvirtual)!
        nach Basis
            brummm brumm (nonvirtual)
            quietsch quietsch (nonvirtual)

            brummm (nonvirtual)!

            Destruktor Auto (nonvirtual):   brummm (nonvirtual)!    quietsch (nonvirtual)!
        nach VolkswagenNonVirtuell

    * Java
        vor Volkswagen
            brummm brummm
            quietsch quietsch
        nach Basis
            brummm brummm
            quietsch quietsch

            brummm brummm
        nach Volkswagen
    -->
---


## Vererbung: "IS-A"-Beziehung zw. Klassen

```cpp
class Student : public Person { ... }
```

::: notes
-   `Student`: abgeleitete Klasse
-   `Person`: Basisklasse
-   `: public`: Vererbungsbeziehung (analog zu `extends` in Java)
-   Erinnerung: `#define  extends  : public`
-   `public`-Vererbung: Verhalten wie in Java
-   Hinweis: Es gibt weitere Spielarten (`protected`, `private`), vgl. Semesterliteratur
:::

[Konsole: vererbungEinfach.cpp]{.bsp}

::: notes
## Vererbung und Konstruktoren

-   Defaultkonstruktoren werden automatisch richtig verkettet
    -   zuerst Aufruf des Basisklassen-Konstruktors
    -   anschließend Behandlung der zusätzlichen Attribute

\smallskip

-   Eigene Konstruktoren verketten:
    -   [Zuerst]{.alert} Basisklassen-Konstruktor aufrufen (in
        Initialisierungsliste!) \newline
        => Konkreten Konstruktor nehmen, nicht `super` wie in Java

    ```cpp
    Student(const string &name = "", double c = 0.0)
    : Person(name), credits(c) { }

    Student(const Student &s)
    : Person(s), credits(s.credits) { }
    ```

[Beispiel: vererbungVerkettung.cpp]{.bsp}
:::

::: notes
## Vererbung und Destruktoren

-   Defaultdestruktoren werden automatisch richtig verkettet
    -   zuerst werden die Destruktoren der zusätzlichen Attribute aufgerufen
    -   dann der Destruktor der Basisklasse

\smallskip

-   Eigene Destruktoren werden automatisch verkettet
-   Destruktor abgeleiteter Klasse muss sich nur um zusätzliche Attribute kümmern
:::

::: notes
## Vererbung und Operatoren

-   Defaultoperatoren werden automatisch richtig verkettet
    -   zuerst Aufruf des Basisklassen-Operators
    -   anschließend Behandlung der zusätzlichen Attribute

\smallskip

-   Eigene Operatoren am Beispiel Zuweisungsoperator:
    -   Zuerst den Zuweisungsoperator der Basisklasse aufrufen
    -   Zugriff über Superklassennamen und Scope-Operator (nicht mit `super`!)

        ```cpp
        const Student &operator=(const Student &s) {
            if (this != &s) {
                Person::operator=(s);
                credits = s.credits;
            }
            return *this;
        }
        ```
:::

## Überladen vs. Überschreiben

::: notes
-   **Überladen**:
    -   Methoden gleichen Namens mit unterschiedlicher Signatur
    -   Überladen von aus Oberklasse geerbten Methoden verdeckt diese \newline
        => Zugriff nur über Scope-Operator `::`

\smallskip

-   **Überschreiben**:
    -   Neuimplementierung einer Methode aus der Oberklasse (identische Signatur)
:::

```cpp
class A {
public:
    void f();
    void f(int); // Ueberladen
    void g();
};


class B : public A {
public:
    void f(double); // Ueberladen, verdeckt Methoden aus A!
    void g();       // Ueberschrieben
};
```

[[Beispiel: ueberladen-ueberschreiben.cpp]{.bsp}]{.notes}

::: notes
## Vererbung von Freundschaften

-   Freundschaften werden nicht vererbt!
-   `friends` der Basisklasse haben keinen Zugriff auf zusätzliche
    private Attribute/Methoden der Unterklassen
-   Aber: weiterhin Zugriff auf die geerbten privaten Elemente!
:::

## Abstrakte Klassen

-   Eine **Klasse** ist [abstrakt]{.alert}, wenn sie mindestens eine abstrakte Methode hat
-   Eine **Methode** ist in C++ [abstrakt]{.alert}, wenn sie
    1.  als [virtuell]{.alert} deklariert ist, **und**
    2.  der Deklaration ein "`=0`" folgt

::: notes
[Abstrakte Methoden]{.alert} können [Implementierung]{.alert} haben! => Implementierung [außerhalb]{.alert} der Klassendeklaration
:::

\bigskip

```cpp
class Person {
public:
    virtual string toString() const = 0;
...
};

string Person::toString() const { ... }  // Implementierung :-)
```

[[Beispiel: vererbungAbstrakt.cpp]{.bsp}]{.notes}

## Was passiert im folgenden Beispiel?

::: notes
IS-A Beziehung: Objekte können als Objekte ihrer Oberklasse behandelt werden
:::

```cpp
class Person { ... }
class Student : public Person { ... }

Student s("Heinz", "heizer");
Person &p = s;

cout << s.toString() << endl;
cout << p.toString() << endl;
```

[Konsole: polyStat.cpp]{.bsp}

::: notes
Antwort: Es wird die falsche Methode aufgerufen!

-   `s.toString()` => `Student::toString()` => wie erwartet
-   `p.toString()` => `Person::toString()` => [**unerwartet**]{.alert}!
:::

## Polymorphie: statisch und dynamisch

-   C++ entscheidet zur [**Kompilierzeit**]{.alert}, welche Methode aufgerufen wird
    -   `p` ist vom Typ `Person` => `p.toString()`
        => `Person::toString()`
    -   Dieses Verhalten wird **statisches Binden** genannt.

\bigskip

-   Von Java her bekannt: **dynamisches Binden**
    -   Typ eines Objektes wird zur **Laufzeit** ausgewertet

## Dynamisches Binden geht auch in C++ ...

1.  Methoden in **Basisklasse** als **virtuelle Funktion** deklarieren \newline
    => Schlüsselwort `virtual`

\smallskip

2.  Virtuelle Methoden in Subklasse normal überschreiben (gleiche Signatur)
    -   Zusätzlich muss der Rückgabetyp exakt übereinstimmen \newline
        (Ausnahme: Rückgabe Pointer/Referenz auf _abgeleitete_ Klasse)

\smallskip

::: notes
3.  Objekte mittels Basisklassen-Referenzen bzw. -Pointer zugreifen (siehe nächste Folie)
:::

\bigskip

```cpp
class Person {
    virtual string toString() const { ... }
};
```

[Konsole: polyDyn.cpp]{.bsp}

## Vorsicht Slicing

```cpp
Student s("Heinz", 10.0);
Person p("Holger");

p = s;
cout << "Objekt s (Student): " << s.toString() << endl;
cout << "Objekt p (Person):  " << p.toString() << endl;
```

[Konsole polySlicing.cpp]{.bsp}

\pause

::: notes
=> `p` ist vom Typ `Person`

-   Zuweisung von Objekten vom Typ `Student` ist erlaubt (Polymorphie)
-   `p` hat aber nur Speicherplatz für genau eine `Person`
    => "Abschneiden" aller Elemente, die nicht Bestandteil von
    `Person` sind!
-   Slicing passiert immer beim [Kopieren/Zuweisen]{.alert} von Objekten
:::

\bigskip
=> **Dyn. Polymorphie** in C++ immer über [**Referenzen**]{.alert}
(bzw. Pointer) **und** [**virtuelle Methoden**]{.alert}

::: notes
## Anmerkungen zu Polymorphie in C++

-   **Gestaltung der API**:
    -   Zum Überschreiben gedachte Methoden als virtuell deklarieren
    -   Nicht virtuelle Methoden aus der Basisklasse nicht überschreiben

\smallskip

-   Trennung von Deklaration und Implementierung:
    -   Deklaration als virtuelle Funktion nur im Deklarationsteil
    -   Keine Wiederholung im Implementierungsteil (analog zu Defaultwerten)

\smallskip

-   "Virtualität vererbt sich":
    -   Virtuelle Funktionen sind virtuell in der Vererbungshierarchie hinab ab
        der ersten Deklaration als virtuell

\smallskip

-   Virtualität ist "teuer": Es muss eine Tabelle aller virtuellen Funktionen aufgebaut werden und zur
    Laufzeit geprüft werden, welche Funktion genommen werden soll
:::

## Vererbung in C++ und Casting

```cpp
Person *p  = new Student("Heinz", 0.3);   // erlaubt
Student *s = (Student *) p;               // nur mit Cast!

p          = new Person("Harald");
Student *s = (Student *) p;               // leider moeglich!

Student *s = dynamic_cast<Student *>(p);  // zur Laufzeit
```

::: notes
-   Pointer haben Typ, Zuweisung immer nur an allgemeineren Pointer
-   Normaler C-Cast wird nicht geprüft!
-   Für dynamisches Binden: `dynamic_cast<Typ>(elem)`
:::

\bigskip

-   `dynamic_cast<Typ>(elem)` prüft zur Laufzeit die Typverträglichkeit:
    -   Liefert ggf. `NULL` (Pointer) oder `bad_cast`-Exception (Referenz)
    -   Voraussetzung: dynamisches Binden

        ::: notes
        -   Geht nur bei Klassen, die mindestens eine virtuelle Methode haben!
        -   Geht nur für Pointer/Referenzen auf Klassen!
        :::

::: notes
### Typumwandlung zur Compile-Zeit

Notwendigkeit zum Casten: oft schlechtes Design!

-   C: `(TYP) Ausdruck;`
    -   Syntaktisch leicht zu übersehen
    -   Schwer für Tools auffindbar (search & replace, ...)
    -   Umgeht Typkontrolle des Compilers

\smallskip

-   C++-Alternative: `static_cast<TYP>(Ausdruck)`

    ```cpp
    class A { ... };
    class B: public A { ... };
    B b, *pb;
    A *pa = &b;

    pb = (B*) pa;
    pb = static_cast<B*>(pa);
    ```

=> `static_cast` ist nur geeignet, wenn bereits zur **Compile-Zeit**
feststeht, dass ein Basisklassenzeiger auf ein Objekt einer abgeleiteten Klasse
zeigt. Eine Prüfung erfolgt nicht.
:::

::: notes
### Typumwandlung zur Laufzeit

`dynamic_cast<TYP>(Ausdruck)`

-   Typprüfung zur Laufzeit \newline
    (außer bereits zur Compile-Zeit möglich, dann wie `static_cast<TYP>`)
-   `TYP` muss Pointer oder Referenz auf Klasse sein
-   Ergebnis:
    -   `Ausdruck` ist Pointer, der nicht auf Objekt von `TYP` oder
        davon abgeleiteter Klasse zeigt => Nullpointer `(TYP*)0`
    -   `Ausdruck` ist Referenz, die nicht auf Objekt von `TYP` oder
        davon abgeleiteter Klasse verweist => Exception `bad_cast`

[Beispiel: typumwandlung.cpp]{.bsp}
:::

::: notes
## Private Vererbung: Implementierungsvererbung

-   Nur Implementierung wird geerbt:
    -   `public`-Methoden der Oberklasse dürfen in Unterklasse genutzt werden
    -   Geerbte Methoden gehören aber nicht zur Schnittstelle \newline
        => Objekte der Unterklasse dürfen die geerbten Methoden nicht aufrufen

```cpp
class UltimativeAntwort : public Antwort, private DeepThought { }
```

_Anmerkung_: Delegation ist ähnlich, aber eleganter!

[Beispiel: privateVererbung.cpp]{.bsp}
:::

::: notes
## Neues in C++11 zur Vererbung

-   Schlüsselwort `override`:
    Die Methode muss eine virtuelle Methode der Klassenhierarchie überschreiben.

\smallskip

-   Schlüsselwort `final`:
    Die virtuelle Methode darf nicht in abgeleiteten Klassen überschrieben werden.

[Beispiel: override.cpp]{.bsp}
:::


## Mehrfachvererbung in C++

\bigskip
\bigskip

```cpp
class HiWi: public Student, public Angestellter {...};
```

\pause
\bigskip

![](images/mehrfachvererbung-studi_new.png){width="50%"}

[Hinweis Speicherlayout ...]{.bsp}

## Gleichnamige Methoden aus Basisklassen geerbt

![](images/mehrfachvererbung-namenskollision_new.png){width="50%"}

::: notes
## Namenskollision bei Mehrfachvererbung auflösen

-   Scope-Operator `::` nutzen:

    ```cpp
    HiWi h("Anne", 23.0, 40.0);

    cout << h.Student::toString() << endl;
    cout << h.Angestellter::toString() << endl;
    cout << h.Student::getName() << endl;
    cout << h.Angestellter::getName() << endl;
    ```

\smallskip

-   Methode in abgeleiteter Klasse überschreiben

    ```cpp
    HiWi h("Anne", 23.0, 40.0);

    cout << h.toString() << endl;
    cout << h.Student::toString() << endl;
    cout << h.Angestellter::toString() << endl;
    ```
:::

[Konsole vererbungMultiMethoden.cpp]{.bsp}

## Gemeinsam geerbte Attribute sind mehrfach vorhanden

![](images/mehrfachvererbung-attributkollision_new.png){width="50%"}

[Konsole vererbungMultiAttribute.cpp]{.bsp}

## Mehrfachvererbung in C++: Virtuelle Basisklassen

```cpp
class Angestellter: virtual public Person {...};
class Student: virtual public Person {...};

class HiWi: public Student, public Angestellter {...};
```

\bigskip

-   `Person` ist jetzt eine [virtuelle Basisklasse]{.alert}
-   Auswirkungen erst in Klasse `HiWi`
-   Dadurch sind gemeinsam genutzte Anteile nur einfach vorhanden

::: notes
```cpp
Student s("Heinz", 10.0);           // wie vorher: nur EIN name-Feld
Angestellter a("Holger", 80.5);     // wie vorher: nur EIN name-Feld

HiWi h("Anne", 23.0, 40.0);         // jetzt auch nur EIN name-Feld
```
:::

[Konsole vererbungMultiVirtual.cpp]{.bsp}

## Sonderregeln bei virtueller Ableitung

::: notes
-   Virtuelle Ableitung: Potentiell Konflikte zwischen Konstruktoren!
    -   Gemeinsam geerbtes Attribut nur noch [einmal]{.alert} vorhanden
    -   Konstruktoren werden [nacheinander]{.alert} aufgerufen, alle wollen das
        gemeinsame Attribut initialisieren (durch Aufruf des Konstruktors der
        jeweiligen Basisklasse)
    -   Zuletzt aufgerufener Konstruktor würde "gewinnen"

Deshalb gibt es bei virtueller Ableitung folgende Sonderregeln:
:::

1.  Für virtuelle Basisklassen ist **Mechanismus des Weiterreichens** von
    Initialisierungswerten [**deaktiviert**]{.alert}

\smallskip

2.  Konstruktor einer virtuellen Basisklasse kann in Initialisierungsliste von
    indirekten Unterklassen aufgerufen werden

    Sonst wird der Defaultkonstruktor der virtuellen Basisklasse genutzt!

[Konsole vererbungMultiVirtual.cpp (Basiskonstruktor)]{.bsp}

::: notes
### Mehrfachvererbung in C++ ist ein recht kompliziertes Thema

Warum ist die Möglichkeit dennoch nützlich?

-   In Java kann man nur von einer Klasse erben, aber viele [Interfaces]{.alert}
    implementieren. In C++ gibt es keine Interfaces
    => Interfaces mit abstrakten Klassen Interfaces simulieren
    => Mehrfachvererbung!

-   Modellierung komplexer Zusammenhänge:

    ![](images/mehrfachvererbung-bsp.png)
:::



## Wrap-Up

-   [`public`-Vererbung in C++:]{.notes} `Subklasse : public Superklasse`
-   Keine gemeinsame Oberklasse wie `Object`, kein `super`
-   Verkettung von Operatoren und \*struktoren
-   Abstrakte Klassen in C++

\smallskip

-   Statische und dynamische Polymorphie in C++
    -   Methoden in Basisklasse als `virtual` deklarieren
    -   Dyn. Polymorphie nur mittels Pointer/Referenzen
    -   Slicing in C++ (bei Call-by-Value)

\smallskip


-   Konzept der Mehrfachvererbung
    -   Problem bei rautenförmiger Vererbungsbeziehung: Attribute und Methoden mehrfach vorhanden

\smallskip

-   Virtuelle Basisklassen
    -   Gemeinsam genutzte Attribute und Methoden nur noch einfach vorhanden
    -   Sonderregeln bei virtueller Ableitung







<!-- DO NOT REMOVE - THIS IS A LAST SLIDE TO INDICATE THE LICENSE AND POSSIBLE EXCEPTIONS (IMAGES, ...). -->
::: slides
## LICENSE
![](https://licensebuttons.net/l/by-sa/4.0/88x31.png)

Unless otherwise noted, this work is licensed under CC BY-SA 4.0.
:::
