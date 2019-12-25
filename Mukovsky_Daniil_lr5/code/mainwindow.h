#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QtGui>
#include <QDialog>
#include <QColorDialog>
#include <QString>
#include <QDebug>
#include <QPainter>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QTextEdit>
#include <QEventLoop>
#include <QTimer>
#include <QColor>
#include <QDebug>
#include <QGraphicsView>
#include <QFormLayout>
#include "decodingandcodinghuufmanalgorithm.h"
#include <fstream>
#include "console.h"

#define RUSSIAN "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startCodingButton_clicked();

    void on_stepByStepStart_clicked();

    void on_nextStep_clicked();

    void on_previousStep_clicked();

    void on_stopButton_clicked();

    void on_readFileButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *mainGraphicsScene;

    std::string output = "";
    std::string resultCode = "";
    QPen pen;
    QColor color;
    QBrush brush;
    QFont font;
    BinTree* tree;

    int currentInputLen = 0;
    int inputLen = 0;
    char* input ;
    void setMode(bool isMode);
    void DrawNode(Node* n, int maxdepth, int depth = 0, int x = 0, int y = 0);
    void updateScene();
    bool readInput();

};
bool checkRussian(QString str);

#endif // MAINWINDOW_H
