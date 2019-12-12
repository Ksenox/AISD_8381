#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "quicksort3.h"
#include "array_list.h"

using namespace std;

int console_main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    if (argc > 1 && !strncmp(argv[1], "-c", 2))
    {
        return console_main(argc - 2, argv + 2);
    }
    else
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
}

std::string print_list(array_list& list)
{
    string s;
    for (int i = 0; i < list.size(); i++)
    {
        s += std::to_string(list[i]) + " ";
    }
    return s;
}

int console_main(int argc, char *argv[])
{
    array_list list = array_list();
    cout << "Input array: " << endl;
    for (int i = 0; i < argc; i++)
    {
        list.push_back(atoi(argv[i]));
    }
    cout << print_list(list);
    cout << endl << "Executing algorithm..." << endl;
    string s;
    qsort3way(s, list, 0, list.size() - 1);
    cout << "---LOG---" << endl << s << endl << "---END---" << endl;
    cout << endl << "Result: " << endl << print_list(list) << endl;
    return 0;
}
