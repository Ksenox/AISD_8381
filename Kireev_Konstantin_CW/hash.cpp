#include "hash.h"
#include <processing.h>
long int count_iterations = 0;
long int max_it = 0;

Hash::Hash(int n)
{
    this->BUCKET = n; // constructor
    this->ITEMS = 0;
    table = new list<string>[BUCKET];
}

void Hash::insertItem(string value) // inserts a key into hash table
{
    int index = hashFunction2(value);
    count_iterations++;
    for (auto x : table[index])
        count_iterations++;
    table[index].push_back(value);

    if(table[index].size() > max_it)
        max_it = table[index].size();
    ITEMS++;
    if((float)ITEMS/BUCKET > 0.7)
        resize();
}

void Hash::deleteItem(string key) // deletes a key from hash table
{
    // get the hash index of key
    int index = hashFunction2(key);

    // find the key in (index)th list
    list <string> :: iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++)
        if (*i == key)
            break;

    // if key is found in hash table, remove it
    if (i != table[index].end())
    {
        table[index].erase(i);
        ITEMS--;
    }
}

void Hash::resize()
{
    list <string> *temp = new list <string>[BUCKET];

    for (int i = 0; i < BUCKET; i++)
        for (auto x : table[i])
        {
            int index = hashFunction2(x);
            temp[index].push_back(x);
        }
    max_it = 0;
    count_iterations = 0;
    ITEMS = 0;
    for(int i = 0 ; i < BUCKET; i++)
        table[i].clear();
    BUCKET *= 2;
    table = new list <string>[BUCKET];

    for (int i = 0; i < BUCKET/2; i++)
        for (auto x : temp[i])
        {
            int index = hashFunction2(x);
            table[index].push_back(x);
            count_iterations += table[index].size();
            ITEMS++;
        }
}

void Hash::clearHashTable()
{
    max_it = 0;
    count_iterations = 0;
    ITEMS = 0;
    for(int i = 0 ; i < BUCKET; i++)
        table[i].clear();
    BUCKET = SIZE;
}

int Hash::hashFunction(string x) // adaptive method
{
    long int s = 0;
    for(int i = 0 ; i < x.length(); i++)
        s += x[i];
    return s % BUCKET;
}

int Hash::hashFunction2(string x) // multiplicative method
{
    const int p = 31;
    const int m = pow(10, 9)+9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (int i = 0 ; i < x.length(); i++)
    {
        hash_value = (hash_value + (x[i] - '0' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value % BUCKET;
}

int Hash::hashFunction3(string x) // simple method
{
    return BUCKET;
}

void Hash::displayInfo(QTextEdit *&info)
{
    ofstream f("C:/Users/Adm/Desktop/testdata31.txt", ios::app);
    string out = "";
    int counter_coll = 0;
    for(int i = 0; i < BUCKET; i++)
        if(table[i].size() > 1)
            counter_coll += (table[i].size() - 1);

    info->setPlainText("Amount of Collisions: " + QString::number(counter_coll) +
                       "\nNumber of Stored Items: " + QString::number(ITEMS) +
                       "\nNumber of Buckets: " + QString::number(BUCKET) +
                       "\nLoad Factor: " + QString::number((float)ITEMS/BUCKET) +
                       "\nAmount of iterations of inserts: " + QString::number(count_iterations) +
                       "\nMaximum of iterations in single chain: " + QString::number(max_it));

    out = to_string(count_iterations) + " " + to_string(counter_coll) + " " + to_string(max_it);
    f << out << endl;
    f.close();
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
