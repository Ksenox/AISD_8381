#include<bin_struct.h>

QGraphicsScene *graphic(BinTree *tree, QGraphicsScene *scene, int depth)
{
    if (tree == nullptr)
        return scene;
    scene->clear();
    QPen pen;
    QColor color;
    color.setRgb(220, 220, 220);
    pen.setColor(color);
    int color_c = 220;
    color.setRgb(220, 220, 220);
    QBrush brush (color);
    QFont font;
    font.setFamily("Tahoma");
    pen.setWidth(3);
    int wDeep = static_cast<int>(pow(2, depth));
    int hDelta = 70;
    int wDelta = 15;
    font.setPointSize(wDelta);
    int width = (wDelta*wDeep)/2;
    treePainter(scene, tree->Head, width/2, hDelta, wDelta, hDelta, pen, brush, font, wDeep, color_c);
    return scene;
}

int treePainter(QGraphicsScene *scene, Node *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth, int colour)
{
    if (node == nullptr)
        return 0;
    QString out;
    out.append(QString::number(node->key));
    QColor color;
    color.setRgb(colour, colour, colour);
    pen.setColor(color);
    QGraphicsTextItem *textItem = new QGraphicsTextItem;
    if (node->left != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w-(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    if (node->right != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w+(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    textItem->setPos(w, h);
    textItem->setPlainText(out);
    textItem->setFont(font);
    scene->addEllipse(w-wDelta/2, h, wDelta*5/2, wDelta*5/2, pen, brush);

    scene->addItem(textItem);
    treePainter(scene, node->left, w-(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2, colour - 30);
    treePainter(scene, node->right, w+(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2, colour- 50);
    return 0;
}
