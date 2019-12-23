#ifndef INFOABOUTALGORITHM_H
#define INFOABOUTALGORITHM_H

#include <QWidget>

namespace Ui {
class InfoAboutAlgorithm;
}

class InfoAboutAlgorithm : public QWidget
{
    Q_OBJECT

public:
    explicit InfoAboutAlgorithm(QWidget *parent = nullptr);
    ~InfoAboutAlgorithm();

private:
    Ui::InfoAboutAlgorithm *ui;
};

#endif // INFOABOUTALGORITHM_H
