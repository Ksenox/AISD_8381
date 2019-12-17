#include "mainwindow.h"
#include "ui_mainwindow.h"




std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
        // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::showMaximized();
    mainGraphicsScene = new QGraphicsScene();
    ui->graphicsView->setScene(mainGraphicsScene);
    tree = nullptr;
    pen.setColor(QColor::fromRgb(0, 255, 0));
    started = false;
    first = nullptr;
    second = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    Help* h = new Help;
    h->show();
}


void MainWindow::visualize()
{
    mainGraphicsScene->clear();
    if (!tree) return;
    draw(tree->root, tree->max_depth(tree->root, 1));

}

void MainWindow::draw(Node *n, int maxdepth, int depth, int x, int y)
{
    if (n == nullptr) return;
    int offset = pow(2, maxdepth + 3 - depth);
    // Lines
    if (n->left) mainGraphicsScene->addLine(x + 32, y + 32, x - offset + 32, y + 64 + 32, pen);
    if (n->right) mainGraphicsScene->addLine(x + 32, y + 32, x + offset + 32, y + 64 + 32, pen);
    // Ellipse
    QBrush brush(n->color);
    QPen pen(n->color, 3);
    mainGraphicsScene->addEllipse(x, y, 64, 64, pen, brush);
    // Text
    QGraphicsTextItem *numb = new QGraphicsTextItem();
    numb->setPlainText(QString::fromStdString(n->info));
    numb->setDefaultTextColor(Qt::black);
    numb->setScale(2);
    numb->setPos(x + 16, y + 8);
    mainGraphicsScene->addItem(numb);
    // Next
    draw(n->left, maxdepth, depth + 1, x - offset, y + 64);
    draw(n->right, maxdepth, depth + 1, x + offset, y + 64);
}

void MainWindow::on_pushButton_clicked()
{
    if (first) first->color.setRgb(255, 0, 0);
    if (second) second->color.setRgb(255, 0, 0);

    tree = new binTree();
    elems.clean();
    int i = 0;
    tree->root = new Node();
    std::string s = ui->lineEdit->text().toStdString();
    if(tree->parse_tree(tree->root, s, i)) {
        QMessageBox::warning(this, "Error", "Error parsing tree");
        ui->lineEdit->setText("");
        return;
    }
    tree->get_elems(elems, tree->root);
    Node* first;
    Node* second;
    if (tree->get_duplicates(elems, first, second)) {
        first->color.setRgb(0, 0, 255);
        second->color.setRgb(0, 0, 255);
        QString qs = QString::fromStdString(first->info);
        QMessageBox::information(this, "Result", "There are two or more equal elems with value " + qs);
    }
    else {
        QMessageBox::warning(this, "Result", "There are not two or more equal elems");
    }
    started = false;
    visualize();
}

void MainWindow::on_stepButton_clicked()
{
    if (!started) {
        tree = new binTree();
        elems.clean();
        int i = 0;
        tree->root = new Node();
        std::string s = ui->lineEdit->text().toStdString();
        if(tree->parse_tree(tree->root, s, i)) {
            QMessageBox::warning(this, "Error", "Error parsing tree");
            ui->lineEdit->setText("");
            return;
        }
        started = true;
        tree->get_elems(elems, tree->root);
        a = 0;
        b = 0;
    }
    if (a == elems.size() - 1) {
        QMessageBox::warning(this, "Result", "There are not two or more equal elems");
        started = false;
    }
    else if (b == elems.size() - 1) {
        a++;
        b = a + 1;
    }
    else {
        b++;
    }

    if (elems[a]->info == elems[b]->info) {
        if (started) {
            QString qs = QString::fromStdString(elems[a]->info);
            QMessageBox::information(this, "Result", "There are two or more equal elems with value " + qs);
        }
        started = false;
    }

    if (first) first->color.setRgb(255, 0, 0);
    if (second) second->color.setRgb(255, 0, 0);
    first = elems[a];
    second = elems[b];
    first->color.setRgb(0, 0, 255);
    second->color.setRgb(0, 0, 255);

    visualize();
}

void MainWindow::on_fileButton_clicked()
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
    ui->lineEdit->setText(QString::fromUtf8(inputStr.c_str()));
}
