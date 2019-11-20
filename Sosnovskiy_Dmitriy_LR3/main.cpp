#include "mainwindow.h"
#include <QApplication>

void isStrCorrect(QString str)
{
    if(str.size() == 0) throw "Пустая строка";

    for(auto i : str)
    {
        if(i != ',' && i != '(' && i != ')' && i != 'M' && i != 'm' && i != " " && i.isDigit() == false)
        {
            throw "Лишние символы в строке";
        }
    }

    int lcnt = 0;
    int rcnt = 0;

    for(auto i:str)
    {
        if(i == '(') lcnt++;
        else if(i == ')') rcnt++;
    }

    if(lcnt < rcnt)
    {
        throw "Правых скобок больше";
    }
    else if(lcnt > rcnt)
    {
        throw "Левых скобок больше";
    }
}

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
        bool stop = false;

        std::string inputrstr;

        while(stop != true)
        {
            inputrstr.clear();
            std::cout << "Введите функцию: " << "\n";

            std::cin.sync();
            std::getline(std::cin, inputrstr);

            try {

                isStrCorrect(QString::fromUtf8(inputrstr.c_str()));
                Function func(QString::fromUtf8(inputrstr.c_str()));

                bool steps = false;
                std::string clientAns = " ";

                while(clientAns != "y" && clientAns != "n")
                {
                    std :: cin.sync();
                    std :: cout << "Рассчитать по шагам? [y/n]" << "\n";
                    std :: getline(std::cin, clientAns);
                }
                if(clientAns == "y") steps = true;
                else steps = false;


                std::cin.sync();
                int ans;
                if(steps == true) ans = func.calculateStepByStepForConsole();
                else ans = func.calculate();

                std :: cout << "Ответ: " << ans << "\n";
            }
            catch(const char* exc)
            {
                std::cout << exc << "\n";
            }

            std::cin.sync();
            std::cout << "Попробовать ещё раз?[y/n]" << "\n";
            std::string againAns = " ";
            std::cin >> againAns;
            while(againAns != "y" && againAns != "n")
            {
                std :: cin.sync();
                std :: cout << "y/n?" << "\n";
                std :: getline(std::cin, againAns);
            }
            if(againAns == "n") stop = true;
        }
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

