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
    pyramid,
    step_add,
    step_remove,
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

    void on_butAdd_clicked();

    void on_butStepAdd_clicked();

    void on_butRemove_clicked();

    void on_butGenerateOptimal_clicked();

    void on_butStepRemove_clicked();

    void updateTreeColor();

private:
    utils_tree<int>* tree;
    int current;
    bool is_bst;
    bool is_pyramid;
    utils_vector<node<int>*> bst_stepped;
    utils_vector<node<int>*> pyramid_stepped;
    utils_linked<node<int>*> stack;
    node<int>* state_node;
    int state;
    bool locked;
    bool lockedUpd;
    mode stepped_mode;

    Ui::MainWindow *ui;

    QGraphicsScene *mainGraphicsScene;
    QPen pen;
    QColor color;
    QBrush brush;
    QFont font;

    void DrawNode(node<int>* n, int maxdepth, int depth = 0, int x = 0, int y = 0);
    void SetActiveButtons(bool mode);
    bool ReadElement();
};

#endif // MAINWINDOW_H
