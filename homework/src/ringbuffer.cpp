
/*
 * SmartPointer.h
 *
 */

#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "smartpointer/RefCounter.h"


/**
 * Template class to represent smart pointers (like std::shared_ptr)
 */
template<class T>
class SmartPointer {
public:
    /**
     * Constructor
     *
     * Constructs a new smart pointer from a raw pointer, sets the reference
     * counter to 1.
     *
     * @param p is a raw pointer to the object to be shared
     */
    SmartPointer(T * const p = nullptr);

    /**
     * Copy constructor
     *
     * Constructs a new smart pointer from another smart pointer, increments the
     * reference counter.
     *
     * @param p is another smart pointer
     */
    SmartPointer(const SmartPointer& p);

    /**
     * Destructor
     *
     * Decrements the reference counter. If it reaches zero, the shared object will
     * be free'd.
     */
    virtual ~SmartPointer();

    /**
     * Dereferences the smart pointer
     *
     * @return a pointer to the shared object
     */
    T *operator->() const;

    /**
     * Dereferences the smart pointer
     *
     * @return a reference to the shared object
     */
    T &operator*() const;

    /**
     * Assignment
     *
     * Changes the shared object, thus we need first to do the same
     * like the destructor, then something like the constructor.
     *
     * @param p raw pointer to the new object
     */
    const SmartPointer &operator=(T * const p);

    /**
     * Assignment
     *
     * Changes the shared object, thus we need first to do the same
     * like the destructor, then something like the copy constructor.
     *
     * @param p is another smart pointer
     */
    const SmartPointer &operator=(const SmartPointer& p);

    /**
     * Comparison
     *
     * @return true, if `p` shares the same object
     */
    bool operator==(const SmartPointer& p) const;

    /**
     * Comparison
     *
     * @return true, if `p` does not shares the same object
     */
    bool operator!=(const SmartPointer& p) const;

    /**
     * Boolean context
     *
     * @return true, if we have a shared object; false otherwise
     */
    operator bool() const;

private:
    T* pObj;            ///< Pointer to the current shared object
    RefCounter *rc;     ///< Pointer to the reference counter (used for the current object)
};


#endif  // SMARTPOINTER_H




/*
 * RefCounter.h
 *
 */

#ifndef REFCOUNTER_H
#define REFCOUNTER_H


/**
 * Auxiliary class for counting the references (interface)
 */
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

    /**
     * Returns count
     *
     * @return n
     */
    unsigned int getRefCount() const;

    // Hide copy constructor and assignment operator
    RefCounter(const RefCounter&) = delete;
    RefCounter &operator=(const RefCounter&) = delete;

private:
    unsigned int n;     ///< How many SmartPointer share ownership of "our" object?
};


#endif /* REFCOUNTER_H */




/*
 * RingBuffer.h
 *
 */

#ifndef RINGBUFFER_H
#define RINGBUFFER_H


/**
 * Template class to represent a ring buffer
 *
 * @param T is the type of elements to be stored (via pointer of type `T*`)
 * @param size is the max. number of elements that can be stored
 * @param alloc_t is the type of the allocator used to allocate the pointers to the elements (optional)
 */
template <typename T, size_t size, typename alloc_t = std::allocator<T>>
class RingBuffer {
public:
    /**
     * Constructor that creates a new ring buffer for max. `size` elements
     *
     * Initialises the attributes and allocates memory for `size` elements of type `T*` and let the
     * pointer `elems` point to this new array
     */
    RingBuffer();

    /**
     * Destructor
     *
     * 1. Frees all elements using an allocator of type `alloc_t`
     * 2. Frees the dynamically allocated array `elems`
     */
    ~RingBuffer();

    /**
     * Reading the first (oldest) element
     *
     * If an element has been read, the `head` points to the next element and `count` is decremented.
     * The read element is **not** released.
     *
     * @return Returns a pointer to the first (i.e. oldest) element of the buffer, but does not (yet)
     * delete it; returns `nullptr` if buffer is empty
     */
    T* readBuffer();

