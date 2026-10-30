---
author: Carsten Gips (HSBI)
title: "L-Var: Scopes, Name-Resolver und Symboltabellen"
---

::: tldr
Auf die lexikalische Analyse und die Syntaxanalyse folgt die **semantische Analyse**.
Nach dem Parsen steht fest, dass ein Programm syntaktisch korrekt ist. Nun muss
geprüft werden, ob es auch semantisch korrekt ist. Dies umfasst in der Regel die
Identifikation und Sammlung von Bezeichnern und die Zuordnung zur richtigen Ebene
(Scopes). Außerdem muss die Nutzung von Symbolen validiert werden: Je nach Sprache
müssen beispielsweise Variablen und Funktionen vor ihrer Benutzung zumindest
deklariert sein; Funktionen sollten sich nicht wie Variablen benutzen lassen, ...

Als Werkzeug werden (hierarchische) Tabellen eingesetzt (die sogenannten **Symboltabellen**),
um die verschiedenen
Symbole und Informationen darüber zu verwalten. Wenn es in der zu
übersetzenden Sprache *Nested Scopes* gibt, spiegelt sich dies in den Symboltabellen
wider: Auch hier wird eine entsprechende hierarchische Organisation notwendig. In
der Regel nutzt man Tabellen, die untereinander verlinkt sind.

Eine wichtige Aufgabe ist das Binden von Bezeichner gleichen Namens an ihren
jeweiligen Scope =\> `bind()`. Zusätzlich müssen Symboltabellen auch das Abrufen von
Bezeichnern aus dem aktuellen Scope oder den Elternscopes unterstützen =\>
`resolve()`.
:::





# Was passiert nach der Syntaxanalyse?

::::: columns
::: {.column width="35%"}
``` clojure
(def x : int 1)
(def a : int 2)
(let ((b : int 3)
      (x : int 42))
  (+ a b)
  (let x (+ x a)))
```
:::

::: {.column width="60%"}
```
[Stmt]
  |- VarDecl "x" : INT = IntLiteral(1)
  |- VarDecl "a" : INT = IntLiteral(2)
  \- BlockStmt
     |- VarDecl "b" : INT = IntLiteral(3)
     |- VarDecl "x" : INT = IntLiteral(42)
     |- ExprStmt
     |    \- AddExpr
     |        |- VarExpr "a"
     |        \- VarExpr "b"
     \- AssignStmt
          |- VarExpr "x"
          \- AddExpr
              |- VarExpr "x"
              \- VarExpr "a"
```
:::

:::::


::: notes
**Welches `x` sprechen wir an in `(let x (+ x a))`?**

Nach der Syntaxanalyse braucht der Compiler für die darauf folgenden Phasen
**semantische Analyse**, Optimierung und Codegenerierung **Informationen über
Bezeichner**, z.B.

-   Welcher Bezeichner ist gemeint?
-   Welchen Typ hat ein Bezeichner?

Auf dem Weg zum Interpreter/Compiler müssen die Symbole im AST korrekt zugeordnet
werden. Dies geschieht über Symboltabellen. Im Folgenden werden wir verschiedene
Aspekte von Symboltabellen betrachten und eine mögliche Implementierung erarbeiten,
bevor wir uns in einer anderen Sitzung um die Auswertung (Interpretation) des AST kümmern können.
:::


# Syntax und Semantik

-   **Syntaxregeln**: Formaler Aufbau eines Programms

\smallskip

-   **Semantik**: Bedeutung eines (syntaktisch korrekten) Programms

\bigskip
\bigskip

=\> Keine Codegenerierung/Interpretation für syntaktisch/semantisch inkorrekte Programme!

::: notes
Zur Erinnerung: Die **Syntaxregeln** einer Programmiersprache bestimmen den _formalen
Aufbau_ eines zu übersetzenden Programms. Die **Semantik** gibt die _Bedeutung_ eines
syntaktisch richtigen Programms an.

Lexikalische und syntaktische Analyse können formalisiert mit regulären Ausdrücken
und endlichen Automaten (umgesetzt als Lexer/Scanner), sowie mit CFG und Parsern
durchgeführt werden.

Die Durchführung der semantischen Analyse ist stark von den Eigenschaften der zu
übersetzenden Sprache, sowie der Zielsprache abhängig und kann hier nur beispielhaft
für einige Eigenschaften erklärt werden.

Es darf kein lauffähiges Programm erstellt werden können, das nicht syntaktisch und
semantisch korrekt ist. Ein lauffähiges Programm muss syntaktisch und semantisch
korrekt sein!
:::

# Aufgaben der semantischen Analyse

-   Identifikation und Sammlung der Bezeichner
-   Zuordnung zur richtigen Ebene (Scopes)

\smallskip

-   Typ-Inferenz
-   Typkonsistenz (Ausdrücke, Funktionsaufrufe, ...)

\smallskip

