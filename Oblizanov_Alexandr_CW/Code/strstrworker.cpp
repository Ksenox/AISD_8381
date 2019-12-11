#include "strstrworker.h"

StrStrWorker::StrStrWorker()
{
    iter = 0;
}
int StrStrWorker::generateFile(int size, int maxLength, QString fileName, bool worstCase, int hFuncNum)
{
    string file = fileName.toStdString();
    ofstream out(file);
    QMessageBox message;
    if (!out)
        return BAD_FILE;
    if (size <= 0 || size > SIZE_LIMIT)
        return BAD_SIZE;
    if (maxLength <= 0 || (maxLength == 2 && size > (74+74*74)) || (maxLength == 1 && size > 74))
        return BAD_LENGTH;
    string key;
    string value;
    unsigned int length;
    default_random_engine generator;
    uniform_int_distribution<int> lengthGen(1, maxLength);
    uniform_int_distribution<char> symbolsGen(48, 122);
    QStringList backup;
    int hFunc = (122+48)/2*maxLength; //midrange for worst1
    int keySum = 0;
    if (worstCase)
    {
        switch (hFuncNum)
        {
        case 1:
            for (int i=0; i<size; i++)
            {
                key.clear();
                value.clear();
                keySum = 0;
                while (keySum <= hFunc - 122*2)
                {
                    key += symbolsGen(generator);
                    keySum += key.back();
                }
                key += static_cast<char>((hFunc - keySum)/2);
                keySum += key.back();
                key += static_cast<char>(hFunc - keySum);
                length = static_cast<unsigned int>(lengthGen(generator));
                for (unsigned int j=0; j<length; j++)
                {
                    value += symbolsGen(generator);
                }
                out << key << " " << value << endl;
            }
            break;
        case 2:
            length = static_cast<unsigned int>(maxLength);
            for (int i=0; i<size; i++)
            {
                key.clear();
                value.clear();
                key += 'a';
                for (unsigned int j=0; j<length-2; j++)
                {
                    key += symbolsGen(generator);
                    value += symbolsGen(generator);
                }
                key += 'z';
                out << key << " " << value << endl;
            }
            break;
        case 3:
            int i = 0;
            while (i<size)
            {
                length = 0;
                key.clear();
                value.clear();
                keySum = 0;
                while (keySum <= hFunc - 122*2)
                {
                    key += symbolsGen(generator);
                    keySum += key.back();
                    length++;
                }
                key += static_cast<char>((hFunc - keySum)/2);
                keySum += key.back();
                key += static_cast<char>(hFunc - keySum);
                if (length+2 != static_cast<unsigned int>(maxLength))
                    continue;
                length = static_cast<unsigned int>(lengthGen(generator));
                for (unsigned int j=0; j<length; j++)
                {
                    value += symbolsGen(generator);
                }
                i++;
                out << key << " " << value << endl;
            }
        }
    }
    else
    {
        int i = 0;
        while (i<size)
        {
            key.clear();
            value.clear();
            length = static_cast<unsigned int>(lengthGen(generator));
            for (unsigned int j=0; j<length; j++)
            {
                key += symbolsGen(generator);
            }
            length = static_cast<unsigned int>(lengthGen(generator));
            for (unsigned int j=0; j<length; j++)
            {
                value += symbolsGen(generator);
            }
            if (backup.count(QString::fromStdString(key)))
                continue;
            backup.push_back(QString::fromStdString(key));
            i++;
            out << key << " " << value << endl;
        }
    }
    out.close();
    return 0;
}

QString StrStrWorker::getFromFile(QString fileName)
{
    ifstream fin(qPrintable(fileName), ios::in);
    string out;
    string temp;
    while (true)
    {
        getline(fin, temp);
        out += temp;
        if (!fin.eof())
            out += "\n";
        else
            break;
    }
    fin.close();
    return QString::fromStdString(out);
}

hCreateInfo StrStrWorker::createHashTable(QString input, int hFuncNum, int factor, QString fileName)
{
    ofstream output(fileName.toStdString());
    if (!output)
    {
        info.error = true;
    }
    hTable.setSize(SIZE);
    hTable.clear();
    QStringList pairs = input.split("\n");
    if (pairs[pairs.length()-1].toStdString() == "")
        pairs.pop_back();
    QStringList temp;
    unsigned int iter = 0;
    unsigned int sumIter = 0;
    unsigned int maxIter = 0;
    unsigned int size = static_cast<unsigned int>(factor*pairs.length());
    for (int i=0; i<pairs.length(); i++)
    {
        temp = pairs[i].split(" ");
        if (temp.length() != 2)
        {
            if (!info.error)
            {
                output << "Error! Incorrect file content in line:\n\"";
                output << pairs[i].toStdString();
                output << "\"";
                info.error = true;
            }
            return info;
        }
        switch (hFuncNum)
        {
        case 1:
            iter = hTable.set(temp[0].toStdString(), temp[1].toStdString(), hFunc1(temp[0].toStdString(), size));
            break;
        case 2:
            iter = hTable.set(temp[0].toStdString(), temp[1].toStdString(), hFunc2(temp[0].toStdString(), size));
            break;
        case 3:
            iter = hTable.set(temp[0].toStdString(), temp[1].toStdString(), hFunc3(temp[0].toStdString(), size));
        }
        if (iter > maxIter)
            maxIter = iter;
        sumIter += iter;
    }
    info.hSize = hTable.getSize();
    info.itemCounter = hTable.getItemCounter();
    info.sumIterNum = sumIter;
    info.maxIterNum = maxIter;
    if (!info.error)
    {
        output << "Table length:\t";
        output << QString::number(info.hSize).toStdString();
        output << "\nNumber of items:\t";
        output << QString::number(info.itemCounter).toStdString();
        output << "\nAll inserts iterations:\t";
        output << QString::number(sumIter).toStdString();
        output << "\nMax insert iterations:\t";
        output << QString::number(maxIter).toStdString();
        output << "\n\n";
        output << QString::fromStdString(hTable.print()).toStdString();
        output.close();
    }
    info.error = false;
    return info;
}

unsigned int StrStrWorker::hFunc1(string key, unsigned int size)
{
    unsigned int result = 0;
    for (unsigned int i=0; i<key.length(); i++)
    {
        result += static_cast<unsigned char>(key[i]);
    }
    result %= size;
    return result;
}

unsigned int StrStrWorker::hFunc2(string key, unsigned int size)
{
    unsigned int result = 0;
    result += static_cast<unsigned char>(key.front());
    result += static_cast<unsigned char>(key.back());
    result *= key.length();
    result %= size;
    return result;
}

unsigned int StrStrWorker::hFunc3(string key, unsigned int size)
{
    unsigned int result = 0;
    if (key.length() > 0)
        result += static_cast<unsigned char>(key[0]);
    for (unsigned int i=1; i<key.length(); i++)
    {
        result += static_cast<unsigned char>(key[i]);
    }
    result *= key.length();
    result %= size;
    return result;
}


void StrStrWorker::saveStrToFile(QString output, QString fileName)
{
    ofstream fout(qPrintable(fileName));
    fout << qPrintable(output);
    fout.close();
}
