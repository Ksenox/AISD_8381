#include "graphic.h"

QGraphicsScene *graphic(BinTree *tree, QGraphicsScene *&scene)
{
    if (tree == nullptr)
        return scene;
    scene->clear();
    QPen pen;
    pen.setWidth(5);
    QColor color;
    color.setRgb(192, 192, 192);
    pen.setColor(color);
    QBrush brush (color);
    QFont font;
    font.setFamily("Helvetica");    
    int w_deep = static_cast<int>(pow(2, tree->deep)+2);
    int h = 60;
    int w = 12;
    font.setPointSize(w);
    int width = (w*w_deep)/2;
    paint(scene, tree->root, width/2, h, w, h, pen, brush, font, w_deep);
    return scene;
}

int paint(QGraphicsScene *&scene, Node *node, int width, int height, int w, int h, QPen &pen, QBrush &brush, QFont &font, int depth)
{
    if (node == nullptr)
        return 0;
    QString out;
    out += node->info;
    QGraphicsTextItem *elem = new QGraphicsTextItem;
    elem->setPos(width, height);
    elem->setPlainText(out);
    elem->setFont(font);
    scene->addRect(width-w/2, height, w*5/2, w*5/2, pen, brush);
    if (node->left != nullptr)
        scene->addLine(width+w/2, height+w, width-(depth/2)*w+w/2, height+h+w, pen);
    if (node->right != nullptr)
        scene->addLine(width+w/2, height+w, width+(depth/2)*w+w/2, height+h+w, pen);
    scene->addItem(elem);
    paint(scene, node->left, width-(depth/2)*w, height+h, w, h, pen, brush, font, depth/2);
    paint(scene, node->right, width+(depth/2)*w, height+h, w, h, pen, brush, font, depth/2);
    return 0;
}
