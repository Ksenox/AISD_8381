#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QStringList available_types = {"int", "char", "double", "string"};

    ui->type_selector->addItems(available_types);

    connect(ui->generator_button, SIGNAL(clicked()), this, SLOT(generate()));
    connect(ui->line_button, SIGNAL(clicked()), this, SLOT(read_from_line()));
    connect(ui->file_button, SIGNAL(clicked()), this, SLOT(read_from_file()));

    connect(ui->step_button, SIGNAL(clicked()), this, SLOT(step()));
    connect(ui->back_button, SIGNAL(clicked()), this, SLOT(back()));

    connect(ui->save_button, SIGNAL(clicked()), this, SLOT(save()));
    connect(ui->load_button, SIGNAL(clicked()), this, SLOT(load()));
    connect(ui->reset_button, SIGNAL(clicked()), this, SLOT(clear()));

    connect(ui->log_button, SIGNAL(clicked()), this, SLOT(log()));
    connect(ui->about_treap_button, SIGNAL(clicked()), this, SLOT(about_treap()));
    connect(ui->about_app_button, SIGNAL(clicked()), this, SLOT(about_app()));

    connect(ui->merge_button, SIGNAL(clicked()), this, SLOT(merge()));
    connect(ui->split_button, SIGNAL(clicked()), this, SLOT(split()));
    connect(ui->multiple_button, SIGNAL(clicked()), this, SLOT(mult()));

     std::string log_path(core::PATH);
    core::log = new outlog(this, &log_path);

    core::log->notify(new std::string("Application started..."));

    ui->canvas1->setHidden(true);
    ui->split_pos_box->setMinimum(0);
    generator::ground();
}

MainWindow::~MainWindow() {
    core::log->notify(new std::string("Application terminated..."));
    core::log->notify(new std::string("Have a good day, Mr. User!"));
    delete ui;
}


void MainWindow::configure_input(int new_step_action) {
    switch (new_step_action) {
        case 0:
            ui->merge_button->setEnabled(false);
            ui->split_button->setEnabled(false);
            ui->split_pos_box->setEnabled(false);
            ui->multiple_button->setEnabled(true);

            ui->generator_button->setEnabled(true);
            ui->line_button->setEnabled(true);
            ui->file_button->setEnabled(true);
            ui->type_selector->setEnabled(true);
            ui->line_input->setEnabled(true);
            ui->step_box->setEnabled(true);

            ui->step_button->setEnabled(false);

            core::log->notify(new std::string("Input configured: Initial."));
            break;
        case 1:
            ui->merge_button->setEnabled(true);
            ui->split_button->setEnabled(true);
            ui->split_pos_box->setEnabled(true);
            ui->split_pos_box->setMaximum(core::split_maximum);
            ui->multiple_button->setEnabled(true);

            ui->generator_button->setEnabled(true);
            ui->line_button->setEnabled(true);
            ui->file_button->setEnabled(true);
            ui->type_selector->setEnabled(true);
            ui->line_input->setEnabled(true);
            ui->step_box->setEnabled(true);

            ui->step_button->setEnabled(false);

            core::log->notify(new std::string("Input configured: Ready to act."));
            break;
        case 10:
        case 11:
        case 12:
        case 20:
        case 21:
        case 30:
        case 31:
            ui->merge_button->setEnabled(false);
            ui->split_button->setEnabled(false);
            ui->split_pos_box->setEnabled(false);
            ui->multiple_button->setEnabled(false);

            ui->generator_button->setEnabled(false);
            ui->line_button->setEnabled(false);
            ui->file_button->setEnabled(false);
            ui->type_selector->setEnabled(false);
            ui->line_input->setEnabled(false);
            ui->step_box->setEnabled(false);
            ui->step_box->setChecked(true);

            ui->step_button->setEnabled(true);

            core::log->notify(new std::string("Input configured: Steps in progress."));
            break;
    }

    core::step_action = new_step_action;
}


void MainWindow::generate() {
    std::string* gen = generator::generate();
    core::log->notify(new std::string("New input line generated: " + *gen));
    ui->line_input->setText(QString::fromStdString(*gen));
}

void MainWindow::read_from_file() {
    core::log->notify(new std::string("Reading from file requested."));
    read(true);
}

void MainWindow::read_from_line() {
    core::log->notify(new std::string("Reading from line requested."));
    read(false);
}

