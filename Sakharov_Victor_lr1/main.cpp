#include "LabExec.h"
#include "LabIo.h"

int main (int argc, char* argv[]) {
    string input = ProceedInput(argc, argv);
    if (input.empty()) return 0;
    bool success = CheckStatement(input);
    cout << "> " << (success ? "SUCCESS" : "ERROR") << endl;
    return 0;
}
