#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <cmath>
#include <cctype>
#include <cstring>
using namespace std;

/*10. Построить синтаксический анализатор для определяемого далее понятия константное_выражение.
константное_выражение::= ряд_цифр|константное_выражение знак_операции константное_выражение
знак_операции::= + | - | *
ряд_цифр::= цифра | цифра ряд_цифр */

string ProceedInput(int argc, char** argv);
string ReadFromFile(std::string filename);
string ReadFromConsole();
void ErrorOut(const string& str);
void NextSymbol(string & str, int & pos);
bool ConstExpression(string & str, int & pos);
bool OperationSign(string & str, int & pos);
bool NumberSequence(string & str, int & pos, bool found = false);


int main (int argc, char** argv) {
    string input = ProceedInput(argc, argv);
    int pos = 0;
    bool result = ConstExpression(input, pos);
    if (result) cout << endl << "OK" << endl;
    else cout << endl << "ERROR" << endl;
    return 0;
}

string ProceedInput (int argc, char** argv) {
    cout << "Lab work #1" << endl;
    if (argc > 1) {
        cout << "Reading from argv..." << endl;
        string ins(argv[1]);
        return ins;
    }
    else {
        cout << "Choose your input" << endl;
        cout << "0 - from console" << endl;
        cout << "1 - from file" << endl;
        int num = 0;
        cin >> num;
        string input;
        switch (num) {
            case 0:
                cout << "Your input: ";
                return ReadFromConsole();
            case 1:
                cout << "Filename: ";
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
        cout << "File can't be open!" << endl;
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

void NextSymbol (string& str, int& pos) {
    cout << str[0];
    str = str.substr(1);
    pos++;
}

void ErrorOut (const string& str) {
    static bool first = true;
    if (first) {
        cout << endl << str;
        first = false;
    }
}

//константное_выражение::= ряд_цифр|константное_выражение знак_операции константное_выражение
bool ConstExpression (string& str, int& pos) {
    if (str.length() == 0)
        return false;
    if (NumberSequence(str, pos)) {
        if (OperationSign(str, pos)) {
            if (ConstExpression(str, pos)) {
                return true;
            }
            else {
                ErrorOut("Const expression expected");
                return false;
            }
        }
        return true;
    }
    ErrorOut("CNumber sequence expected");
    return false;
}

//знак_операции::= + | - | *
bool OperationSign (string& str, int& pos) {
    if (str.length() == 0)
        return false;
    if (str.length() > 0 && (str[0] == '+' || str[0] == '-' || str[0] == '*')) {
        NextSymbol(str, pos);
        return true;
    }
    ErrorOut("Sign expected");
    return false;
}

//ряд_цифр::= цифра | цифра ряд_цифр
bool NumberSequence (string& str, int& pos, bool found) {
    if (str.length() == 0)
        return false;
    if (str.length() > 0 && isdigit(str[0])) {
        NextSymbol(str, pos);
        if (NumberSequence(str, pos, true)) {
            return true;
        }
        return true;
    }
    if (!found) ErrorOut("Number sequence expected");
    return false;
}