void MainWindow::read(bool from_file) {
    configure_input(0);
    ui->canvas1->setHidden(true);
    ui->canvas1->prepare_drawing();
    ui->canvas2->prepare_drawing();

    std::string input = ui->line_input->text().toStdString();
    int result = core::launch(ui->canvas2, &input, from_file, ui->type_selector->currentIndex());

    std::string* msg;
    if (result == 0) {
        msg = new std::string("Data sources successfully loaded!");
        core::log->notify(msg);

        ui->canvas1->setHidden(false);
        ui->canvas1->prepare_drawing();
        ui->canvas2->prepare_drawing();

        if (!ui->step_box->isChecked()) {
            msg = new std::string("Quick treap building requested.");
            core::log->notify(msg);

            int res = 0;

            switch (core::type) {
                case 0:
                    res = core::build_rush<int>(ui->canvas1, ui->canvas2, 1, false);
                    break;
                case 1:
                    res = core::build_rush<char>(ui->canvas1, ui->canvas2, 1, false);
                    break;
                case 2:
                    res = core::build_rush<double>(ui->canvas1, ui->canvas2, 1, false);
                    break;
                case 3:
                    res = core::build_rush<std::string>(ui->canvas1, ui->canvas2, 1, false);
                    break;
            }

            if (res == 0) {
                msg = new std::string("Both treaps successfully built.");
                core::log->notify(msg);
                ui->answer->setText(QString::fromStdString(*msg));
                configure_input(1);
                clear();
            } else {
                msg = new std::string("Error occurs during building, check input format again!");
                core::log->notify(msg);
                ui->answer->setText(QString::fromStdString(*msg));
            }
        } else {
            msg = new std::string("Step-by-step treap building requested.");
            core::log->notify(msg);
            configure_input(10);
            step();
        }

    } else {
        msg = new std::string("Error occurs during data source loading. Check the input again!");
        core::log->notify(msg);
        ui->answer->setText(QString::fromStdString(*msg));
    }
}

void MainWindow::back() {
    core::log->notify(new std::string("Step back requested."));

    int result = core::pop(ui->canvas1, ui->canvas2, ui->back_button, nullptr);

    if (result == 0) {
        core::log->notify(new std::string("Step back performed successfully."));
    } else {
        core::log->notify(new std::string("Step back failed!"));
    }

    configure_input(core::step_action);
}

void MainWindow::step() {
    core::log->notify(new std::string("Step forward requested."));

    if (core::step_action % 10 != 0) core::push(ui->back_button, nullptr);

    int result = 0;
    switch (core::type) {
        case 0:
            if (core::step_action < 20) result = core::build_step<int>(ui->canvas1, ui->canvas2);
            else if ((core::step_action >= 20) && (core::step_action < 30)) result = core::merge_step<int>(ui->canvas1, ui->canvas2);
            else result = core::split_step<int>(ui->split_pos_box->value(), ui->canvas1, ui->canvas2);
            break;
        case 1:
            if (core::step_action < 20) result = core::build_step<char>(ui->canvas1, ui->canvas2);
            else if ((core::step_action >= 20) && (core::step_action < 30)) result = core::merge_step<char>(ui->canvas1, ui->canvas2);
            else result = core::split_step<char>(ui->split_pos_box->value(), ui->canvas1, ui->canvas2);
            break;
        case 2:
            if (core::step_action < 20) result = core::build_step<double>(ui->canvas1, ui->canvas2);
            else if ((core::step_action >= 20) && (core::step_action < 30)) result = core::merge_step<double>(ui->canvas1, ui->canvas2);
            else result = core::split_step<double>(ui->split_pos_box->value(), ui->canvas1, ui->canvas2);
            break;
        case 3:
            if (core::step_action < 20) result = core::build_step<std::string>(ui->canvas1, ui->canvas2);
            else if ((core::step_action >= 20) && (core::step_action < 30)) result = core::merge_step<std::string>(ui->canvas1, ui->canvas2);
            else result = core::split_step<std::string>(ui->split_pos_box->value(), ui->canvas1, ui->canvas2);
            break;
    }

    std::string* msg = nullptr;
    if (result == 0) {
        msg = new std::string("Steps forward finished successfully.");
    } else if (result == 1) {
        msg = new std::string("Step forward failed!");
        configure_input(1);
    } else {
        msg = new std::string("Step forward performed.");
    }
    core::log->notify(msg);
    ui->answer->setText(QString::fromStdString(*msg));

    configure_input(core::step_action);
}


