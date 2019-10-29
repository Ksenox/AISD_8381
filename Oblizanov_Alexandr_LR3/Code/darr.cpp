#include "darr.h"

int strCount(string &input)
{
    unsigned int count = 0;
    unsigned int ptr = 0;
    bool num = false;
    if (input.empty())
        return 0;
    for (ptr = 0; ptr < input.length(); ptr++)
    {
        if (input[ptr] == ' ')
        {
            if (num != false)
            {
                count++;
                num = false;
            }
        }
        else
        {
            if (!isdigit(input[ptr]))
                return -1;
            num = true;
        }
    }
    if (num == true)
        count++;
    return static_cast<int>(count);
}

int checkStr(string &bolts, string &nuts)
{
    int nB = strCount(bolts);
    if (nB == -1)
        return ERR_SYMB_B;
    int nN = strCount(nuts);
    if (nN == -1)
        return ERR_SYMB_N;
    if (nN == nB)
        return nN;
    return ERR_LENGTH;
}

dArr makeArray(string &input, int length)
{
    dArr output;
    output.base = new int[length];
    output.length = length;
    stringstream temp;
    temp << input;
    for (int i=0; i<length; i++)
    {
        temp >> output.base[i];
    }
    return output;
}

string getStrFromArray(dArr &input)
{
    string output;
    for (int i=0; i<input.length; i++)
    {
        output += to_string(input.base[i]);
        output += " ";
    }
    output += '\n';
    return output;
}

string getStrCmpAction(dArr &bolts, int ptr1, dArr &nuts, int ptr2)
{
    string output;
    output += "Comparing elements:\nBolts:\n";
    for (int i=0; i<bolts.length; i++)
    {
        if (i == ptr1)
            output += "{";
        output += to_string(bolts.base[i]);
        if (i == ptr1)
            output += "}";
        output += " ";
    }
    output += "\nNuts:\n";
    for (int i=0; i<nuts.length; i++)
    {
        if (i == ptr2)
            output += "{";
        output += to_string(nuts.base[i]);
        if (i == ptr2)
            output += "}";
        output += " ";
    }
    output += '\n';
    return output;
}

string getStrSwapAction(dArr &input, int ptr1, int ptr2)
{
    string output;
    output += "Swapping elements: ";
    for (int i=0; i<input.length; i++)
    {
        if (i == ptr1 || i == ptr2)
            output += "{";
        output += to_string(input.base[i]);
        if (i == ptr1 || i == ptr2)
            output += "}";
        output += " ";
    }
    output += "\n";
    return output;
}

int checkPairs(dArr &bolts, dArr &nuts)
{
    for (int i=0; i<bolts.length; i++)
    {
        if (bolts.base[i] != nuts.base[i])
            return 0;
    }
    return 1;
}

string getPairs(dArr &bolts, dArr &nuts)
{
    string output;
    for (int i=0; i<bolts.length; i++)
    {
        if (bolts.base[i] == nuts.base[i])
        {
            output += "Pair: (";
            output += to_string(bolts.base[i]);
            output += ", ";
            output += to_string(nuts.base[i]);
            output += ")\n";
        }
    }
    return output;
}

int qsortNB(dArr &bolts, dArr &nuts, int start, int length, flags &opt, ofstream &fout, int &n)
{
    int ret = 0;
    QMessageBox out;
    out.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    string output;
    bool equiv = false;
    int bigger = start;
    if (length - start > 1)
    {
        n++;
        int center = nuts.base[length-1];
        int i = start;
        while (i<length-1)
        {
            if (opt.info)
                output = getStrCmpAction(bolts, i, nuts, length-1);
            if (bolts.base[i] < center)
            {
                if (opt.step)
                {
                    output += "Element from bolts is smaller, swapping to left part\n";
                    output += getStrSwapAction(bolts, i, bigger);
                }
                swap(bolts.base[i], bolts.base[bigger]);
                if (opt.step)
                {
                    output += "Result:\nBolts:\n";
                    output += getStrFromArray(bolts);
                    output += "Nuts:\n";
                    output += getStrFromArray(nuts);
                }
                bigger++;
            }
            if (bolts.base[i] == center)
            {
                if (equiv == false)
                    equiv = true;
                else
                {
                    fout << "Error! Found same bolts" << endl;
                    return 2;
                }
                if (opt.step)
                {
                    output += "Element from bolts is equal, swapping to end\n";
                    output += getStrSwapAction(bolts, i, length-1);
                }
                swap(bolts.base[i], bolts.base[length-1]);
                if (opt.step)
                {
                    output += "Result:\nBolts:\n";
                    output += getStrFromArray(bolts);
                    output += "Nuts:\n";
                    output += getStrFromArray(nuts);
                }
                continue;
            }
            if (opt.info)
                fout << output << endl;
            if (opt.step)
            {
                out.setText(QString::fromStdString(output));
                if (out.exec() == QMessageBox::Cancel)
                          return 1;
            }
            i++;
        }
        equiv = false;
        center = bolts.base[length-1];
        bigger = start;
        i = start;
        while (i<length-1)
        {
            if (opt.info)
                output = getStrCmpAction(bolts, length-1, nuts, i);
            if (nuts.base[i] < center)
            {
                if (opt.step)
                {
                    output += "Element from nuts is smaller, swapping to left part\n";
                    output += getStrSwapAction(nuts, i, bigger);
                }
                swap(nuts.base[i], nuts.base[bigger]);
                if (opt.step)
                {
                    output += "Result:\nBolts:\n";
                    output += getStrFromArray(bolts);
                    output += "Nuts:\n";
                    output += getStrFromArray(nuts);
                }
                bigger++;
            }
            if (nuts.base[i] == center)
            {
                if (equiv == false)
                    equiv = true;
                else
                {
                    fout << "Error! Found same nuts" << endl;
                    return 2;
                }
                if (opt.step)
                {
                    output += "Element from nuts is equal, swapping to end\n";
                    output += getStrSwapAction(nuts, i, length-1);
                }
                swap(nuts.base[i], nuts.base[length-1]);
                if (opt.step)
                {
                    output += "Result:\nBolts:\n";
                    output += getStrFromArray(bolts);
                    output += "Nuts:\n";
                    output += getStrFromArray(nuts);
                }
                continue;
            }
            if (opt.info)
                fout << output << endl;
            if (opt.step)
            {
                out.setText(QString::fromStdString(output));
                if (out.exec() == QMessageBox::Cancel)
                    return 1;
            }
            i++;
        }
        ret = qsortNB(bolts, nuts, start, bigger, opt, fout, n);
        if (ret)
            return ret;
        ret = qsortNB(bolts, nuts, bigger, length-1, opt, fout, n);
    }
    return ret;
}

int sortBN(dArr &bolts, dArr &nuts, flags &opt, ofstream &fout, int &n)
{
    return qsortNB(bolts, nuts, 0, bolts.length, opt, fout, n);
}
