#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    status = new QLabel();
    ui->statusBar->addPermanentWidget(status);
    status->setText("Ожидание");
    graphicsScene = new QGraphicsScene();
    ui->graphicsView->setScene(graphicsScene);
    srand(time(NULL));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
    srand(time(nullptr));
    tree = nullptr;
    mode = 0;
    ui->insertButton->setEnabled(true);
    ui->removeButton->setEnabled(true);
    ui->nextButton->setEnabled(false);
    ui->endButton->setEnabled(false);
    visualize();
}

void MainWindow::visualize()
{
    graphicsScene->clear();
    if (tree) {
        draw(graphicsScene, tree, max_depth(tree, 1));
    }
}

void MainWindow::draw(QGraphicsScene* scene, Node *n, int maxdepth, int depth, int x, int y)
{
    if (n == nullptr) return;
    int offset = pow(2, maxdepth + 3 - depth);
    // Lines
    QPen pen(n->color, 3);
    if (n->left) scene->addLine(x + 32, y + 32, x - offset + 32, y + 64 + 32, pen);
    if (n->right) scene->addLine(x + 32, y + 32, x + offset + 32, y + 64 + 32, pen);
    // Ellipse
    QBrush brush(n->color);
    scene->addEllipse(x, y, 64, 64, pen, brush);
    // Text
    QGraphicsTextItem *numb = new QGraphicsTextItem();
    numb->setPlainText(QString::number(n->data));
    numb->setDefaultTextColor(Qt::black);
    numb->setScale(2);
    numb->setPos(x + 16, y + 8);
    scene->addItem(numb);
    // Next
    draw(scene, n->left, maxdepth, depth + 1, x - offset, y + 64);
    draw(scene, n->right, maxdepth, depth + 1, x + offset, y + 64);
}

int MainWindow::read(bool& ok)
{
    ok = true;
    if (ui->elementEdit->text().isEmpty())
    {
        status->setText("Введите элемент!");
        ok = false;
        return 0;
    }
    bool isok;
    int res = ui->elementEdit->text().toInt(&isok);
    if (!isok)
    {
        status->setText("Элемент - не число!");
        ui->elementEdit->setText("");
        ok = false;
        return 0;
    }
    return res;
}


void MainWindow::on_fileButton_clicked()
{
    QString inputStr;
    QString fileName = QFileDialog::getOpenFileName(this, "Open TXT File",  QDir::homePath(), "TXT text (*.txt);;All Files (*)");
    if (fileName == nullptr)
    {
        status->setText("Имя файла не было выбрано");
        return;
    }
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        inputStr = stream.readAll();
    }
    if(inputStr.isEmpty())
        return;
    file.close();
    ui->inputEdit->setText(inputStr);
}

void MainWindow::on_buildButton_clicked()
{
    reset();
    int i = 0;
    string raw = ui->inputEdit->text().toStdString();
    if (parse_tree(tree, raw, i))
    {
        tree = nullptr;
        status->setText("Ошибка обработки дерева");
        return;
    }
    visualize();
    status->setText("Дерево построено");
}

void MainWindow::on_randCountBox_valueChanged(int arg1)
{
    rand_count = arg1;
}

void MainWindow::on_randMaxBox_valueChanged(int arg1)
{
    rand_max = arg1;
}

void MainWindow::on_randButton_clicked()
{
    reset();
    for (int i = 0; i < rand_count; i++)
    {
        int r = rand() % rand_max;
        insert_old(tree, r);
    }
    visualize();
    status->setText("Рандомизация прошла успешно");
}

void MainWindow::on_insertButton_clicked()
{
    bool ok;
    int val = read(ok);
    if (!ok) return;
    if (tree) {
        log = new array_list();
        mode = 1;
        index = 0;
        ui->insertButton->setEnabled(false);
        ui->removeButton->setEnabled(false);
        ui->nextButton->setEnabled(true);
        ui->endButton->setEnabled(true);
        Node* ncopy = copy(tree);
        ncopy = insert(log, ncopy, ncopy, val);
        log->push_back(ncopy);
    }
    visualize();
}

void MainWindow::on_removeButton_clicked()
{
    bool ok;
    int val = read(ok);
    if (!ok) return;
    if (tree) {
        log = new array_list();
        mode = 2;
        index = 0;
        ui->insertButton->setEnabled(false);
        ui->removeButton->setEnabled(false);
        ui->nextButton->setEnabled(true);
        ui->endButton->setEnabled(true);
        Node* ncopy = copy(tree);
        ncopy = remove(log, ncopy, ncopy, val);
        log->push_back(ncopy);
    }
    visualize();
}

void MainWindow::on_nextButton_clicked()
{
    if (index >= log->size() - 1)
    {
        on_endButton_clicked();
    }
    else
    {
        tree = log->at(index);
        index++;
        visualize();
    }
}

void MainWindow::on_endButton_clicked()
{
    tree = log->at(log->size() - 1);
    mode = 0;
    ui->insertButton->setEnabled(true);
    ui->removeButton->setEnabled(true);
    ui->nextButton->setEnabled(false);
    ui->endButton->setEnabled(false);
    visualize();
}
