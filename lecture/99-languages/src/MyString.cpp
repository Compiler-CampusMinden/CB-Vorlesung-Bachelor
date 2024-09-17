
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class MyString {
public:
    MyString(const char *s = "");
    MyString(const MyString &);
    ~MyString();

    string toString() const;

    MyString &operator=(const MyString &);
    MyString &operator+=(const MyString &);
    MyString operator+(const MyString &);
    bool operator!=(const MyString &);

    MyString &operator++();
    MyString operator++(int);

private:
    size_t len;
    char *str;

    void copy(const char *);
    void revert();

    friend ostream &operator<<(ostream &, const MyString &);
};



// *struktoren
MyString::MyString(const char *s) : len(strlen(s)), str(new char[strlen(s) + 1]) {
    copy(s);
}

MyString::MyString(const MyString &s) : MyString(s.str) {
}

MyString::~MyString() {
    delete[] str;
}


// Methoden
void MyString::copy(const char *s) {
    /* ausreichend Speicher da? */
    if (len != strlen(s)) {
        delete[] str;
        len = strlen(s);
        str = new char[len + 1];
    }

    /* kopieren */
    strcpy(str, s);
}

string MyString::toString() const {
    return string(str);
}


// Operatoren
MyString &MyString::operator=(const MyString &s) {
    if (this != &s) {
        copy(s.str);
    }
    return *this;
}

MyString &MyString::operator+=(const MyString &s) {
    /* neue Länge */
    len += s.len;

    /* Speicher holen und kopieren/konkatenieren */
    char *p = new char[len + 1];
    strcpy(p, str);
    strcat(p, s.str);

    /* alten Speicher freigeben und Pointer umhängen */
    delete[] str;
    str = p;

    return *this;
}

MyString MyString::operator+(const MyString &s) {
    return MyString(*this) += s;
}

bool MyString::operator!=(const MyString &s) {
    return strcmp(str, s.str) == 0 ? false : true;
}


// Friends
ostream &operator<<(ostream &out, const MyString &s) {
    return out << s.str;
//    return out << s.toString();
}



// weitere Operatoren
void MyString::revert() {
    char c;
    for (size_t i = 0; i < len / 2; i++) {
        c = *(str + i);
        *(str + i) = *(str + len - i - 1);
        *(str + len - i - 1) = c;
    }
}

MyString &MyString::operator++() {
    revert();
    return *this;
}

MyString MyString::operator++(int) {
    MyString old(*this);
    revert();
    return old;
}
