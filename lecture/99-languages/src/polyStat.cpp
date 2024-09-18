#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


class Person {
public:
    Person(const string &n = "") : name(n) {}

    string toString() const {
        return string("(Person) name: ") + name;
    }

private:
    string name;
};


class Student : public Person {
public:
    Student(const string &name = "", const string &n = "") : Person(name), nick(n) {}

    string toString() const {
        return string("(Student) ") + Person::toString() + " => Nickname: " + nick;
    }

private:
    string nick;
};


int main() {
    Student s("Heinz", "heizer");
    Person &p = s;

    cout << "Objekt s (Student):  " << s.toString() << endl;
    cout << "Referenz p (Person): " << p.toString() << endl;

    return EXIT_SUCCESS;
}
