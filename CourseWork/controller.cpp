#include "controller.h"

Controller::Controller()
{

}

void Controller::calculate(QString inputString)
{
    try{
        treap = new BinaryRandomTreap(inputString);
        QString results = treap->getFromLowestToGreatest();
        view->setAnswer(results);
        QGraphicsScene* scene = treap->drawTree();
        view->displayResults(scene);

    }
    catch(SyntaxErrorException exception)
    {
        view->setAnswer(exception.getErrorString());
        view->displayResults(nullptr);
    }
}

void Controller::openFile()
{
    QString fileWay = QFileDialog::getOpenFileName(0, "Open File", "", "*.txt");

    if(fileWay != nullptr)
    {
        QFile file(fileWay);

        if(file.open(QIODevice::ReadOnly))
        {
            QString inputStringFromFile = nullptr;
            while(!file.atEnd())
            {
                inputStringFromFile += file.readLine();
                if(inputStringFromFile.size() >= 2)
                {
                    inputStringFromFile = inputStringFromFile.remove(inputStringFromFile.size()-2, 2);
                    inputStringFromFile += " ";
                }
            }

            view->setInputFromFile(inputStringFromFile);
        }
    }
}

void Controller::startView()
{
    static GenerationWindow* generationWindow = new GenerationWindow();

    GenerationWindowController* generationWindowController = new GenerationWindowController();

    generationWindowController->attachView(generationWindow);

    generationWindow->show();
}

void Controller::remove(QString str)
{
   /* treap->removeNode(str);
    QString results = treap->getFromLowestToGreatest();
    view->setAnswer(results);
    QGraphicsScene* scene = treap->drawTree();
    view->displayResults(scene);*/
}
