#include "drawingwindow.h"

DrawingWindow::DrawingWindow() :
    mainGraphicsView(new QGraphicsView),
    mainGraphicsScene(new QGraphicsScene),
    mainTextOutput(new QTextEdit),
    showAllButton(new QtMaterialFlatButton),
    inputEl(new QtMaterialTextField)
{
    setUpUI();
}

DrawingWindow::DrawingWindow(std::vector<std::string> inputDatastr, std::vector<std::string> &inpStrs,\
                             bool startDrawMode = false) :
    mainGraphicsView(new QGraphicsView),
    mainGraphicsScene(new QGraphicsScene),
    mainTextOutput(new QTextEdit),
    nextStepButton(new QtMaterialFlatButton),
    prevStepButton(new QtMaterialFlatButton),
    addElButton(new QtMaterialFlatButton),
    delElButton(new QtMaterialFlatButton),
    showAllButton(new QtMaterialFlatButton),
    inputEl(new QtMaterialTextField)
{
    // setups
    setUpUI();
    setUpDrawingTools();

    // functional work
    TableHandler::makeHashTable(inputDatastr, workTable);
    // FIXME: little trick to activate correct coords
    mainGraphicsScene->addLine(0, 0, 1, 0);
    levelsCount = static_cast<int>(workTable->getMaxSize());
    levelsLength = workTable->getChainsLength();
    TableHandler::makeHashTableDump(workTable);
    makeNodesRects(workTable, tableNodesRect);
    this->inpStrs = inpStrs;

    drawNodesStartGrid(levelsCount);
    if(startDrawMode == false) {
        drawBaseRects();
        showAllButton->setDisabled(true);
        reconectForAddDel();
    }
    else {
        // default conditions
        addElButton->setDisabled(true);
        delElButton->setDisabled(true);
        inputEl->setDisabled(true);
        nextStepButton->setDisabled(false);
        prevStepButton->setDisabled(false);
        showAllButton->setDisabled(false);
        TableHandler::stepLoopSwitcher = true;
        connect(prevStepButton, &QtMaterialFlatButton::clicked, this, &DrawingWindow::baseDrawStepBack);
        connect(nextStepButton, &QtMaterialFlatButton::clicked, this, &DrawingWindow::reconnectForStepByStep);
        connect(showAllButton, &QtMaterialFlatButton::clicked, this, &DrawingWindow::showAllSteps);
    }
}

void DrawingWindow::closeEvent(QCloseEvent *event) {
    emit closeSignal();
    TableHandler::disableLoop();
    event->accept();
}

void DrawingWindow::setUpDrawingTools() {
    qDebug() << "setUpDrawingTools()" << endl;

    color.setRgb(0, 0, 0);
    pen.setColor(color);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    font.setFamily("Roboto");
    font.setPointSize(8);
    pen.setWidth(3);
}

void DrawingWindow::reconnectForStepByStep() {
    disconnect(nextStepButton, &QtMaterialFlatButton::clicked, this, &DrawingWindow::reconnectForStepByStep);
    connect(nextStepButton, &QtMaterialFlatButton::clicked, this, &TableHandler::disableLoop);
    drawRectsStepByStep();
}

void DrawingWindow::reconectForAddDel() {
    addElButton->setDisabled(false);
    delElButton->setDisabled(false);
    inputEl->setDisabled(false);
    nextStepButton->setDisabled(true);
    prevStepButton->setDisabled(true);
    showAllButton->setDisabled(true);

    connect(addElButton, &QtMaterialFlatButton::clicked, this, &DrawingWindow::addEl);
    connect(delElButton, &QtMaterialFlatButton::clicked, this, &DrawingWindow::delEl);
}
