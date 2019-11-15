#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buildButton, SIGNAL (clicked()), this, SLOT (build()));
    connect(ui->file_build_button, SIGNAL (clicked()), this, SLOT (build_file()));
    connect(ui->rush_button, SIGNAL (clicked()), this, SLOT (run()));
    connect(ui->stepButton, SIGNAL (clicked()), this, SLOT (step()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::build() {
    string input = ui->input->text().toStdString();
    stepPointer = 0;

    try {
        if (input.length() == 0) throw runtime_error("There was no input!!");
        int space_pos = input.find(" ");
        while (space_pos != (int) string::npos) {
            input.erase(space_pos, 1);
            space_pos = input.find(" ");
        }

        lr = new lab4();
        lr->launch(input);

        ui->tree_view->setText(QString::fromStdString(lr->tree->to_tree_string()));
        ui->answer_label->setText(QString::fromStdString(lr->tree->to_infix_string()));

        ui->input->setEnabled(false);
        ui->buildButton->setEnabled(false);
        ui->file_build_button->setEnabled(false);
        ui->rush_button->setEnabled(true);
        ui->stepButton->setEnabled(true);
    } catch (runtime_error re) {
        ui->tree_view->setText(QString::fromStdString(re.what()));
    }
}

void MainWindow::build_file() {
    string input = ui->input->text().toStdString();
    stepPointer = 0;

    try {
        ifstream fole(input.empty() ? "/home/alex/lab4/input.txt" : input);
        if (fole.fail() || !fole) throw runtime_error("Input stream not created.");
        getline(fole, input);
        if (input.empty()) throw runtime_error("File was empty!");

        lr = new lab4();
        lr->launch(input);

        ui->tree_view->setText(QString::fromStdString(lr->tree->to_tree_string()));
        ui->answer_label->setText(QString::fromStdString(lr->tree->to_infix_string()));

        ui->input->setEnabled(false);
        ui->buildButton->setEnabled(false);
        ui->file_build_button->setEnabled(false);
        ui->rush_button->setEnabled(true);
        ui->stepButton->setEnabled(true);
    } catch (runtime_error re) {
        ui->tree_view->setText(QString::fromStdString(re.what()));
    //} catch (...) {
    //    ui->tree_view->setText(QString::fromStdString("Something went wrong :/"));
    }
}

void MainWindow::run() {
    ui->input->setEnabled(true);
    ui->buildButton->setEnabled(true);
    ui->file_build_button->setEnabled(true);
    ui->rush_button->setEnabled(false);
    ui->stepButton->setEnabled(false);

    try {
        lr->rush();

        ui->tree_view->setText(QString::fromStdString(lr->tree->to_tree_string()));
        ui->answer_label->setText(QString::fromStdString(lr->tree->to_infix_string()));
    } catch (runtime_error re) {
        ui->tree_view->setText(QString::fromStdString(re.what()));
    }
}

void MainWindow::step() {
    ui->rush_button->setEnabled(false);

    try {
        lr->step(&stepPointer);
        stepPointer++;

        string out = lr->state;
        out += "\n\n";
        out += lr->tree->to_tree_string();
        ui->tree_view->setText(QString::fromStdString(out));
        ui->answer_label->setText(QString::fromStdString(lr->tree->to_infix_string()));
    } catch (runtime_error re) {
        ui->input->setEnabled(true);
        ui->buildButton->setEnabled(true);
        ui->file_build_button->setEnabled(true);
        ui->rush_button->setEnabled(false);
        ui->stepButton->setEnabled(false);
        ui->tree_view->setText(QString::fromStdString(re.what()));
    }
}

//TODO: files IO +, step-by-step debug +, o(x)/O(x) in repo.
