#include <cstdlib>      // size_t
//#include <cstddef>
#include <iostream>

using namespace std;


class Token {
public:
    /**
     * Constructs a new token object.
     *
     * @param lexem is a pointer to the text of the token (to be copied)
     * @param row is the row in input where this token was found
     * @param col is the column in input where this token starts
     */
    Token(const char* lexem, int row, int col);

    /**
     * Destructs the token object and free's the stored lexem.
     */
    ~Token();

    /**
     * Access to the token's lexem
     *
     * @return a pointer to the stored lexem
     */
    char* lexem();

    /**
     * Access to the token's row
     *
     * @return the row where this token was found
     */
    int row();

    /**
     * Access to the token's column
     *
     * @return the column where this token starts
     */
    int col();

private:
    char* lexem;    ///< Pointer to the text of the token
    int row;        ///< Row in input where this token was found
    int col;        ///< Column in input where this token starts
};


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
    SmartToken(const Token* p = nullptr);

    /**
     * Copy constructor
     *
     * Constructs a new smart pointer from another smart pointer, increments
     * the reference counter.
     *
     * @param p is another smart pointer
     */
    SmartToken(const SmartToken& p);

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
     * Changes the shared token, thus we need first to do the same like the
     * destructor, followed by something like the constructor.
     *
     * @param p is another smart pointer
     */
    SmartToken& operator=(const SmartToken& p);

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
     * @return true, if `p` shares the same token
     */
    bool operator==(const SmartToken& p) const;

private:
    Token* pObj;        ///< Pointer to the current shared token
    RefCounter* rc;     ///< Pointer to the reference counter (used for the current token)

    releaseObject();                         ///< Decrement reference counter and free object if necessary
    acquireObject(Token* p, RefCounter* r);  ///< Copy pointer to token and reference counter and increment reference counter
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


class RingBuffer {
public:
    /**
     * Constructor that creates a new ring buffer for max. `size` elements
     *
     * Initialises the attributes and allocates memory for `size` elements
     * of type `SmartToken` and let the pointer `elems` point to this new
     * array
     *
     * @param size is the max. number of elements that can be stored
     */
    RingBuffer(size_t size);

    /**
     * Destructor
     *
     * free's the dynamically allocated array `elems`
     */
    ~RingBuffer();

    /**
     * Reading the first (oldest) element
     *
     * If an element has been read, the `head` points to the next element
     * and `count` is decremented. The read element is **not** released.
     *
     * @return Returns (a copy of) the first (i.e. oldest) element of the
     * buffer, but does not (yet) release it; returns an empty `SmartToken`
     * if buffer is empty
     */
    SmartToken readBuffer();

    /**
     * Adding a new element
     *
     * Appends the new element to the end of the queue. If the buffer is
     * full, the oldest element will be overwritten by the new element. The
     * old element will take care of releasing its memory (smart pointer).
     *
     * @param data is a reference to the element to be added
     */
    void writeBuffer(const SmartToken& data);

private:
    size_t count;           ///< number of elements currently stored in the buffer
    size_t head;            ///< points to the beginning of the buffer (oldest element)
    size_t size;            ///< length of array `elems`
    SmartToken* elems;      ///< array with `size` places of type `SmartToken`, dynamically allocated
};















/*
 * ===========================================================================
 *                                   MUSTERLOESUNG
 * ===========================================================================
 */

Token::Token(const char* l, int r, int c) : row(r), col(c) {
    lexem = new char[strlen(l)];
    strcpy(lexem, l);
}
Token::~Token() { delete lexem; }
char* Token::lexem() { return lexem; }
int Token::row() { return row; }
int Token::col() { return col; }


SmartToken::SmartToken(const Token* ptr) {
    acquireObject(ptr, (ptr != nullptr) ? new RefCounter() : nullptr);
}
SmartToken::SmartToken(const SmartToken& sp) {
    acquireObject(sp.pObj, sp.rc);
}
SmartToken::~SmartToken() {
    releaseObject();
}
SmartToken& SmartToken::operator=(const SmartToken& p) {
    if (pObj == sp.pObj) {
        return *this;
    }

    releaseObject();
    acquireObject(p.pObj, p.rc)

    return *this;
}
Token& SmartToken::operator*() {
    if (pObj == nullptr) {
        throw NullPointerException();
    }
    return *pObj;
}
Token* SmartToken::operator->() {
    if (pObj == nullptr) {
        throw NullPointerException();
    }
    return pObj;
}
bool SmartToken::operator==(const SmartToken& sp) const {
    return pObj == sp.pObj;
}
void SmartToken::releaseObject() {
    if (pObj) {
        rc->dec();
        if (rc->isZero()) {
            delete rc;
            delete pObj;
            rc = nullptr;
            pObj = nullptr;
        }
    }
}
void SmartToken::acquireObject(Token* p, RefCounter* r) {
    pObj = p;
    rc = r;
    if (rc) rc->inc();
}


