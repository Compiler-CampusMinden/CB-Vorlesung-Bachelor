---
author: Carsten Gips (HSBI)
title: "L-Var: Interpreter mit Environments und Statements"
---

::: tldr
TODO

Für Blöcke und Variablen muss man analog zum Aufbau von Symboltabellen wieder Scopes
berücksichtigen, d.h. man benötigt Strukturen ähnlich zu den Symboltabellen (hier
"Umgebung" (*Environment*) genannt). Es gibt eine globale Umgebung, und mit dem
Betreten eines neuen Blocks wird eine neue Umgebung aufgemacht, deren
Eltern-Umgebung die bisherige Umgebung ist.

Zu jedem Namen kann man in einer Umgebung einen Wert definieren bzw. abrufen. Dabei
muss man je nach Semantik der zu interpretierenden Sprache unterscheiden zwischen
der "Definition" und der "Zuweisung" einer Variablen: Die Definition erfolgt i.d.R.
in der aktuellen Umgebung, bei der Zuweisung sucht man ausgehend von der aktuellen
Umgebung bis hoch zur globalen Umgebung nach dem ersten Vorkommen der Variablen und
setzt den Wert in der gefundenen Umgebung. Bei Sprachen, die Variablen beim ersten
Zugriff definieren, muss man dieses Verhalten entsprechend anpassen.

-   Verständnis des `Environment`-Konzepts zur Laufzeit
-   Interpreter-Erweiterung für Statements (`exec`)
-   Variable-Lesen als Expression (`VarExpr`)
-   Scopes im Interpreter modellieren
:::

# Erinnerung: Interpreter für L-Expr

``` java
public class InterpreterLexpr extends InterpreterLint {

    @Override
    public Value eval(Expr expr) {
        return switch (expr) {
            case MulExpr(var l, var r) -> {
                int a = Value.asInt(eval(l));
                int b = Value.asInt(eval(r));
                yield new IntVal(a * b);
            }

            default -> super.eval(expr);
        };
    }
}
```

::: notes
Wir hatten eine Methode `Value eval(Expr expr)` zum Auswerten von Ausdrücken
(Expressions) definiert. Da der `InterpreterLexpr` von `InterpreterLint` ableitet,
überschreiben wir diese Methode. Wir müssen nur die neuen Auswertungen ergänzen, und
für die bisherigen Fälle rufen wir einfach `super.eval(expr)` auf.

Diese werden wir in L-Var wie gewohnt mit weiteren Ausdrücken ergänzen.

Aber wir haben in L-Var zusätzlich noch Anweisungen (Statements), die bei der
Auswertung keinen Wert liefern. Die Statements können wir ähnlich auswerten wie die
Expressions, aber wir brauchen noch ein Konzept, wie wir mit dem Zustand umgehen ...
:::

# Zustände: Auswerten von Anweisungen

::::: columns
::: column
``` clojure
(def x : int 1)
(let ((a : int 2)
      (b : int 3))
  (+ a b)
  (let x (+ x b)))
```
:::

::: column
    +-------------------+
    |    GLOBAL ENV     |
    +-------------------+
    | values = [x : 1]  |
    +-------------------+
              ^
              |
              |
    +-------------------+
    |    LOCAL ENV      |
    +-------------------+
    | values = [a : 2,  |
    |           b : 3]  |
    +-------------------+
:::
:::::

::: notes
Das erinnert nicht nur zufällig an den Aufbau der Symboltabellen :-)

Und so lange es nur um Variablen ginge, könnte man die Symboltabellen (`Scope`)
erweitern und für das Speichern der Werte nutzen. Allerdings müssen wir noch
Funktionen und Strukturen bzw. Klassen realisieren, und spätestens dann funktioniert
diese Idee nicht mehr! (vgl. Challenge)

Also lohnt es sich, direkt neue Strukturen für das Halten von Variablen und Werten
aufzubauen.
:::

# Environments - Laufzeit-Sicht auf Scopes

