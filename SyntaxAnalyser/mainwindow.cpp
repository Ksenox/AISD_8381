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


// Function of clicking on check button
void MainWindow::on_Check_syntax_button_clicked()
{
    string input = ui->Input_text_field->text().toStdString();

    char* input_text = new char[input.size() + 1];

    input_text[input.size()] = '\0';

    for(unsigned int i = 0; i < input.size(); i++)
    {
        input_text[i] = input[i];
    }


   Text_with_brackets_syntax_checker *text_with_brackets_syntax_checker = new Text_with_brackets_syntax_checker();

   if(input.size() != 0)
   {
       try {
           text_with_brackets_syntax_checker->check_text_with_brackets_syntax(input_text, ui->Input_text_field->text().toStdString().size(), 0);
           if(ui->File_output_flag->isChecked() == false)
           {
                ui->Answer_text_field->setTextColor(Qt::darkGreen);
                ui->Answer_text_field->setText("Correct syntax");
           }
           else
           {
                QFile answer_file("D:\\ProgrammFiles\\QtProjects\\untitled1\\Answer.txt");
                answer_file.open(QIODevice::WriteOnly);
                answer_file.write("Correct syntax");
                answer_file.close();
           }
       } catch (Syntax_mistake & syntax_mistake) {

           if(ui->File_output_flag->isChecked() == false)
           {
               ui->Answer_text_field->clear();
               ui->Answer_text_field->setTextColor(Qt::red);
               syntax_mistake.print_syntax_mistake(QString(input_text), ui->Answer_text_field);
           }
           else
           {
                QFile answer_file("D:\\ProgrammFiles\\QtProjects\\untitled1\\Answer.txt");
                answer_file.open(QIODevice::WriteOnly);
                answer_file.write("Incorrect syntax");
                answer_file.close();
           }
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

    if(input_file.exists() == false) return;

    input_file.open(QIODevice::ReadOnly);

    ui->Input_text_field->setText(input_file.readAll());

    input_file.close();

    ui->Input_text_field->update();
}