-   Validieren der Nutzung von Symbolen
    -   Vermeidung von Mehrfachdefinition
    -   Zugriff auf nicht definierte Bezeichner
    -   (Lesender) Zugriff auf nicht initialisierte Bezeichner
    -   Funktionen werden nicht als Variablen genutzt
    -   ...

::: notes
Die semantische Analyse überprüft die Gültigkeit eines syntaktisch korrekten
Programms bzgl. statischer semantischer Eigenschaften und liefert die Grundlage für
die (Zwischen-) Codeerzeugung und -optimierung. Insbesondere wird hier die
Typkonsistenz (in Ausdrücken, von Parametern, ...) überprüft, und implizite
Typumwandlungen werden vorgenommen. Oft müssen Typen automatisch bestimmt werden
(z.B. bei Polymorphie, Typinferenz). Damit Typen bestimmt oder angepasst werden
können, müssen Bezeichner zunächst identifiziert werden, d.h. bei namensgleichen
Bezeichnern der richtige Bezug bestimmt werden.
:::

\bigskip
\bigskip

=\> [Ein wichtiges]{.notes} Hilfsmittel dazu sind **Symboltabellen**

::: notes
## Identifizierung von Objekten

Beim Compiliervorgang müssen Namen immer wieder den dazugehörigen Definitionen
zugeordnet, ihre Eigenschaften gesammelt und geprüft und darauf zugegriffen werden.
Symboltabellen werden im Compiler fast überall gebraucht.

Welche Informationen zu einem Bezeichner gespeichert und ermittelt werden, ist dann
abhängig von der Klasse des Bezeichners.

## Validieren der Nutzung von Symbolen

Hier sind viele Möglichkeiten denkbar. Dies reicht von den unten
aufgeführten Basisprüfungen bis hin zum Prüfen der Typkompatibilität bei
arithmetischen Operationen. Dabei müssen für alle Ausdrücke die Ergebnistypen
berechnet werden und ggf. automatische Konvertierungen vorgenommen werden, etwa bei
`3+4.1` ...

-   Zugriff auf Variablen: Müssen sichtbar sein (und definiert sein)
-   Zugriff auf Funktionen: Vorwärtsreferenzen sind OK
-   Variablen werden nicht als Funktionen genutzt
-   Funktionen werden nicht als Variablen genutzt

Vorgriff auf L-Fun: Da Funktionen oft bereits vor dem Bekanntmachen der Definition aufgerufen werden dürfen,
bietet sich ein **zweimaliger Durchlauf** (*pass*) an: Beim ersten Traversieren des
AST werden alle Definitionen in der Symboltabelle gesammelt. Beim zweiten Durchlauf
werden dann die Referenzen aufgelöst.

## Das Mittel der Wahl: Tabellen für die Symbole (= Bezeichner)

**Def.:** **Symboltabellen** sind die zentrale Datenstruktur zur Identifizierung und
Verwaltung von bezeichneten Elementen.

Die Organisation der Symboltabellen ist stark anwendungsabhängig. Je nach
Sprachkonzept gibt es eine oder mehrere Symboltabellen, deren Einträge vom Lexer
oder Parser angelegt werden. Die jeweiligen Inhalte jedes einzelnen Eintrags kommen
aus den verschiedenen Phasen der Compilierung. Symboltabellen werden oft als
Hashtables oder auch als Bäume implementiert, manchmal als verkettete Listen. In
seltenen Fällen kommt man auch mit einem Stack aus.

Eine Symboltabelle enthält benutzerdefinierte Bezeichner (oder Verweise in eine
Hashtable mit allen vorkommenden Namen), manchmal auch die Schlüsselwörter der
Programmiersprache. Die einzelnen Felder eines Eintrags variieren stark, abhängig
vom Typ des Bezeichners (= Bezeichnerklasse).

Manchmal gibt es für Datentypen eine Extra-Tabelle, ebenso eine für die Werte von
Konstanten.

Manchmal werden die Namen selbst in eine (Hash-) Tabelle geschrieben. Die
Symboltabelle enthält dann statt der Namen Verweise in diese (Hash-) Tabelle.
:::




# Symbole und (nested) Scopes


::::: columns
::: {.column width="35%"}
``` clojure
(def x : int 1)
(def a : int 2)
(let ((b : int 3)
      (x : int 42))
  (+ a b)
  (let x (+ x a)))
```
:::

::: {.column width="50%"}

```
    +------------------------------+
    |     GLOBAL SCOPE             |
    +------------------------------+
    | symbols = [x : int, a : int] |
    +------------------------------+
                   ^
                   |
    +------------------------------+
    |     LOCAL SCOPE              |
    +------------------------------+
    | symbols = [b : int, x : int] |
    +------------------------------+
```
:::

:::::

\bigskip

**Aufgaben**:

-   `bind()`: Symbole [im Scope]{.notes} definieren
-   `resolve()`: Symbole [aus Scope oder Eltern-Scope]{.notes} abrufen

