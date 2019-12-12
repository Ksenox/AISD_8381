#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    tree(nullptr),
    state(0),
    locked(false),
    lockedUpd(false),
    stepped_mode(empty),
    ui(new Ui::MainWindow),
    mainGraphicsScene(new QGraphicsScene())
{
    ui->setupUi(this);
    ui->graphicsView->setScene(mainGraphicsScene);
    QMainWindow::showMaximized();
    QColor color = QColor(203, 119, 47);

    pen.setColor(color);
    brush.setColor(color);
    font.setFamily("Roboto");
    pen.setWidth(3);

    srand(static_cast<unsigned long>(time(nullptr)));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTreeColor()));
    timer->start(100);
    stack = utils_linked<node<int>*>();
    ui->horizontalSlider->setValue(2);
    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(1.0 / 2, 1.0 / 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateGraphics()
{
    if (lockedUpd) return;
    lockedUpd = true;
    mainGraphicsScene->clear();
    if (!tree) return;
    DrawNode(tree->root, tree->max_depth());
    lockedUpd = false;
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
    if (ui->input->text().isEmpty())
    {
        QMessageBox::warning(this, "Warining!", "Input is empty. Applying test: 13(8(6(3(1)(4))(7))(10(9)(11)))(14))");
        ui->input->setText("13(8(6(3(1)(4))(7))(10(9)(11)))(14))");
    }
    QString tempInp = ui->input->text();
    QTextStream stream(&tempInp);
    foreach (QString i, QString(stream.readAll()).split(QRegExp("[ \t]"), QString::SkipEmptyParts))
        readingStr.append(i.toUtf8().constData());
    tree = new utils_tree<int>(readingStr);
    is_bst = tree->is_bst_stepped(bst_stepped, tree->root, INT_MIN, INT_MAX);
    is_pyramid = tree->is_pyramid_stepped(pyramid_stepped, tree->root, INT_MAX);
    ui->balancedLabel->setText("Binary tree");
    UpdateGraphics();
}

void MainWindow::on_butGenerateOptimal_clicked()
{
    if (!tree) on_butGenerate_clicked();
    if (!tree || tree->max_depth() <= 2) return;
    tree->to_optimal();
    ui->balancedLabel->setText("AVL tree");
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
    QBrush brush(n->color);
    color.setRgb(0, 255 * (depth/(float)maxdepth), 255 * ((maxdepth - depth)/(float)maxdepth));
    QPen pen(color, 3);
    mainGraphicsScene->addEllipse(x, y, 64, 64, pen, brush);
    QGraphicsTextItem *numb = new QGraphicsTextItem();
    numb->setPlainText(QString::number(n->data));
    numb->setDefaultTextColor(Qt::white);
    numb->setScale(2);
    numb->setPos(x + 16, y + 8);
    mainGraphicsScene->addItem(numb);
    DrawNode(n->left, maxdepth, depth + 1, x - offset, y + 64);
    DrawNode(n->right, maxdepth, depth + 1, x + offset, y + 64);
}

void MainWindow::SetActiveButtons(bool mode)
{
    ui->butAdd->setEnabled(mode);
    ui->butStepAdd->setEnabled(mode);
    ui->butRemove->setEnabled(mode);
    ui->butStepRemove->setEnabled(mode);
    ui->butFile->setEnabled(mode);
    ui->butStepBst->setEnabled(mode);
    ui->butStepPyramid->setEnabled(mode);
    ui->butRun->setEnabled(mode);
    ui->butGenerate->setEnabled(mode);
    ui->butGenerateOptimal->setEnabled(mode);

    ui->inputElement->setEnabled(mode);
    ui->input->setEnabled(mode);
}

bool MainWindow::ReadElement()
{
    if (!tree) return false;
    if (ui->inputElement->text().isEmpty())
    {
        QMessageBox::warning(this, "Warining!", "Input elemet is empty. Applying random data");
        ui->inputElement->setText(QString::number(rand() % 20));
    }
    bool ok;
    int res = ui->inputElement->text().toInt(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "Warining!", "Input elemet isn't a number!");
        ui->inputElement->setText("");
        return false;
    }
    current = res;
    return true;
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(1.0 / position, 1.0 / position);
}

