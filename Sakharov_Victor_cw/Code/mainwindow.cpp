#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QShortcut>

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
//    ui->butAdd->setEnabled(false);
//    ui->butRemove->setEnabled(false);
//    ui->butStepAdd->setEnabled(false);
//    ui->butStepRemove->setEnabled(false);
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this, SLOT(on_butUndo_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_X), this, SLOT(on_butRedo_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateGraphics(bool save)
{
    if (lockedUpd) return;
    lockedUpd = true;
    switch (stepped_mode) {
    case bst:
        ui->stateLabel->setText("bst");
        break;
    case empty:
        ui->stateLabel->setText("empty");
        break;
    case pyramid:
        ui->stateLabel->setText("pyramid");
        break;
    case step_add:
        ui->stateLabel->setText("step_add");
        break;
    case step_remove:
        ui->stateLabel->setText("step_remove");
        break;
    }
    if (!tree || tree->redolist.empty()) ui->butRedo->setEnabled(false);
    else ui->butRedo->setEnabled(true);
    if (!tree || tree->undolist.empty()) ui->butUndo->setEnabled(false);
    else ui->butUndo->setEnabled(true);
    mainGraphicsScene->clear();
    if (!tree) return;
    if (save) {
        ofstream myfile;
        myfile.open("backup.txt");
        myfile << tree->node_string(tree->root) + "\n";
        myfile.close();
    }
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
    ChangeMode(empty, nullptr);
    UpdateGraphics();
}

void MainWindow::on_butGenerateOptimal_clicked()
{
    if (!tree) on_butGenerate_clicked();
    if (!tree || tree->max_depth() <= 2) return;
    tree->to_optimal();
    ui->balancedLabel->setText("AVL tree");
    ChangeMode(empty, nullptr);
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
    QColor c = n->color;
    c.setHsvF(c.hueF(), c.saturationF(), n->light);
    QBrush brush(c);
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

void MainWindow::ChangeMode(mode newmode, QPushButton* but)
{
    if (newmode == stepped_mode)
    {
        tree->save();
    }
    else if (newmode == empty)
    {
        SetActiveButtons(true);
    }
    else
    {
        tree->go_red(tree->root);
        tree->undolist.clear();
        tree->redolist.clear();
        SetActiveButtons(false);
        if (but) but->setEnabled(true);
    }
    if (tree->undolist.empty()) ui->butUndo->setEnabled(false);
    else ui->butUndo->setEnabled(true);
    if (tree->redolist.empty()) ui->butRedo->setEnabled(false);
    else ui->butRedo->setEnabled(true);
    stepped_mode = newmode;
}

bool MainWindow::TryRedo()
{
    if (!tree->redolist.empty())
    {
        tree->redo();
        UpdateGraphics();
        return true;
    }
    return false;
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->graphicsView->resetTransform();
    ui->graphicsView->scale(1.0 / position, 1.0 / position);
}

void MainWindow::on_butStepBst_clicked()
{
    ChangeMode(bst, ui->butStepBst);
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
        n->light = 1;
    }
    UpdateGraphics();
}

void MainWindow::on_butStepPyramid_clicked()
{
    ChangeMode(pyramid, ui->butStepPyramid);
    if (pyramid_stepped.empty())
    {
        if (is_pyramid) QMessageBox::information(this, "Pyramid?", "    YES    ");
        else QMessageBox::warning(this, "Pyramid?", "    NO    ");
        ChangeMode(empty, nullptr);
    }
    else
    {
        node<int>* n = pyramid_stepped.pop_front();
        n->color.setRgb(0, 0, 255);
        n->light = 1;
    }
    UpdateGraphics();
}

void MainWindow::on_butAdd_clicked()
{
    if (!tree) return;
    ChangeMode(empty, nullptr);
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
    if (!tree) return;
    ChangeMode(step_add, ui->butStepAdd);
    if (TryRedo()) return;
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
            state_node->light = 1;
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
                ChangeMode(empty, nullptr);
                state = 0;
            }
            break;
        case 2: // Up
            if (stack.size() <= 1)
            {
                QMessageBox::information(this, "Insertion", "Completed");
                ChangeMode(empty, nullptr);
                state = 0;
                break;
            }
            n = stack.pop_back();
            n->color.setRgb(0, 0, 255);
            n->light = 1;
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

void MainWindow::on_butRemove_clicked()
{
    if (!tree) return;
    ChangeMode(empty, nullptr);
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
    ChangeMode(step_remove, ui->butStepRemove);
    if (TryRedo()) return;
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
                ChangeMode(empty, nullptr);
                state = 0;
            }
            else
            {
                if (current < state_node->data)
                {
                    stack.push_back(state_node);
                    state_node->color.setRgb(0, 255, 0);
                    state_node->light = 1;
                    state_node = state_node->left;
                }
                else if (current > state_node->data)
                {
                    stack.push_back(state_node);
                    state_node->color.setRgb(0, 255, 0);
                    state_node->light = 1;
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
                ChangeMode(empty, nullptr);
                state = 0;
            }
            else
            {
                l = stack.pop_back();
                l->color.setRgb(0, 0, 255);
                l->light = 1;
                if (l == tree->root) tree->root = tree->balance(l);
                else if (l == stack.back()->left) stack.back()->left = tree->balance(l);
                else stack.back()->right = tree->balance(l);
            }
            break;
    }
    UpdateGraphics();
}

void MainWindow::updateTreeColor()
{
    if (!tree || locked || lockedUpd) return;
    tree->go_darker();
    UpdateGraphics(false);
}

void MainWindow::on_butUndo_clicked()
{
    tree->undo();
    UpdateGraphics();
}

void MainWindow::on_butRedo_clicked()
{
    tree->redo();
    UpdateGraphics();
}

void MainWindow::on_butLoad_clicked()
{
    string s = "";
    tree = new utils_tree<int>(s);
    tree->load();
}