    /**
     * Adding a new element
     *
     * Appends the new element to the end of the queue. If the buffer is full, the oldest element will be
     * deleted with an allocator of type `alloc_t` and the pointer to the new element will be inserted in
     * this location.
     *
     * @param data is a pointer to the element to be added (allocated with an allocator of type `alloc_t`)
     */
    void writeBuffer(T *data);

    /**
     * Indicates the number of elements in the ring buffer relative to its size on the LED display
     */
    void displayStatus() const;

private:
    alloc_t m_allocator;    ///< allocator to free element pointers

    size_t count;           ///< number of elements currently stored in the buffer
    size_t head;            ///< points to the beginning of the buffer (oldest element)
    T **elems;              ///< array with `size` places of type `T*`, dynamically allocated
};


#endif  // RINGBUFFER_H














/*
 * SmartPointerImpl.h
 *
 */

#ifndef SMARTPOINTERIMPL_H
#define SMARTPOINTERIMPL_H

#include <cstddef>
#include <cassert>

#include "smartpointer/NullPointerException.h"
#include "smartpointer/SmartPointer.h"


/*
 * ===========================================================================
 * Eigentliche Smartpointer-Klasse (Implementierung: Template -> .h)
 *
 *                                   MUSTERLOESUNG
 * ===========================================================================
 */

template<typename T>
SmartPointer<T>::SmartPointer(T * const ptr) :
        pObj(ptr), rc((ptr != nullptr) ? new RefCounter() : nullptr) {
    if (rc) {
        rc->inc();
    }
}

template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T> &sp) :
        pObj(sp.pObj), rc(sp.rc) {
    if (rc) {
        rc->inc();
    }
}

template<typename T>
SmartPointer<T>::~SmartPointer() {
    deleteObject();
}

template<typename T>
T *SmartPointer<T>::operator->() const {
    if (pObj == nullptr) {
        throw NullPointerException();
    }
    return pObj;
}

template<typename T>
T &SmartPointer<T>::operator*() const {
    if (pObj == nullptr) {
        throw NullPointerException();
    }
    return *pObj;
}

template<class T>
const T *SmartPointer<T>::getObject() const {
    return pObj;
}

template<class T>
const RefCounter *SmartPointer<T>::getRefCounter() const {
    return rc;
}

template<typename T>
const SmartPointer<T> &SmartPointer<T>::operator=(T * const p) {
    if (p == pObj) {
        return *this;
    }

    deleteObject();

    if (p != nullptr) {
        rc = new RefCounter();
        rc->inc();
    } else {
        rc = nullptr;
    }
    pObj = p;

    return *this;
}

template<typename T>
const SmartPointer<T> &SmartPointer<T>::operator=(const SmartPointer<T> &sp) {
    if (pObj == sp.pObj) {
        return *this;
    }

    deleteObject();

    rc = sp.rc;
    pObj = sp.pObj;
    if (rc != nullptr) {
        rc->inc();
    }

    return *this;
}

template<typename T>
bool SmartPointer<T>::operator==(const SmartPointer<T> &sp) const {
    return pObj == sp.pObj;
}

template<typename T>
bool SmartPointer<T>::operator!=(const SmartPointer<T> &sp) const {
    return !(*this == sp);
}

template<class T>
SmartPointer<T>::operator bool() const {
    return bool(pObj);
}

template<class T>
void SmartPointer<T>::deleteObject() {
    if (pObj) {
        assert(rc != nullptr);
        rc->dec();
        if (rc->isZero()) {
            delete rc;
            delete pObj;
            rc = nullptr;
            pObj = nullptr;
        }
    }
}


#endif  // SMARTPOINTERIMPL_H

/*
 * RefCounter.cpp
 *
 */

#include "smartpointer/RefCounter.h"

/*
 * ===========================================================================
 * Hilfsklasse zum Zaehlen der Referenzen: Implementierung
 *
 *
 *                                  MUSTERLOESUNG
 * ===========================================================================
 */

RefCounter::RefCounter() :
        n(0) {
}
void RefCounter::inc() {
    n++;
}
void RefCounter::dec() {
    n--;
}
bool RefCounter::isZero() const {
    return n == 0;
}
unsigned int RefCounter::getRefCount() const {
    return n;
}


