#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "allheaders.h"
#include "HashTable.h"
#include "drawingwindow.h"

#include <qtmaterialslider.h>
#include <qtmaterialradiobutton.h>
#include <qtmaterialtoggle.h>
#include <qtmaterialtextfield.h>
#include <qtmaterialscrollbar.h>
#include <qtmaterialflatbutton.h>
#include <qtmaterialdialog.h>
#include <qtmaterialcheckbox.h>
#include "lib/qtmaterialstyle.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onRunButtonClicked();
    void onFileOpenButtonClicked();
    void activateWindow();

private:
    void setUpUI();

    // WORK BUTTONS
    QtMaterialFlatButton *fileOpenButton;
    QLabel *fileWayLabel;
    QtMaterialFlatButton *runButton;
    QtMaterialRadioButton *stepByStepMode;
    QtMaterialRadioButton *allInMomentMode;
    DrawingWindow *drawingWindow;

    std::vector<std::string> inputDataStr;
};

#endif // MAINWINDOW_H
