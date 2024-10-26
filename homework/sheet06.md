---
archetype: assignment
title: "Blatt 06: C++"
author: "Carsten Gips, BC George (HSBI)"

hidden: true
---

<!--  pandoc -s -f markdown -t markdown+smart-grid_tables-multiline_tables-simple_tables --columns=94 --reference-links=true  sheet06.md  -o xxx.md  -->

## A6.1: TODO

TODO


## A6.2: TODO

TODO


**S5**: noch irgendwas Richtung Speicherverwaltung/Heap extra


### Aufgabe 1: Implementierung eines einfachen Tokenizers (25 Punkte)

Erstellen Sie eine Funktion `void tokenize(const std::string& input, std::vector<std::string>& tokens)`, die einen gegebenen String als Eingabe erhält und diesen in Tokens (Wörter) splittet. Nutzen Sie Referenzen, um die Token-Liste zu aktualisieren. Testen Sie die Funktion mit verschiedenen Eingabestrings und geben Sie die Tokens aus.


### Aufgabe 2: Syntaxanalyse mit Referenzen (30 Punkte)

Implementieren Sie eine einfache Funktion `bool parseExpression(const std::string& expr, int& result)`, die überprüft, ob eine als String dargestellte mathematische Ausdrucksform (z.B. "3 + 4") syntaktisch korrekt ist. Die Funktion soll das Ergebnis der Berechnung zurückgeben. Nutzen Sie Referenzen für den Rückgabewert und testen Sie die Funktion mit verschiedenen mathematischen Ausdrücken.




### Aufgabe 1: Überladene Funktionen (15 Punkte)

Erstellen Sie eine C++-Bibliothek mit überladenen Funktionen, um den Flächeninhalt verschiedener Formen zu berechnen. Implementieren Sie folgende Funktionen:

- `double area(double radius)`: Berechnet die Fläche eines Kreises.
- `double area(double width, double height)`: Berechnet die Fläche eines Rechtecks.
- `double area(double side1, double side2, double side3)`: Berechnet die Fläche eines Dreiecks mithilfe der Heronschen Formel.

Testen Sie Ihre Implementierung in der `main`-Funktion mit unterschiedlichen Parametern.


### Aufgabe 2: Pointer und Arrays (20 Punkte)

Schreiben Sie eine Funktion `void initializeArray(int* arr, int size)`, die ein Array von Ganzzahlen mit aufsteigenden Werten initialisiert (beginnend bei 1). Erstellen Sie in der `main`-Funktion ein dynamisches Array, initialisieren Sie es mit Ihrer Funktion und geben Sie die Werte aus. Stellen Sie sicher, dass der Speicher ordnungsgemäß freigegeben wird.


### Aufgabe 3: Mehrdimensionale Arrays mit Pointer-Arithmetik (25 Punkte)

Erstellen Sie eine Funktion `void transposeMatrix(int* matrix, int rows, int cols)`, die eine Matrix (2D-Array) transponiert. Nutzen Sie Pointer-Arithmetik und zeigen Sie die ursprüngliche und die transponierte Matrix in der `main`-Funktion an. Achten Sie darauf, den Speicher für die Matrix dynamisch zu allozieren und zu deallozieren.


### Aufgabe 4: Memory Management und Fehlerbehandlung (25 Punkte)

Implementieren Sie eine Funktion `int* allocateAndFillArray(int size)`, die ein Array alloziert, es mit zufälligen Werten befüllt (zwischen 1 und 100) und zurückgibt. Fügen Sie einfache Fehlerbehandlungen für die Speicherzuweisung hinzu. In der `main`-Funktion sollten die Werte des Arrays ausgegeben und danach der Speicher freigegeben werden.


### Aufgabe 5: Komplexe Datenverwaltung mit Referenzen (30 Punkte)

Erstellen Sie eine Struktur `Student`, die `name`, `matrikelnummer` und `note` enthält. Implementieren Sie folgende Funktionen:

- `void setStudentDetails(Student& s, const std::string& name, int matrikelnummer, double note)`: Setzt die Werte eines Studenten.
- `double calculateAverage(const Student* students, int count)`: Berechnet den Durchschnitt der Noten eines gegebenen Studenten-Arrays.

In der `main`-Funktion sollten Sie mindestens 5 Studenten anlegen, deren Werte initialisieren und den Durchschnitt der Noten ausgeben.

