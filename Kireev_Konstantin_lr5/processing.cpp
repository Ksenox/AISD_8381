#include <processing.h>

Hash h(SIZE);

void createHashTable(QTextEdit *&output, QTextEdit *&in, QTextEdit *&info)
{
    h.clearHashTable();
    QStringList array = in->toPlainText().split(" ");
    string* a = new string[array.length()];
    for (int i = 0; i < array.length(); ++i)
        a[i] = array[i].toStdString();

    for (int i = 0; i < array.length(); i++)
        h.insertItem(a[i]);
    h.displayHash(output);
    h.displayInfo(info);
}

void deleteItemFromHashTable(QTextEdit *&output, QLineEdit *&input)
{
    string x = input->text().toStdString();
    h.deleteItem(x);
    h.displayHash(output);
}

void generateAverageCase(QTextEdit *&in, QLineEdit *&sizeac)
{
    int size = sizeac->text().toInt();
    srand(time(NULL));
    string arr[size];
    for(int i = 0 ; i < size; i++)
        arr[i] = "";

    size_t newLen;
    string newRandomValue;
    for (int i = 0; i < size;)
    {
        newLen = rand() % 10 + 1;
        newRandomValue = "";
        newRandomValue = generateRandomString(newLen);
        arr[i] = newRandomValue;
        i++;
    }
    QString outputstr;
    for (int i = 0; i < size; i++)
        outputstr += QString::fromStdString(arr[i]) + " ";
    outputstr.remove(outputstr.size()-1, 1);
    in->setPlainText(outputstr);
}

string generateRandomString(size_t length)
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
