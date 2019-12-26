#ifndef MAINVIEW_H
#define MAINVIEW_H
#include <QString>
#include <QGraphicsScene>
class MainController;

class MainView
{
protected:
    MainController* controller;
public:
    void attachController(MainController* controller);
    virtual void setAnswer(QString answer) = 0;
    virtual void setInputFromFile(QString input) = 0;
    virtual void displayResults(QGraphicsScene* scene) = 0;

    MainView();
};

#endif // MAINVIEW_H