**Bonusaufgabe (15 Punkte):**
Implementieren Sie eine Funktion `void countVowels(const std::string& str, int& count)`, die die Anzahl der Vokale in einem gegebenen String zählt. Testen Sie die Funktion in der `main`-Funktion mit verschiedenen Eingaben. Verwenden Sie dabei Referenzen zur Rückgabe des Zählers.







---


## Zusammenfassung

Ziel dieses Aufgabenblattes ist die praktische Anwendung der C++-Kenntnisse, insbesondere werden Pointer, Referenzen und Klassen angewendet und vertieft. Als Anwendungsbeispiel werden bestimmte in der C++-Welt wohlbekannte Smartpointer modelliert sowie ein einfacher Ringpuffer programmiert. Sie lernen mit dem *Reference Counting* nebenbei eine verbreitete Technik der *Garbage Collection* kennen.

## Methodik

Sie werden auf diesem Blatt vier einfache Klassen in C++ implementieren.

Es empfiehlt sich, zunächst die Beispiele gründlich zu analysieren, um die gewünschte Funktionsweise der einzelnen Klassen vorab präzise zu verstehen. Sie werden zu einigen Dingen in der C++-Literatur recherchieren müssen.

Implementieren Sie immer eine Klasse vollständig und testen Sie Ihren Code sowohl mit den vorgegebenen Beispielen als auch mit eigenen Beispielen, bevor Sie sich an die nächste Aufgabe/Klasse setzen.



## Speicherverwaltung in C/C++

C und C++ erlauben als hardwarenahe Programmiersprachen den direkten Umgang mit dem Programmspeicher (Heap). Ein Programm kann dynamisch zu jeder Zeit weiteren Speicher anfordern und so beispielsweise mitwachsende Datenstrukturen realisieren.

Da der Heap-Speicher endlich ist, muss man nicht mehr benötigten Speicher auch wieder freigeben. Anderenfalls ist irgendwann der komplette Heap belegt und das Programm kann nicht mehr ordnungsgemäß arbeiten. Für die Freigabe ist man als Programmierer:in selbst zuständig.

### Beispiel für eine Tokenizer-Funktion


Im folgenden Programmschnipsel soll eine Funktion `next_token()` das nächste Token berechnen. So eine Funktion findet sich typischerweise im Lexer. Für die Rückgabe des Tokens hat man in C++ drei Möglichkeiten: als Kopie, als Referenz oder als Pointer.

```cpp
// Return as copy
Token next_token() {
    Token wuppie = Token("wuppie", 1, 4);   // will be deleted automatically after this function call
    return wuppie;
}
int main() {
    Token x = next_token();                 // copy constructor + assignment operator; no need to free
}
```

```cpp
// Return as pointer
Token* next_token() {
    Token* foo = new Token("foo", 9, 35);   // will be free'd manually (responsibility of caller)
    Token* bar = new Token("bar", 7, 10);   // leaves a memory hole!!!

    return foo;
}
int main() {
    Token* x = next_token();                // only the pointer (i.e. address) will be copied
    ...
    delete x;                               // caller needs to free this object
}
```


```cpp
// Return as C++ reference
Token& next_token() {
    Token* foo = new Token("foo", 9, 35);   // will be free'd manually (responsibility of caller)
    Token* bar = new Token("bar", 7, 10);   // leaves a memory hole!!!

    return *foo;
}
int main() {
    Token& x = next_token();                // no copy, `x` is just a new alias for `foo`
    ...
    delete x;                               // caller needs to free this object
}
```

Die Rückgabe per Kopie (Standardfall in C/C++) würde ein lokales Objekt auf dem Stack (im Beispiel wäre das `wuppie`) als Kopie zurückgeben.

-   Vorteil: Der Compiler kümmert sich um die Freigabe der lokalen Variable `wuppie`, d.h. nach Beendigung des Funktionsaufrufs wird das Objekt automatisch vom Stack entfernt. Da hierbei einfach der Stackpointer zurückgesetzt wird, ist diese "Freigabe" eine sehr preiswerte Operation. (Anmerkung: Man spricht trotzdem von "Freigabe" des Objekts, obwohl lediglich der Stackpointer zurückgesetzt wird und das Objekt zunächst auf dem Stack noch vollständig ist. Es kann und wird aber im weiteren Verlauf des Programms überschrieben.)
-   Nachteil: Der Aufrufer darf nicht einfach auf das Objekt auf dem Stack zugreifen (dieses ist ja nach Beendigung der Funktion nicht mehr gültig). Deshalb muss das Objekt bei der Rückgabe kopiert werden (Copy-Konstruktor). Zusätzlich erfolgt beim Aufrufer noch eine Zuweisung, bei der die Attribute des Objekts vermutlich erneut kopiert werden. Dies kann (je nach Aufbau der Objekte) sehr teuer sein!


