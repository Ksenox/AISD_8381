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

// Block of functions for text typing using buttons
void MainWindow::on_A_button_clicked()
{
    ui->Input_text_field->setText(ui->Input_text_field->toPlainText() + "A");
}

void MainWindow::on_B_button_clicked()
{
    ui->Input_text_field->setText(ui->Input_text_field->toPlainText() + "B");
}

void MainWindow::on_Square_left_button_clicked()
{
    ui->Input_text_field->setText(ui->Input_text_field->toPlainText() + "[");
}

void MainWindow::on_Square_right_button_clicked()
{
    ui->Input_text_field->setText(ui->Input_text_field->toPlainText() + "]");

}

void MainWindow::on_Circle_left_button_clicked()
{
    ui->Input_text_field->setText(ui->Input_text_field->toPlainText() + "(");

}

void MainWindow::on_Circle_right_button_clicked()
{
    ui->Input_text_field->setText(ui->Input_text_field->toPlainText() + ")");

}

void MainWindow::on_Waving_left_button_clicked()
{
    ui->Input_text_field->setText(ui->Input_text_field->toPlainText() + "{");

}

void MainWindow::on_Waving_right_button_clicked()
{
    ui->Input_text_field->setText(ui->Input_text_field->toPlainText() + "}");

}
// endof block of letters buttons


// Function of clicking on check button
void MainWindow::on_Check_syntax_button_clicked()
{
   const char *input_text = ui->Input_text_field->toPlainText().toStdString().c_str();

   QString outtext(input_text);

   Text_with_brackets_syntax_checker *text_with_brackets_syntax_checker = new Text_with_brackets_syntax_checker();

   if(outtext.size() != 0)
   {
       try {
           text_with_brackets_syntax_checker->check_text_with_brackets_syntax(input_text, ui->Input_text_field->toPlainText().toStdString().size(), 0, 0);
           ui->Answer_text_field->setTextColor(Qt::darkGreen);
           ui->Answer_text_field->setText("Correct syntax");
       } catch (Syntax_mistake & syntax_mistake) {
           ui->Answer_text_field->clear();
           ui->Answer_text_field->setTextColor(Qt::red);
           syntax_mistake.print_syntax_mistake(outtext, ui->Answer_text_field);
       }
   }
   else {
       ui->Answer_text_field->setText("No input text found");
   }
}

void MainWindow::on_Load_from_file_button_clicked()
{
    QString input_file_directory = QFileDialog::getOpenFileName(nullptr, "Open Dialog", "", "*.txt");

    QFile input_file(input_file_directory);

    input_file.open(QIODevice::ReadOnly);

    ui->Input_text_field->setText(input_file.readAll());
}

void MainWindow::on_Open_logs_file_button_clicked()
{



}
