#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


class Person {
public:
    Person(const string &n = "") : name(n) {
        cout << "Konstruktor Person mit (" << name << ")" << endl;
    }

    const string &getName() const {
        return name;
    }

    string toString() const {
        return string("Name: ") + name;
    }

private:
    string name;
};


class Student : public Person {
public:
    Student(const string &name = "", const string &kurs = "") : Person(name), modul(kurs) {
        cout << "Konstruktor Student mit (" << name << ", " << kurs << ")" << endl;
    }

    const string &getModul() const {
        return modul;
    }

    string toString() {
        return Person::toString() + string(", Modul: ") + modul;
    }

private:
    string modul;
};


class Angestellter : public Person {
public:
    Angestellter(const string &name = "", const string &firmenname = "") : Person(name), firma(firmenname) {
        cout << "Konstruktor Angestellter mit (" << name << ", " << firmenname << ")" << endl;
    }

    const string &getFirma() const {
        return firma;
    }

    string toString() {
        return Person::toString() + string(", Firma: ") + firma;
    }

private:
    string firma;
};


class HiWi : public Student, public Angestellter {
public:
    HiWi(const string &name = "", const string &kurs = "", const string &firmenname = "")
    : Student(name, kurs), Angestellter(name, firmenname) {
        cout << "Konstruktor HiWi mit (" << name << ", " << kurs << ", " << firmenname << ")" << endl;
    }
/*
    string toString() {
        return string("HiWi.toString()");
    }
*/
};


int main() {
    cout << "lege Studi Heinz an" << endl;
    Student s("Heinz", "SP");

    cout << "\nlege Angestellten Holger an" << endl;
    Angestellter a("Holger", "KleinWeich");

    cout << "\nlege HiWi Anne an" << endl;
    HiWi h("Anne", "PGM", "DummSoft");


    cout << endl;
    cout << "toString (s): " << s.toString() << endl;
    cout << "getName  (s): " << s.getName() << endl;
    cout << "getModul (s): " << s.getModul() << endl;

    cout << endl;
    cout << "toString (a): " << a.toString() << endl;
    cout << "getName  (a): " << a.getName() << endl;
    cout << "getFirma (a): " << a.getFirma() << endl;

    cout << endl;
    cout << "toString (h):               " << h.toString() << endl;
    cout << "getName  (h):               " << h.getName() << endl;
    cout << "getModul (h):               " << h.getModul() << endl;
    cout << "getFirma (h):               " << h.getFirma() << endl;
/*
    cout << "toString (h):               " << h.toString() << endl;
    cout << "toString (h::student):      " << h.Student::toString() << endl;
    cout << "toString (h::angestellter): " << h.Angestellter::toString() << endl;
*/


    return EXIT_SUCCESS;
}
