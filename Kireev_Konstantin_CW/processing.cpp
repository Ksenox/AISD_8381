#include <processing.h>

Hash h(SIZE);

void createHashTable(QTextEdit *&output, QTextEdit *&in, QTextEdit *&info)
{
    h.clearHashTable();
    ifstream f(qPrintable(in->toPlainText()), ios::in);
    string out;
    getline(f, out);
    f.close();

    QStringList array = QString::fromStdString(out).split(" ");
    string* a = new string[array.length()];
    for (int i = 0; i < array.length(); ++i)
        a[i] = array[i].toStdString();

    for (int i = 0; i < array.length(); i++)
        h.insertItem(a[i]);
    h.displayHash(output);
    h.displayInfo(info);
}

void insertItemToHashTable(QTextEdit *&output, QLineEdit *&input, QTextEdit *&info)
{
    string x = input->text().toStdString();
    h.insertItem(x);
    h.displayHash(output);
    h.displayInfo(info);
}

void deleteItemFromHashTable(QTextEdit *&output, QLineEdit *&input, QTextEdit *&info)
{
    string x = input->text().toStdString();
    h.deleteItem(x);
    h.displayHash(output);
    h.displayInfo(info);
}

void generateWorstCase(QTextEdit *&in, QLineEdit *&sizeac, QLineEdit *&len)
{
    int size = sizeac->text().toInt();
    if(size < 0)
        size -= size - 1;
    srand(time(NULL));
    string arr[size];
    for(int i = 0 ; i < size; i++)
        arr[i] = "";

    int newLen = len->text().toInt();
    if(newLen < 0)
        newLen -= newLen - 1;
    string newRandomValue;
    string a[newLen];
    for (int i = 0; i < newLen; i++)
    {
        newRandomValue = "";
        newRandomValue = generateRandomString(1);
        a[i] = newRandomValue;
    }

    for (int i = 0; i < size;)
    {
        for(int j = 0; j < newLen; j++)
            arr[i] += a[j];
        for (int k = 0; k < newLen; k++)
            swap(a[k], a[rand() % newLen]);
        i++;
    }

    string out = "";
    for (int i = 0; i < size; i++)
        out += arr[i] + " ";
    out.erase(out.size()-1, 1);

    ofstream f(qPrintable(in->toPlainText()), ios::out);
    f << out;
    f.close();
}

void generateWorstCase2(QTextEdit *&in, QLineEdit *&sizeac, QLineEdit *&len)
{
    int size = sizeac->text().toInt();
    if(size < 0)
        size -= size - 1;
    string arr[size];
    string newRandomValue = "";
    for(int i = 0 ; i < size; i++)
        arr[i] = "";
    int newLen = len->text().toInt();
    if(newLen < 0)
        newLen -= newLen - 1;
    newRandomValue = generateRandomString(newLen);
    for (int i = 0; i < size;)
    {
        arr[i] = newRandomValue;
        i++;
    }
    string out = "";
    for (int i = 0; i < size; i++)
        out += arr[i] + " ";
    out.erase(out.size()-1, 1);
    ofstream f(qPrintable(in->toPlainText()), ios::out);
    f << out;
    f.close();
}

void generateAverageCase(QTextEdit *&in, QLineEdit *&sizeac, QLineEdit *&len)
{
    int size = sizeac->text().toInt();
    if(size < 0)
        size -= size - 1;
    srand(time(NULL));
    string arr[size];
    for(int i = 0 ; i < size; i++)
        arr[i] = "";

    int newLen = len->text().toInt();
    if(newLen < 0)
        newLen -= newLen - 1;
    string newRandomValue;
    for (int i = 0; i < size;)
    {
        newRandomValue = "";
        newRandomValue = generateRandomString(newLen);
        arr[i] = newRandomValue;
        i++;
    }

    string out = "";
    for (int i = 0; i < size; i++)
        out += arr[i] + " ";
    out.erase(out.size()-1, 1);

    ofstream f(qPrintable(in->toPlainText()), ios::out);
    f << out;
    f.close();
}

string generateRandomString(int length)
{
    auto randchar = []() -> char
    {
        const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        return alphanum[ rand() % (sizeof(alphanum) - 1) ];
    };

    string str(length, 0);
    generate_n(str.begin(), length, randchar);
    return str;
}
