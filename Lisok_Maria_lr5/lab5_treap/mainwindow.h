#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "headers.h"
#include "treapNode.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void graphic(TreapNode<ul>*, bool) ;
    public slots:
        void onFileOpenButtonClicked();
        void onTreapDrawingButtonClicked();
        void onStepTreapDrawingButtonClicked();
        void onTreapSplitingButtonClicked();

    private:
        Ui::MainWindow *ui;

        void treePainter(TreapNode<ul> *, int, int, int, int, QPen &, QBrush &, QFont &, int);
        void setUpUI();
        void createTreap();
        QPushButton *fileOpen;
        QPushButton *drawingTreap;
        QPushButton *stepDrawingTreap;
        QPushButton *splitTreap;
        QCheckBox *stepSwitch;

        QGraphicsView *mainGraphicsView;
        QGraphicsScene *mainGraphicsScene;
        QPen pen;
        QColor color;
        QBrush brush;
        QFont font;

        QLineEdit *inputLine;
        QLineEdit *splitKeyInput;
        QLineEdit *slpitError;
        QLabel *inputExprLabel;
        QLabel *splitElLabel;
        TreapNode<ul>* workingTreap;

        bool isDrawing{false};

};

#endif // MAINWINDOW_H
