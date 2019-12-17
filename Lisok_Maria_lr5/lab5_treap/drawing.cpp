#include "mainwindow.h"
#include "headers.h"
#include "treapNode.h"

void MainWindow::graphic(TreapNode<ul>* node, bool isRoot) {
    if (!workingTreap)
        return;
    QPen pen;
    QColor color;
    color.setRgb(196, 242, 209);
    pen.setColor(color);
    QBrush brush (color);
    QFont font;
    font.setFamily("Tahoma");
    pen.setWidth(2);
    int wDeep = static_cast<int>(pow(2, node->height())+2);
    int hDelta = 70;
    int wDelta = 15;
    font.setPointSize(11);
    font.setBold(true);
    int width = (wDelta*wDeep)/2;
    mainGraphicsView->setScene(mainGraphicsScene);
    if(isRoot){
        node->setStartPos(width/2, hDelta);
        if(wDelta*wDeep > 400)
            node->setWidth(wDelta*wDeep + 2*hDelta);
        else
            node->setWidth(2*(wDelta*wDeep));
    }
    else{
        node->setWidth(4*width+hDelta);
    }
    treePainter(node, node->getStartPos().x(), node->getStartPos().y(), wDelta, hDelta, pen, brush, font, wDeep);
}

void MainWindow::treePainter(TreapNode<ul> *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth) {
    if (!node)
        return;
    if(node->stepButStepEnable) node->loopLatency();
    QGraphicsTextItem *textItem = new QGraphicsTextItem;
    textItem->setPos(w, h);
    textItem->setPlainText(QString::number(node->getKey())+": "+QString::number(node->getPriority()));
    textItem->setFont(font);
    mainGraphicsScene->addEllipse(w-wDelta/2, h, node->MajorAxis, node->DrawingSize, pen, brush);
    if (node->mLeft)
        mainGraphicsScene->addLine(w+wDelta/2, h+wDelta, w-(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    if (node->mRight)
        mainGraphicsScene->addLine(w+wDelta/2, h+wDelta, w+(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    mainGraphicsScene->addItem(textItem);
    treePainter(node->mLeft, w-(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    treePainter(node->mRight, w+(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
}
