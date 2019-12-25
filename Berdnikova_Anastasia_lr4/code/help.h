#ifndef HELP_H
#define HELP_H

#include <QDialog>

namespace Ui {
class Help;
}

class Help : public QDialog
{
    Q_OBJECT

public:
    bool isOpen = 0;
    explicit Help(QWidget *parent = 0);
    ~Help();

private:
    Ui::Help *ui;
};

#endif // HELP_H
