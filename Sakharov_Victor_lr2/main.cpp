#include <iostream>
#include "structs.h"
#include "LabExec.h"
#include "LabIo.h"
#include "LabExec.h"

int main (int argv, char** argc) {
    //string input = ProceedInput(argv, argc);
    string input = ReadFromConsole();
    int pos = 0;
    string copy = string(input);
    errorFlag = false;
    Expression* expression = ScanExpression(copy, pos);
    if (!copy.empty() && !errorFlag) {
        cout << pos << ": End of expression expected" << endl;
        errorPos = pos;
        errorFlag = true;
    }
    cout << input << endl;
    if (errorFlag) {
        for (int i = 0; i < errorPos; i++) {
            cout << '.';
        }
        cout << "^" << endl << "ERROR" << endl;
    }
    else {
        cout << "SUCCESS" << endl;
    }
    return 0;
}