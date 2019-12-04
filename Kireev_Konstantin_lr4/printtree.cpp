#include "printtree.h"

QGraphicsScene *graphic(tree *symb, QGraphicsScene *&scene)
{
    if (symb == nullptr)
        return scene;
    scene->clear();
    QPen pen;
    QColor color;
    color.setRgb(220, 220, 220);
    pen.setColor(color);
    QBrush brush (color);
    QFont font;
    font.setFamily("Tahoma");
    pen.setWidth(3);
    int wDeep = static_cast<int>(pow(2, 4)+2);
    int hDelta = 70;
    int wDelta = 15;
    font.setPointSize(wDelta);
    int width = (wDelta*wDeep)/2;
    treePainter(scene, symb, width/2, hDelta, wDelta, hDelta, pen, brush, font, wDeep);
    return scene;
}

int treePainter(QGraphicsScene *&scene, tree *symb, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth)
{
    if (symb == nullptr)
        return 0;
    QString out;
    out += symb->name;
    QGraphicsTextItem *textItem = new QGraphicsTextItem;
    textItem->setPos(w, h);
    textItem->setPlainText(out);
    textItem->setFont(font);
    scene->addEllipse(w-wDelta/2, h, wDelta*5/2, wDelta*5/2, pen, brush);
    if (symb->childLeft != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w-(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    if (symb->childRight != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w+(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    scene->addItem(textItem);
    treePainter(scene, symb->childLeft, w-(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    treePainter(scene, symb->childRight, w+(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    return 0;
}
