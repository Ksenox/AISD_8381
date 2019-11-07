#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    abt = new (about);
    hlp = new (help);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
  Masha  Grisha Sasha
  Sasha  Vanya
  Dasha  Masha
  Kostya Ilya
  Vanya  Mitya
  ..............................
  Pasha Misha
  Misha Vanya Sasha
  Kostya Petya
  Petya Masha
 * */


void MainWindow::on_resultButtom_clicked()
{
    try {
            fml = new Family();
            QStringList list1 = ui->Input->toPlainText().split('\n');
            fml->COUNT=list1.length();
            if(can) {
                for (int i=0;i<fml->COUNT;i++) {
                    if(list1[i].length()>0)
                        fml->input(list1[i]);
                }
            }
            QString out= "";
            for (auto i=0;i<fml->all_names.size();i++){
                for (auto j=i;j<fml->all_names.size();j++){
                    QString X = fml->all_names[i];
                    QString Y = fml->all_names[j];
                    if (fml->is_relative(X,Y)) {
                        out += (X+" & "+Y+"\n");
                    }
                    ui->Output->setText(out);
                }
            }
    }
    catch (errors  e) {
        switch (e) {
            case WRONG_STRING:
            QMessageBox::critical(this, "Error", "Wrong string");
        }
    }


}


void MainWindow::on_Input_textChanged()
{
    can = true;
}





void MainWindow::on_actionOpen_file_triggered()
{
    QString fileName = QFileDialog().getOpenFileName();

    if (!fileName.isNull()){

        QFile file(fileName);

        if (file.open(file.ReadOnly)){
            QString data = file.readAll();
            ui->Input->setText(data);
        }
        else {
            QMessageBox::warning(this, "Error", "Error to open file");
        }
    }
}

void MainWindow::on_actionHelp_triggered()
{
    hlp->show();
}

void MainWindow::on_actionAbout_triggered()
{
    abt->show();
}

void MainWindow::on_actionExit_triggered()
{
    MainWindow::close();
}
