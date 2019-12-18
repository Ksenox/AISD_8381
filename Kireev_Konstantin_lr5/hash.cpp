#include "hash.h"

Hash::Hash(int n)
{
    this->BUCKET = n; // constructor
    table = new list<string>[BUCKET];
}

void Hash::insertItem(string value) // inserts a key into hash table
{
    int index = hashFunction(value);
    table[index].push_back(value);
}

void Hash::deleteItem(string key) // deletes a key from hash table
{
    // get the hash index of key
    int index = hashFunction(key);

    // find the key in (inex)th list
    list <string> :: iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++)
        if (*i == key)
            break;

    // if key is found in hash table, remove it
    if (i != table[index].end())
        table[index].erase(i);
}

void Hash::clearHashTable()
{
    for(int i = 0 ; i < SIZE; i++)
        table[i].clear();
}

int Hash::hashFunction(string x) // adaptive method
{
    int s = 0;
    for(int i = 0 ; i < x.length(); i++)
        s += x[i];
    return s % SIZE;
}

int Hash::hashFunction2(int x) // multiplicative method
{
    double r = x * 0.13 ;
    r = r - (int)r;
    return r * SIZE;
}

int Hash::hashFunction3(int x) // simple method
{
    return x % SIZE;
}

void Hash::displayInfo(QTextEdit *&info)
{
    int counter_coll = 0, counter = 0, counter_data = 0;
    for(int i = 0; i < SIZE; i++)
    {
        if(table[i].size() > 1)
            counter_coll += (table[i].size() - 1);
        counter += table[i].size();
        if(table[i].size() > 0)
            counter_data += 1;
    }
    float lf = (float)counter_data/BUCKET;
    info->setPlainText("Amount of Collisions: " + QString::number(counter_coll) +
                       "\nNumber of Stored Items: " + QString::number(counter) +
                       "\nNumber of Buckets: " + QString::number(BUCKET) +
                       "\nLoad Factor: " + QString::number(lf));
}

void Hash::displayHash(QTextEdit *&output) //print hash table
{
    QString outputstr;
    for (int i = 0; i < BUCKET; i++)
    {
        outputstr += "[" + QString::number(i) + "]  ";
        for (auto x : table[i])
            outputstr += QString::fromStdString(x) + " ----- ";
        outputstr += "NULL\n";
    }
    outputstr += "\n";
    output->setPlainText(outputstr);
}
