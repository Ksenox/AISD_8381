#include "outlog.h"


int outlog::width = 500;

std::string outlog::log_file = "";


outlog::outlog(QWidget* parent, std::string* path_to_dir) : QWidget() {
    this->parent = parent;

    QScrollArea *scroll = new QScrollArea(this);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    logs = new QLabel(this);
    logs->setContentsMargins(7, 7, 7, 7);
    logs->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    scroll->setWidget(logs);
    scroll->setWidgetResizable(true);

    QHBoxLayout *dialog_layout = new QHBoxLayout(this);
    dialog_layout->addWidget(scroll);

    setLayout(dialog_layout);

    log_file = *path_to_dir + "log.lg";

    std::ofstream fstr(log_file);
    fstr.flush();
    fstr.close();
}

outlog::~outlog() {}


void outlog::notify(std::string* message) {
    std::ofstream outfile(log_file, std::ios_base::app);
    outfile << *message;
    outfile << '\n';
    outfile.flush();
    outfile.close();

    if (this->isVisible()) {
        QString text = logs->text();
        text.append(QString::fromStdString(*message));
        text.append("\n");
        logs->setText(text);
    }
}

void outlog::showEvent(QShowEvent *event) {
    std::stringstream buffer;

    std::ifstream infile(log_file);
    buffer << infile.rdbuf();
    infile.close();

    QString text = logs->text();
    text.append(QString::fromStdString(buffer.str()));
    logs->setText(text);

    setGeometry(parent->geometry().right(), parent->geometry().top(), width, parent->geometry().height());
    this->setWindowTitle("Logs");
    event->accept();
}

void outlog::closeEvent (QCloseEvent *event) {
    QString text;
    logs->setText(text);
    event->accept();
}
