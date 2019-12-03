#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "allheaders.h"
#include "test.h"

void MainWindow::setUpUI() {
    qDebug() << "UI set up started" << endl;

    // creates actual widget instances
    // from QtDesigner
    ui->setupUi(this);

    // working zone - main widget
    QWidget *canvas = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    // set main vertical layout
    canvas->setLayout(layout);

    // sets the stretch factor at position index
    // and aligning of main widget
    layout->setStretch(1, 2);
    layout->setAlignment(Qt::AlignCenter);

    // set main widget of window
    canvas->setStyleSheet("QWidget { background: white; }");
    setCentralWidget(canvas);

    //  set up full buttons layout
    runButton->setText("Run");
    fileOpen->setText("Open file");
    findEl->setText("Find");
    findElInput->setLabel("Element to find");
    fileWay->setStyleSheet("QLabel {color : black; }");
    mainTextOutput->setStyleSheet("QWidget {color : black; }");
    findElInput->setStyleSheet("QWidget {color : black; }");
    fileWay->setAlignment(Qt::AlignCenter);
    QHBoxLayout *allButtonsLayout = new QHBoxLayout();
    QGridLayout *workingBut = new QGridLayout();
    workingBut->addWidget(runButton, 0, 0, Qt::AlignLeft);
    workingBut->addWidget(fileOpen, 0, 1, Qt::AlignRight);
    workingBut->addWidget(fileWay, 1, 0, 1, 1, Qt::AlignCenter);
    QHBoxLayout *findElLayout = new QHBoxLayout();
    findElLayout->addWidget(findEl);
    findElLayout->addWidget(findElInput);
    allButtonsLayout->addLayout(workingBut);
    allButtonsLayout->addLayout(findElLayout);

    // main layout setup
    layout->addLayout(allButtonsLayout);
    layout->addWidget(mainTextOutput);
    mainTextOutput->setReadOnly(true);

    // default conditions
    findElInput->setDisabled(true);
    findEl->setDisabled(true);

    /* SIGNALS AND SLOTS CONNECTIONS */
    connect(runButton, SIGNAL(clicked()), this, SLOT(onRunButtonClicked()));
    connect(fileOpen, SIGNAL(clicked()), this, SLOT(onFileOpenButtonClicked()));
    connect(findEl, SIGNAL(clicked()), this, SLOT(onFindElButtonClicked()));
}
