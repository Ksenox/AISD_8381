#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusLabel = new QLabel(this);
    statusLabel2 = new QLabel(this);
    statusProgressBar = new QProgressBar(this);
    statusLabel->setText("Status Label");
    statusProgressBar->setTextVisible(false);
    // addPermanentWidget(label) would add it to the first empty spot from the bottom right
    // If you're just wanting to show a message, you could use: statusBar()->showMessage(tr("Message Here"))
    ui->statusBar->addWidget(statusLabel);
    ui->statusBar->addWidget(statusLabel2);
    ui->statusBar->addWidget(statusProgressBar,1);

    model = new mainmodel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::syncState()
{
    ui->List1->clear();
    ui->List2->clear();
    ui->List3->clear();
    state s = model->current_state;
    statusLabel->setText(QString::number(model->current_state.column));
    statusLabel2->setText(QString::number(model->current_state.position));
    for (int i = 0; i < s.l1->length(); i++)
    {
        QString str = QString::number((*s.l1)[i]);
        QListWidgetItem* item = new QListWidgetItem(str);

        ui->List1->addItem(item);
    }
    for (int i = 0; i < s.l2->length(); i++)
    {
        QString str = QString::number((*s.l2)[i]);
        QListWidgetItem* item = new QListWidgetItem(str);

        ui->List2->addItem(item);
    }
    for (int i = 0; i < s.l3->length(); i++)
    {
        QString str = QString::number((*s.l3)[i]);
        QListWidgetItem* item = new QListWidgetItem(str);

        ui->List3->addItem(item);
    }
}

void MainWindow::on_GenerateButton_clicked()
{
    model->current_state.column = 0;
    model->current_state.position = 0;
    while (model->current_state.l1->length() > 0) model->current_state.l1->pop();
    while (model->current_state.l2->length() > 0) model->current_state.l2->pop();
    while (model->current_state.l3->length() > 0) model->current_state.l3->pop();
    std::srand(std::time(nullptr));
    int max = rand() % 10 + 3;
    for (int i = 0; i < max; i++)
    {
        model->current_state.l1->push(rand()%100);
    }
    syncState();
}

void MainWindow::on_LinkedListButton_clicked()
{
    //model->undo_states = utils_list<state>();
    model->current_state.SetLinked();
}

void MainWindow::on_ArrayListButton_clicked()
{
    //model->undo_states = utils_list<state>();
    model->current_state.SetArr();
}

void MainWindow::on_BackButton_clicked()
{

}

void MainWindow::on_AutoButton_clicked()
{
    syncState();
}

void MainWindow::on_ForwardButton_clicked()
{
    // save state
    utils_strandsort::step(model->current_state);
    syncState();
}

void MainWindow::on_SortButton_clicked()
{
    utils_strandsort::sort(model->current_state);
    syncState();
}