RefCounter::RefCounter() : n(0) {}
void RefCounter::inc() { ++n; }
void RefCounter::dec() { --n; }
bool RefCounter::isZero() const { return n == 0; }


RingBuffer::RingBuffer(size_t size) : count(0), head(0), size(size) {
    elems = new SmartToken[size];
}
RingBuffer::~RingBuffer() {
    delete [] elems;
}
SmartToken RingBuffer::readBuffer() {
    if (count) {
        SmartToken& elem = elems[head];
        head = (head + 1) % size;
        --count;
        return elem;
    }
    return SmartToken();
}
void RingBuffer::writeBuffer(const SmartToken& data) {
    size_t tail;

    /* Puffer voll? Head freigeben */
    if (count == size) {
        head = (head + 1) % size;
        --count;
    }

    /* Daten ins Ende schreiben */
    tail = (head + count) % size;
    elems[tail] = data;
    ++count;
}


class Foo {
public:
    ~Foo() {
        cout << "Destruktor Foo" << endl;
    }
    SmartToken<Foo> ptr;
};


void f1() {
    Foo *c = new Foo;
    SmartToken<Foo> p3 = c;

    cout << "ab hier wirds spannend ;) \n\n" << endl;
}

void f2() {
    Foo *a = new Foo;
    Foo *b = new Foo;

    SmartToken<Foo> p1 = a;
    SmartToken<Foo> p2 = b;
    a->ptr = p2;
    b->ptr = p1;

    cout << "ab hier wirds spannend ;) \n\n" << endl;
//    delete b;
//    cout << "\n\n hinter delete b ... \n\n" << endl;
}

void f3() {
    Foo *d = new Foo;
    Foo *e = new Foo;

    d->ptr = e;
    e->ptr = d;

    cout << "ab hier wirds spannend ;) \n\n" << endl;
//    delete e;
//    cout << "\n\n hinter delete b ... \n\n" << endl;
}


/*
 * ===========================================================================
 * main()
 * ===========================================================================
 *
 */
int main(void) {
    f1();
    f2();
    f3();

    return EXIT_SUCCESS;
}


#include <iostream>
#include <vector>

#include "ringbuffer/RingBuffer.hpp"
#include "ringbuffer/NoOpAllocator.h"
#include "ringbuffer/MyAllocator.h"
#include "ringbuffer/SPAllocator.h"


/*
 *
 *                      MUSTERLOESUNG
 *
 * g++ -std=c++17 -I../../include demoRingBuffer.cpp
 */


int main(int argc, char **argv) {
    // MyAllocator
    {
        cout << endl << "MyAllocator" << endl;
        vector<int, MyAllocator<int>> bar(8);
        bar.push_back(42);
        for (auto x: bar) cout << x << " ";
        cout << endl;
    }


    // RingBuffer I
    {
        cout << endl << "RingBuffer I" << endl;
        MyAllocator<int> ma;
        RingBuffer<int, 10, MyAllocator<int>> rb;

        rb.displayStatus();
        cout << "sizeof(int): " << sizeof(int) << endl;

        int *x = ma.allocate(1);
        *x = 42;
        cout << "x: " << *x << " at " << (long) x << endl;

        rb.writeBuffer(x);
        rb.displayStatus();

        int *y = rb.readBuffer();
        cout << "x: " << *x << " at " << (long) x << endl;
        cout << "y: " << *y << " at " << (long) y << endl;

        *y = 7;
        cout << "x: " << *x << "; x-y: " << (long) x - long (y) << endl;
    }


    // RingBuffer II
    {
        cout << endl << "RingBuffer II" << endl;
        RingBuffer<int, 10, NoOpAllocator<int>> rb;

        rb.displayStatus();
        cout << "sizeof(int): " << sizeof(int) << endl;

        int xyz = 42;
        cout << "xyz: " << xyz << " at " << (long) &xyz << endl;

        int *x = &xyz;
        cout << "x: " << *x << " at " << (long) x << endl;

        rb.writeBuffer(x);
        rb.displayStatus();

        int *y = rb.readBuffer();
        cout << "x: " << *x << " at " << (long) x << endl;
        cout << "y: " << *y << " at " << (long) y << endl;

        *y = 7;
        cout << "x: " << *x << "; x-y: " << (long) x - long (y) << endl;
    }

    return EXIT_SUCCESS;
}
