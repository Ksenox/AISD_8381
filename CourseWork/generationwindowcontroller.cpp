#include "generationwindowcontroller.h"

GenerationWindowController::GenerationWindowController()
{

}

void GenerationWindowController::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(0, "Open File", "", "*.txt");
    view->setFilePath(filePath);
}

void GenerationWindowController::generate()
{

    QString filePath = view->getFilePath();

    if (QFile::exists(filePath) == false)
    {
        view->setFilePath("Файл не найден");
        return;
    }

    int hardness = view->getSpinNumber();

    QString task;

    task = TaskGenerator::generateTask(hardness);


    QFile file(filePath);
    file.open(QIODevice::WriteOnly);

    file.write(task.toUtf8());
    file.close();

}