::: notes
Wir benötigen analog zu `Scope` eine Datenstruktur, die einen Verweis auf das
Eltern-Environment hat und die zu einem Namen Werte (also `Value` statt `Decl` wie
in `Scope`) speichert. Nachfolgend die Kernfunktionalität (unvollständig):
:::

``` java
public record Env(Env parent, Map<String, Value> values) {

    public void define(String name, Value value) { values.put(name, value); }

    public Value get(String name, int depth) {
        Env env = envAtDepth(depth);
        return env.values.get(name);
    }

    public void assign(String name, Value value, int depth) {
        Env env = envAtDepth(depth);
        env.values.put(name, value);
    }

    // === helper ===
    private Env envAtDepth(int depth) {
        Env env = this;
        for (int i = 0; i < depth && env != null; i++) env = env.parent();
        return env;
    }
}
```

::::::: notes
-   `Env` bildet **lexikalische Scopes zur Laufzeit** ab:
    -   `parent` zeigt auf das "umgebende" Environment ("Eltern-Environment")
    -   `values` speichert zu einem Namen den Wert für den aktuellen Scope
-   Zugriffsmöglichkeiten:
    -   Definieren von Namen mit `define()`
    -   Abfrage von Werten mit `get()`
    -   Neuzuweisung von Namen mit `assign()`

Hier modellieren wir die Semantik von Lispy mit. Ein Name (Variable, ...) kann nur
genau einmal pro Scope definiert werden - Mehrfachdefinitionen bedeuten einen
Fehler. Das haben wir bereits in einem früheren Pass (Name-Resolver) geprüft,
deshalb können wir hier das Definieren eines Namens in `define()` einfach halten.
Das Definieren eines Namens (hier einer Variablen) passiert immer im aktuellen
Scope/Environment.

Für den Abruf eines Wertes zu einem Namen mit `get()` nutzen wir die im früheren
Pass (Name-Resolver) berechnete Tiefeninformation: Dort hatten wir bereits für jeden
Namen (a) geprüft, ob dieser vom aktuellen Scope aus sichtbar ist, und (b)
berechnet, wieviele Schritte (Scopes) man nach "oben" gehen muss. Diese Information
nutzen wir jetzt: Wir suchen uns nicht mehr rekursiv durch die Environments nach
"oben" (wie in `Scope#resolve()`), sondern lassen uns gezielt das passende (Eltern-)
Environment geben und rufen dort in der Hashmap `values` den gespeicherten Wert ab.
Dass der Name vorhanden ist und in dieser "Tiefe", hatten wir bereits im
Name-Resolver geprüft und müssen das hier nicht wiederholen.

Wir haben eine *mutable* Semantik in Lispy, d.h. Variablen können im Laufe ihres
Lebens neue Werte zugewiesen werden. Dies kann mit `assign()` erledigt werden. In
Lispy ist es ein Fehler, einer bisher unbekannten Variable einen Wert zuweisen zu
wollen - dies hatten wir bereits im Name-Resolver geprüft ... Jetzt brauchen wir nur
noch die Tiefeninformation und gehen einfach entsprechend viele Environments nach
"oben" und aktualisieren dort gespeicherten Wert für den Namen. Ein rekursives
Suchen wie in `Scope#resolve()` brauchen wir hier also nicht mehr.

::: important
## Zusammenspiel semantische Analyse und Interpretation

Die Prüfung der aufgezählten Fehlerzustände ist bereits im Name-Resolver
(`NameResolverLvar` in Verbindung mit `Scope`) erfolgt! Dort haben wir bereits
geprüft:

-   ob ein Name doppelt definiert (gebunden) werden soll: bei der Behandlung von
    `VarDecl` mit `Scope#bind()`
-   ob eine Zuweisung an eine nicht definierte Variable erfolgen soll: bei der
    Behandlung von `AssignStmt` mit `Scope#resolve()`
-   ob ein Name vom aktuellen Scope/Environment aus sichtbar ist: bei der Behandlung
    von `VarExpr` mit `Scope#resolve()`