Die Rückgabe per Pointer erfordert ein Objekt, welches innerhalb der Funktion erzeugt wird und dessen Lebensdauer über das Funktionsende hinausreicht. Das Objekt muss in diesem Fall also auf dem Heap angelegt werden.

-   Vorteil: Die Rückgabe erfordert lediglich die Kopie der Adresse des Objekts (also des Pointers). Hier handelt es sich vereinfacht um einen Integer, d.h. diese Operation ist relativ preiswert.
-   Nachteil: Das Objekt muss vom Aufrufer wieder freigegeben werden, sobald es nicht mehr benötigt wird. Dies muss man explizit programmieren!


Die Rückgabe per C++-Referenz erfordert ebenfalls ein Objekt, welches innerhalb der Funktion erzeugt wird und dessen Lebensdauer über das Funktionsende hinausreicht. Das Objekt muss in diesem Fall also wieder auf dem Heap angelegt werden.

-   Vorteil: Die Rückgabe erfordert keinerlei Kopien, da sich die Referenz `x` an das Objekt `foo` bindet und lediglich einen neuen Alias für dieses Objekt darstellt.
-   Nachteil: Das Objekt muss vom Aufrufer wieder freigegeben werden, sobald es nicht mehr benötigt wird. Dies muss man explizit programmieren!


Es hat sich gezeigt, dass der Umgang mit den Heap-Ressourcen sehr fehleranfällig ist. Ein Aspekt dabei ist, dass man häufig die Freigabe der Objekte vergisst oder dass die Programmpfade so unübersichtlich sind, dass man nicht genau weiss, ob und wann man Objekte freigeben soll (denken Sie an Exceptions).


### Smartpointer als Lösung

Während man in Sprachen wie Java die Speicherverwaltung komplett dem Compiler überlässt oder wie in Rust mit strikten Ownership-Modellen arbeitet, hat man in C++ die sogenannten [Smartpointer](https://en.cppreference.com/book/intro/smart_pointers) erdacht. Diese ersetzen den direkten Umgang mit den einfachen Pointern (auch als *raw pointer* bezeichnet) und lösen das Problem der Freigabe der verwalteten Ressourcen.^[Dereferenzierung von Null-Pointern
oder nicht initialisierten Pointern, Nutzung von `delete` für Pointer, die nicht mit `new`
erstellt wurden, mehrfaches `delete`, Speicherlöcher durch Vergessen von `delete`, Dangling
Pointer, verwitwete Objekte, ...] Es gibt verschiedene Modelle, insbesondere gibt es die Variante *unique pointer*, bei der immer nur genau ein Smartpointer gleichzeitig die selbe Ressource besitzen darf, und die *shared pointer*, bei der mehrere Smartpointer gleichzeitig die selbe Ressource verwalten können. Sobald die Lebensdauer des *unique pointer* oder des letzten *shared pointer* endet, wird die verwaltete Ressource automatisch vom Smartpointer freigegeben.

Das folgende Beispiel arbeitet mit einer selbst implementierten Variante der *shared pointers*. Dabei ist die Klasse `SmartToken` ein Smartpointer für Objekte vom Typ `Token`:

```cpp
void fluppie() {
    SmartToken wuppie = SmartToken(new Token("wuppie", 1, 4));      // new smart pointer for token "wuppie": wuppie lives on the stack, the token lives on the heap (`new`)

    if (bla==42) {
        SmartToken fluppie = SmartToken(wuppie);                    // fluppie shares resource with wuppie
        SmartToken fluppie2(wuppie);                                // fluppie2 shares resource with wuppie
        // at this point there are 3 smart pointers sharing the same resource (token "wuppie")
        SmartToken foo = SmartToken(new Token("foo", 9, 35));       // new smart pointer for token "foo"
    }   // fluppie, fluppie2, foo will be removed from the stack - foo releases its resource

    // wuppie is the only smart pointer with shared resource "wuppie"

} // wuppie will be removed from the stack - wuppie releases its resource
```

