#include <iostream>
#include <cassert>
#include <cstddef>

using namespace std;


// g++ -Wall --std=c++17 ringbuffer.cpp


class Token {
public:
    /**
     * Constructs a new token object.
     *
     * @param l is a pointer to the text of the token (to be copied)
     * @param r is the row in input where this token was found
     * @param c is the column in input where this token starts
     */
    Token(const char* l, int r, int c);

    /**
     * Destructs the token object and free's the stored lexem.
     */
    ~Token();

    char* lexem;    ///< Pointer to the text of the token
    int row;        ///< Row in input where this token was found
    int col;        ///< Column in input where this token starts

friend ostream &operator<<(ostream &out, const Token &t);
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

    unsigned int n;     ///< How many SmartToken share ownership of "our" object?

friend ostream &operator<<(ostream &out, const RefCounter &rc);
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
    SmartToken(Token* p = nullptr);

    /**
     * Copy constructor
     *
     * Constructs a new smart pointer from another smart pointer, increments
     * the reference counter.
     *
     * @param sp is another smart pointer
     */
    SmartToken(const SmartToken& sp);

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
     * Changes the shared token, thus we need first to perform something like
     * the destructor, followed by something like the constructor.
     *
     * @param sp is another smart pointer
     */
    SmartToken& operator=(const SmartToken& sp);

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
     * @param sp is another smart pointer
     * @return true, if `sp` shares the same token
     */
    bool operator==(const SmartToken& sp) const;

private:
    Token* pObj;        ///< Pointer to the current shared token
    RefCounter* rc;     ///< Pointer to the reference counter (used for the current token)

    void releaseObject();                           ///< Decrement reference counter and free object if necessary
    void acquireObject(Token* p, RefCounter* r);    ///< Copy pointer to token and reference counter and increment reference counter

friend ostream &operator<<(ostream &out, const SmartToken &st);
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
    RingBuffer(unsigned int size);

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
    unsigned int count;     ///< number of elements currently stored in the buffer
    unsigned int head;      ///< points to the beginning of the buffer (oldest element)
    unsigned int size;      ///< length of array `elems`
    SmartToken* elems;      ///< array with `size` places of type `SmartToken`, dynamically allocated

friend ostream &operator<<(ostream &out, const RingBuffer &rb);
};















/*
 * ===========================================================================
 *                                   MUSTERLOESUNG
 * ===========================================================================
 */

Token::Token(const char* l, int r, int c) : lexem(nullptr), row(r), col(c) {
    lexem = new char[strlen(l)+1];  // +1 for terminating '\0'
    strcpy(lexem, l);

    cout << "Token::Token():" << *this << endl;
}
Token::~Token() {
    cout << "Token::~Token(): " << *this << endl;

    delete lexem;
}
ostream &operator<<(ostream &out, const Token &t) {
    return out << "{lexem: " << t.lexem << ", row: " << t.row << ", column: " << t.col << "}";
}


RefCounter::RefCounter() : n(0) { cout << "RefCounter::RefCounter()" << endl; }
void RefCounter::inc() { ++n; }
void RefCounter::dec() { --n; }
bool RefCounter::isZero() const { return n == 0; }
ostream &operator<<(ostream &out, const RefCounter &rc) {
    return out << "{rc: " << rc.n << "}";
}


