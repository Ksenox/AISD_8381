#include "console.h"


int startConsole()
{
    int load;
    string bolts;
    string nuts;
    dArr boltsArr;
    dArr nutsArr;
    flags opt;
    int n;
    opt.console = true;
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
    if (!sortBN(boltsArr, nutsArr, opt, fout, n))
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

