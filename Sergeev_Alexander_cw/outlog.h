#ifndef OUTLOG_H
#define OUTLOG_H

#include <QWidget>
#include <QCloseEvent>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QLabel>
#include <fstream>
#include <sstream>


class outlog : public QWidget {
    Q_OBJECT

public:
    outlog(QWidget * parent, std::string* path_to_dir);
    ~outlog() override;

    void notify(std::string* message);

    static int width;

private:
    static std::string log_file;

    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    QWidget* parent;
    QLabel* logs;

};

#endif // OUTLOG_H
