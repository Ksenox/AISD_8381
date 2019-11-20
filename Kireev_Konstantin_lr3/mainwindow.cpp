#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pixmap_sort(":/resources/img/sort.jpg");
    QIcon ButtonIcon(pixmap_sort);
    ui->incrementShell->setIcon(ButtonIcon);
    ui->incrementShell->setIconSize(pixmap_sort.rect().size());
    QPixmap pixmap_array(":/resources/img/array.png");
    QIcon ButtonIconArray(pixmap_array);
    ui->array->setIcon(ButtonIconArray);
    ui->array->setIconSize(pixmap_array.rect().size());
    QPixmap pixmap_info(":/resources/img/info.png");
    QIcon ButtonIconInfo(pixmap_info);
    ui->info1->setIcon(ButtonIconInfo);
    ui->info1->setIconSize(pixmap_info.rect().size());
    ui->info2->setIcon(ButtonIconInfo);
    ui->info2->setIconSize(pixmap_info.rect().size());
    QPixmap pixmap_steps(":/resources/img/steps.png");
    QIcon ButtonIconSteps(pixmap_steps);
    ui->step1->setIcon(ButtonIconSteps);
    ui->step1->setIconSize(pixmap_steps.rect().size());
    ui->comboBox->addItem("Шелла");
    ui->comboBox->addItem("Седжвика");
    ui->comboBox->addItem("Хиббарда");
    ui->comboBox->addItem("Пратта");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_array_clicked()
{
    srand(time(0));
    QString str_n = ui->lineEdit->text();
    int n = str_n.toInt();
    int array[n];
    QString arrayStr;
    for(int i = 0; i < n; i++)
    {
        array[i] = rand()%100;
        arrayStr += QString::number(array[i]) + " ";
    }
    ui->before_sort->setText(arrayStr);
}

void MainWindow::on_info1_clicked()
{
   QMessageBox::information(this, "Массив", "Генерация массива");
}

void MainWindow::on_incrementShell_clicked()
{
    QString before_sort_str = ui->before_sort->toPlainText();
    QString after_sort_str;
    ShellSort sort;
    int value = ui->comboBox->currentIndex();
    switch(value)
    {
        case(0):
            { after_sort_str = sort.Shell(before_sort_str, 0, 0); break; }
        case(1):
            { after_sort_str = sort.Shell(before_sort_str, 1, 0); break; }
        case(2):
            { after_sort_str = sort.Shell(before_sort_str, 2, 0); break; }
        case(3):
            { after_sort_str = sort.Shell(before_sort_str, 3, 0); break; }
    }
    ui->after_sort->setText(after_sort_str);
}

void MainWindow::on_info2_clicked()
{
    int value = ui->comboBox->currentIndex();
    switch(value)
    {
        case(0):
            { QMessageBox::information(this, "Последовательность Шелла", "Первоначально используемая Шеллом последовательность длин промежутков: d[1] = N/2, d[i] = d[i-1]/2, d[k] = 1\nВ худшем случае, сложность алгоритма составит O(N^{2})"); break; }
        case(1):
            { QMessageBox::information(this, "Последовательность Седжвика", "Предложенная Седжвиком последовательность: d[i] = 9*2^{i} - 9*2^{i/2} + 1, если i четное и d[i] = 8*2^{i} - 6*2^{(i+1)/2} + 1, если i нечетное\nПри использовании таких приращений средняя сложность алгоритма составляет: O(N^{7/6}), а в худшем случае порядка O(N^{4/3})"); break; }
        case(2):
            { QMessageBox::information(this, "Последовательность Хиббарда", "Предложенная Хиббардом последовательность:\nвсе значения 2^{i} - 1 ≤ N, i ∈ N\nТакая последовательность шагов приводит к алгоритму сложностью O(N^{3/2})"); break; }
        case(3):
            { QMessageBox::information(this, "Последовательность Пратта", "Предложенная Праттом последовательность: все значения 2^{i} * 3^{j} ≤ N/2, i,j ∈ N; В таком случае сложность алгоритма составляет O(N(logN)^{2})"); break; }
        default: exit(1);
    }
}

void MainWindow::on_step1_clicked()
{
    QString before_sort_str = ui->before_sort->toPlainText();
    QString after_sort_str;
    ShellSort sort;
    int value = ui->comboBox->currentIndex();
    switch(value)
    {
        case(0):
            { after_sort_str = sort.Shell(before_sort_str, 0, 1); break; }
        case(1):
            { after_sort_str = sort.Shell(before_sort_str, 1, 1); break; }
        case(2):
            { after_sort_str = sort.Shell(before_sort_str, 2, 1); break; }
        case(3):
            { after_sort_str = sort.Shell(before_sort_str, 3, 1); break; }
    }
    ui->after_sort->setText(after_sort_str);
}
