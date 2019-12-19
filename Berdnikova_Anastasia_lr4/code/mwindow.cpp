#include "mwindow.h"
#include "ui_mwindow.h"

MWindow::MWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWindow)
{
    ui->setupUi(this);
    help = new Help;
}

MWindow::~MWindow()
{
    delete ui;
}

Tree* creat_tree(Tree *head, std::string str)
{
    head = new Tree;
    head->get_val(str[str.length()-1]);
    Tree* node = head;
    int i = str.length()-2;
    while(i>=0){
        node->create_node(str[i]);
        if(str[i]==42 || str[i]==43 || str[i]==45 || str[i]==47){
            if(node->ret_l())
                node = node->ret_l();
            else
                node = node->ret_r();
        }
        if(str[i]>=48 && str[i]<=57){
            while((node->ret_r() && node->ret_l()) && node->ret_parent()!=nullptr){
                node = node->ret_parent();
            }
        }
        i--;
    }
    return head;
}

void MWindow::on_process_clicked()
{
    std::stringstream outp;
//    Tree* head;
    head = creat_tree(head, ui->input->text().toStdString());
    std::string str = head->print_node();
    ui->output->setText(QString::fromStdString(str));
}

void MWindow::on_show_t_clicked()
{
    Dialog* dialog = new Dialog;
    int maxdeep = head->deepmax();
    head->displaytree(dialog, 1, maxdeep, 0, 0, 0, 0);

    dialog->exec();
}

void MWindow::on_actionHelp_triggered()
{
    if(!help->isOpen){
        help->show();
    }
}
