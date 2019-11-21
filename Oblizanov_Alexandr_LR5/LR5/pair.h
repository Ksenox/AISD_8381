#ifndef PAIR_H
#define PAIR_H
#include "libraries.h"

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
    S *f;
    T *s;
    bool active;
    bool deleted;
};

template <typename S, typename T>
Pair<S,T>::Pair()
{
    f = NULL;
    s = NULL;
    active = false;
    deleted = false;
}

template <typename S, typename T>
Pair<S,T>::Pair(S x, T y)
{
    f = new S;  *f = x;
    s = new T;  *s = y;
    active = true;
    deleted = false;
}

template <typename S, typename T>
S Pair<S,T>::getFirst()
{
    if (f != NULL)
        return *f;
    else
        return NULL;
}

template <typename S, typename T>
T Pair<S,T>::getSecond()
{
    if (s != NULL)
        return *s;
    else
        return NULL;
}

template <typename S, typename T>
void Pair<S,T>::setFirst(S x)
{
    if (f==NULL)
        f = new S;
    *f = x;
    active = true;
    deleted = false;
}

template <typename S, typename T>
void Pair<S,T>::setSecond(T y)
{
    if (s == NULL)
        s = new T;
    *s = y;
    active = true;
    deleted = false;
}

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
        ss<<",";
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

template <typename S, typename T>
int Pair<S,T>::isActive()
{
    return active;
}

template <typename S, typename T>
int Pair<S,T>::wasDeleted()
{
    return deleted;
}

template <typename S, typename T>
Pair<S,T>::Pair(Pair &other)
{
    f = NULL; s = NULL;
    if (other.f != NULL)
        f = new S(*other.f);
    if (other.s != NULL)
        s = new T(*other.s);
}

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

template <typename S, typename T>
void Pair<S,T>::setDeleted()
{
    deleted = true;
}

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
