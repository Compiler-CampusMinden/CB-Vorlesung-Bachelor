#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


class Person {
public:
    Person(const string &n = "") : name(n) {}

    virtual string toString() const {
        return string("(Person) name: ") + name;
    }

    string name;
};


class Student : public Person {
public:
    Student(const string &name = "", const string &n = "") : Person(name), nick(n) {}

    string toString() const {
        return string("(Student) ") + Person::toString() + " => Nickname: " + nick;
    }

    string nick;
};


int main() {
    Student s("Heinz", "SP");
    Person p = s;
    cout << endl << "Objekt s (Student):  " << s.toString() << endl;
    cout << "Referenz p (Person): " << p.toString() << endl << endl;

    /*
    s.name = "Holger";
    s.nick = "KI";
    p.name = "AUTSCH :-)";
    cout << "Objekt s (Student):  " << s.toString() << endl;
    cout << "Referenz p (Person): " << p.toString() << endl << endl;
    */

    return EXIT_SUCCESS;
}
