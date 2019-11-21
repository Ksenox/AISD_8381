#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainmodel(new logic_model()),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLabel* textLabel = new QLabel(this);
    textLabel->setText("Column: ");
    statusLabel = new QLabel(this);
    QLabel* textLabel2 = new QLabel(this);
    textLabel2->setText("Position: ");
    statusLabel2 = new QLabel(this);
    //statusProgressBar = new QProgressBar(this);

    //statusProgressBar->setTextVisible(false);
    // addPermanentWidget(label) would add it to the first empty spot from the bottom right
    // If you're just wanting to show a message, you could use: statusBar()->showMessage(tr("Message Here"))
    ui->statusBar->addWidget(textLabel);
    ui->statusBar->addWidget(statusLabel);
    ui->statusBar->addWidget(textLabel2);
    ui->statusBar->addWidget(statusLabel2);
    //ui->statusBar->addWidget(statusProgressBar,1);
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
    state s = mainmodel->current;
    statusLabel->setText(QString::number(s.column));
    statusLabel2->setText(QString::number(s.position));
    syncListView(ui->List1, *s.l1);
    syncListView(ui->List2, *s.l2);
    syncListView(ui->List3, *s.l3);
    if (s.column == 3)
    {
        QString result = "";
        for (int i = 0; i < s.l3->size(); i++)
        {
            result += QString::number(s.l3->at(i)) + " ";
        }
        ui->Output->setText(result);
    }
    else
    {
        ui->Output->setText("");
    }
    mainmodel->busy = false;
}

void MainWindow::syncListView(QListWidget* view, IList<int>& list)
{
    for (int i = 0; i < list.size(); i++)
    {
        int v = list[i];
        QListWidgetItem* item = new QListWidgetItem(QString::number(list[i]));
        QColor color;
        int r = v < 128 ? (127 - v) * 2 : 0;
        int g = v < 128 ? v * 2 : (255 - v) * 2;
        int b = v <= 128 ? 0 : (v - 128) * 2;
        color.setRgb(r, g, b);
        item->setBackgroundColor(color);
        view->addItem(item);
    }
}

void MainWindow::on_GenerateButton_clicked()
{
    M_CHECK
    mainmodel->Generate(ui->RandomCount->text().isEmpty() ? 20 : ui->RandomCount->text().toInt(), 255);
    syncState();
    M_UNLOCK
}

void MainWindow::on_ProceedButon_clicked()
{
    M_CHECK
    if (!ui->Input->toPlainText().isEmpty())
    {
        mainmodel->Clear();
        for (auto i : ui->Input->toPlainText().split(' '))
        {
            mainmodel->current.l1->push_back(i.toInt());
        }
        syncState();
    }
    M_UNLOCK
}

void MainWindow::on_LinkedListButton_clicked()
{
    M_CHECK
    mainmodel->SetLinked();
    syncState();
    M_UNLOCK
}

void MainWindow::on_ArrayListButton_clicked()
{
    M_CHECK
    mainmodel->SetArr();
    syncState();
    M_UNLOCK
}

void MainWindow::on_AutoButton_clicked()
{
    M_CHECK
    mainmodel->SortStep();
    syncState();
    M_UNLOCK
}


void MainWindow::on_SortButton_clicked()
{
    M_CHECK
    mainmodel->Sort();
    syncState();
    M_UNLOCK
}




