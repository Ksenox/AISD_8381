#include "mainwindow.h"
#include "headers.h"

void MainWindow::setUpUI() {
    QWidget *canvas = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    canvas->setLayout(layout);

    layout->setStretch(1, 2);
    layout->setAlignment(Qt::AlignCenter);

    setCentralWidget(canvas);

    fileOpen->setText("file");
    drawingTreap->setText("Draw treap");
    stepDrawingTreap->setText("Step of drawing");
    splitTreap->setText("Split");
    stepSwitch->setText("Step mode");
    inputExprLabel->setText("Input:");
    splitElLabel->setText("Split by: ");
    inputLine->setValidator(new QRegExpValidator(QRegExp("[0-9()\\s]*"), inputLine));
    splitKeyInput->setValidator(new QRegExpValidator(QRegExp("[0-9()]*"), splitTreap));
    mainGraphicsView->setMinimumSize(500, 500);


    QHBoxLayout *exprWorkLayout = new QHBoxLayout();
    QVBoxLayout *allButLayout = new QVBoxLayout();
    QVBoxLayout *mainWorkingLayout = new QVBoxLayout();
    QVBoxLayout *splitLayout = new QVBoxLayout();
    QHBoxLayout *splitMainLayout = new QHBoxLayout();
    splitMainLayout->addWidget(splitElLabel);
    splitMainLayout->addWidget(splitKeyInput);
    splitMainLayout->addWidget(splitTreap);
    splitLayout->addLayout(splitMainLayout);
    splitLayout->addWidget(slpitError);
    QHBoxLayout *inputTreapLayout = new QHBoxLayout();
    inputTreapLayout->addWidget(inputExprLabel);
    inputTreapLayout->addWidget(inputLine);
    inputTreapLayout->addWidget(fileOpen);
    QHBoxLayout *drawingLayout = new QHBoxLayout();
    drawingLayout->addWidget(drawingTreap);
    drawingLayout->addWidget(stepSwitch);
    drawingLayout->addWidget(stepDrawingTreap);

    allButLayout->addLayout(inputTreapLayout);
    allButLayout->addLayout(splitLayout);
    allButLayout->addLayout(drawingLayout);

    exprWorkLayout->addLayout(allButLayout);
    exprWorkLayout->addWidget(mainGraphicsView);

    mainWorkingLayout->addLayout(exprWorkLayout);

    layout->addLayout(mainWorkingLayout);

    // default conditions
    stepSwitch->setChecked(false);
    stepDrawingTreap->setDisabled(true);

    connect(drawingTreap, SIGNAL(clicked()), this, SLOT(onTreapDrawingButtonClicked()));
    connect(fileOpen, SIGNAL(clicked()), this, SLOT(onFileOpenButtonClicked()));
    connect(stepDrawingTreap, SIGNAL(clicked()), this, SLOT(onStepTreapDrawingButtonClicked()));
    connect(splitTreap, SIGNAL(clicked()), this, SLOT(onTreapSplitingButtonClicked()));

}
