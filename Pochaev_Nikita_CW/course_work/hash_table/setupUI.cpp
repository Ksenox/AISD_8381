#include "mainwindow.h"
#include "allheaders.h"
#include "TableHandler.h"
#include "drawingwindow.h"

void MainWindow::setUpUI() {
    qDebug() << "main window UI set up" << endl;

    setWindowTitle(tr("Course work"));

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

    //  set up buttons
    runButton->setText("Run");
    runButton->setToolTip("Start hash table visualization");
    fileOpenButton->setText("Open file");
    fileOpenButton->setToolTip("File with strings (names) for hash table");
    fileOpenButton->setIcon(QtMaterialTheme::icon("file", "folder_open"));
    fileOpenButton->setIconSize(QSize(35, 35));
    fileWayLabel->setStyleSheet("QLabel {color : black; }");
    fileWayLabel->setText("Please, open the file");
    stepByStepMode->setText("Step by step building");
    stepByStepMode->setToolTip("New element insert - one step");
    allInMomentMode->setText("Automate building");
    allInMomentMode->setToolTip("Full table will be built in a moment");

    QVBoxLayout *modeChooseLayout = new QVBoxLayout;
    modeChooseLayout->addWidget(stepByStepMode);
    modeChooseLayout->addWidget(allInMomentMode);

    QVBoxLayout *fileRunLayout = new QVBoxLayout;
    fileRunLayout->addWidget(fileOpenButton);
    fileRunLayout->addWidget(fileWayLabel);
    fileRunLayout->addWidget(runButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(fileRunLayout, 0, 0, 3, 1, Qt::AlignLeft);
    mainLayout->addLayout(modeChooseLayout, 0, 2, 2, 3, Qt::AlignRight);

    layout->addLayout(mainLayout);

    // set up minimum window size
    int height = mainLayout->geometry().height();
    if (height != minimumHeight() || height != maximumHeight()) {
        setMinimumHeight(height);
        setMaximumHeight(height);
    }
    int width = mainLayout->geometry().width();
    if (width != minimumWidth() || height != maximumWidth()) {
        setMinimumWidth(width);
        setMaximumWidth(width);
    }

    // default conditions
    runButton->setDisabled(true);

    /* SIGNALS AND SLOTS CONNECTIONS */
    connect(runButton, &QtMaterialFlatButton::clicked, this, &MainWindow::onRunButtonClicked);
    connect(fileOpenButton, &QtMaterialFlatButton::clicked, this, &MainWindow::onFileOpenButtonClicked);
}

void DrawingWindow::setUpUI() {
    qDebug() << "drawing window UI set up" << endl;

    setWindowTitle(tr("Hash Table Visualization"));

    mainGraphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    mainGraphicsView->setScene(mainGraphicsScene);
    mainGraphicsView->setRenderHints(QPainter::Antialiasing);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    this->resize(static_cast<int>(width), static_cast<int>(height));

    QVBoxLayout *layout = new QVBoxLayout;

    // set main vertical layout
    setLayout(layout);

    // sets the stretch factor at position index
    // and aligning of main widget
    layout->setStretch(1, 2);
    layout->setAlignment(Qt::AlignCenter);

    setStyleSheet("QWidget { background: white; }");

    // init and set up buttons
    nextStepButton->setIcon(QtMaterialTheme::icon("navigation", "arrow_forward"));
    nextStepButton->setToolTip("Next step");
    nextStepButton->setIconSize(QSize(35, 35));
    prevStepButton->setIcon(QtMaterialTheme::icon("navigation", "arrow_back"));
    prevStepButton->setToolTip("Step back");
    prevStepButton->setIconSize(QSize(35, 35));
    addElButton->setIcon(QtMaterialTheme::icon("content", "add"));
    addElButton->setToolTip("Add new string in hash table");
    addElButton->setIconSize(QSize(35, 35));
    delElButton->setIcon(QtMaterialTheme::icon("content", "delete_sweep"));
    delElButton->setIconSize(QSize(35, 35));
    delElButton->setToolTip("Delete string from hash table");
    showAllButton->setText("Show all");
    showAllButton->setToolTip("Stop step by step mode and show everything");
    inputEl->setLabel("Enter the string for adding / deleting");
    inputEl->setTextColor(QColor::fromRgb(0, 0, 0));
    inputEl->setMinimumWidth(200);
    inputEl->setMaximumWidth(300);
    mainTextOutput->setReadOnly(true);
    mainTextOutput->setAlignment(Qt::AlignCenter);
    mainTextOutput->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainTextOutput->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainTextOutput->setTextColor(QColor::fromRgb(0, 0, 0));

    QHBoxLayout *stepsLayout = new QHBoxLayout;
    stepsLayout->addWidget(prevStepButton);
    stepsLayout->addWidget(nextStepButton);
    stepsLayout->addWidget(showAllButton);

    QHBoxLayout *elManipLayout = new QHBoxLayout;
    elManipLayout->addWidget(inputEl);
    elManipLayout->addWidget(addElButton);
    elManipLayout->addWidget(delElButton);

    QHBoxLayout *allButtonLayout = new QHBoxLayout;
    QSpacerItem *centralSpacer = new QSpacerItem(1500, 50, QSizePolicy::Maximum, QSizePolicy::Minimum);
    allButtonLayout->addLayout(stepsLayout);
    allButtonLayout->addSpacerItem(centralSpacer);
    allButtonLayout->addLayout(elManipLayout);

    QHBoxLayout *textOutLayout = new QHBoxLayout;
    QSpacerItem *leftTextSpacer = new QSpacerItem(200, 50, QSizePolicy::Preferred, QSizePolicy::Minimum);
    QSpacerItem *rightTextSpacer = new QSpacerItem(200, 50, QSizePolicy::Preferred, QSizePolicy::Minimum);
    textOutLayout->addSpacerItem(leftTextSpacer);
    textOutLayout->addWidget(mainTextOutput);
    textOutLayout->addSpacerItem(rightTextSpacer);

    mainTextOutput->setMaximumHeight(50);
    mainTextOutput->setMaximumWidth(200);
    mainGraphicsView->setMinimumHeight(200);

    layout->addLayout(allButtonLayout);
    layout->addWidget(mainGraphicsView);
    layout->addLayout(textOutLayout);
}
