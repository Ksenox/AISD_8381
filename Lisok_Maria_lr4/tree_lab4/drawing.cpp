#include "allheaders.h"
#include "mainwindow.h"
#include "btree.h"
#include "drawing.h"

static bool stepLoopSwitcher = false;
static bool stepButStepEnable = false;

void graphic(struct Node* tree, QGraphicsScene *&scene) {
    if (tree == nullptr)
        return;
    scene->clear();
    QPen pen;
    QColor color;
    color.setRgb(220, 220, 220);
    pen.setColor(color);
    QBrush brush (color);
    QFont font;
    font.setFamily("Tahoma");
    pen.setWidth(3);
    int wDeep = static_cast<int>(pow(2, countDeep(tree))+2);
    int hDelta = 70;
    int wDelta = 15;
    font.setPointSize(wDelta);
    int width = (wDelta*wDeep)/2;
    treePainter(scene, tree, width/2, hDelta, wDelta, hDelta, pen, brush, font, wDeep);
}

int treePainter(QGraphicsScene *&scene, struct Node* node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth) {
    if (node == nullptr)
        return 0;
    QString out;
    out += node->value;
    if(stepButStepEnable) loopLatency();
    QGraphicsTextItem *textItem = new QGraphicsTextItem;
    textItem->setPos(w, h);
    textItem->setPlainText(out);
    textItem->setFont(font);
    scene->addEllipse(w-wDelta/2, h, wDelta*5/2, wDelta*5/2, pen, brush);
    if (node->left != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w-(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    if (node->right != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w+(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    scene->addItem(textItem);
    treePainter(scene, node->left, w-(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    treePainter(scene, node->right, w+(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    return 0;
}

// STEP BY STEP
void loopLatency() {
    qDebug() << "Loop latency for step-by-step started" << endl;
    for( ; ; ) {
        QApplication::processEvents();
        if(stepLoopSwitcher == false) break;
    }
    stepLoopSwitcher = true;
}

void changeLoopState() {
    stepLoopSwitcher = false;
}

void changeStepByStepMode() {
    stepButStepEnable = true;
}

void setDisableStepMode() {
    stepButStepEnable = false;
}
