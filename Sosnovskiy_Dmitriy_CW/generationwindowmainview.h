#ifndef GENERATIONWINDOWMAINVIEW_H
#define GENERATIONWINDOWMAINVIEW_H
#include <QString>
class GenerationWindowMainController;

class GenerationWindowMainView
{
protected:
    GenerationWindowMainController* controller;

public:
    void attachController(GenerationWindowMainController* controller);

    GenerationWindowMainView();

    virtual void setFilePath(QString path) = 0;

    virtual QString getFilePath() = 0;

    virtual int getSpinNumber() = 0;
};

#endif // GENERATIONWINDOWMAINVIEW_H
