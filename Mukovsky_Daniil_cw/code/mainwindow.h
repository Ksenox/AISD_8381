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
#include <QScrollBar>
#include "decodingandcodinghuufmanalgorithm.h"
#include <fstream>
#include "infoaboutalgorithm.h"
#include "instruction.h"

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

    void on_stopButton_clicked();

    void on_readFileButton_clicked();

    void on_saveButton_clicked();

    void on_addElement_clicked();

    void on_upgradeTree_clicked();

    void on_prevStep_clicked();

    void on_readBit_clicked();

    void on_addElemDecode_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_actionAbout_algorithm_triggered();

    void on_actionInstruction_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *mainGraphicsScene;
    char* input;
    int currentInputLen = 0;
    int inputLen = 0;
    std::string output;
    std::string resultCode;
    std::string realOutput;
    QString answ;
    QPen pen;
    QColor color;
    QBrush brush;
    QFont font;
    QScrollBar* scrollBar;
    int algorithm;
    enum {decoding = 0,coding = 1};
    BinTree* tree;
    Node* curNode;
    Node* zeroNode;
    void setMode(bool isMode);
    void DrawNode(Node* n, int maxdepth, int depth = 0, int x = 0, int y = 0);
    void updateScene();
    bool readInput(bool isAlg);
    void setStepEncodeMode();
    void setOrdinaryMode();
    void setAddElemDecodeMode();
    void setReadBitMode();
    void setUpgrTreeMode();
    void freeSteps();
    void allClear();
    bool decodeCheck(QString code);
    void setLogs(std::string output,std::string resultCode );
    QString deleteSpaces(QString& str);
    enum {upgTree = 0,addSymb=1,readBit=2 , addEl=3};
    int maxTreeArrayLen = 0;
    QVector <BinTree*> treeArray;
    QVector <int> isPrevStep;
    QVector <int> diffInputLen;
    QVector <std::string> stepCode;
    QVector <std::string> stepOutput;
    QString inputString;
    InfoAboutAlgorithm* infoForm1;
    Instruction* infoForm2;
};
bool checkRussian(QString str);

#endif // MAINWINDOW_H
