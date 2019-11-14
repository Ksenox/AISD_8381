#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buildButton, SIGNAL (clicked()), this, SLOT (build()));
    connect(ui->rush_button, SIGNAL (clicked()), this, SLOT (run()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::build() {
    string input = ui->input->text().toStdString();

    try {
        lr = new lab4();
        lr->launch(input);

        ui->tree_view->setText(QString::fromStdString(lr->tree->to_tree_string()));
        ui->answer_label->setText(QString::fromStdString(lr->tree->to_infix_string()));

        ui->input->setEnabled(false);
        ui->buildButton->setEnabled(false);
        ui->rush_button->setEnabled(true);
    } catch (runtime_error re) {
        ui->tree_view->setText(QString::fromStdString(re.what()));
    }
}

void MainWindow::run() {
    ui->input->setEnabled(true);
    ui->buildButton->setEnabled(true);
    ui->rush_button->setEnabled(false);

    try {
        lr->rush();

        ui->tree_view->setText(QString::fromStdString(lr->tree->to_tree_string()));
        ui->answer_label->setText(QString::fromStdString(lr->tree->to_infix_string()));
    } catch (runtime_error re) {
        ui->tree_view->setText(QString::fromStdString(re.what()));
    }
}