/*
 * RingBuffer.h
 *
 */

#ifndef RINGBUFFER_H
#define RINGBUFFER_H


#include <cstdlib>      // size_t
#include <cstddef>
#include <iostream>

using namespace std;


/**
 * Template class to represent a ring buffer
 *
 * @param T is the type of elements to be stored (via pointer of type `T*`)
 * @param size is the max. number of elements that can be stored
 * @param alloc_t is the type of the allocator used to allocate the pointers to the elements (optional)
 */
template <typename T, size_t size, typename alloc_t = std::allocator<T>>
class RingBuffer {
public:
    /**
     * Constructor that creates a new ring buffer for max. `size` elements
     *
     * Initialises the attributes and allocates memory for `size` elements of type `T*` and let the
     * pointer `elems` point to this new array
     */
    RingBuffer() : m_allocator(alloc_t()), count(0), head(0) {
        elems = static_cast<T**>(malloc(size * sizeof(T*)));
        if (!elems) throw bad_alloc();
    }

    /**
     * Destructor
     *
     * 1. Frees all elements using an allocator of type `alloc_t`
     * 2. Frees the dynamically allocated array `elems`
     */
    ~RingBuffer() {
        /* Elemente mit m_allocator freigeben */
        while (count) {
            T* data = readBuffer();
            m_allocator.deallocate(data, 1);
        }

        /* eigentlichen Puffer freigeben */
        free(elems);
    }

    /**
     * Reading the first (oldest) element
     *
     * If an element has been read, the `head` points to the next element and `count` is decremented.
     * The read element is **not** released.
     *
     * @return Returns a pointer to the first (i.e. oldest) element of the buffer, but does not (yet)
     * delete it; returns `nullptr` if buffer is empty
     */
    T* readBuffer() {
        if (count) {
            T *elem = elems[head];
            head = (head + 1) % size;
            --count;
            return elem;
        }
        return nullptr;
    }

    /**
     * Adding a new element
     *
     * Appends the new element to the end of the queue. If the buffer is full, the oldest element will be
     * deleted with an allocator of type `alloc_t` and the pointer to the new element will be inserted in
     * this location.
     *
     * @param data is a pointer to the element to be added (allocated with an allocator of type `alloc_t`)
     */
    void writeBuffer(T *data) {
        size_t tail;

        if (data) {
            /* Puffer voll? Head freigeben */
            if (count == size) {
                m_allocator.deallocate(elems[head], 1);
                head = (head + 1) % size;
                --count;
            }

            /* Daten ins Ende schreiben */
            tail = (head + count) % size;
            elems[tail] = data;
            ++count;
        }
    }

    /**
     * Indicates the number of elements in the ring buffer relative to its size on the LED display
     */
    void displayStatus() const {
        cout << "RingBuffer: Anzahl der Elemente: " << count << endl;
        cout << "RingBuffer: Kapazizät: " << size << " (noch " << size-count << " Elemente frei)" << endl;
    }

private:
    alloc_t m_allocator;    ///< allocator to free element pointers

    size_t count;           ///< number of elements currently stored in the buffer
    size_t head;            ///< points to the beginning of the buffer (oldest element)
    T **elems;              ///< array with `size` places of type `T*`, dynamically allocated
};


#endif  // RINGBUFFER_H








/*
 * mainsmartpointer.cpp
 *
 *                                  MUSTERLOESUNG
 *
 *
 */

#include <cstdlib>
#include <iostream>

#include "smartpointer/SmartPointer.h"

using namespace std;


class Foo {
public:
    ~Foo() {
        cout << "Destruktor Foo" << endl;
    }
    SmartPointer<Foo> ptr;
};


void f1() {
    Foo *c = new Foo;
    SmartPointer<Foo> p3 = c;

    cout << "ab hier wirds spannend ;) \n\n" << endl;
}

void f2() {
    Foo *a = new Foo;
    Foo *b = new Foo;

    SmartPointer<Foo> p1 = a;
    SmartPointer<Foo> p2 = b;
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

    return 0;
}
