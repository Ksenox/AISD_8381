#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "utils_headers.h"
#include "utils_linked.h"
#include "utils_vector.h"
#include "utils_tree.h"
#include <cmath>

enum mode
{
    empty,
    bst,
    pyramid
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void UpdateGraphics();

private slots:
    void on_butFile_clicked();

    void on_butGenerate_clicked();

    void on_butRun_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_butStepBst_clicked();

    void on_butStepPyramid_clicked();

private:
    utils_tree<int>* tree;
    bool is_bst;
    bool is_pyramid;
    utils_vector<node<int>*> bst_stepped;
    utils_vector<node<int>*> pyramid_stepped;
    bool locked;
    mode stepped_mode;

    Ui::MainWindow *ui;

    QGraphicsScene *mainGraphicsScene;
    QPen pen;
    QColor color;
    QBrush brush;
    QFont font;

    void DrawNode(node<int>* n, int maxdepth, int depth = 0, int x = 0, int y = 0);
};

#endif // MAINWINDOW_H
