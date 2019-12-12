#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>
#include <algorithm>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsEffect>
#include <QFileDialog>
#include <QStandardPaths>
#include <QtGui>
#include <QLabel>
#include <QColorDialog>
#include <QInputDialog>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QStringList>
#include <QTextBrowser>
#include <QTextEdit>
#include <stack>
#include "modify.h"
#include "graphic.h"




struct Branch {
    Branch() = default;

    std::string root = "0";
    std::shared_ptr<Branch> left = nullptr;
    std::shared_ptr<Branch> right = nullptr;
    int deep = 0;

};


class BinTree {
public:
    BinTree() {
        head = std::make_shared<Branch>();
    }

    bool iscorrect(std::string& s) {
        if ((s[0] != '(' || s[s.length() - 1] != ')') && s.length() != 1)
            return false;
        else return true;
    }


    bool addRoots(std::shared_ptr<Branch> temp, std::string s) {

        if (!iscorrect(s)) {
            return 0;
        }

        size_t bracket_cnter = 0;
        size_t i = 0;

        if (isalpha(s[0]) || isdigit(s[0])) {
            if (s.length() == 1) {
                temp->root = s[i];
                return 1;
            }
            else return 0;
        }

        for (size_t i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                bracket_cnter++;
            }
            else if (s[i] == ')') {
                bracket_cnter--;
            }

            if ((s[i] == '+' || s[i] == '-' || s[i] == '*') && bracket_cnter == 1) {

                temp->left = std::make_shared<Branch>();
                temp->right = std::make_shared<Branch>();

                temp->root = s[i];

                if (!addRoots(temp->left, s.substr(1, i - 1)))
                    return 0;

                if (!addRoots(temp->right, s.substr(i + 1, s.length() - i - 2)))
                    return 0;

                return 1;
            }
        }
        return 0;
    }

    int countDeep(std::shared_ptr<Branch> node)
    {
        if (node == nullptr)
            return 0;
        int cl = countDeep(node->left);
        int cr = countDeep(node->right);
        return 1 + ((cl>cr)?cl:cr);
    }

    void pri( QGraphicsScene *&scene)
    {
        head->deep = countDeep(head);
        graphic(head, scene);
    }



    void replace_with_associative(std::string s, QGraphicsScene *&scene) {
        if (!addRoots(head, s)) {
            std::cout << "incorrect expression form" << std::endl;
            return;
        }

        head->deep = countDeep(head);
        graphic(head, scene);
       // ui->textBrowser->insertPlainText(QString::fromStdString(make_prefix_expression(head)));
        std::ofstream out;          // поток для записи
        out.open("D:\\temp.txt");
        out << "prefix form:\n" << make_prefix_expression(head)  << std::endl;
        out << "suffix form:\n" << make_suffix_expression(head)  << std::endl;


        std::cout << "prefix form:\n" << make_prefix_expression(head) << std::endl;
        std::cout << "suffix form:\n" << make_suffix_expression(head) << std::endl;

        change_tree(head);
        head->deep = countDeep(head);
        std::cout << "expression after associative changes:\n" << make_infix_expression(head) << std::endl;

    }


    std::string make_prefix_expression(std::shared_ptr<Branch> temporary) {
        if (!temporary->left || !temporary->right) {
            return temporary->root;
        }
        return "(" + temporary->root + " " + make_prefix_expression(temporary->left) + " " + make_prefix_expression(temporary->right) + ")";
    }

    std::string make_suffix_expression(std::shared_ptr<Branch> temporary) {
        if (!temporary->left || !temporary->right) {
            return temporary->root;
        }
        return "(" + make_suffix_expression(temporary->left) + " " + make_suffix_expression(temporary->right) + " " + temporary->root + ")";
    }

    std::string make_infix_expression(std::shared_ptr<Branch> temporary) {
        if (!temporary->left || !temporary->right) {
            return temporary->root;
        }
        return "(" + make_infix_expression(temporary->left) + " " + temporary->root + " " + make_infix_expression(temporary->right) + ")";
    }

    void change_tree(std::shared_ptr<Branch> temporary) {
        if (!temporary->left || !temporary->right) {
            return;
        }

        if (temporary->root == "*") {
            if (temporary->left->root == "+") {
                Branch buffer = *temporary->left->right;
                temporary->left->right = temporary->right;
                temporary->left->root = "*";
                temporary->root = "+";
                temporary->right = std::make_shared<Branch>();
                temporary->right->left = std::make_shared<Branch>();
                temporary->right->right = std::make_shared<Branch>();
                temporary->right->root = "*";
                *temporary->right->left = buffer;
                temporary->right->right = temporary->left->right;
            }
            else if (temporary->right->root == "+") {
                Branch buffer = *temporary->right->left;
                temporary->right->left = temporary->left;
                temporary->right->root = "*";
                temporary->root = "+";
                temporary->left = std::make_shared<Branch>();
                temporary->left->right = std::make_shared<Branch>();
                temporary->left->left = std::make_shared<Branch>();
                temporary->left->root = "*";
                *temporary->left->right = buffer;
                temporary->left->left = temporary->right->left;
            }
        }

        change_tree(temporary->left);
        change_tree(temporary->right);
    }

    QGraphicsScene *graphic(std::shared_ptr<Branch> node, QGraphicsScene *&scene)
    {
        if (head == nullptr)
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
        int w_deep = static_cast<int>(pow(2, head->deep)+2);
        int h = 60;
        int w = 12;
        font.setPointSize(w);
        int width = (w*w_deep)/2;
        paint(scene, head, width/2, h, w, h, pen, brush, font, w_deep);
        return scene;
    }

    int paint(QGraphicsScene *&scene, std::shared_ptr<Branch> node, int width, int height, int w, int h, QPen &pen, QBrush &brush, QFont &font, int depth)
    {
        if (node == nullptr)
            return 0;
        QString out;
        out = node->root[0];
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

private:
    std::shared_ptr<Branch> head;
    //std::map<size_t, std::string> depth_root_map;
    size_t depth = 0;
};
