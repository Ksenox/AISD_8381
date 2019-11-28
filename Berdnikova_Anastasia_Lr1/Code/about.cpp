#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
//    QPixmap myPixmap("qrc:/img/img/cover.jpg");
//    ui->YA->setPixmap( myPixmap );
}

about::~about()
{
    delete ui;
}


