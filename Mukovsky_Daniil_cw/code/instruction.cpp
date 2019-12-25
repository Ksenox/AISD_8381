#include "instruction.h"
#include "ui_instruction.h"

Instruction::Instruction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Instruction)
{
    ui->setupUi(this);
    this->setWindowTitle("Instruction");
    setAttribute(Qt::WA_DeleteOnClose);
}

Instruction::~Instruction()
{
    delete ui;
}
