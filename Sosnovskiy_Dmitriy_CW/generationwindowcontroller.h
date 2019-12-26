#ifndef GENERATIONWINDOWCONTROLLER_H
#define GENERATIONWINDOWCONTROLLER_H
#include <generationwindowmaincontroller.h>
#include <taskgenerator.h>
#include <QFileDialog>
class GenerationWindowController : public GenerationWindowMainController
{
public:
    GenerationWindowController();

    void openFile() override;

    void generate() override;
};

#endif // GENERATIONWINDOWCONTROLLER_H