void MainWindow::on_butStepBst_clicked()
{
    if (stepped_mode == empty || stepped_mode == bst)
    {
        stepped_mode = bst;
        SetActiveButtons(false);
        ui->butStepBst->setEnabled(true);
        if (bst_stepped.empty())
        {
            if (is_bst) QMessageBox::information(this, "BST?", "    YES    ");
            else QMessageBox::warning(this, "BST?", "    NO    ");
            stepped_mode = empty;
            SetActiveButtons(true);
        }
        else
        {
            node<int>* n = bst_stepped.pop_front();
            n->color.setRgb(0, 255, 0);
        }
        UpdateGraphics();
    }
}

void MainWindow::on_butStepPyramid_clicked()
{
    if (stepped_mode == empty || stepped_mode == pyramid)
    {
        stepped_mode = pyramid;
        SetActiveButtons(false);
        ui->butStepPyramid->setEnabled(true);
        if (pyramid_stepped.empty())
        {
            if (is_pyramid) QMessageBox::information(this, "Pyramid?", "    YES    ");
            else QMessageBox::warning(this, "Pyramid?", "    NO    ");
            stepped_mode = empty;
            SetActiveButtons(true);
        }
        else
        {
            node<int>* n = pyramid_stepped.pop_front();
            n->color.setRgb(0, 0, 255);
        }
        UpdateGraphics();
    }
}

void MainWindow::on_butAdd_clicked()
{
    if (!ReadElement()) return;
    if (tree->search(current))
    {
        QMessageBox::information(this, "Insertion", "Duplicate");
    }
    else
    {
        tree->insertbalanced(current);
    }
    ui->inputElement->setText("");
    UpdateGraphics();

}

void MainWindow::on_butStepAdd_clicked()
{
    if (!ReadElement()) return;
    if (locked || !tree) return;
    locked = true;
    if (stepped_mode == empty || stepped_mode == step_add)
    {
        stepped_mode = step_add;
        SetActiveButtons(false);
        ui->butStepAdd->setEnabled(true);
        node<int>* n;
        switch (state)
        {
            case 0: // Init
                stack.clean();
                state_node = tree->root;
                state = 1;
                break;
            case 1: // Down
                stack.push_back(state_node);
                state_node->color.setRgb(0, 255, 0);
                if (current < state_node->data)
                {
                    state_node = state_node->left;
                    if (!state_node)
                    {
                        stack.back()->left = new node<int>(current);
                        state = 2;
                    }
                }
                else if (current > state_node->data)
                {
                    state_node = state_node->right;
                    if (!state_node)
                    {
                        stack.back()->right = new node<int>(current);
                        state = 2;
                    }
                }
                else
                {
                    QMessageBox::information(this, "Insertion", "Duplicate");
                    stepped_mode = empty;
                    SetActiveButtons(true);
                    state = 0;
                }
                break;
            case 2: // Up
                if (stack.size() <= 1)
                {
                    QMessageBox::information(this, "Insertion", "Completed");
                    stepped_mode = empty;
                    SetActiveButtons(true);
                    state = 0;
                    break;
                }
                n = stack.pop_back();
                n->color.setRgb(0, 0, 255);
                tree->fixheight(n);
                if (tree->bfactor(n) == 2)
                {
                    if (tree->bfactor(n->right) < 0) n->right = tree->rotateright(n->right);
                    if (n == stack.back()->left) stack.back()->left = tree->rotateleft(n);
                    else stack.back()->right = tree->rotateleft(n);
                }
                if (tree->bfactor(n) == -2)
                {
                    if (tree->bfactor(n->left) > 0) n->left = tree->rotateleft(n->left);
                    if (!stack.back())
                    {
                        QMessageBox::critical(this, "Insertion", "NULL");
                    }
                    if (n == stack.back()->left) stack.back()->left = tree->rotateright(n);
                    else stack.back()->right = tree->rotateright(n);
                }
                break;
        }
        UpdateGraphics();
    }
    locked = false;
    //
//    if (!n) return new node<T>(data);
//    if (data < n->data) n->left = insertbalanced(n->left, data);
//    else n->right = insertbalanced(n->right, data);
//    fixheight(n);
//    if (bfactor(n) == 2)
//    {
//        if (bfactor(n->right) < 0)
//            n->right = rotateright(n->right);
//        return rotateleft(n);
//    }
//    if (bfactor(n) == -2)
//    {
//        if (bfactor(n->left) > 0)
//            n->left = rotateleft(n->left);
//        return rotateright(n);
//    }
//    return n;
    //
}