Für jedes `define()`, `assign()` und `get()` hier im Interpreter bzw. Environment
haben wir (wenn wir alles richtig gemacht haben) bereits **vorher** im Name-Resolver
und Symboltabelle ein entsprechendes `bind()` und `resolve()` geprüft.

**Deshalb braucht der Code für `Env` für diese Punkte keine extra Fehlerprüfungen!**

Wer sich damit unwohl fühlt, kann gern hier zusätzliche Prüfungen mit einbauen. Dann
bitte aber in der Fehlermeldung auf einen **internen Fehler** hinweisen - diese
Fehler hätten nämlich bereits in der semantischen Analyse auffallen müssen!
:::

::: tip
## Implementierungsdetail `Env`

Es lohnt sich, der Klasse `Env` zwei extra Hilfskonstruktoren mitzugeben:

``` java
public record Env(Env parent, Map<String, Value> values) {
    public Env() { this(null); }

    public Env(Env parent) { this(parent, new HashMap<>()); }

    // ...
}
```

Das erleichtert später das Anlegen neuer Environments.
:::

::: tip
## Nested Environments vs. Stack von Environments

Unsere Environments sind analog zu den Scopes aufgebaut und haben einen Verweis auf
das Eltern-Environment. Damit kann man einen Namen rekursiv vom aktuellen
Environment aus nach "oben" bis zur Wurzel (globales Environment) suchen.

In vielen Fällen könnte man auf diese Verzeigerung verzichten und im Interpreter
einfach einen Stack von einfachen Environments pflegen - jeder neue Scope legt ein
neues Environment oben auf den Stack, jedes Verlassen eines Scopes entfernt den
obersten Eintrag. Das funktioniert sogar für Funktionsaufrufe!

Es gibt aber Szenarien, wo dies nicht ausreicht. Wir werden möglicherweise für unser
Lispy so ein Szenario sehen. Können Sie sich selbst ein Szenario überlegen, wo ein
`Stack<Env>` im Interpreter nicht reicht und wir wissen müssen, was das
Eltern-Environment `Env parent` ist? (vgl. Challenges)
:::

::: important
## Unterscheidung Scopes und Environments

Beide Strukturen (`Scope` und `Env`) sind strukturell ähnlich aufgebaut. Beide haben
einen Verweis auf den Eltern-Scope bzw. das Eltern-Environment. Beide speichern zu
einem Namen eine Information. Beide haben eine Art Auflösemechanismus, um die
Information zu einem Namen abzurufen. Beide dienen ähnlichen Zwecken: Ein
`Scope`-Objekt spiegelt wie ein `Env`-Objekt einen Sichtbarkeitsbereich (Scope) in
unserem zu verarbeitenden Programm.

Der Unterschied liegt in der Benutzung:

-   `Scope` ist eine **statische** Sicht auf die Sichtbarkeitsbereiche.

    Wir bauen mit `Scope` die Symboltabellenstruktur während der semantischen
    Analyse im Name-Resolver auf. Dabei betreten wir jeden Scope, beispielsweise das
    `let`-with-Scopes (oder später in L-Fun den Funktionskörper) und prüfen, ob wir
    semantischen Regeln der Sprache Lispy eingehalten wurden: Sind alle Namen
    sichtbar (ggf. über die Eltern-Beziehung bis zum globalen Scope hoch), werden
    keine Namen im selben Scope mehrfach definiert, ist der Name bei einer Zuweisung
    bereits vorher definiert worden? Entsprechend speichern wir zu einem Namen die
    Information der Definition, also den `Decl`-Knoten des AST, der zu diesem Namen
    gehört. Wir werden später in L-Fun sehen, dass wir zwar die lokalen Variablen im
    Funktionskörper ganz normal auflösen, aber keine Funktionsaufrufe verfolgen! Wir
    interpretieren keine Anweisungen oder Ausdrücke, sondern prüfen nur die
    Sichtbarkeiten.