Im Beispiel wird mit `new Token("wuppie", 1, 4)` ein neues Token-Objekt auf dem Heap angelegt. Der Smartpointer `wuppie` übernimmt die Ressource im Konstruktor und verwaltet den Pointer. Wichtig ist zu beobachten: Das Token wird auf dem Heap angelegt, während der Smartpointer `wuppie` eine normale lokale ("automatische") Variable ist und auf dem Stack liegt.

In der Kontrollstruktur werden weitere Smartpointer angelegt. Die ersten beiden (`fluppie`, `fluppie2`) teilen sich die Ressource (den Pointer auf das Token) mit `wuppie`. Es wird kein neues Token angelegt oder kopiert. Der dritte Smartpointer `foo` verwaltet ein weiteres Token.

Mit der Kontrollstruktur endet auch die Lebensdauer der lokalen Variablen `fluppie`, `fluppie2` und `foo`, sie werden automatisch vom Stack entfernt. Da `foo` der letzte Smartpointer ist, der das Token "foo" verwaltet, wird hier die Ressource freigegeben. Bei `fluppie` und `fluppie2` werden nur die Smartpointer auf dem Stack entfernt, die verwaltete Ressource (Token "wuppie") bleibt erhalten, da die noch von einem anderen Smartpointer verwaltet wird.

Mit dem Ende der Funktion endet auch die Lebensdauer des Smartpointers `wuppie`. Er wird automatisch vom Stack entfernt, und da er im Beispiel der letzte Smartpointer ist, der das Token "wuppie" verwaltet, wird dabei automatisch der Pointer zu "wuppie" wieder freigegeben.

Ein Smartpointer soll entsprechend folgende Eigenschaften haben:

-   Verwendung soll analog zu normalen Pointern sein (Operatoren `*` und `->` überladen)
-   Smartpointer haben niemals einen undefinierten Wert: entweder sie zeigen auf ein Objekt oder
    auf `nullptr`^[Sie müssen für `nullptr` den g++ auf C++11 oder höher umstellen (`--std=c++11`)
    und den Header `<cstddef>` includen.]
-   Kopieren von Smartpointern führt dazu, dass sich mehrere Smartpointer das verwiesene Objekt
    _teilen_
-   Smartpointer löschen sich selbst (und das verwiesene Objekt, falls kein anderer Smartpointer
    mehr darauf zeigt), wenn die Smartpointer ungültig werden (bei Verlassen des Scopes bzw. bei
    explizitem Aufruf von `delete`)
-   Es gibt keine verwitweten Objekte mehr: Wenn mehrere Smartpointer auf das selbe Objekt zeigen,
    darf erst der letzte Smartpointer das Objekt aus dem Heap löschen
-   Smartpointer funktionieren nur für mit `new` erzeugte Objekte

Weitere übliche Eigenschaften, die wir auf diesem Blatt außen vor lassen (Templates haben wir hier noch nicht behandelt, Exceptions werden wir gar nicht betrachten):

-   Smartpointer sollen für beliebige Klassen nutzbar sein (Template-Klasse)
-   Dereferenzierung von nicht existierenden Objekten (d.h. der Smartpointer zeigt intern auf
    `nullptr`) führt nicht zum Programmabsturz, sondern zu einer Exception

### Reference Counting

Smartpointer werden erzeugt, indem sie entweder einen Pointer auf die zu verwaltende Ressource bekommen (Konstruktor) oder eine Referenz auf ein anderes Smartpointer-Objekt (Copy-Konstruktor).

Im Smartpointer wird entsprechend der Pointer auf die zu verwaltende Ressource gespeichert.

Für die Bestimmung, wie viele Smartpointer sich eine Ressource teilen, muss ein Zähler implementiert werden. Sobald sich ein weiterer Smartpointer die Ressource teilt, muss dort auch der Zähler (per Pointer!) übernommen werden und entsprechend inkrementiert werden. Im Destruktor muss der Zähler dekrementiert werden. Falls dabei der Zähler den Wert 0 erreicht, werden die Pointer auf die Ressource und den Zähler freigegeben.

Bei einer Zuweisung verfährt man analog.

