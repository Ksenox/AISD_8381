#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "cvector.h"
#define SIZE 256

template <typename S, typename T>
class HashTable
{
public:
    HashTable();
    HashTable(unsigned int size);

    void setSize(int size);
    unsigned int getSize();
    void setStep(bool s);
    unsigned int getItemCounter();

    Pair<S,T> & operator[](unsigned int index);
    unsigned int set(S x, T y, unsigned int index);
    Pair<S,T> get(S key, unsigned int index);
    unsigned int remove(S key, unsigned int index);
    void clear();

    string getString(S key, unsigned int index);
    string print();
    string printStep(unsigned int index);
private:
    CVector< Pair<S,T> > table;
    unsigned int itemCounter;
    bool step;
};

template <typename S, typename T>
HashTable<S,T>::HashTable()
{
    itemCounter = 0;
    setSize(SIZE);
}

template <typename S, typename T>
HashTable<S,T>::HashTable(unsigned int size)
{
    itemCounter = 0;
    setSize(size);
}

template <typename S, typename T>
void HashTable<S,T>::setSize(int size)
{
    table.resize(size);
}

template <typename S, typename T>
void HashTable<S,T>::setStep(bool s)
{
    step = s;
}

template <typename S, typename T>
unsigned int HashTable<S,T>::getSize()
{
    return table.getCapacity();
}

template <typename S, typename T>
unsigned int HashTable<S,T>::getItemCounter()
{
    return itemCounter;
}

template <typename S, typename T>
unsigned int HashTable<S,T>::set(S x, T y, unsigned int index)
{
    unsigned int counter = 1;
    if (index + 5 >= table.getCapacity())
        table.resize((index + 5) * 2);
    while (table[index].isActive())
    {
        index++;
        counter++;
        if (index + 5 >= table.getCapacity())
            table.resize((index + 5) * 2);
    }
    table[index].setFirst(x);
    table[index].setSecond(y);
    itemCounter++;
    return counter;
}

template <typename S, typename T>
Pair<S,T> HashTable<S,T>::get(S key, unsigned int index)
{
    while (table[index].isActive())
    {
        if (table[index].wasDeleted())
        {
            index++;
            continue;
        }
        if (table[index].getFirst() != key)
            index++;
        else
            break;
    }
    return table[index];
}

template <typename S, typename T>
unsigned int HashTable<S,T>::remove(S key, unsigned int index)
{
    unsigned int counter = 1;
    while (table[index].isActive())
    {
        printStep(index);
        if (table[index].wasDeleted())
        {
            index++;
            counter++;
            continue;
        }
        if (table[index].getFirst() != key)
        {
            index++;
            counter++;
        }
        else
            break;
    }
    if (table[index].isActive())
    {
        table[index].~Pair();
        table[index].setDeleted();
        itemCounter -= 1;
        return counter;
    }
    else
        return 0;

}

template <typename S, typename T>
void HashTable<S,T>::clear()
{
    for (unsigned int i=0; i<table.getCapacity(); i++)
    {
        table[i].~Pair();
    }
    itemCounter = 0;
}

template <typename S, typename T>
string HashTable<S,T>::getString(S key, unsigned int index)
{
    string output;
    while (table[index].isActive())
    {
        if (table[index].getFirst() != key)
            index++;
        else
            break;
    }
    if (table[index].isActive())
        output = table[index].toString();
    else
        output = "No key in table";
    return output;
}

template <typename S, typename T>
string HashTable<S,T>::print()
{
    string output;
    for (unsigned int i=0; i<table.getCapacity(); i++)
    {
        if (table[i].isActive() && !table[i].wasDeleted())
        {
            output += to_string(i);
            output += "\t";
            output += table[i].toString();
            output += "\n";
        }
    }
    return output;
}

template <typename S, typename T>
string HashTable<S,T>::printStep(unsigned int index)
{
    string output;
    for (unsigned int i=0; i<table.getCapacity(); i++)
    {
        if (table[i].isActive() && !table[i].wasDeleted())
        {
            if (i == index)
                output += "{";
            output += to_string(i);
            output += "\t";
            output += table[i].toString();
            if (i == index)
                output += "}";
            output += "\n";
        }
        if (table[i].wasDeleted() && i == index)
        {
            output += "Passing deleted element\n";
        }
    }
    QMessageBox out;
    out.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    out.setText(QString::fromStdString(output));
    if (out.exec() == QMessageBox::Cancel)
              return output;
}

template <typename S, typename T>
Pair<S,T> & HashTable<S,T>::operator[](unsigned int index)
{
    return table[index];
}

#endif // HASHTABLE_H
