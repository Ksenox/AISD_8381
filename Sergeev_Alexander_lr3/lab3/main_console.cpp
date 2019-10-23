#include <bits/stdc++.h>
#include "universal_exception.h"
#include "lab3.h"

using namespace std;


string readFromFile(string fileName);


int main() {
    try {
        string input = readFromFile("input.txt");

        double millis = lab3::process(input, false);

        cout << endl << "Program finished in " << millis << " milliseconds" << endl;
        cerr << endl << lab3::getMessage() << endl;
        cout << endl << lab3::getAnswer() << endl;

    } catch (universal_exception& UE) {

        cerr << UE.toString() << endl;
        return EXIT_ERROR_CODE;
    }

    return 0;
}

string readFromFile(string fileName) {
    string name;
    cout << "Enter the path to input file (\"" + fileName + "\" by default):" << endl;
    getline(cin, name);
    if (!name.empty()) fileName = name;

    ifstream infile(fileName);
    if (!infile || infile.fail()) {
        throw universal_exception(INPUT_FILE_EXCEPTION_CODE);
    }
    string input;
    getline(infile, input);
    infile.close();

    if (input.empty()) {
        throw universal_exception(INPUT_FILE_EXCEPTION_CODE);
    }

    return input;
}
