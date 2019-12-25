#include "printhash.h"

QGraphicsScene *graphic(Hash_cl<string, string> &Hash_, QGraphicsScene *&scene){
    scene->clear();
    QPen pen;
    QColor color;
    color.setRgb(0, 0, 0);
    pen.setColor(color);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    QBrush brush (QColor::fromRgb(255,255,255));
    QFont font;
    font.setFamily("Arial");
    pen.setWidth(3);
    add_rect(scene, Hash_, 20, 20, 120, 40, pen, brush, font); //x1, y1, h, w
}

void add_rect(QGraphicsScene *&scene, Hash_cl<string, string> &Hash_, int x1, int y1, int h, int w, QPen &pen, QBrush &brush, QFont &font){
    QString out;
    for (int i = 0; i < Hash_.get_size(); i++) {
        if (Hash_[i].h_func != 0 && Hash_[i].fl_del == 0){
            out.clear();
            out += QString::fromStdString(Hash_[i].key1);
            out += "\t";
            out += QString::fromStdString(Hash_[i].value1);
            QGraphicsTextItem *textItem = new QGraphicsTextItem;
            textItem->setPos(x1, y1);
            textItem->setPlainText(out);
            textItem->setFont(font);
            if (i == Hash_.get_last_added())
                pen.setColor(QColor::fromRgb(114,190,116));
            if (i == Hash_.get_last_repeat()){
                pen.setColor(QColor::fromRgb(255,0,0));
                Hash_.reset_last_repeat();
            }
            scene->addRect(x1, y1, h, w, pen, brush);
            scene->addItem(textItem);
            pen.setColor(QColor::fromRgb(0,0,0));
            y1 += 40;
        }
    }
    return;
}



