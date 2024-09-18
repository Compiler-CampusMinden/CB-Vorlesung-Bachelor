#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


class Person {
public:
    Person() : name("DEFAULT") {}

    Person(const string &n) : name(n) { cout << "Person: name==" + n << endl; }

    const string &getName() const {
        return name;
    }

    string toString() const {
        return string("Name: ") + name;
    }

private:
    string name;
};


class Student : virtual public Person {
public:
    Student(const string &name = "", const string &kurs = "") : Person(name), modul(kurs) {
        cout << "\tStudent: " << name << endl;
    }

    string toString() {
        return Person::toString() + string(", Modul: ") + modul;
    }

private:
    string modul;
};


class Angestellter : virtual public Person {
public:
    Angestellter(const string &name = "", const string &firmenname = "") : Person(name), firma(firmenname) {
        cout << "\tAngestellter: " << name << endl;
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
    : Student(name + " STUDI", kurs), Angestellter(name + " ANGEST", firmenname) {}
//    : Person(name), Student(name+" STUDI", kurs), Angestellter(name+" ANGEST", firmenname) {}

/*
    string toString() {
        return string("HiWi.toString()");
    }
*/
};


int main() {
    HiWi h("Anne", "PGM", "DummSoft");

    cout << "getName (h):                " << h.getName() << endl;
    cout << "getName (h::student):       " << h.Student::getName() << endl;
    cout << "getName (h::angestellter):  " << h.Angestellter::getName() << endl;

    cout << endl;
    cout << "toString (h):               " << h.toString() << endl;


    return EXIT_SUCCESS;
}
