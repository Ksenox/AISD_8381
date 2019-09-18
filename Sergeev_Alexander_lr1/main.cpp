#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

bool isBracket(char t);
bool isChar(char t);
bool skipChar(ifstream &text, char breakChar);

int main() {
    setlocale (0,"Rus");

    ifstream infile("/home/alex/Documents/current/alg_lab1/in_seq.txt");
    if (!infile) cout << "NO FILE!" << endl;

    cout << "INPUT IS:" << endl;
    bool b = skipChar(infile, 0);

    cout << endl;
    if (b) {
        cout << "TEXT WITH BRACKETS!" << endl;
    } else {
        cout << "ERROR!" << endl;
    }

    return 0;
}

bool isChar(char t) {
    return (t == ' ') || (t == 'A') || (t == 'B');
}

bool isBracket(char t) {
    return (t == '(') || (t == ')') || (t == '[') || (t == ']') || (t == '{') || (t == '}');
}

bool skipChar(ifstream &text, char breakChar) {
    char t;
    bool b = true;
    while (text >> t) {
        cout << t;

        if (isBracket(t) || !isChar(t)) {
            if (t == breakChar) {
                return true;
            }
            if (t == '(') {
                b &= skipChar(text, ')');
            } else if (t == '[') {
                b &= skipChar(text, ']');
            } else if (t == '{') {
                b &= skipChar(text, '}');
            } else {
                return false;
            }
        }
    }
    return b & (0 == breakChar);
}