-   `Env` ist die **dynamische** Sicht auf die Sichtbarkeitsbereiche.

    Wir speichern zu jedem Namen den zugehörigen Wert in der `Env`. Wir
    interpretieren nun die Ausdrücke und Anweisungen, d.h. wir berechnen Werte und
    erzeugen Nebeneffekte. Jedes `Env`-Objekt entspricht einem Scope im
    verarbeiteten Programm. Die Environment-Struktur baut sich dynamisch während der
    Verarbeitung auf und ab, und im Unterschied zur semantischen Analyse verfolgen
    wir später in L-Fun dann (natürlich) auch die Funktionsaufrufe - jeder
    Funktionsaufruf legt einen neuen "Scope" an, in dem die lokalen Variablen im
    Funktionskörper für diesen Aufruf definiert sind. Dies nennt man auch oft "Call
    Frame" oder "Stack Frame" - und unsere `Env`-Objekte entsprechen exakt diesen
    Call-Frames. (Oft würde man tatsächlich mit einem `Stack<Env>` auskommen, aber
    manche Dinge gehen leider nur über die Struktur mit dem Eltern-Zeiger.)
:::
:::::::

# Interpreter für L-Var - Überblick

::: notes
## Vorüberlegungen

Der Interpreter für L-Var wird wie üblich vom Interpreter der Vorstufe ableiten,
d.h. wir haben `class InterpreterLvar extends InterpreterLexpr`.

In L-Var haben wir eine zusätzliche Expression: `VarExpr`. Wir überschreiben
entsprechend die geerbte Methode `eval(expr)` und fügen einen neuen Fall hinzu.

Zusätzlich haben wir in L-Var jetzt Statements. Da Statements "ausgeführt" werden
und dabei Nebeneffekte erzeugen, werden wir analog zu den Expressions eine Methode
`exec(stmt)` einführen, um die Statements zu verarbeiten.

Außerdem besteht L-Var aus einer Liste von Statements: `Lvar = [Stmt]`. Wir
benötigen entsprechend eine neue Einstiegsmethode und Felder, um den Zustand zu
speichern. Wir bekommen zusätzlich aus der semantischen Analyse die Symboltabellen
und die Sprunginformationen (gekapselt in einen Sidetable).

Wenn unser Interpreter nun eine Liste von Statements abarbeitet - was soll er dann
zurückliefern? Eine Expression evaluiert ja zu einem Wert, aber Statements nicht.
Trotzdem wäre es schön, wenn wir den zuletzt erzeugten Wert speichern und
zurückgeben könnten: Wir haben ja das `ExprStmt`, welches eine Expression ist - den
Wert dieser Expression könnten wir zurückgeben, so in unserem Programm überhaupt ein
`ExprStmt` vorkommt. Wenn es mehrere davon gibt, interessiert uns das zuletzt
ausgewertete `ExprStmt`.

## Start des Interpreters
:::

``` java
public class InterpreterLvar extends InterpreterLexpr {
    protected SemaInfo sema;
    protected Env env;
    protected Value last;

    public Value interpret(List<Stmt> stmts, SemaInfo semaInfo) {
        sema = semaInfo;  env = sema.globalEnv;  last = UNIT;

        stmts.forEach(this::exec);

        return last;
    }

    // protected void exec(Stmt stmt) ...
    // protected Value eval(Expr expr) ...
}
```

::: notes
Damit haben wir den Kern des Interpreters für L-Var aufgebaut.

Wir benötigen ein Start-Environment, welches wir über den Sidetable `semaInfo`
holen. Dazu ergänzen wir diese Klasse wie folgt:

``` java
public class SemaInfo {
    public Scope globalScope = new Scope();
    public Map<Stmt, Scope> symbols = new IdentityHashMap<>();
    public Map<VarExpr, Integer> depths = new IdentityHashMap<>();

    public Env globalEnv = new Env();  // NEU
}
```

Da wir das `semaInfo`-Objekt außerhalb des Interpreters anlegen, haben wir so die
Gelegenheit, bei Bedarf das globale Environment mit Defaults vorzubefüllen. Das
werden wir später in L-Fun tun.