::: notes
Scopes können ineinander verschachtelt sein. Die Spezifikation der zu übersetzenden
Sprache legt fest, in welcher Reihenfolge Scopes zu durchsuchen sind, wenn auf einen
Bezeichner Bezug genommen wird, der nicht im aktuellen Scope definiert ist.

Insgesamt bilden die Scopes oft eine Baumstruktur, wobei jeder Knoten einen Scope
repräsentiert und seine Kinder die direkt in ihm enthaltenen Scopes sind. Dabei ist
es in der Regel so, dass Scopes sich entweder vollständig überlappen oder gar nicht.
Wenn ein Bezeichner nicht im aktuellen Scope vorhanden ist, muss er in der Regel
entlang der Verkettung nach "oben" zum "Elternscope" gesucht werden.

Im Beispiel würden wir im innersten Scope für `(let x (+ x a))` die Namen `x` und `a`
auflösen müssen. Das `x` finden wir direkt im aktuellen (innersten) Scope, während das
`a` hier nicht zu finden ist. Deshalb muss hier auf der Suche nach diesem Namen zum umschließenden
Elternscope gewechselt werden und dort gesucht werden. Dies wiederholt sich bei Bedarf rekursiv bis
zur Wurzel, also bis zum globalen Scope. Wenn der Bezeichner dann immer noch nicht gefunden werden
kann, ist dies ein Fehler (Zugriff auf ein nicht definiertes Symbol).

Dieses Verhalten nennt man auch **lexikalische Namensauflösung**.
:::


# Symboltabelle für Nested Scopes

```java
public record Scope(Scope parent, HashMap<String, Decl> symbols) {

    public void bind(String name, Decl symbol) {
        if (symbols.containsKey(name))
            throw new RuntimeException("name already defined: " + name);
        symbols.put(name, symbol);
    }

    public Decl resolve(String name) { return resolve(name, 0).decl; }
    public Resolution resolve(String name, int depth) {
        Decl decl = symbols.get(name);
        if (decl != null) return new Resolution(decl, depth);
        if (parent != null) return parent.resolve(name, depth + 1);
        throw new RuntimeException("undefined name: " + name);
    }

    public record Resolution(Decl decl, int depth) {}
}
```

::: notes
## Implementierung mit hierarchischen (verketteten) Tabellen

Pro Scope wird eine Symboltabelle `Scope` angelegt, dabei enthält jede Symboltabelle
zusätzlich einen Verweis auf ihre Vorgängersymboltabelle für den umgebenden Scope.
Die globale Symboltabelle hat keinen Vorgänger, hier kann man `null` als `parent` nutzen.

::: tip
Streng genommen ist die Klasse `Scope` eine Modellierung für den Scope, und das Feld
`HashMap<String, Decl> symbols` ist die eigentliche Symboltabelle.

"Scope" ist streng genommen ein logischer Sichtbarkeitsbereich für Namen, und eine
Symboltabelle ist einem Scope zugeordnet und speichert Namen und die zugehörige Definition.

Wir werden die beiden Begriffe "Scope" und "Symboltabelle" synonym verwenden, solange
die Bedeutung eindeutig ist.
:::

::: tip
Es gibt Modellierungen wie beispielsweise [@Parr2010, p. 142], die für die zu
speichernden Elemente mit einem Namen (Variablen, Funktionen, Klassen, ...) eine
elaborierte Klassenstruktur vorsehen. Wir werden stattdessen ausgewählte AST-Knoten
zu einem Namen speichern. Das wird bei Klassen etwas umständlicher, dafür müssen
wir nicht wie bei [@Parr2010] eine ausgeprägte zusätzliche Klassenhierarchie pflegen.
:::

## Speichern von Symbolen

**Welche AST-Knoten wollen/müssen wir speichern?**

Es geht eigentlich nur darum, für jeden **Namen** denjenigen **Scope** festzuhalten, in dem dieser
**Name definiert** wird. Entsprechend wollen wir gar nicht _alle_ AST-Knoten festhalten, sondern
nur die `*Decl`-Klassen im AST. Um dies typsicher zu gestalten, fügen wir ein weiteres Interface
`Decl` hinzu:

```java
public interface Decl {
    String name();
}
```

und markieren die relevanten AST-Klassen damit:

```java
public record VarDecl(String name, Type type, Expr init) implements Stmt, Decl {}
```

In L-Var betrifft das nur die `VarDecl`! (Später werden wir in L-Fun für Funktionsdefinitionen
und in L-Class für Klassendefinitionen analog arbeiten.)

## Vorgehen bei der Namensauflösung

Wir legen also für die Namensauflösung initial einen globalen Scope an, und starten die Traversierung des AST an dessen
Wurzel. Sobald wir dabei
einen neuen Scope betreten,
legen wir einen neuen Kindscope an und setzen diesen Scope als den aktuellen (Arbeits-) Scope - wir haben also einen lokalen
Scope betreten. Das kann in L-Var nur bei `let`-mit-Scopes passieren (also beim Betreten eines
`BlockStmt`-AST-Knotens). Später werden wir noch andere Sprachfeatures kennenlernen, die einen neuen Scope öffnen.

