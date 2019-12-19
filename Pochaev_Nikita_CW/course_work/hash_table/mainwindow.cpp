#include "mainwindow.h"
#include "allheaders.h"

#include "TableHandler.h"
#include "HashTable.h"
#include "drawingwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    fileOpenButton(new QtMaterialFlatButton),
    fileWayLabel(new QLabel),
    runButton(new QtMaterialFlatButton),
    stepByStepMode(new QtMaterialRadioButton),
    allInMomentMode(new QtMaterialRadioButton)
{
    setUpUI();
}

MainWindow::~MainWindow() {
}

void MainWindow::onFileOpenButtonClicked() {
    qDebug() << "onFileOpenlicked();" << endl;

    fileWayLabel->clear();

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open TXT File"),  QDir::homePath(),
            tr("TXT text (*.txt);;All Files (*)"));

    if (fileName == nullptr) {
        qDebug() << "No file was choosen!" << endl;
        fileWayLabel->setText("No file was choosen!");
        return;
    }

    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        foreach (QString i, QString(stream.readAll()).split(QRegExp("[\n]"), \
                                                            QString::SkipEmptyParts))
        inputDataStr.push_back(i.toUtf8().constData());
    }

    fileWayLabel->setText(fileName);

    // working function activate
    runButton->setDisabled(false);

    file.close();

    qDebug() << "End of onFileOpenlicked()" << endl;
}

void MainWindow::onRunButtonClicked() {
    qDebug() << "onRunButtonClicked();" << endl;

    if(inputDataStr.empty()) {
        fileWayLabel->setText("No input data!");
        return;
    }

    drawingWindow = new DrawingWindow(inputDataStr, inputDataStr, stepByStepMode->isChecked() == true);
    connect(drawingWindow, &DrawingWindow::closeSignal, this, &MainWindow::activateWindow);
    drawingWindow->show();
    setDisabled(true);
}

void MainWindow::activateWindow() {
    this->setDisabled(false);
}
