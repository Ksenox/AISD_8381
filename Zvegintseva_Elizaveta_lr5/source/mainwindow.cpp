#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    questionGraphicsScene = new QGraphicsScene();
    answerGraphicsScene = new QGraphicsScene();
    ui->questionGraphicsView->setScene(questionGraphicsScene);
    ui->answerGraphicsView->setScene(answerGraphicsScene);
    reset();
}

MainWindow::~MainWindow()
{
    delete ui;
    mode = 0;
}

void MainWindow::reset()
{
    srand(time(nullptr));
    questionTree = nullptr;
    answerTree = nullptr;
    mode = ui->radioRemoveButton->isChecked();
    var_count = ui->varNum->value();
    difficulty = ui->difficultyBox->value();
    ui->questionBrowser->setPlainText("Поле для заданий");
    ui->answerBrowser->setPlainText("Поле для ответов");
    visualize();
}

void MainWindow::visualize()
{
    ui->questionGraphicsView->setScene(questionGraphicsScene);
    ui->answerGraphicsView->setScene(answerGraphicsScene);
    questionGraphicsScene->clear();
    answerGraphicsScene->clear();
    if (questionTree) {
        draw(questionGraphicsScene, questionTree->root, questionTree->max_depth(questionTree->root, 1));
    }
    if (answerTree) {
        draw(answerGraphicsScene, answerTree->root, answerTree->max_depth(answerTree->root, 1));
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
        QMessageBox::warning(this, "Warining!", "Input elemet is empty. Applying random data");
        ui->elementEdit->setText(QString::number(rand() % 100));
        ok = false;
        return 0;
    }
    bool isok;
    int res = ui->elementEdit->text().toInt(&isok);
    if (!isok)
    {
        QMessageBox::warning(this, "Warining!", "Input elemet isn't a number!");
        ui->elementEdit->setText("");
        ok = false;
        return 0;
    }
    return res;
}


void MainWindow::on_resetButton_clicked()
{
    reset();
}

void MainWindow::on_varButton_clicked() // Генерируем вариает в гуй
{
    string question = "";
    string answer = "";
    questionTree = new binTree();
    answerTree = new binTree();
    questionTree->root = nullptr;
    answerTree->root = nullptr;
    if (mode == 0) generate_var_insert(question, answer, *questionTree, *answerTree, difficulty);
    else generate_var_remove(question, answer, *questionTree, *answerTree, difficulty);
    ui->questionBrowser->setPlainText(QString::fromStdString(question));
    ui->answerBrowser->setPlainText(QString::fromStdString(answer));
    visualize();
}

void MainWindow::on_genFileButton_clicked() // Генерируем вариает в файл
{
    string question = "";
    string answer = "";
    if (mode == 0) generate_vars_insert(question, answer, var_count, difficulty);
    else generate_vars_remove(question, answer, var_count, difficulty);
    ui->questionBrowser->setPlainText(QString::fromStdString(question));
    ui->answerBrowser->setPlainText(QString::fromStdString(answer));
    file_write("input.txt", question);
    file_write("output.txt", answer);
    visualize();
}

void MainWindow::on_varNum_valueChanged(int arg1)
{
    var_count = arg1;
}

void MainWindow::on_difficultyBox_valueChanged(int arg1)
{
    difficulty = arg1;
}

void MainWindow::on_radioInsertButton_toggled(bool checked)
{
    mode = 0;
}

void MainWindow::on_radioRemoveButton_toggled(bool checked)
{
    mode = 1;
}

void MainWindow::on_inFIleButton_clicked()
{
    QString inputStr;
    QString fileName = QFileDialog::getOpenFileName(this, "Open TXT File",  QDir::homePath(), "TXT text (*.txt);;All Files (*)");
    if (fileName == nullptr)
    {
        QMessageBox::warning(this, "Warning", "File name is empty");
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

void MainWindow::on_treeGenButton_clicked()
{
    reset();
    if (questionTree) answerTree = questionTree;
    questionTree = new binTree();
    int i = 0;
    questionTree->root = nullptr;
    std::string s = ui->inputEdit->text().toStdString();
    if(questionTree->parse_tree(questionTree->root, s, i)) {
        QMessageBox::warning(this, "Error", "Error parsing tree");
        ui->inputEdit->setText("");
        reset();
        return;
    }
    visualize();
}

void MainWindow::on_insertButton_clicked()
{
    bool ok;
    int val = read(ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Error reading element");
        return;
    }
    if (questionTree) {
        answerTree = questionTree;
        binTree* tree = new binTree();
        tree->root = questionTree->copy(questionTree->root);
        questionTree = tree;
        questionTree->insert(questionTree->root, val);
    }
    visualize();
}

void MainWindow::on_removeButton_clicked()
{
    bool ok;
    int val = read(ok);
    if (!ok) {
        QMessageBox::warning(this, "Error", "Error reading element");
        return;
    }
    if (questionTree) {
        answerTree = questionTree;
        binTree* tree = new binTree();
        tree->root = questionTree->copy(questionTree->root);
        questionTree = tree;
        questionTree->remove(questionTree->root, val);
    }
    visualize();
}