void MainWindow::save() {
    core::log->notify(new std::string("Save state requested."));

    QString file = QFileDialog::getSaveFileName(this, tr("Open Directory"), QString::fromStdString(core::PATH + "saving.sv"), tr("State save files (*.sv)"));
    std::string fstring(file.toStdString());

    if (fstring != "") {
        try {
            int result = core::push(ui->load_button, &fstring);
            if (result == 0) core::log->notify(new std::string("Save state performed."));
            else core::log->notify(new std::string("Save state ended with error!"));
        } catch (std::runtime_error re) {
            core::log->notify(new std::string("Save state can not be performed: " + std::string(re.what())));
        }
    } else core::log->notify(new std::string("Save state cancelled."));
}

void MainWindow::load() {
    ui->canvas1->setHidden(false);
    ui->canvas1->prepare_drawing();
    ui->canvas2->prepare_drawing();

    core::log->notify(new std::string("Load state requested."));

    QString file = QFileDialog::getOpenFileName(this, tr("Open Directory"), QString::fromStdString(core::PATH), tr("State save files (*.sv)"));
    std::string fstring(file.toStdString());

    if (fstring != "") {
        int result = core::pop(ui->canvas1, ui->canvas2, ui->load_button, &fstring);
        if (result == 0) {
            configure_input(core::step_action);
            ui->answer->setText(QString::fromStdString("Loded state from file " + fstring));
        }
        else core::log->notify(new std::string("Load state ended with error!"));
    } else core::log->notify(new std::string("Load state cancelled."));
}

void MainWindow::clear() {
    core::log->notify(new std::string("Clear history requested."));

    core::clear_stack(ui->back_button);
}


void MainWindow::log() {
    core::log->notify(new std::string("Log window requested."));

    core::log->show();
}

void MainWindow::about_treap() {
    core::log->notify(new std::string("It was decided to learn something new about treaps."));

    QMessageBox* msgbox = new QMessageBox(this);
    msgbox->setWindowTitle("About: treaps");
    msgbox->setText(QString::fromStdString("Treap is a combination of \"binary search tree\" and \"binary heap\". It contains values in binary tree order and keys in binary heap order.\n") +
                    QString::fromStdString("In this particular app a list based on treap is shown. A search operation can be performed for O(log2N) iterations on this kind of list."));
    msgbox->open();
}

void MainWindow::about_app() {
    core::log->notify(new std::string("It was decided to read user manual."));

    QMessageBox* msgbox = new QMessageBox(this);
    msgbox->setWindowTitle("About: treaps");
    msgbox->setText(QString::fromStdString("This program shows how list based on treap works. A few words about its functionality:\n") +
                    QString::fromStdString("1. Input: Input string (in line or in file) must be formatted. Elements should be separated by \", \", trees (up to two) with \" = \". ") +
                    QString::fromStdString("There can be one or two trees, but the first should be present in any case.\n") +
                    QString::fromStdString("2. Steps: Every tree function in the programm may be performed by steps. All of them (except build) differ from their fast analogues ") +
                    QString::fromStdString("due to their recursive nature. Do not be misled, this was made for demonstrative purposes only!\n") +
                    QString::fromStdString("3. Build: Nothing interesting about this function - it builds a treap from given array values.\n") +
                    QString::fromStdString("4. Generate input: Generates from 8 up to 13 integers, divided in two treaps or not. Use for quick and simple input source.\n") +
                    QString::fromStdString("5. Merge: Merges second tree into first one.\n") +
                    QString::fromStdString("6. Split: Splits first tree into two from the given position. Given number means number of elements left in the first tree.\n") +
                    QString::fromStdString("7. Step/Back: While step is only available during \"step mode\", back also keeps all operations performed with tree. Be careful, mode is also kept!\n") +
                    QString::fromStdString("8. Save/Load: You can save or load a programm state to/from separate file. Operations stack is NOT included!\n") +
                    QString::fromStdString("9. Multiple times: This function goal is to demonstrate the depth of the treap for some big (comparably) numbers. ") +
                    QString::fromStdString("WARNING: this can cause performance freezes. It runs NOT in separate thread. 2000 - is big enough for demonstration. I warned you!"));
    msgbox->open();
}