Im Feld `env` merkt sich der Interpreter, in welchem Environment wir uns aktuell
befinden. Zu Beginn ist dies das globale Environment. Wann immer wir einen Scope
öffnen, erzeugen wir ein neues Kind-Environment (Eltern-Environment ist `env`) und
halten es in `env` fest. Wenn wir einen Block verlassen, setzen wir das `env` wieder
zurück. Wenn wir alles richtig machen, sollte am Ende der Ausführung des Programms
`env` wieder auf dem globalen Environment stehen.

Ansonsten iterieren wir über die Liste der Statements und führen jedes einzelne aus.
Die Ergebnisse von `ExprStmt` merken wir uns in `last`, dieses liefern wir am Ende
zurück.
:::

# Statements: Ausführen einer Variablendeklaration und eines 'let'-with-Scope

``` ebnf
Stmt = ExprStmt(Expr) | VarDecl(String, Type, Expr)
     | AssignStmt(Expr, Expr) | BlockStmt([Stmt])
```

::: notes
Wie oben angeteasert haben wir vier neue Statements in L-Var:

-   `ExprStmt`: "Cast" einer Expression als Statement
-   `VarDecl`: Definiert eine neue Variable (samt Initialisierung)
-   `AssignStmt`: Weist einer existierenden Variablen einen neuen Wert zu
-   `BlockStmt`: Öffnet einen neuen lokalen Scope für die Ausführung der enthaltenen
    Statements

Für diese Statements definieren wir nun die Methode `exec(stmt)` in
`InterpreterLvar`:
:::

``` java
protected void exec(Stmt stmt) {
    switch (stmt) {
        case ExprStmt(var expr) -> last = eval(expr);

        case VarDecl(var name, var type, var init) -> {
            Value i = eval(init);
            env.define(name, i);
        }

        case BlockStmt(var s) -> {
            env = new Env(env);
            s.forEach(this::exec);
            env = env.parent();
        }

        default -> throw error("unexpected statement: " + stmt);
    }
}
```

::: notes
## Auswertung von Expression-Statements

In L-Var können keine Expressions mehr direkt in der obersten Sprachebene
vorkommen - jede Expression wird in ein `ExprStmt` verpackt.

Um diese auszuwerten, wird einfach die `eval()`-Methode mit der Expression
aufgerufen. Dabei entsteht ein Wert, und diesen merken wir uns im Feld `last` des
`InterpreterLvar`. Falls wir später noch einmal ein `ExprStmt` verarbeiten, würden
wir das Feld entsprechend überschreiben. Damit merken wir uns in diesem Feld den
jeweils letzten Wert ...

## Auswertung einer Variablendefinition

Eine Variablendefinition (`VarDecl`) besteht aus drei Teilen: einem Namen, dem Typ
und der Initialisierung.

Die Initialisierung ist eine Expression - diese werten wir wie gewohnt mit `eval()`
aus.

Als Typ kann in L-Var nur ein `int` vorkommen, mehr erlaubt die Grammatik nicht.
Später werden wir noch weitere Typen ergänzen und in einem weiteren AST-Pass vor dem
Interpreter prüfen - das ist der sogenannte "Type Checker". Für den Interpreter
spielt der Typ an sich aber keine weitere Rolle - wir werten die
Initialisierungsexpression aus, und der dabei entstehende Wert passt zum Typ der
Variablen, anderenfalls hätte der Type-Checker einen Fehler gemeldet.

Da eine `VarDecl` einen neuen Namen (die Variable) im aktuellen Scope einführt,
definieren wir den Namen im aktuellen Environment und speichern den Wert aus der
Initialisierungsexpression.

## Auswerten eines `let`-with-Scopes

Ein `let`-with-Scopes kapselt Statements, die in einem neuen lokalen Scope
ausgeführt werden sollen. Im AST finden wir das als `BlockStmt`-Knoten.

