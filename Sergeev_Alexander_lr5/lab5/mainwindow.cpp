#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lab5.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QStringList available_types = {"string", "char", "int", "double"};

  ui->type_selector->addItems(available_types);

  connect(ui->line_button, SIGNAL(clicked()), this, SLOT(read_from_line()));
  connect(ui->file_button, SIGNAL(clicked()), this, SLOT(read_from_file()));
  connect(ui->step_button, SIGNAL(clicked()), this, SLOT(step()));

  connect(ui->straightforward_button, SIGNAL(clicked()), this, SLOT(rush_forward()));
  connect(ui->proceed_button, SIGNAL(clicked()), this, SLOT(step_forward()));
  connect(ui->multiple_button, SIGNAL(clicked()), this, SLOT(mult_forward()));
}

MainWindow::~MainWindow() {
  delete ui;
}


void MainWindow::enable_input(bool val) {
    ui->straightforward_button->setEnabled(!val);
    ui->proceed_button->setEnabled(!val);
    ui->multiple_button->setEnabled(!val);

    ui->line_button->setEnabled(val);
    ui->file_button->setEnabled(val);
    ui->type_selector->setEnabled(val);
    ui->line_input->setEnabled(val);
    ui->step_box->setEnabled(val);
}

void MainWindow::step_input(bool val) {
    ui->straightforward_button->setEnabled(!val);
    ui->proceed_button->setEnabled(!val);
    ui->multiple_button->setEnabled(!val);

    ui->step_button->setEnabled(val);
}


void MainWindow::read_from_file() {
    std::string input = ui->line_input->text().toStdString();
    int result = lab5::launch(ui->canvas, &input, true, ui->type_selector->currentIndex(), ui->step_box->isChecked());

    if (result == 0) {
        enable_input(false);
        ui->answer->setText("Both trees successfully loaded.");
    } else if (result == 2) {
        enable_input(false);
        step_input(true);
        ui->answer->setText("Continue building...");
    } else {
        ui->answer->setText("Error occures, input again.");
    }
}

void MainWindow::read_from_line() {
    std::string input = ui->line_input->text().toStdString();
    int result = lab5::launch(ui->canvas, &input, false, ui->type_selector->currentIndex(), ui->step_box->isChecked());

    if (result == 0) {
        enable_input(false);
        ui->answer->setText("Both trees successfully loaded.");
    } else if (result == 2) {
        enable_input(false);
        step_input(true);
        ui->answer->setText("Continue building...");

    } else {
        ui->answer->setText("Error occures, input again.");
    }
}


void MainWindow::step() {
    int result = 1;

    switch (lab5::type) {
        case 0:
            result = lab5::launch_steps<std::string>(ui->canvas);
            break;
        case 1:
            result = lab5::launch_steps<char>(ui->canvas);
            break;
        case 2:
            result = lab5::launch_steps<int>(ui->canvas);
            break;
        case 3:
            result = lab5::launch_steps<double>(ui->canvas);
            break;
    }

    if (result == 0) {
        step_input(false);
        ui->answer->setText("Both trees successfully loaded.");
    } else {
        ui->answer->setText("Continue building...");
    }
}


void MainWindow::step_forward() {
    ui->straightforward_button->setEnabled(false);
    ui->multiple_button->setEnabled(false);

    int result = 1;

    switch (lab5::type) {
        case 0:
            result = lab5::step<std::string>(ui->canvas);
            break;
        case 1:
            result = lab5::step<char>(ui->canvas);
            break;
        case 2:
            result = lab5::step<int>(ui->canvas);
            break;
        case 3:
            result = lab5::step<double>(ui->canvas);
            break;
    }

    if (result == 0) {
        enable_input(true);
        ui->answer->setText("Merge successful.");
    } else {
        ui->answer->setText("Continue merging...");
    }
}

void MainWindow::rush_forward() {
    int result = 1;

    switch (lab5::type) {
        case 0:
            result = lab5::rush<std::string>(ui->canvas);
            break;
        case 1:
            result = lab5::rush<char>(ui->canvas);
            break;
        case 2:
            result = lab5::rush<int>(ui->canvas);
            break;
        case 3:
            result = lab5::rush<double>(ui->canvas);
            break;
    }

    if (result == 0) {
        enable_input(true);
        ui->answer->setText("Merge successful.");
    } else {
        ui->answer->setText("Error occures, merge again.");
    }
}

void MainWindow::mult_forward() {
    int result = 1;

    switch (lab5::type) {
        case 0:
            result = lab5::mult<std::string>(ui->canvas);
            break;
        case 1:
            result = lab5::mult<char>(ui->canvas);
            break;
        case 2:
            result = lab5::mult<int>(ui->canvas);
            break;
        case 3:
            result = lab5::mult<double>(ui->canvas);
            break;
    }

    if (result == 0) {
        enable_input(true);
        ui->answer->setText("Research successful.");
    } else {
        ui->answer->setText("Error occures, research again.");
    }
}
