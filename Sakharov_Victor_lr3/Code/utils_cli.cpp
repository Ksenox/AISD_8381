#include "utils_cli.h"

int utils_cli::exec(int argc, char *argv[])
{
    argc = 5; //STUB
    char* t[] = {"34", "234", "54", "756", "6"}; //STUB
    argv = t;
    logic_model model = logic_model();
    cout << "Executing input..." << endl << "Input got: " << endl;
    for (int i = 0; i < argc; i++)
    {
        model.current.l1->push_back(atoi(argv[i]));
    }
    cout << model.ToString();
    cout << endl << "Executing algorithm..." << endl;
    model.Sort();
    cout << endl << "Result: " << endl << model.ToString();
    return 0;
}