```cpp
class SmartToken {
public:
    /**
     * Constructor
     *
     * Constructs a new smart pointer from a raw pointer, sets the reference
     * counter to 1.
     *
     * @param p is a raw pointer to the token to be shared
     */
    SmartToken(Token* p = nullptr);

    /**
     * Copy constructor
     *
     * Constructs a new smart pointer from another smart pointer, increments
     * the reference counter.
     *
     * @param sp is another smart pointer
     */
    SmartToken(const SmartToken& sp);

    /**
     * Destructor
     *
     * Decrements the reference counter. If it reaches zero, the shared token
     * will be free'd.
     */
    ~SmartToken();

    /**
     * Assignment
     *
     * Changes the shared token, thus we need first to perform something like
     * the destructor, followed by something like the constructor.
     *
     * @param sp is another smart pointer
     */
    SmartToken& operator=(const SmartToken& sp);

private:
    Token* pObj;        ///< Pointer to the current shared token
    RefCounter* rc;     ///< Pointer to the reference counter (used for the current token)
};

class RefCounter {
public:
    /**
     * Default constructor
     */
    RefCounter();

    /**
     * Increment count
     */
    void inc();

    /**
     * Decrement count
     */
    void dec();

    /**
     * Compare the counter with zero
     *
     * @return true if n==0, false otherwise
     */
    bool isZero() const;

    // Hide copy constructor and assignment operator
    RefCounter(const RefCounter&) = delete;
    RefCounter& operator=(const RefCounter&) = delete;

private:
    unsigned int n;     ///< How many SmartToken share ownership of "our" object?
};
```

### Dereferenzierung von Smartpointern

(*Anmerkung*: Dies ist ein Vorgriff auf die Lektion "Operatoren". Betrachten und implementieren Sie die vorgegebenen Operatoren einfach wie normale Methoden.)

Pointer lassen sich dereferenzieren, d.h. man greift direkt auf das verwiesene Objekt zu. Dies lässt sich auch für Smartpointer erreichen, indem die beiden Dereferenzierungsoperatoren überladen werden.

```cpp
class SmartToken {
public:
    /**
     * Dereferences the smart pointer
     *
     * @return a reference to the shared token
     */
    Token& operator*();

    /**
     * Dereferences the smart pointer
     *
     * @return a pointer to the shared token
     */
    Token* operator->();
};
```

Damit lässt sich das folgende Verhalten realisieren:

```cpp
Token* foo = new Token("foo", 9, 35);
SmartToken wuppie = SmartToken(new Token("wuppie", 1, 4));

// Access via token pointer
cout << (*foo).lexem    << endl;    // "foo"
cout << foo->lexem      << endl;    // "foo"

// Access via smart pointer
cout << (*wuppie).lexem << endl;    // "wuppie"
cout << wuppie->lexem   << endl;    // "wuppie"
```

Dabei ist die Form "`->`" eine vereinfachte Darstellung von `(*ptr).`, d.h. ein Pointer (linke Seite des Ausdrucks) wird dereferenziert und man greift auf Attribute oder Methoden des verwiesenen Objekts zu (rechte Seite des Ausdrucks).




## Aufgaben

### A6.1: Klasse für Token (2P)

Implementieren Sie in C++ die Klasse `Token` mit der folgenden Schnittstelle:

```cpp
class Token {
public:
    /**
     * Constructs a new token object.
     *
     * @param l is a pointer to the text of the token (to be copied)
     * @param r is the row in input where this token was found
     * @param c is the column in input where this token starts
     */
    Token(const char* l, int r, int c);

    /**
     * Destructs the token object and free's the stored lexem.
     */
    ~Token();

private:
    char* lexem;    ///< Pointer to the text of the token
    int row;        ///< Row in input where this token was found
    int col;        ///< Column in input where this token starts
};
```

Trennen Sie Deklaration und Implementierung.

Der Konstruktor muss den übergebenen `char*` kopieren, d.h. Sie müssen die Länge des C-Strings bestimmen, ausreichend viel Speicher mit `new` reservieren und danach den String kopieren (C-Funktion).

Sorgen Sie dafür, dass der Speicher beim Vernichten eines Token-Objekts wieder korrekt freigegeben wird.

Bei Bedarf können Sie zusätzliche Attribute und Methoden hinzufügen.

Testen Sie Ihre `Token`-Klasse an selbst gewählten Beispielen.

### A6.2: Reference Counter (1P)