Beim Verlassen eines `BlockStmt`-AST-Knotens nach oben im Baum (alle Kinder des `BlockStmt`-Knotens wurden also besucht)
wird der aktuelle Scope auf den Elternscope des bisherigen aktuellen Scopes gesetzt - wir verlassen den lokalen Scope und
befinden uns wieder im umgebenden Elternscope.

Wann immer beim Traversieren des AST ein `VarDecl`-Knoten besucht wird, tragen wir dessen Namen (also den Namen
der Variablen) und den
AST-Knoten (die Definition dieser Variablen, also ihre `VarDecl`) mit `bind()` in die aktuelle Symboltabelle (in den aktuellen Scope)
ein.

::: tip
Ein mehrfaches Eintragen im selben Scope bedeutet
in Lispy einen semantischen Fehler. Es gibt andere Sprachen, die eine wiederholte Definition im selben Scope erlauben.
TODO: Beispiel!
:::

Wenn wir umgedreht einen Namen suchen, etwa beim Abarbeiten eines `VarExpr`-Knotens im AST, suchen wir diesen Namen
mit `resolve()` im aktuellen Scope. Wenn wir den Namen hier finden, ist diese Variablen in diesem Scope definiert und wir
können mit der Abarbeitung fortfahren. Anderenfalls versuchen wir den Namen rekursiv über die Elternscopes aufzulösen. Erst, wenn
wir den Namen nicht finden können, liegt in Lispy ein Fehler vor.

::: tip
Es gibt Sprachen wie Javascript, die Probleme beim Auflösen von Namen nicht als Fehler betrachten und dann on-the-fly diesen Namen
einfach neu definieren.
:::

::: important
Wir haben die `resolve()`-Methode vorsorglich bereits überladen mit einer Variante `Resolution resolve(String name, int depth)`. Diese zählt
mit, wie viele Schritte beim Auflösen nach "oben" gegangen wurde und liefert den gefundenen AST-Knoten und die Tiefe (Anzahl der Schritte)
als Tupel `Resolution` zurück. Das spart uns später im Interpreter das erneute Suchen der Namen ...
:::
:::


# Name-Resolver - lexikalische Auflösung von Namen


::: notes
## Aufgaben vom Name-Resolver

Wir wollen mit dem `NameResolverLvar` prüfen, ob alle Namen (in L-Var nur Variablen) korrekt verwendet wurden.

Insbesondere dürfen in L-Var Variablen in einem Scope nicht mehrfach definiert werden (`VarDecl`). Eine Definition in einem
lokalen Scope darf aber die Definition einer Variable in einem der Elternscopes überdecken (*shadowing*).

Beim lesenden Zugriff auf eine Variable per `VarExpr` müssen wir sicherstellen, dass diese Variable von dem aktuellen
Scope aus sichtbar ist. Sie kann also entweder im selben Scope definiert sein, oder in einem der von diesem Scope aus
erreichbaren Elternscopes.

Beim schreibenden Zugriff auf eine Variable in `AssignStmt` müssen wir ebenfalls prüfen, ob sie sichtbar ist.

Jeder Block (`BlockStmt`) öffnet einen neuen localen Scope, wobei der bisherige Scope der Elternscope wird. Am Ende
des Blockes müssen wir unseren aktuellen Scope dann wieder zurücksetzen.
:::

```java
public class NameResolverLvar {
    public Scope scope = new Scope();  // global scope
    public Map<Stmt, Scope> symbols = new IdentityHashMap<>();
    public Map<VarExpr, Integer> depths = new IdentityHashMap<>();

    public void resolve(List<Stmt> stmts) {
        stmts.forEach(this::resolve);
    }

    // protected void resolve(Stmt stmt) ...
    // protected void resolve(Expr expr) ...
}
```

::: notes
## Hilfsvariablen / Felder

Der Name-Resolver braucht eine Hilfsvariable `Scope scope`, um sich bei der Traversierung den aktuellen Scope zu merken.
Beim Start initialisieren wir diesen einmal, d.h. initial ist `scope` der globale Scope.

Beim Auflösen von Namen berechnen wir jeweils, wo wir diesen
Namen in Bezug zum aktuellen Scope gefunden haben, d.h. wir berechnen die Anzahl der Schritte vom aktuellen Scope zu
den Elternscopes hoch. Eine "0" bedeutet, dass wir den Namen im aktuellen Scope gefunden haben, "1" wäre dann der direkte
Elternscope, usw. Diese Information wollen wir für den Interpreter speichern. Dazu legen wir das Feld
`Map<VarExpr, Integer> depths` an.

::: important
Wir speichern in der `Map<VarExpr, Integer> depths` zu `VarExpr`-Objekten (also unseren Variablen) die Suchtiefe.

