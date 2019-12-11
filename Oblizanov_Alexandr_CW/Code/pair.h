#ifndef PAIR_H
#define PAIR_H
#include "libraries.h"

// Class assignment:        Pair of 2 elements of any type for HASH TABLE
// Features:                Keeps info about being DELETED or being ACTIVE
template <typename S, typename T>
class Pair
{
public:
    Pair();
    Pair(S,T);
    Pair(Pair &);
    ~Pair();
    const Pair & operator=(const Pair &other);

    string toString();

    S getFirst();
    T getSecond();
    void setFirst(S);
    void setSecond(T);
    void setDeleted();

    int isActive();
    int wasDeleted();
private:
    S *f;           // FIRST element
    T *s;           // SECOND element
    bool active;    // ACTIVE state
    bool deleted;   // DELETED state
};

// Function assignment:     Empty pair constructor
// Features:                Sets ACTIVE and DELETED to false
template <typename S, typename T>
Pair<S,T>::Pair()
{
    f = NULL;
    s = NULL;
    active = false;
    deleted = false;
}

// Function assignment:     Pair constructor by two elements
// Features:                Sets ACTIVE to true and DELETED to false
template <typename S, typename T>
Pair<S,T>::Pair(S x, T y)
{
    f = new S;  *f = x;
    s = new T;  *s = y;
    active = true;
    deleted = false;
}

// Function assignment:     Pair constructor by another pair
// Features:                1. Copy elements from the other pair
//                          2. Copy ACTIVE and DELETED states
template <typename S, typename T>
Pair<S,T>::Pair(Pair &other)
{
    f = NULL; s = NULL;
    if (other.f != NULL)
        f = new S(*other.f);
    if (other.s != NULL)
        s = new T(*other.s);
    active = other.active;
    deleted = other.deleted;
}

// Function assignment:     Returns pair's FIRST element value
// Features:                Read only
template <typename S, typename T>
S Pair<S,T>::getFirst()
{
    if (f != NULL)
        return *f;
    else
        return NULL;
}

// Function assignment:     Returns pair's SECOND element value
// Features:                Read only
template <typename S, typename T>
T Pair<S,T>::getSecond()
{
    if (s != NULL)
        return *s;
    else
        return NULL;
}

// Function assignment:     Sets FIRST pair element
// Features:                1. Allocates memory if necessary
//                          2. Sets ACTIVE to true and DELETED to false
template <typename S, typename T>
void Pair<S,T>::setFirst(S x)
{
    if (f==NULL)
        f = new S;
    *f = x;
    active = true;
    deleted = false;
}

// Function assignment:     Sets SECOND pair element
// Features:                1. Allocates memory if necessary
//                          2. Sets ACTIVE to true and DELETED to false
template <typename S, typename T>
void Pair<S,T>::setSecond(T y)
{
    if (s == NULL)
        s = new T;
    *s = y;
    active = true;
    deleted = false;
}

// Function assignment:     Creates string in the format "(FIRST, SECOND)"
// Features:                1. If element is empty, writes "NULL" in its place
//                          2. If pair is empty, writes "NULL"
template <typename S, typename T>
string Pair<S,T>::toString()
{
    stringstream ss;
    if (active)
    {
        ss << "(";
        if (f == NULL)
            ss << "NULL";
        else
            ss << (*f);
        ss<<" ";
        if (s == NULL)
            ss << "NULL";
        else
            ss << (*s);
        ss << ")";
    }
    else
    {
        ss << "NULL";
    }
    return ss.str();
}

// Function assignment:     Returns true if pair is ACTIVE
template <typename S, typename T>
int Pair<S,T>::isActive()
{
    return active;
}

// Function assignment:     Returns true if pair is DELETED
template <typename S, typename T>
int Pair<S,T>::wasDeleted()
{
    return deleted;
}

// Function assignment:     Pair destructor
// Features:                1. Deletes elements
//                          2. Set ACTIVE and DELETED to false
template <typename S, typename T>
Pair<S,T>::~Pair()
{
    if (f != NULL)
        delete f;
    if (s != NULL)
        delete s;
    f = NULL;
    s = NULL;
    deleted = false;
    active = false;
}

// Function assignment:     Set DELETED to true
template <typename S, typename T>
void Pair<S,T>::setDeleted()
{
    deleted = true;
}

// Function assignment:     Copy another pair by operator =
// Features:                1. Deletes old elements if necessary
//                          2. Copy elements from another pair
//                          3. Copy ACTIVE and DELETED states
template <typename S, typename T>
const Pair<S,T> & Pair<S,T>::operator=(const Pair<S,T> &other)
{
    if(this != &other)
    {
        if(f != NULL)
        delete f;
        if(s != NULL)
        delete s;
        f = NULL; s = NULL;
        if (other.f != NULL)
        f = new S(*other.f);
        if (other.s != NULL)
        s = new T(*other.s);
        deleted = other.deleted;
        active = other.active;
    }
    return *this;
}

#endif // PAIR_H
