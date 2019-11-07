#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    bool console = false;

    for(int i = 1; i < argc; i++)
    {
        if(!strcmp("console", argv[i]))
        {
            console = true;
        }
    }

    if(console)
    {
        std::cout << "Введите функцию: " << "\n";
        std::string inputrstr;

        std::getline(std::cin, inputrstr);

        bool steps = false;
        char clientAns = '0';

        while(clientAns != 'y' && clientAns != 'n')
        {
            std :: cout << "Рассчитать по шагам? [y/n]" << "\n";
            std :: cin >> clientAns;
        }

        if(clientAns == 'y') steps = true;
        else steps = false;

        Function func(QString::fromUtf8(inputrstr.c_str()));

        int ans;
        if(steps == true) ans = func.calculateStepByStepForConsole();
        else ans = func.calculate();

        std :: cout << "Ответ: " << ans << "\n";
    }
    else
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}
