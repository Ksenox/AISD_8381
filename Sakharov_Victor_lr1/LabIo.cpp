#include "LabIo.h"

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
        cout << "> 3 - random example" << endl;
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
            case 3:
                return ReadRandomFromExamples();
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
    cin >> res;
    return res;
}

string ReadRandomFromExamples () {
    // Генерация рандомного числа от 0 до 9
    std::mt19937 mt(time(nullptr));
    std::uniform_int_distribution<int> dist(0, 9);
    std::string res = string(Examples[dist(mt)]);
    cout << "> " << res << endl;
    return res;
}

void ProceedOutput (const std::string output, const int indent) {
    for (int i = 0; i < indent; ++i) {
        cout << " ";
    }
    cout << output << endl;
}

void ProceedError (const std::string& error, int& pos) {
    if (pos != -1) {
        pos = -1;
        cout << "> " << error << endl;
    }
}