void MainWindow::merge() {
    std::string* msg = new std::string("Treap merge requested.");
    core::log->notify(msg);

    try {
        core::push(ui->back_button, nullptr);
    } catch (std::runtime_error re) {
        core::log->notify(new std::string("Can not push state - trees not initialized."));
    }

    if (!ui->step_box->isChecked()) {
        msg = new std::string("Quick treap merge requested.");
        core::log->notify(msg);

        int res = 0;

        switch (core::type) {
            case 0:
                res = core::merge_rush<int>(ui->canvas1, ui->canvas2);
                break;
            case 1:
                res = core::merge_rush<char>(ui->canvas1, ui->canvas2);
                break;
            case 2:
                res = core::merge_rush<double>(ui->canvas1, ui->canvas2);
                break;
            case 3:
                res = core::merge_rush<std::string>(ui->canvas1, ui->canvas2);
                break;
        }

        if (res == 0) {
            msg = new std::string("Treaps successfully merged.");
            core::log->notify(msg);
            ui->answer->setText(QString::fromStdString(*msg));
            configure_input(1);
        } else {
            msg = new std::string("Error occurs during merging!");
            core::log->notify(msg);
            ui->answer->setText(QString::fromStdString(*msg));
        }
    } else {
        msg = new std::string("Step-by-step treap merging requested.");
        core::log->notify(msg);
        configure_input(20);
        step();
    }
}

void MainWindow::split() {
    std::string* msg = new std::string("Treap split requested.");
    core::log->notify(msg);

    try {
        core::push(ui->back_button, nullptr);
    } catch (std::runtime_error re) {
        core::log->notify(new std::string("Can not push state - trees not initialized."));
    }

    if (!ui->step_box->isChecked()) {
        msg = new std::string("Quick treap split requested.");
        core::log->notify(msg);

        int res = 0;

        switch (core::type) {
            case 0:
                res = core::split_rush<int>(ui->split_pos_box->value(), ui->canvas1, ui->canvas2);
                break;
            case 1:
                res = core::split_rush<char>(ui->split_pos_box->value(), ui->canvas1, ui->canvas2);
                break;
            case 2:
                res = core::split_rush<double>(ui->split_pos_box->value(), ui->canvas1, ui->canvas2);
                break;
            case 3:
                res = core::split_rush<std::string>(ui->split_pos_box->value(), ui->canvas1, ui->canvas2);
                break;
        }

        if (res == 0) {
            msg = new std::string("Treaps successfully splitted.");
            core::log->notify(msg);
            ui->answer->setText(QString::fromStdString(*msg));
            configure_input(1);
        } else {
            msg = new std::string("Error occurs during splitting!");
            core::log->notify(msg);
            ui->answer->setText(QString::fromStdString(*msg));
        }
    } else {
        msg = new std::string("Step-by-step treap splitting requested.");
        core::log->notify(msg);
        configure_input(30);
        step();
    }
}

void MainWindow::mult() {
    std::string* msg = new std::string("Multiple treap building research requested.");
    core::log->notify(msg);

    configure_input(0);
    ui->canvas1->setHidden(true);
    ui->canvas1->prepare_drawing();
    ui->canvas2->prepare_drawing();

    std::string input = ui->line_input->text().toStdString();
    int result = core::launch(ui->canvas2, &input, false, ui->type_selector->currentIndex());

    if (result == 0) {
        msg = new std::string("Data sources successfully loaded!");
        core::log->notify(msg);

        log();

        switch (core::type) {
            case 0:
                result = core::mult<int>(ui->canvas2);
                break;
            case 1:
                result = core::mult<char>(ui->canvas2);
                break;
            case 2:
                result = core::mult<double>(ui->canvas2);
                break;
            case 3:
                result = core::mult<std::string>(ui->canvas2);
                break;
        }

        if (result == 0) {
            msg = new std::string("Research successful.");
            core::log->notify(msg);
            ui->answer->setText(QString::fromStdString(*msg));
        } else {
            msg = new std::string("Error occuresduring research!");
            core::log->notify(msg);
            ui->answer->setText(QString::fromStdString(*msg));
        }

        clear();
    } else {
        msg = new std::string("Error occures, input again (in \"research\" mode you can only input from line)!");
        core::log->notify(msg);
        ui->answer->setText(QString::fromStdString(*msg));
    }
}