Wir legen ein neues Environment an, wobei das bisherige Environment das
Eltern-Environment wird, und halten es in `env` fest. Dann iterieren wir über alle
Statements im `BlockStmt` und rufen jeweils `exec()` auf. Am Ende setzen wir das
Environment wieder auf das alte Environment zurück.

## Ausführen einer Zuweisung

Die Zuweisung an eine bereits existierende Variable erfolgt für den
`AssignStmt`-Knoten.

**Wichtig**: Der Fall für `AssignStmt` ist hier nicht gezeigt und verbleibt als
Challenge/Hausaufgabe.
:::

# Expressions: Lese-Zugriff auf Variablen

``` ebnf
Expr = VarExpr(String)
```

::: notes
In L-Var haben wir eine neue Expression: den lesenden Zugriff auf Variablen, d.h.
`VarExpr`. Diese bauen wir wie gewohnt ein, indem wir die `eval()`-Methode
überschreiben und passend ergänzen:
:::

``` java
@Override
protected Value eval(Expr expr) {
    return switch (expr) {
        case VarExpr v -> {
            int depth = sema.depths.get(v);
            yield env.get(v.name(), depth);
        }

        default -> super.eval(expr);
    };
}
```

:::: notes
Wenn wir eine Variable lesen wollen, beispielsweise in `(+ a b)`, dann taucht das
als `VarExpr` im AST auf. Jede `VarExpr` kapselt dabei den Namen der Variablen (`a`,
`b`).

Wir haben vor dem Interpreter den Name-Resolver laufen lassen. Der hat (a) geprüft,
ob im aktuellen Scope dieser Name sichtbar ist, und (b) berechnet, wieviele Schritte
(Scopes) man nach "oben" gehen muss.

Im Interpreter können wir diese Tiefeninformation aus dem Sidetable abrufen, und
dann vom aktuellen Environment entsprechend viele Schritte nach "oben" gehen und
dort auf die Variable zugreifen und den dort gespeicherten Wert zurückliefern.

::: important
## Zusammenspiel semantische Analyse und Interpretation

Auch hier gilt: Die notwendigen Prüfungen sind bereits im Name-Resolver
(`NameResolverLvar` in Verbindung mit `Scope`) erfolgt! Wenn es dabei einen Fehler
gegeben hätte, wären wir nicht im Interpreter angekommen. Beispielsweise wenn die
referenzierte Variable nicht sichtbar ist vom dem aktuellen Scope aus, dann hätte
das der Name-Resolver bereits festgestellt.

**Deshalb brauchen wir hier keine extra Fehlerprüfungen!**

Wer sich damit unwohl fühlt, kann gern hier zusätzliche Prüfungen mit einbauen. Dann
bitte aber in der Fehlermeldung auf einen **internen Fehler** hinweisen - diese
Fehler hätten nämlich bereits in der semantischen Analyse auffallen müssen!
:::
::::

# Wrap-up

-   Interpreter simulieren die Programmausführung
    -   Namen und Symbole auflösen
    -   Speicherbereiche simuliere
    -   Code ausführen: Read-Eval-Loop

\smallskip

-   Scopes mit `Environment` (analog zu Symboltabellen)
-   Interpretation von Blöcken und Variablen (Deklaration, Zuweisung)

::: readings
TODO

In [@Nystrom2021] kann man in Kapitel 6 "Parsing Expressions" und Kapitel 7
"Evaluation Expressions" nachlesen.
:::

::: outcomes
-   k3: Ich kann Environment-Strukturen analog zu den Symboltabellen aufbauen, um
    Namen und Werte dynamisch zu speichern
-   k3: Ich kann eine Read-Eval-Schleife implementieren und dabei durch
    Traversierung des AST die dort abgelegten Anweisungen und Ausdrücke
    interpretieren
:::

::: challenges
**Nested Scopes**

Betrachten Sie folgendes Programm:

``` clojure
(def x : int 10)
(let ((x : int 1)
      (y : int 2))
  (+ x y)
  (let ((y : int 3))
        (+ x y))
    (+ x y))
```

