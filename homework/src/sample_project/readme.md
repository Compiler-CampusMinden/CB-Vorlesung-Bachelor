# Sample Project

Dies ist ein Starter-Projekt für die Übungsaufgaben in "Compilerbau" (Bachelor). Es existiert
eine Gradle-Konfiguration (Java-Projekt), JUnit und ANTLR sind auch bereits eingebunden. Das
Projekt zeigt den Umgang mit den Grammatiken. Zusätzlich existieren Beispielgrammatiken für
einige Übungsblätter.

## Installation

Öffnen Sie den Ordner `sample_project` als neues Java-Projekt "mit existierenden Quellen" in
IntelliJ. Achten Sie dabei darauf, dass Sie als "Build-Model" entsprechend "Gradle" auswählen,
damit die Konfiguration übernommen wird.

Sie benötigen ein installiertes [Java SE Development Kit 21 LTS](https://jdk.java.net/21/).
Achten Sie darauf, dass dieses auch wirklich von IntelliJ verwendet wird (unter
Projekt-Einstellungen).

## Gradle-Tasks

### Aufräumen

`./gradlew clean`

### Starten des Programms

Sie konfigurieren Ihr Programm im [`build.gradle`](build.gradle) in der Variablen `mainClass`.

Danach können Sie das Programm kompilieren und starten über `./gradlew run`.

### Formatieren

Ihre Java-Sourcen können Sie mit `./gradlew spotlessApply` formatieren.

### Testen

`./gradlew check`

### Grammatik neu übersetzen

Die Grammatik liegt im Ordner `src/main/antlr`. Sie wird standardmäßig beim Bauen der
Applikation übersetzt, also beispielsweise beim Ausführen von `./gradlew run` oder
`./gradlew build`.

Die generierten Dateien liegen im Build-Ordner: `build/generated-src/antlr/main/`. Falls Ihre
Grammatik in einem Package liegt (siehe `HelloPackage.g4` im Package `my.pkg`), dann wird für
die generierten Sourcen automatisch dieses Package mit angelegt. Sie müssen entsprechend in
der Grammatik über die Direktive `@header` dieses Package in die generierten Sourcen
generieren lassen.

Wenn Sie die Grammatik einzeln übersetzen wollen, können Sie dies mit
`./gradlew generateGrammarSource` tun.

<!--  pandoc -s -f markdown -t markdown+smart-grid_tables-multiline_tables-simple_tables --columns=94 readme.md -o xxx.md  -->
