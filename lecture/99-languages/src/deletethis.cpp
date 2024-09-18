#include <iostream>
#include <cstdlib>

using namespace std;

class Foo {
public:
    ~Foo() {
        cout << "Foo::~Foo()" << endl;
        delete this;
    }
};


int main() {
    {
        Foo a;
    }
    cout << "nach Scope" << endl << endl;


    return EXIT_SUCCESS;
}