void MainWindow::on_butRemove_clicked()
{
    if (!ReadElement()) return;
    if (tree->search(current))
    {
        tree->removebalanced(current);
        ui->inputElement->setText("");
        UpdateGraphics();
    }
    else
    {
        QMessageBox::information(this, "Removing", "There is no " + QString::number(current) + " element.");
    }
}

// FIX IT
void MainWindow::on_butStepRemove_clicked()
{
    if (!ReadElement()) return;
    if (stepped_mode == empty || stepped_mode == step_remove)
    {
        stepped_mode = step_remove;
        SetActiveButtons(false);
        ui->butStepRemove->setEnabled(true);
        node<int>* l;
        node<int>* r;
        node<int>* min;
        switch (state)
        {
            case 0: // Init
                stack.clean();
                state_node = tree->root;
                state = 1;
                break;
            case 1: // Down
                if (!state_node)
                {
                    QMessageBox::information(this, "Removing", "No element");
                    stepped_mode = empty;
                    SetActiveButtons(true);
                    state = 0;
                }
                else
                {
                    if (current < state_node->data)
                    {
                        stack.push_back(state_node);
                        state_node->color.setRgb(0, 255, 0);
                        state_node = state_node->left;
                    }
                    else if (current > state_node->data)
                    {
                        stack.push_back(state_node);
                        state_node->color.setRgb(0, 255, 0);
                        state_node = state_node->right;
                    }
                    else
                    {
                        l = state_node->left;
                        r = state_node->right;
                        if (!r)
                        {
                            if (state_node == tree->root) tree->root = l;
                            else if (state_node == stack.back()->left) stack.back()->left = l;
                            else stack.back()->right = l;
                        }
                        else
                        {
                            min = tree->findmin(r);
                            min->right = tree->removemin(r);
                            min->left = l;
                            if (state_node == tree->root) tree->root = tree->balance(min);
                            else if (state_node == stack.back()->left) stack.back()->left = tree->balance(min);
                            else stack.back()->right = tree->balance(min);
                        }
                        delete state_node;
                        state = 2;
                    }
                }
                break;
            case 2: // Up
                if (stack.size() <= 0)
                {
                    QMessageBox::information(this, "Removing", "Completed");
                    stepped_mode = empty;
                    SetActiveButtons(true);
                    state = 0;
                }
                else
                {
                    l = stack.pop_back();
                    l->color.setRgb(0, 0, 255);
                    if (l == tree->root) tree->root = tree->balance(l);
                    else if (l == stack.back()->left) stack.back()->left = tree->balance(l);
                    else stack.back()->right = tree->balance(l);
                }
                break;
        }
    }
    UpdateGraphics();
//    if (!n) return nullptr;
//    if (data < n->data)
//    {
//        n->left = removebalanced(n->left,data);
//    }
//    else if (data > n->data)
//    {
//        n->right = removebalanced(n->right,data);
//    }
//    else
//    {
//        node<T>* l = n->left;
//        node<T>* r = n->right;
//        delete n;
//        if (!r) return l;
//        node<T>* min = findmin(r);
//        min->right = removemin(r);
//        min->left = l;
//        return balance(min);
//    }
//    return balance(n);
}

void MainWindow::updateTreeColor()
{
    if (!tree || locked || lockedUpd) return;
    tree->go_darker();
    UpdateGraphics();
}
