#ifndef GENERATIONWINDOW_H
#define GENERATIONWINDOW_H

#include <QMainWindow>
#include "generationwindowmaincontroller.h"

namespace Ui {
class GenerationWindow;
}

class GenerationWindow : public QMainWindow, public GenerationWindowMainView
{
    Q_OBJECT

public:
    explicit GenerationWindow(QWidget *parent = nullptr);
    ~GenerationWindow();

    void setFilePath(QString path) override;

    QString getFilePath() override;

    int getSpinNumber() override;

private slots:

    void on_outputFileChoiceButton_clicked();

    void on_generateButton_clicked();

private:
    Ui::GenerationWindow *ui;


};

#endif // GENERATIONWINDOW_H
