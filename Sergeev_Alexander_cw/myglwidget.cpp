#include "myglwidget.h"


MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

MyGLWidget::~MyGLWidget() {}


void MyGLWidget::paintGL() {
    if (map != nullptr) {
        QPainter painter(this);
        painter.drawPixmap(this->rect(), *map, map->rect());
    } else {
        QPainter painter(this);
        painter.fillRect(this->rect(), QBrush(Qt::white));
        painter.setPen(Qt::black);
        painter.setFont(QFont("Consolas", 30));
        painter.drawText(rect(), Qt::AlignCenter, "Nothing here. Yet.");
        painter.end();
    }
}

void MyGLWidget::show(const std::string* outfile) {
    this->update();

    QFile file(QString::fromStdString(*outfile));
    file.open(QIODevice::WriteOnly);
    map->save(&file, "PNG");
}
