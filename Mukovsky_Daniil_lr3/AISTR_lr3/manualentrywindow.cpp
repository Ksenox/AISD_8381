#include "manualentrywindow.h"
#include "ui_manualentrywindow.h"

manualEntryWindow::manualEntryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manualEntryWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ввод вручную");
    setAttribute(Qt::WA_DeleteOnClose);
}

manualEntryWindow::~manualEntryWindow()
{
    delete ui;
}

void manualEntryWindow::on_pushButton_clicked()
{
    emit sendString(ui->Array->text());
    close();
}

