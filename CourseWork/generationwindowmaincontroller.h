#ifndef GENERATIONWINDOWMAINCONTROLLER_H
#define GENERATIONWINDOWMAINCONTROLLER_H
#include "generationwindowmainview.h"

class GenerationWindowMainController
{
protected:
    GenerationWindowMainView* view;
public:
    void attachView(GenerationWindowMainView* view);

    GenerationWindowMainController();

    virtual void openFile() = 0;

    virtual void generate() = 0;
};

#endif // GENERATIONWINDOWMAINCONTROLLER_H