-   Zeichnen Sie zu einigen ausgewählten Programmpunkten den Zustand des
    Environments:
    -   Nach `def x`
    -   Nach Eintritt in den ersten `let`-Block
    -   Nach Eintritt in den inneren `let`-Block
-   Welche Werte haben `x` und `y` jeweils an diesen Stellen?
-   Notieren Sie, wie `BlockStmt` im Interpreter diese Environments erzeugt und
    zurücksetzt.

**`Scope` vs. `Env`**

Im Skript wurde behauptet, dass man zum Speichern der Werte während der
Interpretation neue Datenstrukturen benötigt und nicht die bereits in der
semantischen Analyse aufgebauten Symboltabellen dafür nutzen kann.

Zeigen Sie an einem praktischen Beispiel, warum dies so ist.

<!--
Symboltabellen (unsere `Scope`-Modellierung) sind **statisch** und verfolgen keine Aufrufe.
D.h. für einen Funktionskörper werden alle Namen in der passenden Symboltabelle abgelegt
und aufgelöst, aber keine Funktionsaufrufe verfolgt.

Wenn man einen rekursiven Aufruf hat, hat man aber plötzlich pro Aufruf einen neuen
Stackframe. Wenn man nun Werte in den Symboltabellen ablegen würde, würde man sich gegenseitig
die Variablen überschreiben.

Deshalb muss man zur Laufzeit des Interpreters **dynamisch** neue Environments anlegen und
passend verknüpfen und füllen. Die statische Symboltabelle reicht nicht mehr.
-->

**Ausführen einer `AssignStmt` in `exec(stmt)`**

Im Code oben wurde die Methode `exec(stmt)` partiell gezeigt - die Behandlung des
`AssignStmt` fehlte.

Holen Sie dies nach: Wie sollte der Fall für `AssignStmt` aussehen? Welche Elemente
hat ein `AssignStmt`-Knoten (wie sah der entsprechende Teil der konkreten und
abstrakten Syntax aus)? Wie führt man damit eine Zuweisung aus?

<!--
```java
case AssignStmt(var assignee, var expr) -> {
    if (!(assignee instanceof VarExpr v))
        throw error("assignee should be a variable");
    Value value = eval(expr);
    int depth = sema.depths.get(v);
    env.assign(v.name(), value, depth);
}
```
-->

**Nested Environments vs. Stack von Environments**

Unsere Environments sind analog zu den Scopes aufgebaut und haben einen Verweis auf
das Eltern-Environment. Damit kann man einen Namen rekursiv vom aktuellen
Environment aus nach "oben" bis zur Wurzel (globales Environment) suchen.

In vielen Fällen könnte man auf diese Verzeigerung verzichten und im Interpreter
einfach einen Stack von einfachen Environments pflegen - jeder neue Scope legt ein
neues Environment oben auf den Stack, jedes Verlassen eines Scopes entfernt den
obersten Eintrag. Das funktioniert sogar für Funktionsaufrufe!

Es gibt aber Szenarien, wo dies nicht ausreicht. Wir werden möglicherweise für unser
Lispy so ein Szenario sehen. Können Sie sich selbst ein Szenario überlegen, wo ein
`Stack<Env>` im Interpreter nicht reicht und wir wissen müssen, was das
Eltern-Environment `Env parent` ist?

<!--
Wenn man mit Closures arbeitet: Eine Funktion gibt eine Funktion zurück, die aber
auf die Werte in der Funktion zugreift, d.h. diese zurückgegebene Funktion schließt
die Namen in der definierenden Funktion ein, führt also ein *closure* dieser Namen
durch ... Die Closure muss dann nach dem Verlassen der ursprünglichen Funktion noch
auf den lokalen Scope im Funktionskörper zugreifen können! Aber nach dem Verlassen
der Funktion würde im Stack-Modell das Environment ja vom Stack gelöscht und dann
nicht mehr zugreifbar! Deshalb muss man in diesem Fall mit den Parent-Zeigern
arbeiten ...
-->
:::