Unsere Modellierung nutzt
für  `VarExpr` die Record-Klassen aus Java, d.h. hier wird vom Compiler/Laufzeitsystem automatisch eine `equals()`- und
`hashCode()`-Implementierung bereitgestellt. Wenn wir eine einfache `HashMap` nehmen würden, würden zwei unterschiedliche
`VarExpr`-Objekte mit dem selben Inhalt als gleich betrachtet und entsprechend in der Map zusammenfallen.

Wir können aber im AST in unterschiedlichen Scopes Referenzen auf die selbe Variable haben bzw. sogar mit dem selben Namen
auf unterschiedliche Variablen in unterschiedlichen Scopes verweisen (*shadowing*).
D.h. wir haben deshalb unterschiedliche `VarExpr`-Objekte im AST, die aber über die automatische `equals()`- und
`hashCode()`-Implementierung für die Record-Klassen bei gleichem Variablennamen in einer normalen `HashMap` als gleich
betrachtet würden. Damit wir diese Objekte in der Map unterscheiden können (wir wollen ja zu jeder konkreten Verwendung einer Variablen
die entsprechend dort gültige Suchtiefe speichern), nutzen wir als Implementierung eine
`IdentityHashMap`, die auf die Objekt-ID  schaut.
:::

Wir bauen bei der Traversierung des AST die Symboltabellenstruktur auf. Jeder lokale Scope kennt seinen Elternscope,
d.h. die Verzeigerung geht im Baum von unten nach oben. Sobald wir einen lokalen Scope nach oben verlassen, würden wir deshalb
nicht mehr auf diesen Scope zugreifen können. Das ist im Name-Resolver nicht weiter relevant, aber wir werden später noch weitere
Passes über den AST aufbauen, die den Zugriff auf den korrekten Scope bzw. die in einem Scope geltende Symboltabelle benötigen.
Damit wir dann die Symboltabellenstruktur nicht erneut aufbauen müssen, speichern wir für jedes Statement einfach den
Scope (bzw. die Symboltabelle), die zu dem Zeitpunkt des Besuchs dieses Statements galt. Dafür nutzen wir das Feld `Map<Stmt, Scope> symbols`.

::: tip
Wer genau hinschaut, wundert sich über die Sichtbarkeit der Felder im `NameResolverLvar`: Diese steht auf `public`, was
in der objektorientierten Programmierung unüblich ist. Der Hintergrund dafür ist, dass wir auf diese drei Felder später
Zugriff brauchen - aber wir können in der Einstiegsmethode `resolve(List<Stmt> stmts)` leider nur ein Ergebnis zurückliefern
und nicht alle drei ... Wir werden das Problem weiter unten über eine **Sidetable** lösen.
:::


## Ablauf

Wir starten mit dem globalen Scope und laufen den AST in Form der als Parameter übergebenen Liste der Statements ab.
Für jedes Statement müssen wir den Auflösevorgang  anstoßen, d.h. für jedes `Stmt` im übergebenen AST wird `resolve(stmt)`
aufgerufen.

Hier müssen wir die einzelnen Statemtent-Typen unterscheiden und entsprechend agieren (s.u.). Expressions tauchen nicht
als eigenständiges Element in L-Var-Programmen auf, sondern nur als Teile von Statements. Beim Besuchen der Statements
müssen wir entsprechend jeweils auch das Auflösen per `resolve(expr)` anstoßen (s.u.)
:::


# Name-Resolver - Traversierung für Statements (Ausschnitt)

::: notes
Der Name-Resolver iteriert in der Einstiegsmethode über alle übergebenen Statements und ruft für jedes Statement
`resolve(stmt)` auf.

Nun müssen wir unterscheiden, um welchen `Stmt`-Knoten im AST es sich jeweils handelt und die weitere Traverierung
anstoßen. Dies könnten wir über das Visitor-Pattern machen - da wir unseren AST mit Record-Klassen modelliert haben,
können wir hier auch komfortabel die Traversierung über `switch`-Expressions und Pattern Matching erledigen.

Erinnerung an die abstrakte Syntax in L-Var (nur der Teile der `Stmt`-Regel gezeigt):
:::


```ebnf
Stmt = VarDecl(String, Type, Expr) | BlockStmt([Stmt]) | ...
```


```java
protected void resolve(Stmt stmt) {
    symbols.put(stmt, scope);

    switch (stmt) {
        case VarDecl(var name, var type, var init) -> {
            resolve(init);  resolveType(type);
            scope.bind(name, (VarDecl) stmt);
        }
        case BlockStmt(var s) -> {
            scope = new Scope(scope);
            s.forEach(this::resolve);
            scope = scope.parent();
        }
        default -> throw new RuntimeException("unexpected statement: " + stmt);
    }
}
```

::: notes

**Wichtig**: In der Skizze oben ist nur ein Ausschnitt gezeigt - die Verarbeitung von `ExprStmt` und `AssignStmt` bleiben als Challenge oder
Hausaufgabe.

