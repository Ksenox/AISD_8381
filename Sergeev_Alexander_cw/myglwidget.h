#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QPainter>
#include <QFile>
#include <sstream>
#include <iomanip>
#include "treap.h"


const int BONES_LIMIT = 5;
const int CIRCLE_SIZE = 40;


class MyGLWidget : public QOpenGLWidget {
public:
    QPixmap* map = nullptr;


    MyGLWidget(QWidget *parent);
    ~MyGLWidget() override;


    template<typename T>
    void set_tree(treap<T>* source, double outline) {
        pntr = new QPainter(map);
        pntr->fillRect(map->rect(), QBrush(Qt::white));
        pntr->setBrush(Qt::white);
        pntr->setFont(QFont("Consolas", 8));

        bool drawing_bones = source->max_depth() >= BONES_LIMIT;
        if (!drawing_bones) pntr->setPen(QPen(Qt::black, 3));

        int depth = static_cast<int>(source->max_depth());
        stepY = static_cast<int>(map->height() / depth);

        paint_node(source->get_root()->get_left(), false, map->width() / 2, stepY / 2, map->width() / 4, outline);
        paint_node(source->get_root()->get_right(), true, map->width() / 2, stepY / 2, map->width() / 4, outline);
        if (!drawing_bones) {
            std::stringstream knot;
            knot << source->get_root()->get_state() << "\n" << std::setprecision(4) << source->get_root()->get_index();

            if (abs(source->get_root()->get_index() - outline) < 0.0001) {
                pntr->setBrush(Qt::red);
                pntr->drawEllipse(QPointF(map->width() / 2, stepY / 2), CIRCLE_SIZE, CIRCLE_SIZE);
                pntr->setBrush(Qt::white);
            } else {
                pntr->drawEllipse(QPointF(map->width() / 2, stepY / 2), CIRCLE_SIZE, CIRCLE_SIZE);
            }
            pntr->drawText(QRect(map->width() / 2 - CIRCLE_SIZE / 2, stepY / 2 - CIRCLE_SIZE / 2, CIRCLE_SIZE, CIRCLE_SIZE), Qt::AlignCenter, QString::fromStdString(knot.str()));

            populate_node(source->get_root()->get_left(), false, map->width() / 2, stepY / 2, map->width() / 4, outline);
            populate_node(source->get_root()->get_right(), true, map->width() / 2, stepY / 2, map->width() / 4, outline);
        }

        stepY = 0;
        pntr->end();
        free(pntr);
    }

    void declare(std::string* msg) {
        pntr = new QPainter(map);
        pntr->fillRect(map->rect(), QBrush(Qt::white));
        pntr->setPen(Qt::black);
        pntr->setFont(QFont("Consolas", 8));
        pntr->drawText(rect(), Qt::AlignCenter, QString::fromStdString(*msg));
        pntr->end();
        free(pntr);

        this->update();
    }

    void prepare_drawing() {
        free(this->map);
        this->map = new QPixmap(this->width(), this->height());

        pntr = new QPainter(map);
        pntr->fillRect(map->rect(), QBrush(Qt::white));
        pntr->end();
        free(pntr);
    }

    void show(const std::string* outfile);

protected:
    void paintGL() override;

private:
    int stepY = 0;
    QPainter* pntr;

    template<typename T>
    void paint_node(treap_node<T>* node, bool is_right, int parent_x, int parent_y, int half_stepX, double outline) {
        if (node == nullptr) return;

        int child_x = parent_x + ((is_right) ? (half_stepX) : (-half_stepX));
        int child_y = parent_y + stepY;

        if (abs(node->get_index() - outline) < 0.0001) {
            pntr->setPen(QPen(Qt::red, pntr->pen().width()));
            pntr->drawLine(parent_x, parent_y, child_x, child_y);
            pntr->setPen(QPen(Qt::black, pntr->pen().width()));
        } else {
            pntr->drawLine(parent_x, parent_y, child_x, child_y);
        }


        paint_node(node->get_left(), false, child_x, child_y, half_stepX / 2, outline);
        paint_node(node->get_right(), true, child_x, child_y, half_stepX / 2, outline);
    }

    template<typename T>
    void populate_node(treap_node<T>* node, bool is_right, int parent_x, int parent_y, int half_stepX, double outline) {
        if (node == nullptr) return;

        int child_x = parent_x + ((is_right) ? (half_stepX) : (-half_stepX));
        int child_y = parent_y + stepY;

        std::stringstream knot;
        knot << node->get_state() << "\n" << std::setprecision(4) << node->get_index();

        if (abs(node->get_index() - outline) < 0.0001) {
            pntr->setBrush(Qt::red);
            pntr->drawEllipse(QPointF(child_x, child_y), CIRCLE_SIZE, CIRCLE_SIZE);
            pntr->setBrush(Qt::white);
        } else {
            pntr->drawEllipse(QPointF(child_x, child_y), CIRCLE_SIZE, CIRCLE_SIZE);
        }
        pntr->drawText(QRect(child_x - CIRCLE_SIZE / 2, child_y - CIRCLE_SIZE / 2, CIRCLE_SIZE, CIRCLE_SIZE), Qt::AlignCenter, QString::fromStdString(knot.str()));

        if (node->get_left() != nullptr) {
            populate_node(node->get_left(), false, child_x, child_y, half_stepX / 2, outline);
        }
        if (node->get_right() != nullptr) {
            populate_node(node->get_right(), true, child_x, child_y, half_stepX / 2, outline);
        }
    }
};

#endif // MYGLWIDGET_H
