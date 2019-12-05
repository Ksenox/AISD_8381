#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    tree(nullptr),
    ui(new Ui::MainWindow),
    locked(false),
    stepped_mode(empty)
{
    ui->setupUi(this);
    QMainWindow::showMaximized();
    mainGraphicsScene = new QGraphicsScene();
    ui->graphicsView->setScene(mainGraphicsScene);
    QColor color = QColor(203, 119, 47);
    pen.setColor(color);
    brush.setColor(color);
    font.setFamily("Roboto");
    pen.setWidth(3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateGraphics()
{
    mainGraphicsScene->clear();
    if (!tree) return;
    DrawNode(tree->root, tree->max_depth());
}

void MainWindow::on_butFile_clicked()
{
    std::string inputStr;
    QString fileName = QFileDialog::getOpenFileName(this, "Open TXT File",  QDir::homePath(), "TXT text (*.txt);;All Files (*)");
    if (fileName == nullptr)
    {
        QMessageBox::warning(this, "Warning", "File name is empty");
        return;
    }
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        foreach (QString i ,QString(stream.readAll()).split(QRegExp("[ \t]"), QString::SkipEmptyParts))
        inputStr.append(i.toUtf8().constData());
    }
    if(inputStr.empty())
        return;
    file.close();
    ui->input->setText(QString::fromUtf8(inputStr.c_str()));
}

void MainWindow::on_butGenerate_clicked()
{
    std::string readingStr;
    if (ui->input->text().isEmpty()) ui->input->setText("9(8(6(3(1)(2))(5))(5(3)(1)))(7))");
    QString tempInp = ui->input->text();
    QTextStream stream(&tempInp);
    foreach (QString i, QString(stream.readAll()).split(QRegExp("[ \t]"), QString::SkipEmptyParts))
        readingStr.append(i.toUtf8().constData());
    tree = new utils_tree<int>(readingStr);
    is_bst = tree->is_bst_stepped(bst_stepped, tree->root, INT_MIN, INT_MAX);
    is_pyramid = tree->is_pyramid_stepped(pyramid_stepped, tree->root, INT_MAX);
    UpdateGraphics();
}


void MainWindow::on_butRun_clicked()
{
    if (locked || !tree) return;
    locked = true;
    if (is_bst) QMessageBox::information(this, "BST?", "    YES    ");
    else QMessageBox::warning(this, "BST?", "    NO    ");
    if (is_pyramid) QMessageBox::information(this, "Pyramid?", "    YES    ");
    else QMessageBox::warning(this, "Pyramid?", "    NO    ");
    UpdateGraphics();
    locked = false;
}

void MainWindow::DrawNode(node<int> *n, int maxdepth, int depth, int x, int y)
{
    if (n == nullptr) return;
    int offset = pow(2, maxdepth + 3) / pow(2, depth);
    if (n->left) mainGraphicsScene->addLine(x + 32, y + 32, x - offset + 32, y + 64 + 32, pen);
    if (n->right) mainGraphicsScene->addLine(x + 32, y + 32, x + offset + 32, y + 64 + 32, pen);
    if (n->mode == stepped_mode) color.setRgb(0, 255, 0);
    else color.setRgb(255, 0, 0);
    QBrush brush(color);
    color.setRgb(0, 255 * (depth/(float)maxdepth), 255 * ((maxdepth - depth)/(float)maxdepth));
    QPen pen(color, 3);
    mainGraphicsScene->addEllipse(x, y, 64, 64, pen, brush);
    QGraphicsTextItem *numb = new QGraphicsTextItem();
    numb->setPlainText(QString::number(n->data));
    numb->setDefaultTextColor(Qt::black);
    numb->setScale(2);
    numb->setPos(x + 16, y + 8);
    mainGraphicsScene->addItem(numb);
    DrawNode(n->left, maxdepth, depth + 1, x - offset, y + 64);
    DrawNode(n->right, maxdepth, depth + 1, x + offset, y + 64);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(1.0 / position, 1.0 / position);
}

void MainWindow::on_butStepBst_clicked()
{
    if (stepped_mode == pyramid) return;
    stepped_mode = bst;
    if (bst_stepped.empty())
    {
        if (is_bst) QMessageBox::information(this, "BST?", "    YES    ");
        else QMessageBox::warning(this, "BST?", "    NO    ");
        stepped_mode = empty;
    }
    else
    {
        node<int>* n = bst_stepped.pop_front();
        n->mode = bst;
    }
    UpdateGraphics();
}

void MainWindow::on_butStepPyramid_clicked()
{
    if (stepped_mode == bst) return;
    stepped_mode = pyramid;
    if (pyramid_stepped.empty())
    {
        if (is_pyramid) QMessageBox::information(this, "Pyramid?", "    YES    ");
        else QMessageBox::warning(this, "Pyramid?", "    NO    ");
        stepped_mode = empty;
    }
    else
    {
        node<int>* n = pyramid_stepped.pop_front();
        n->mode = pyramid;
    }
    UpdateGraphics();
}
