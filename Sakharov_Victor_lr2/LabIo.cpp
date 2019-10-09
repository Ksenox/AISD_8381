#include "LabIo.h"

bool errorFlag;
int errorPos;

// Функция ввода данных
string ProceedInput (int argc, char** argv) {
    cout << "> Lab work #1" << endl;
    if (argc > 1) {
        cout << "> Reading from argv..." << endl;
        string ins(argv[1]);
        return ins;
    }
    else {
        cout << "> Choose your input" << endl;
        cout << "> 0 - from console" << endl;
        cout << "> 1 - from file input.txt" << endl;
        cout << "> 2 - from custom file" << endl;
        int command = 0;
        cin >> command;
        string input;

        switch (command) {
            case 0:
                cout << "> Your input: ";
                return ReadFromConsole();
            case 1:
                return ReadFromFile("input.txt");
            case 2:
                cout << "> Filename: ";
                cin >> input;
                return ReadFromFile(input);
            default:
                return ProceedInput(0, nullptr);
        }
    }
}

string ReadFromFile (std::string filename) {
    ifstream infile(filename);
    if (!infile) {
        cout << "> File can't be open!" << endl;
        return "";
    }
    string res;
    infile >> res;
    return res;
}

string ReadFromConsole () {
    string res;
    getline(cin, res);
    return res;
}

void ProceedError (const std::string& error, int pos) {
    if (!errorFlag) {
        errorFlag = true;
        errorPos = pos;
        cout << "> " << pos << ": " << error << endl;
    }
    //cout << "> " << pos << ": " << error << endl;
}
