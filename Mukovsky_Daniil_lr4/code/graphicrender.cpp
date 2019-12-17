#include "graphicrender.h"


int netTreePainter(QGraphicsScene *&scene, Node *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth, int color_c)
{
    if (node == nullptr)
        return 0;
    QString out;
    out += node->info;
    QColor color,color_n;
    color_n.setRgb(201, 174, 73);
    color.setRgb(color_c, color_c, color_c);

    QGraphicsTextItem *textItem = new QGraphicsTextItem;
    textItem->setPos(w, h);
    textItem->setPlainText(out);
    textItem->setFont(font);
    pen.setColor(color);
    brush.setColor(color);
    if (node->left != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w-(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    if (node->right != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w+(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    if (node->flag==true){
        pen.setColor(color_n);
        brush.setColor(color_n);
        scene->addEllipse(w-wDelta/2, h, wDelta*5/2, wDelta*5/2, pen, brush);
        }
    else
        scene->addEllipse(w-wDelta/2, h, wDelta*5/2, wDelta*5/2, pen, brush);
    scene->addItem(textItem);
    netTreePainter(scene, node->left, w-(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2, color_c);
    netTreePainter(scene, node->right, w+(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2, color_c);
    return 0;
}

QGraphicsScene *graphicConfig(BinaryTree *tree, QGraphicsScene *&scene, int depth)
{
    if (tree == nullptr)
        return scene;
    scene->clear();
    QPen pen;
    QColor color;
    color.setRgb(220, 220, 220);
    int color_c = 220;
    pen.setColor(color);
    color.setRgb(220, 220, 220);
    QBrush brush (color);
    QFont font;
    font.setFamily("Tahoma");
    pen.setWidth(3);
    int wDeep = static_cast<int>(pow(2, depth + 2));
    int hDelta = 70;
    int wDelta = 15;
    font.setPointSize(wDelta);
    int width = (wDelta*wDeep)/2;
    netTreePainter(scene, tree->root, width/2, hDelta, wDelta, hDelta, pen, brush, font, wDeep, color_c);
    return scene;
}