Implementieren Sie nun die Klasse `RefCounter` mit der obigen Schnittstelle. Auch hier können Sie bei Bedarf zusätzliche Attribute und Methoden hinzufügen.

Testen Sie Ihre `RefCounter`-Klasse an selbst gewählten Beispielen.


### A6.3: Smartpointer (3P)

Implementieren Sie nun die Smartpointer für `Token`-Objekte mit folgender Signatur (wie oben, leicht erweitert):

```cpp
class SmartToken {
public:
    /**
     * Constructor
     *
     * Constructs a new smart pointer from a raw pointer, sets the reference
     * counter to 1.
     *
     * @param p is a raw pointer to the token to be shared
     */
    SmartToken(Token* p = nullptr);

    /**
     * Copy constructor
     *
     * Constructs a new smart pointer from another smart pointer, increments
     * the reference counter.
     *
     * @param sp is another smart pointer
     */
    SmartToken(const SmartToken& sp);

    /**
     * Destructor
     *
     * Decrements the reference counter. If it reaches zero, the shared token
     * will be free'd.
     */
    ~SmartToken();

    /**
     * Assignment
     *
     * Changes the shared token, thus we need first to perform something like
     * the destructor, followed by something like the constructor.
     *
     * @param sp is another smart pointer
     */
    SmartToken& operator=(const SmartToken& sp);

    /**
     * Dereferences the smart pointer
     *
     * @return a reference to the shared token
     */
    Token& operator*();

    /**
     * Dereferences the smart pointer
     *
     * @return a pointer to the shared token
     */
    Token* operator->();

    /**
     * Comparison
     *
     * @param sp is another smart pointer
     * @return true, if `sp` shares the same token
     */
    bool operator==(const SmartToken& sp) const;

private:
    Token* pObj;        ///< Pointer to the current shared token
    RefCounter* rc;     ///< Pointer to the reference counter (used for the current token)
};
```


Bei Bedarf können Sie zusätzliche Attribute und Methoden hinzufügen.

Testen Sie Ihre `SmartToken`-Klasse an selbst gewählten Beispielen sowie an den obigen Beispielen.


### A6.4: Ringpuffer (4P)

Ein Ringpuffer ist eine Form der abstrakten Datenstruktur "Warteschlange" (_Queue_), die nur
eine beschränkte Anzahl $n$ von Elementen (Datensätzen) aufnehmen kann. Die Daten werden nach
dem FIFO-Prinzip über die Funktion `write()` am Ende der Schlange eingefügt und mit der Funktion
`read()` vom Anfang der Schlange entnommen.

Aus Effizienzgründen wird bei `read()` nur der Pointer auf das erste Element zurückgeliefert,
das gelesene Element wird aber (noch) nicht aus dem Ringpuffer entfernt. Über ein Attribut
`head` merkt man sich stattdessen, wo das nächste zu lesende Element liegt (auf dem Platz hinter
dem aktuell gelesenen). Ist der Puffer voll, wird bei `write()` das älteste Element entfernt und
das neue Element auf dem frei gewordenen Platz im internen Array `elems` eingefügt.

Der Ringpuffer soll Elemente vom Typ `T` (Template-Parameter) speichern. Es wird davon ausgegangen,
dass die Pointer mit einem Allocator vom Typ `alloc_t` angelegt wurden; entsprechend werden die
Elemente (Pointer) im Ringpuffer bei der Freigabe darüber auch wieder freigegeben.

Der Puffer kann effizient durch ein zur Laufzeit angelegtes **Array** mit `size` (Template-Parameter)
Plätzen zur Speicherung der Pointer auf die Elemente realisiert werden. Die Ringstruktur wird durch
Modulo-Operationen auf den Array-Indizes realisiert.



---

TODO: (S3) Smartpointer (ohne Templates - also für konkreten Typ oder mit void-Pointer??, und ohne Operatoren) => Big3 noch in die erste Sitzung nehmen wg. Zuweisung und Destruktor? War B08 in SP. ANWENDUNGSBEISPIEL geben!
Problem: Wir brauchen Klassen, Big3 und *Operatoren*. Templates könnte man durch feste Nutzlast ersetzen - vielleicht sowas wie MyString und statt der Operatoren Getter/Setter/Methoden?

TODO: (S5) Speicherverwaltung auf Java-Seite vorbereiten. War B04 in SP (übersetzung von new xyz()? - klassen als java-klassen, heap simulieren?)

