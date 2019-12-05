#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString inputString = ui->input->text();
    try{
        QGraphicsScene* scene = new QGraphicsScene(this);
        BinaryTree binTree(inputString, scene);
        QString answer = binTree.getForestBreadthString();
        answer.remove(answer.size()-2, 2);
        ui->output->setText(answer);
        ui->binTreePicture->setScene(binTree.scene);
    }
    catch (const char* exc)
    {
        ui->output->setText(exc);
    }
}

void MainWindow::on_action_triggered()
{
    QMessageBox::information(0, "Правила ввода", "Скобочная запись бинарного дерева имеет вид: \n < БД > ::= < пусто > | < непустое БД > \n < непустое БД > ::=  (< корень > < БД > < БД > ).");
}

void MainWindow::on_action_2_triggered()
{
    QMessageBox::information(0, "Формат вывода", "В поле ответа будут выведены элементы соответствующего леса. Элементы выводятся по ширине, то есть элементы каждого уровня выводятся слева направо, начиная с уровня корня. \nЗнак \"#\" означает пустое значение элемента.");
}