SmartToken::SmartToken(Token* ptr) : pObj(nullptr), rc(nullptr) {
    if (ptr) acquireObject(ptr, new RefCounter());

    cout << "SmartToken::SmartToken(Token*): " << *this << endl;
}
SmartToken::SmartToken(const SmartToken& sp) : pObj(nullptr), rc(nullptr) {
    acquireObject(sp.pObj, sp.rc);

    cout << "SmartToken::SmartToken(SmartToken&): " << *this << endl;
}
SmartToken::~SmartToken() {
    cout << "SmartToken::~SmartToken(): " << *this << endl;

    releaseObject();
}
SmartToken& SmartToken::operator=(const SmartToken& sp) {
    cout << "SmartToken::operator=: lhs=" << *this << ", rhs: " << sp << endl;

    if (pObj == sp.pObj) {
        return *this;
    }

    releaseObject();
    acquireObject(sp.pObj, sp.rc);

    return *this;
}
Token& SmartToken::operator*() {
    cout << "SmartToken::operator*: " << *this << endl;

    assert(pObj != nullptr);
    return *pObj;
}
Token* SmartToken::operator->() {
    cout << "SmartToken::operator->: " << *this << endl;

    assert(pObj != nullptr);
    return pObj;
}
bool SmartToken::operator==(const SmartToken& sp) const {
    cout << "SmartToken::operator==: lhs=" << *this << ", rhs: " << sp << endl;

    return pObj == sp.pObj;
}
void SmartToken::releaseObject() {
    cout << "SmartToken::releaseObject(): " << *this << endl;

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
    cout << "SmartToken::acquireObject(): *this=" << *this << ", Token=" << p << ", RC: " << r << endl;

    pObj = p;
    rc = r;
    if (rc) rc->inc();
}
ostream &operator<<(ostream &out, const SmartToken &st) {
    if (st.pObj && st.rc)
        return out << "{pObj: " << st.pObj << ", rc: " << st.rc << " >> " << *(st.pObj) << " >> " << *(st.rc) << "}";
    else
        return out << "{pObj: " << st.pObj << ", rc: " << st.rc << "}";
}


