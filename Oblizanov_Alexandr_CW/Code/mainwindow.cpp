#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inout.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->outputText->setReadOnly(true);
    ui->OutSetPlot->setChecked(true);
    ui->MTestSum->setChecked(true);
    ui->MTestPairs->setChecked(true);
    setupPlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupPlot()
{
    ui->outputPlot->addGraph();
    ui->outputPlot->addGraph();
    ui->outputPlot->addGraph();
    ui->outputPlot->graph(0)->setName("hFunc1");
    ui->outputPlot->graph(1)->setName("hFunc2");
    ui->outputPlot->graph(2)->setName("hFunc3");
    ui->outputPlot->graph(0)->setPen(QPen(QBrush(QColor((Qt::red))), 3));
    ui->outputPlot->graph(1)->setPen(QPen(QBrush(QColor((Qt::green))), 3));
    ui->outputPlot->graph(2)->setPen(QPen(QBrush(QColor((Qt::blue))), 3));
    ui->outputPlot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag | QCP::iSelectLegend);
    ui->outputPlot->axisRect()->setRangeZoom(Qt::Vertical);
    ui->outputPlot->axisRect()->setRangeDrag(Qt::Vertical);
    ui->outputPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
    ui->outputPlot->legend->setVisible(true);
    QSharedPointer<QCPAxisTicker> ticker(new QCPAxisTicker);
    ticker->setTickCount(20);
    ui->outputPlot->xAxis->setTicker(ticker);
    ui->outputPlot->yAxis->setTicker(ticker);
}

void MainWindow::on_GPushOk_clicked()
{
    int pairs = ui->GInputPairs->toPlainText().toInt();
    int length = ui->GInputLength->toPlainText().toInt();
    QString fileName = ui->GInputFile->toPlainText();
    QMessageBox message;
    int res = ssw.generateFile(pairs, length, fileName, ui->GCheckWorst->isChecked(), ui->spinHFunc->value());
    switch (res)
    {
    case BAD_SIZE:
        message.setText("Error! Pairs number input is not correct.");
        message.exec();
        break;
    case BAD_LENGTH:
        message.setText("Error! Words length input is not correct.");
        message.exec();
        break;
    case BAD_FILE:
        message.setText("Error! File name input is not correct.");
        message.exec();
        break;
    default:
        message.setText("File was created.");
        message.exec();
    }
    ui->HInputFile->setText(ui->GInputFile->toPlainText());
}

void MainWindow::on_HPushOk_clicked()
{
    QString fileName = ui->HInputFile->toPlainText();
    QString output = ui->HInputOut->toPlainText();
    int factor = ui->spinFactor->value();
    QMessageBox errOut;
    hCreateInfo info = ssw.createHashTable(ssw.getFromFile(fileName), ui->spinHFunc->value(), factor, output);
    if (info.error)
    {
        errOut.setText("Error!");
        errOut.exec();
    }
    else
        ui->outputText->setText(ssw.getFromFile(output));
}

void MainWindow::on_MPushOk_clicked()
{
    testInfo info;
    testResult res;
    QMessageBox message;
    string output;
    if (ui->MInputMin->toPlainText().isEmpty() || ui->MInputMax->toPlainText().isEmpty())
    {
        message.setText("Error! Min or max input is not correct");
        message.exec();
        return;
    }
    ui->OutSetPlot->setChecked(true);
    info.min = ui->MInputMin->toPlainText().toInt();
    info.max = ui->MInputMax->toPlainText().toInt();
    info.step = ui->spinStep->value();
    info.fileName = "test.txt";
    info.checkMaxIter = ui->MTestMax->isChecked();
    info.worstCase = ui->GCheckWorst->isChecked();
    if (ui->MTestKey->isChecked())
    {
        info.mode = 1;
        info.maxLength = 0;
        info.size = ui->GInputPairs->toPlainText().toInt();
        info.factor = ui->spinFactor->value();
    }
    else if (ui->MTestPairs->isChecked())
    {
        info.mode = 2;
        info.size = 0;
        info.maxLength = ui->GInputLength->toPlainText().toInt();
        info.factor = ui->spinFactor->value();
    }
    else
    {
        info.mode = 3;
        info.factor = 0;
        info.size = ui->GInputPairs->toPlainText().toInt();
        info.maxLength = ui->GInputLength->toPlainText().toInt();
    }
    int err = pairNumTester(ssw, info, ui->outputPlot, output, res);
    switch (err)
    {
    case BAD_SIZE:
        message.setText("Error! Pairs number input is not correct.");
        message.exec();
        break;
    case BAD_LENGTH:
        message.setText("Error! Words length input is not correct.");
        message.exec();
        break;
    case BAD_FILE:
        message.setText("Error! File name input is not correct.");
        message.exec();
        break;
    case BAD_MAXMIN:
        message.setText("Error! Max should be greater than min.");
        message.exec();
        break;
    default:
        message.setText("Plot was created.");
        message.exec();
    }
    ui->outputText->setText(QString::fromStdString(output));
    ui->outputPlot->replot();
}

void MainWindow::on_OutSetPlot_toggled(bool checked)
{
    if (checked)
        ui->outputText->hide();
    else
        ui->outputText->show();
}

void MainWindow::on_OutSaveFile_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save to TXT file"), QDir::homePath(), tr("*.txt"));
    if (QString::compare(filePath, QString()) != 0)
    {
        QMessageBox message;
        ssw.saveStrToFile(ui->outputText->toPlainText(), filePath);
        message.setText("Saved to file");
        message.exec();
    }
}