## Variablen-Definition

Ein `VarDecl`-Statement besteht aus einem Variablennamen (Typ `String`), einem Typ in unserer Lispy-Sprache (Typ `Type`)
und einer Expression für die Initialisierung (Typ `Expr`).

Wir müssen im Name-Resolver prüfen, ob es diesen Typ wirklich gibt
und dieser vom aktuellen Scope aus sichtbar ist, d.h. wir rufen `resolveType(type)` auf.

::: tip
In L-Var gibt es zunächst nur den "eingebauten" Typ `int` in Lispy. Hier müssen wir nichts prüfen bei der Namensauflösung.

```java
protected void resolveType(Type type) {} // nothing to do here
```

Wir werden aber später kennenlernen, wie man in Lispy Klassen definiert (Sprachstufe L-Class). Diese nutzerdefinierten
Klassen sind eigene Typen, die dynamisch im AST auftauchen. Dann müssen wir entsprechend prüfen, ob der Typname in der `VarDecl`
tatsächlich sichtbar ist und ein Klassentyp ist - deshalb legen wir uns hier vorausschauend eine **Hook-Methode** `resolveType(Type type)`
an. Da  wir in L-Var nichts tun müssen, bleibt diese Hook-Methode erstmal leer - später in L-Class werden wir diese geeignet
überschreiben.
:::

Die Initialisierung der Variablen ist eine Expression, d.h. dort können Verweise auf andere Variablen vorkommen. Entsprechend
rufen wir hier `resolve(init)` auf.

