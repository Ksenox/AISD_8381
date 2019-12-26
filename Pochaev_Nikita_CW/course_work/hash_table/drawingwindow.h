#ifndef DRAWINGWINDOW_H
#define DRAWINGWINDOW_H

#include "allheaders.h"
#include "HashTable.h"
#include "TableHandler.h"

#include <QSpacerItem>

#include <qtmaterialslider.h>
#include <qtmaterialradiobutton.h>
#include <qtmaterialtoggle.h>
#include <qtmaterialtextfield.h>
#include <qtmaterialscrollbar.h>
#include <qtmaterialflatbutton.h>
#include <qtmaterialdialog.h>
#include <qtmaterialcheckbox.h>
#include "lib/qtmaterialstyle.h"

class DrawingWindow : public QWidget {
    Q_OBJECT

public:
    DrawingWindow();
    DrawingWindow(std::vector<std::string>, std::vector<std::string>&, bool);

private:
    void setUpUI();
    void setUpDrawingTools();

    QGraphicsView *mainGraphicsView;
    // correct, cuz there's the only one scene + view
    QGraphicsScene *mainGraphicsScene;
    QTextEdit *mainTextOutput;
    QtMaterialFlatButton *nextStepButton;
    QtMaterialFlatButton *prevStepButton;
    QtMaterialFlatButton *addElButton;
    QtMaterialFlatButton *delElButton;
    QtMaterialFlatButton *showAllButton;
    QtMaterialTextField *inputEl;

    const QPoint startDrawPos{10, 10};
    // The Ultimate Question of Life,
    // the Universe, and Everything, also Node Size
    const int nodeHight{42};
    const int nodeWidth{42};
    const int spaceBetNodes{8};
    const int rectWidth{62};
    const int rectHieght{42};
    const int arrowLength{42};
    const int arrowTriangleLength{6};
    const int arrowTriangleHight{6};

    int levelsCount{0};
    std::vector<int> levelsLength;
    int stepsCount{0};
    std::vector<std::string> inpStrs;
    class nodeRect {
    public:
        QRect geomPar;
        std::string data;
        int level;
        int posInLevel;

        bool operator == (const nodeRect& rv) const {
            return (geomPar == rv.geomPar && data == rv.data && level == rv.level && posInLevel == rv.posInLevel);
        }
        bool operator != (const nodeRect& rv) const {
            return (geomPar != rv.geomPar || data != rv.data || level != rv.level || posInLevel != rv.posInLevel);
        }
    };
    // current rects
    std::vector<nodeRect> tableNodesRect;
    // BACKUP FOR STEP BACK
    std::vector<std::vector<nodeRect>> tableBackUp;

    QPen pen;
    QColor color;
    QBrush brush;
    QFont font;

    void drawNodesStartGrid(int);
    void drawNode(std::string data, int level, int pos);
    void makeNodesRects(lrstruct::HashTable<std::string>*, std::vector<nodeRect>&);
    void drawBaseRects();
    void drawRectsStepByStep();
    void drawRect(nodeRect&, QPen, QBrush);

    lrstruct::HashTable<std::string> *workTable;

protected:
    void closeEvent(QCloseEvent*);

protected slots:
    void reconnectForStepByStep();
    void baseDrawStepBack();
    void showAllSteps();
    void reconectForAddDel();

    void addEl();
    void delEl();

signals:
    void closeSignal();

};

#endif // DRAWINGWINDOW_H
