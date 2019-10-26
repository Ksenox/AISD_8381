#include "console.h"

int sortBNConsole(dArr &bolts, dArr &nuts, flags &opt, ofstream &fout)
{
    return qsortNBConsole(bolts, nuts, 0, bolts.length, opt, fout);
}

int qsortNBConsole(dArr &bolts, dArr &nuts, int start, int length, flags &opt, ofstream &fout)
{
    int ret = 0;
    string output;
    bool equiv = false;
    int bigger = start;
    if (length - start > 1)
    {
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
                    return 2;
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
                cout << output << endl;
                cout << "Press any key to continue" << endl;
                getchar();
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
                    return 2;
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
                cout << output << endl;
                cout << "Press any key to continue" << endl;
                getchar();
            }
            i++;
        }
        ret = qsortNBConsole(bolts, nuts, start, bigger, opt, fout);
        if (ret)
            return ret;
        ret = qsortNBConsole(bolts, nuts, bigger, length-1, opt, fout);
    }
    return ret;
}

int startConsole()
{
    int load;
    string bolts;
    string nuts;
    dArr boltsArr;
    dArr nutsArr;
    flags opt;
    ofstream fout("output.txt");
    cout << "Type 1 for load arrays from file, 0 for console input" << endl;
    cin >> load;
    if (load)
    {
        string filePath;
        cout << "Type file path" << endl;
        cin >> filePath;
        ifstream fin(filePath, ios::in);
        if (fin)
        {
            getline(fin, bolts);
            getline(fin, nuts);
        }
        else
        {
            cout << "Error! Wrong file name" << endl;
            return 0;
        }
        fin.close();
    }
    else
    {
        cout << "Type bolts array:" << endl;
        cin.ignore(1);
        getline(cin, bolts);
        cout << "Type nuts array:" << endl;
        getline(cin, nuts);
    }
    int num = checkStr(bolts, nuts);
    switch (num) {
    case 0:
        cout << "Error! Inputs are empty\n";
        return 0;
        break;
    case ERR_SYMB_B:
        cout << "Error! Bolts input contains not only digits\n";
        return 0;
        break;
    case ERR_SYMB_N:
        cout << "Error! Nuts input contains not only digits\n";
        return 0;
        break;
    case ERR_LENGTH:
        cout << "Error! Number of bolts does not match number of nuts\n";
        return 0;
        break;
    }
    boltsArr = makeArray(bolts, num);
    nutsArr = makeArray(nuts, num);
    cout << "Type 1 for activating full info, 0 for short answer" << endl;
    cin >> opt.info;
    if (opt.info)
    {
        cout << "Type 1 for activating steps, 0 for result only" << endl;
        cin >> opt.step;
    }
    cin.ignore(1);
    if (!sortBNConsole(boltsArr, nutsArr, opt, fout))
    {
        if (!checkPairs(boltsArr, nutsArr))
            fout << "There are unpairable bolts and nuts\n";
        else
        {
            fout << "Sorting is finished\nBolts:\n";
            fout << getStrFromArray(boltsArr);
            fout << "Nuts:\n";
            fout << getStrFromArray(nutsArr);
            fout << "Pairs of bolts and nuts:\n";
            fout << getPairs(boltsArr, nutsArr);
        }
    }
    else
    {
        fout << "Sorting was cancelled\n";
    }
    fout.close();
    ifstream fin("output.txt");
    string output;
    string temp;
    while (!fin.eof())
    {
        getline(fin, temp);
        output += temp;
        output += "\n";
    }
    fin.close();
    cout << output;
}

