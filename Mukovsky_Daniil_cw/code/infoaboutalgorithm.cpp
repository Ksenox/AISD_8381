#include "infoaboutalgorithm.h"
#include "ui_infoaboutalgorithm.h"

InfoAboutAlgorithm::InfoAboutAlgorithm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoAboutAlgorithm)
{
    ui->setupUi(this);
    this->setWindowTitle("Info about algorithm");
    setAttribute(Qt::WA_DeleteOnClose);
}

InfoAboutAlgorithm::~InfoAboutAlgorithm()
{
    delete ui;
}
