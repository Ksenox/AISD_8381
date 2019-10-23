#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->input_button, SIGNAL (clicked()), this, SLOT (build()));
    connect(ui->step_button, SIGNAL (clicked()), this, SLOT (step()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::build() {
    string input = ui->input->text().toStdString();

    ui->input->setEnabled(false);
    ui->input_button->setEnabled(false);
    ui->step_button->setEnabled(true);

    lab3::process(input, true);
    step();
}

void MainWindow::step() {
    if (lab3::isInit()) {
        lab3::friendlyStep();

        string definition;
        definition = "CURRENT DATA STATE:\n\n\n";
        definition += "Input Line:\n\n";
        definition += lab3::getSource();
        definition += "\n";

        for (unsigned long i = 0; i < lab3::getCurrentPos() - 1; i++) {
            definition += " ";
        }
        definition += "^\n\n\n";

        definition += "Stack state:\n\n";
        definition += lab3::getStackState()->toString();
        definition += "\n";
        definition += "Length: ";
        definition += to_string(*lab3::getStackState()->getStackSize());
        definition += "\n\n\n";

        definition += "Next command: ";
        definition += lab3::getNextCommand();

        ui->output->setText(QString::fromStdString(definition));

        string answer = lab3::getAnswer();
        ui->answer->setText(QString::fromStdString(answer));
    } else {
        ui->input->setEnabled(true);
        ui->input_button->setEnabled(true);
        ui->step_button->setEnabled(false);

        string definition;
        definition = "RESULTS:\n\n\n";
        definition += lab3::getMessage();

        ui->output->setText(QString::fromStdString(definition));

        string answer = lab3::getAnswer();
        ui->answer->setText(QString::fromStdString(answer));
    }
}
