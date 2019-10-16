#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->buildButton, SIGNAL (clicked()), this, SLOT (build()));
    connect(ui->fillButton, SIGNAL (clicked()), this, SLOT (fill()));
    connect(ui->outputButton, SIGNAL (clicked()), this, SLOT (calculate()));
}

void MainWindow::build() {
    if (ui->buildInput->text().toStdString().length() == 0) return;

    ui->fillButton->setText(FILL_TEXT);
    ui->fillInput->setText("");
    ui->answer->setText("");
    ui->answer->setEnabled(false);
    ui->fillButton->setEnabled(true);
    ui->outputButton->setEnabled(false);
    ui->output->setText("");

    try {
        output = "";
        this->input = ui->buildInput->text().toStdString();
        if (input.length() > MAX_CHARS) {
            string msg = "WARNING! DUE TO 1000+ CHAR LENGTH OF INPUT, ERROR DESCRIPTION WILL BE INCORRECT";
            this->printError(input, MAX_CHARS, msg);
        }
        convertPower(input);

        this->list = new AtomicList(input);
        this->output = "LISTED:";
        list->toFile(output);
    } catch (int e) {
        ui->fillButton->setEnabled(false);
        catchErrors(e);
    }

    ui->output->setText(QString::fromStdString(output));
}

void MainWindow::fill() {
    if (ui->fillInput->text().toStdString().length() == 0) return;

    ui->fillButton->setText(REFILL_TEXT);
    ui->answer->setText("");
    ui->answer->setEnabled(false);
    ui->outputButton->setEnabled(true);

    try {
        output = "";
        this->data = ui->fillInput->text().toStdString();
        this->list->fill(data);
        this->output = "FILLED:";
        list->toFile(output);
    } catch (int e) {
        catchErrors(e);
    }

    ui->output->setText(QString::fromStdString(output));
}

void MainWindow::calculate() {
    ui->answer->setEnabled(true);

    string answer = "ANSWER IS: ";
    try {
        output = "";
        answer.append(to_string(this->list->count(output)));
        this->output = "CALCULATED:";
    } catch (int e) {
        catchErrors(e);
    }

    ui->output->setText(QString::fromStdString(output));
    ui->answer->setText(QString::fromStdString(answer));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::catchErrors(int e) {
    string msg;
    int pure = e / MAX_CHARS;
    int info = e % MAX_CHARS;
    switch (pure * MAX_CHARS) {
        case WrongFormatException:
            output.append("INPUT WRONGLY FORMATTED, APPLICATION TERMINATED\n");
            msg = "Unidentified symbol here.";
            printError(input, info, msg);
            break;
        case UnidentifiedOperatorException:
            output.append("UNDEFINED OPERATOR FOUND, APPLICATION TERMINATED\n");
            msg = "Operator \"";
            msg += (char) info;
            msg += "\" can not be recognised.";
            printError(input, (int) input.find((char) info) + 1, msg);
            break;
        case VariableCountingException:
            output.append("VARIABLES WERE NOT REPLACED WITH NUMBERS BEFORE CALCULATION, APPLICATION TERMINATED\n");
            msg = "Variable \"";
            msg += (char) info;
            msg += "\" caused the exception.";
            printError(input, (int) input.find((char) info) + 1, msg);
            break;
        default:
            output.append("SOMETHING TERRIBLE HAPPENED, APPLICATION TERMINATED\n");
            break;
        }
}

void MainWindow::printError(string &errorString, int pos, string& message) {
    output.append(errorString).append("\n");
    for (int i = 0; i < pos - 1; ++i) {
        output.append(" ");
    }
    output.append("^\n").append(message);
}

void MainWindow::convertPower(string &expr) {
    unsigned long powerPos = expr.find("power(");
    while (powerPos != string::npos) {
        expr.replace(powerPos, 6, "(^ ");
        powerPos = expr.find("power(");
    }
    powerPos = expr.find(',');
    while (powerPos != string::npos) {
        expr[powerPos] = ' ';
        powerPos = expr.find(',');
    }
}