Danach können wir dann die neue Variable "binden": Wir legen für den Variablennamen im aktuellen Scope eine Referenz auf den
`VarDecl`-Knoten an. Das `bind()` prüft dabei, ob es für diesen Namen noch keinen Eintrag gibt. Damit wissen wir, dass die
Variable korrekt definiert wurde: Sie wurde bisher noch nicht in diesem Scope definiert, und der angegebene Typ ist sichtbar
(später, in L-Class) und in der Initialisierungs-Expression sind alle Variablennamen vom aktuellen Scope aus sichtbar. Wenn
wir später auf diesen Variablennamen verweisen (etwa in einer `VarExpr), dann können wir ihn rekursiv über die Scopes hier im
aktuellen Scope finden (sofern die Kette passt).

::: important
Es spielt eine große Rolle, in welcher Reihenfolge man den Initialisierungsausdruck und die neue Variable bearbeitet!

Was würde passieren, wenn man zuerst die Variable bindet und danach die Initialisierung auswertet? (siehe Challenge)
:::


## BlockStmt

Ein `BlockStmt` wurde in L-Var für ein `let`-mit-Scope angelegt.
Es öffnet einen neuen lokalen Scope, in dem die im `BlockStmt` gespeicherten Statements ausgewertet werden sollen.

Entsprechend legen wir einen neuen Scope an und nutzen als Elternscope den aktuellen Scope. Der neue Scope wird der aktuelle
Scope. Dann iterieren wir über die Statements des `BlockStmt` und führen hier die Namensauflösung durch. Am Ende setzen wir den
aktuellen Scope wieder auf den vorigen Scope zurück.

## Besonderheiten

Wir haben damit alle in L-Var bekannten AST-Knoten vom Typ `Stmt` besucht (`ExprStmt` und `AssignStmt` seien noch hinzugefügt).
Wenn wir hier über einen anderen `Stmt`-Knoten laufen würden, wäre das ein Fehler - das wäre ein Statement aus einer späteren
Sprachstufe!

Der Name-Resolver baut die Scope-Strukturen und damit die Symboltabellen während der AST-Traversierung auf und wieder ab.
Wir werden später in L-If  einen Type-Checker hinzufügen, der als zweiter Pass nach dem Name-Resolver noch einmal über
den AST läuft und  die Typen prüft. Hier brauchen  wir für jedes Statement erneut den Scope bzw. die Symboltabelle, die
für dieses Statement relevant ist. Damit wir die Symboltabellen  dann nicht erneut aufbauen müssen, speichern wir einfach
diese Information am Anfang von `resolve(stmt)` im Feld `symbols`.
:::


# Name-Resolver - Traversierung für Expressions (Ausschnitt)

::: notes
In Lispy können Expressions als Teil von Statements vorkommen. In `resolve(stmt)` haben wir beispielsweise die `VarDecl`
bearbeitet und für die Initialisierungs-Expression `resolve(expr)` aufgerufen.

Erinnerung an die abstrakte Syntax in L-Var (nur ein kleiner Teil der `Expr`-Hierarchie gezeigt):
:::

```ebnf
Expr = IntLiteral(Int) | AddExpr(Expr, Expr) | VarExpr(String)
```


```java
protected void resolve(Expr expr) {
    switch (expr) {
        case IntLiteral _ -> {} // nothing to do

        case AddExpr(var l, var r) -> List.of(l, r).forEach(this::resolve);

        case VarExpr e -> {
            var res = scope.resolve(e.name(), 0);
            depths.put(e, res.depth());
        }

        default -> throw new RuntimeException("unexpected expression: " + expr);
    }
}
```

::: notes
**Wichtig**: In der Skizze oben ist nur ein Ausschnitt gezeigt - die Verarbeitung von `SubExpr`, `MulExpr` und `DivExpr` bleiben als Challenge oder
Hausaufgabe.

## Integer-Literal

In einem `IntLiteral` speichern wir nur einen Integerwert, keine weiteren Namen. Dieser Knoten stellt ein Blatt im AST dar.
Deshalb brauchen wir hier nichts tun.

## Addition

Ein `AddExpr`-Knoten hat zwei Kinder, die wiederum Expressions sind. Für beide Kinder stoßen wir die rekursive Namensauflösung
an. Mehr ist hier nicht zu tun.

## Lesender Variabenzugriff

Eine `VarExpr` ist ein Verweis auf einen Variablennamen in einer Expression, beispielsweise `x` in `(+ x 2)`. Dies sind lesende
Zugriffe, d.h. der Variablenname muss vom aktuellen Scope aus sichtbar sein.

Wir rufen entsprechend auf dem aktuellen Scope ein `resolve()` für den Namen auf. Wenn die Variable in diesem Scope oder in einem
der darüber erreichbaren Elternscopes gebunden wurde, bekommen wir als Ergebnis den definierenden AST-Knoten (eine `VarDecl`) sowie
die Tiefe (Anzahl der Schritte vom aktuellen Scope aus) zurück - anderenfalls wirft `Scope#resolve()` einen Fehler. Die Tiefe
speichern wir für den Interpreter in unserem Feld `depths`.

## Besonderheiten

Wie bei `resolve(stmt)` haben wir damit alle in L-Var bekannten AST-Knoten vom Typ `Expr` besucht (`SubExpr`, `MulExpr` und `DivExpr` seien noch hinzugefügt).
Wenn wir hier über einen anderen `Expr`-Knoten laufen würden, wäre das ein Fehler - das wäre eine Expression aus einer späteren
Sprachstufe!
:::




# Implementierungsdetail: Sammeln der Daten in einer Sidetable

::: notes
Wir haben im `NameResolverLvar` einige auf `public` gestellte Felder gesehen:
`Scope scope`,  `Map<Stmt, Scope> symbols` und `Map<VarExpr, Integer> depths`. Hier werden bei der Traversierung
des AST im Name-Resolver Daten gesammelt, die in späteren AST-Passes (Type-Checker, Interpreter) relevant sind.

Wir werden in späteren Sprachstufen noch weitere Daten sammeln, beispielsweise Typ-Informationen oder Informationen
für die statische Namensauflösung.

Im `NameResolverLvar` haben wir diese Felder selbst initialisiert. Dies ist einerseits aus SWE-Sicht ungünstig
(schlechte Testbarkeit), andererseits werden wir später den Bedarf haben, "vordefinierte" Namen im globalen Scope anzulegen, bevor
der Resolver oder irgendein anderer Pass die Arbeit aufnimmt.

Deshalb bietet es sich an, diese Daten in ein gemeinsames Objekt zu kapseln, die sogenannte **Sidetable**. Dieses
Objekt wird extern initialisiert und an jeden Pass als Input gegeben. Die Passes können die relevanten Informationen
aus dem Sidetable benutzen und ergänzen und am Ende des Durchlaufs die aktualisierte Sidetable zurückgeben.

Wir definieren  als Sidetable hier die Klasse `SemaInfo`:
:::

```java
public class SemaInfo {
    public Scope globalScope = new Scope();
    public Map<Stmt, Scope> symbols = new IdentityHashMap<>();
    public Map<VarExpr, Integer> depths = new IdentityHashMap<>();
}

```

::: notes
`SemaInfo` sammelt alle derzeit relevanten Ergebnisse der semantischen Analyse. In späteren Sprachstufen werden
wir noch weitere Felder hinzufügen.

Die `SemaInfo` ist eine reine "Datenklasse" - wir haben wir nur eine Aggregierung von Feldern und kein Verhalten,
weshalb die Felder der Einfachheit alle `public` sind.

Damit können wir unseren `NameResolverLvar` anpassen:
:::

``` java
public class NameResolverLvar {
    protected SemaInfo sema;
    protected Scope scope;

    public SemaInfo resolve(List<Stmt> stmts, SemaInfo semaInfo) {
        sema = semaInfo;  scope = sema.globalScope;
        stmts.forEach(this::resolve);
        return sema;
    }
    // protected void resolve(Stmt stmt) ...
    // protected void resolve(Expr expr) ...
}
```

::: notes
Wir behalten das lokale Feld `scope` - das ist der aktuelle Scope beim Traversieren, das hat nichts mit dem Sidetable
zu tun. Die anderen beiden Felder `symbols` und `depth` wandern in den Sidetable, den wir als neues Feld
`SemaInfo sema` festhalten.

Entsprechend sind im obigen Code in den `resolve()`-Methoden noch zwei weitere Änderungen notwendig:

1. In `resolve(Stmt stmt)` würden wir dann entsprechend `sema.symbols.put(stmt, scope);` ausführen
(statt wie oben `symbols.put(stmt, scope);`).
2. Zusätzlich müssten wir in `resolve(Expr expr)` noch
`sema.depths.put(e, res.depth());` (statt `depths.put(e, res.depth());`, in `case VarExpr e`) ändern.

:::


# Wrap-Up

-   **Semantische Analyse**: Traversierung des AST [(oft zwei Passes über den AST notwendig)]{.notes}
    -   Identifikation und Sammlung der Bezeichner
    -   Zuordnung zur richtigen Ebene (Scopes)
    -   Validieren der Nutzung von Symbolen
    -   Später:
        -   Typ-Inferenz
        -   Typkonsistenz (Ausdrücke, Funktionsaufrufe, ...)

\smallskip

-   **Symboltabellen**: Verwaltung von Symbolen und Typen [(Informationen über
    Bezeichner)]{.notes}
    -   Blöcke: Nested Scopes =\> hierarchische Organisation
    -   Binden von Bezeichner gleichen Namens an ihren jeweiligen Scope =\> `bind()`
    -   Abrufen von Bezeichnern aus dem aktuellen Scope oder den Elternscopes =\>
       `resolve()`





::: readings
Zur Namensauflösung kann man in [@Nystrom2021] kann man in Kapitel 11 "Resolving and Binding" nachlesen.
Dabei behandelt [@Nystrom2021] die Verbindung zwischen Name-Resolver und Interpreter technisch anders, aber
das Grundprinzip der Namensauflösung ist ähnlich wie hier gezeigt.

Wir haben für unsere Symboltabellen die bereits vorhandenen AST-Knoten benutzt, um die Anzahl der Klassen möglichst
übersichtlich zu halten. In [@Parr2010] (Kapitel 6, 7 und 8)
wird eine "ordentliche" Symbols-Klassenstruktur entwickelt und für die Namensauflösung eingesetzt. Die Grundprinzipien
sind wie in diesem Skript gezeigt, aber die separate Klassenstruktur bringt gewisse Vorteile mit sich.
:::

::: outcomes
-   k2: Ich kann die Aufgaben der semantischen Analyse an einem Beispiel erklären
-   k2: Ich kann die Bedeutung von Symboltabellen erklären und die Aufgaben und
    Verbindung zu den Compiler-Phasen verdeutlichen
-   k3: Ich kann Symboltabellen für Nested Scopes implementieren unter Nutzung von
    passenden Strukturen/Klassen und einem Listener
-   k3: Ich kann Symbole über die Scopes auflösen
-   k3: Ich kann einfache statische Prüfungen anhand der Symboltabellen durchführen
:::

::: challenges
**Lexikalisches Auflösen von Namen**

Betrachten Sie dieses L-Var-Programm:

``` clojure
(def x : int 10)
(def y : int 20)
(let ((x : int 1))
  (+ x y)
(let ((y : int 2))
  (+ x y))
```

-   Zeichnen Sie den **Scope-Baum** (statisch).
-   Notieren Sie für jede `VarExpr` (`x` und `y`):
    -   Auf welche `VarDecl` zeigt sie?
    -   Welchen `depth`-Wert würde der Resolver berechnen?
-   Skizzieren Sie, wie `sema.depths` für diese Variable-Expressions aussehen
    würde.

**resolve(stmt)**

Wir haben oben einige Statements ausgelassen. Vervollständigen Sie `void resolve(Stmt stmt)` nun
für  `ExprStmt` und `AssignStmt`.

**resolve(expr)**

Wir haben oben einige Expressions ausgelassen. Vervollständigen Sie `void resolve(Expr expr)` nun
für  `SubExpr`, `MulExpr` und `DivExpr`.


**resolve(VarDecl)**

Es spielt eine große Rolle, in welcher Reihenfolge man beim Bearbeiten eines `VarDecl`-Knotens
den Initialisierungsausdruck und die neue Variable bearbeitet!

Was würde passieren, wenn man zuerst die Variable bindet und danach die Initialisierung auswertet?



**Grenzen der semantischen Analyse**

Welche semantischen Eigenschaften [einer Sprache]{.notes} kann die semantische
Analyse nicht überprüfen?

-   Wer ist dann dafür verantwortlich?
-   Wie äußert sich das im Fehlerfall?

<!--
Dinge, die erst durch eine Ausführung/Interpretation eines Programms berechnet
werden können.

Beispielsweise können Werte von Ausdrücken oft erst zur Laufzeit bestimmt werden.
Insbesondere kann die semantische Analyse in der Regel nicht feststellen, ob ein
Null-Pointer übergeben wird und anschließend dereferenziert wird.
-->

:::