RingBuffer::RingBuffer(unsigned int size) : count(0), head(0), size(size), elems(nullptr) {
    elems = new SmartToken[size];

    cout << "RingBuffer::RingBuffer(): " << *this << endl;
}
RingBuffer::~RingBuffer() {
    cout << "RingBuffer::~RingBuffer(): " << *this << endl;

    delete [] elems;
}
SmartToken RingBuffer::readBuffer() {
    cout << "RingBuffer::readBuffer(): " << *this << endl;

    if (count) {
        SmartToken& elem = elems[head];
        head = (head + 1) % size;
        --count;
        return elem;
    }
    return SmartToken();
}
void RingBuffer::writeBuffer(const SmartToken& data) {
    cout << "RingBuffer::writeBuffer(): *this=" << *this << ", data=" << data << endl;

    unsigned int tail;

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
ostream &operator<<(ostream &out, const RingBuffer &rb) {
    return out << "{size: " << rb.size << ", count: " << rb.count << ", head: " << rb.head << "}";
}


int main(int argc, char **argv) {
    // Token
    {
        cout << endl << endl << ">> Token" << endl;

        Token wuppie = Token("wuppie", 1, 4);   // should be deleted automatically after this block
        Token* foo = new Token("foo", 9, 35);   // will be free'd manually
        Token* bar = new Token("bar", 7, 10);   // leaves a memory hole

        cout << endl;
        delete foo;

        cout << endl;
    }


    // SmartToken
    {
        cout << endl << endl << ">> SmartToken" << endl;

        SmartToken st;                                                  // uses default c'tor (all empty)
        SmartToken wuppie = SmartToken(new Token("wuppie", 1, 4));      // default c'tor w/ pointer
        {
            cout << endl;
            SmartToken fluppie = SmartToken(wuppie);                    // copy c'tor
            SmartToken fluppie2(wuppie);                                // copy c'tor
            SmartToken foo = SmartToken(new Token("foo", 9, 35));       // default c'tor w/ pointer

            cout << endl;
            cout << "st == wuppie: " << (st == wuppie) << endl;             // 0 (no)
            cout << "fluppie == wuppie: " << (fluppie == wuppie) << endl;   // 1 (yes)
            cout << "foo == wuppie: " << (foo == wuppie) << endl;           // 0 (no)

            cout << endl;
            cout << "st: " << st << endl;               // {pObj: 0x0, rc: 0x0}
            cout << "wuppie: " << wuppie << endl;       // {pObj: 0xN, rc: 0xM, lexem: wuppie, row: 1, col: 4, rc: 3}
            cout << "fluppie: " << fluppie << endl;     // {pObj: 0xN, rc: 0xM, lexem: wuppie, row: 1, col: 4, rc: 3}
            cout << "foo: " << foo << endl;             // {pObj: 0xO, rc: 0xP, lexem: foo, row: 9, col: 35, rc: 1}

            cout << endl;
        }

        cout << endl;
        cout << "st: " << st << endl;               // {pObj: 0x0, rc: 0x0}
        cout << "wuppie: " << wuppie << endl;       // {pObj: 0xN, rc: 0xM, lexem: wuppie, row: 1, col: 4, rc: 1}

        cout << endl;
//        cout << "*st: " << *st << endl;                             // ERROR (runtime)
        cout << "*wuppie: " << *wuppie << endl;                     // {lexem: wuppie, row: 1, col: 4}
        cout << "(*wuppie).lexem: " << (*wuppie).lexem << endl;     // wuppie
        cout << "wuppie->lexem: " << wuppie->lexem << endl;         // wuppie

        cout << endl;
    }


    // RingBuffer
    {
        cout << endl << endl << ">> RingBuffer" << endl;
        SmartToken wuppie = SmartToken(new Token("wuppie", 1, 4));
        SmartToken fluppie = SmartToken(wuppie);
        SmartToken fluppie2(wuppie);
        SmartToken foo = SmartToken(new Token("foo", 9, 35));

        cout << endl << ">> RingBuffer: create" << endl;
        RingBuffer rb(3);
        cout << "rb: " << rb << endl;
        cout << "rb.readBuffer(): " << rb.readBuffer() << endl;     // {pObj: 0x0, rc: 0x0}

        cout << endl << ">> RingBuffer: write" << endl;
        rb.writeBuffer(wuppie);
        rb.writeBuffer(fluppie);
        rb.writeBuffer(fluppie2);
        cout << "rb: " << rb << endl;
        cout << "wuppie: " << wuppie << endl;       // {pObj: 0xN, rc: 0xM, lexem: wuppie, row: 1, col: 4, rc: 6}

        cout << endl << ">> RingBuffer: read (wuppie)" << endl;
        cout << "rb.readBuffer(): " << rb.readBuffer() << endl;     // {pObj: 0xN, rc: 0xM, lexem: wuppie, row: 1, col: 4, rc: 3}
        cout << "rb: " << rb << endl;

        cout << endl << ">> RingBuffer: read (fluppie)" << endl;
        cout << "rb.readBuffer(): " << rb.readBuffer() << endl;     // {pObj: 0xN, rc: 0xM, lexem: wuppie, row: 1, col: 4, rc: 3}
        cout << "rb: " << rb << endl;

        cout << endl << ">> RingBuffer: read (fluppie2)" << endl;
        cout << "rb.readBuffer(): " << rb.readBuffer() << endl;     // {pObj: 0xO, rc: 0xP, lexem: foo, row: 9, col: 35, rc: 1}
        cout << "rb: " << rb << endl;

        cout << endl << ">> RingBuffer: read (empty)" << endl;
        cout << "rb.readBuffer(): " << rb.readBuffer() << endl;     // {pObj: 0x0, rc: 0x0}
        cout << "rb: " << rb << endl;

        cout << endl;
        cout << "wuppie: " << wuppie << endl;       // {pObj: 0xN, rc: 0xM, lexem: wuppie, row: 1, col: 4, rc: 6} => 3x explizit, 3x Kopie

        cout << endl << ">> RingBuffer: write (n+1)" << endl;
        rb.writeBuffer(foo);
        rb.writeBuffer(wuppie);
        rb.writeBuffer(fluppie);
        rb.writeBuffer(fluppie2);                   // overwrites foo
        cout << "rb: " << rb << endl;
        cout << "foo: " << foo << endl;             // {pObj: 0xO, rc: 0xP, lexem: foo, row: 9, col: 35, rc: 1}
        cout << "wuppie: " << wuppie << endl;       // {pObj: 0xN, rc: 0xM, lexem: wuppie, row: 1, col: 4, rc: 6}
        cout << "rb.readBuffer(): " << rb.readBuffer() << endl;     // {pObj: 0xN, rc: 0xM, lexem: wuppie, row: 1, col: 4, rc: 7}
        cout << "rb: " << rb << endl;

        cout << endl;
    }


    return EXIT_SUCCESS;
}
