#include "core.h"


outlog* core::log = nullptr;

const std::string core::PATH = "C:/Users/miles/Documents/lab5/fls/";

int core::step_action = 0;

int core::split_maximum = 0;

const std::string core::input_file = PATH + "in.txt";
const std::string core::output_file1 = PATH + "out1.png";
const std::string core::output_file2 = PATH + "out2.png";
const std::string core::stack_file = PATH + "stack.svx";

int core::stack_size = 0;

const std::string core::subitem_delimiter = ";";  // number 2;
const std::string core::item_delimiter = ", ";  // number 2;
const std::string core::range_delimiter = " .. "; // number 4;
const std::string core::tree_delimiter = " = "; // number 3;
const std::string core::end_delimiter = "\n";  // number 1;

std::istream* core::in_stream = nullptr;

int core::type = 0;


int core::launch(MyGLWidget* mglw, std::string* input, bool ff, int tp) {
    mglw->prepare_drawing();

    log->notify(new std::string("Reading source data from " + *input + ", which is file (" + std::to_string(ff) +") of type " + std::to_string(type) + "..."));

    std::string* msg;
    std::string tree_string;
    if (ff) {
        std::ifstream* is = new std::ifstream();
        if (input->empty()) {
            log->notify(new std::string("Opening default file, located at " + input_file));
            is->open(input_file);
        } else {
            log->notify(new std::string("Opening file, located at " + *input));
            is->open(*input);
        }

        if (*is && !is->fail()) {
            in_stream = is;
            log->notify(new std::string("File opened!"));
        } else {
            msg = new std::string("File can not be opened :(");
            log->notify(msg);
            mglw->declare(msg);
            return 1;
        }

    } else {
        if (input->empty()) {
            msg = new std::string("The input was empty.");
            log->notify(msg);
            mglw->declare(msg);
            return 1;
        } else {
            log->notify(new std::string("Opening string from input line."));
            std::stringstream* is = new std::stringstream();
            *is << *input;
            in_stream = is;
        }
    }

    type = tp;

    msg = new std::string("Data source loaded. We are ready 2 build.");
    log->notify(msg);
    mglw->declare(msg);
    return 0;
}


std::string* core::read_tree(std::istream* stream, int* delim_num) {
    log->notify(new std::string("Reading data from input stream."));

    std::string* result = new std::string();
    std::string buffer = std::string(3, ' ');
    *delim_num = 0;

    unsigned long long pos = 0;
    long long read = 0;
    while ((*delim_num == 0) && (*delim_num != 1)) {
        bool quit_flag = false;
        if (!(stream->read(&buffer[0], static_cast<signed>(buffer.length())))) quit_flag = true;
        read = stream->gcount();
        result->append(buffer);

        pos = result->find(item_delimiter);
        if (pos != std::string::npos) {
            *delim_num = 2;
            continue;
        }

        pos = result->find(range_delimiter);
        if (pos != std::string::npos) {
            *delim_num = 4;
            continue;
        }

        pos = result->find(tree_delimiter);
        if (pos != std::string::npos) {
            *delim_num = 3;
            continue;
        }

        pos = result->find(end_delimiter);
        if (pos != std::string::npos) {
            *delim_num = 1;
            continue;
        }

        if (quit_flag) break;
    }

    if (pos != std::string::npos) {
        stream->clear();
        for (unsigned long long i = 0; i < (result->length() - pos) - (buffer.length() - static_cast<unsigned>(read)); i++) {
            stream->unget();
        }
        stream->ignore(*delim_num);

    } else {
        pos = result->length() - (buffer.length() - static_cast<unsigned>(read));
    }
    *result = result->substr(0, pos);

    return result;
}


int core::push(QPushButton* back_button, std::string* filename) {
    std::string name;
    if (filename != nullptr) name = *filename;
    else name = stack_file;

    log->notify(new std::string("Pushing state to file at " + name + "..."));

    std::stringstream stack_data;
    std::ifstream file_input(stack_file);

    stack_data << type << '\n';
    stack_data << step_action << '\n';
    switch (core::type) {
        case 0:
            if ((tree1<int> == nullptr) || (tree2<int> == nullptr)) throw std::runtime_error("Trees have not been initialized.");
            stack_data << *(tree1<int>->to_string(0)) << tree_delimiter << *(tree2<int>->to_string(0)) << '\n';
            break;
        case 1:
            if ((tree1<char> == nullptr) || (tree2<char> == nullptr)) throw std::runtime_error("Trees have not been initialized.");
            stack_data << *(tree1<char>->to_string(0)) << tree_delimiter << *(tree2<char>->to_string(0)) << '\n';
            break;
        case 2:
            if ((tree1<double> == nullptr) || (tree2<double> == nullptr)) throw std::runtime_error("Trees have not been initialized.");
            stack_data << *(tree1<double>->to_string(0)) << tree_delimiter << *(tree2<double>->to_string(0)) << '\n';
            break;
        case 3:
            if ((tree1<std::string> == nullptr) || (tree2<std::string> == nullptr)) throw std::runtime_error("Trees have not been initialized.");
            stack_data << *(tree1<std::string>->to_string(0)) << tree_delimiter << *(tree2<std::string>->to_string(0)) << '\n';
            break;
    }

    long long before_pos = in_stream->tellg();
    if (in_stream->peek() != EOF) stack_data << in_stream->rdbuf();

    in_stream->clear();

    long long after_pos = in_stream->tellg() - before_pos;
    for (long long i = 0; i < after_pos; i++) in_stream->unget();

    stack_data << '\n';

    if ((file_input.peek() != EOF) && (filename == nullptr)) stack_data << file_input.rdbuf();

    std::ofstream file_output(name);
    file_output << stack_data.rdbuf();
    file_output.flush();
    file_output.close();

    if (filename == nullptr) {
        stack_size++;
        back_button->setEnabled(true);
    }

    return 0;
}

int core::pop(MyGLWidget* mglw1, MyGLWidget* mglw2, QPushButton* back_button, std::string* filename) {
    std::string name;
    if (filename != nullptr) name = *filename;
    else name = stack_file;

    log->notify(new std::string("Getting state from file at " + name + "..."));

    std::stringstream ss1, ss2;
    std::string* support = new std::string();
    std::ifstream file_input(name);

    std::getline(file_input, *support);
    ss1 << *support;
    ss1 >> type;

    std::getline(file_input, *support);
    ss2 << *support;
    ss2 >> step_action;

    std::getline(file_input, *support);
    std::string double_buff;
    std::getline(file_input, double_buff);
    support->append("\n");
    support->append(double_buff);

    std::istringstream* os = new std::istringstream(support->c_str());
    in_stream = os;

    int result = 0;
    switch (core::type) {
        case 0:
            result = build_rush<int>(mglw1, mglw2, 1, true);
            break;
        case 1:
            result = build_rush<char>(mglw1, mglw2, 1, true);
            break;
        case 2:
            result = build_rush<double>(mglw1, mglw2, 1, true);
            break;
        case 3:
            result = build_rush<std::string>(mglw1, mglw2, 1, true);
            break;
    }
    free(support);

    if (filename == nullptr) stack_size--;
    else stack_size = 0;
    if (stack_size <= 0) back_button->setEnabled(false);

    std::stringstream buffer;
    buffer << file_input.rdbuf();

    std::ofstream file_output(stack_file);
    file_output << buffer.rdbuf();
    file_output.flush();
    file_output.close();
    file_input.close();

    return result;
}

void core::clear_stack(QPushButton* load_button) {
    log->notify(new std::string("Clearing all files."));

    in_stream = new std::istringstream();
    load_button->setEnabled(false);
    stack_size = 0;

    std::ofstream stack_output(stack_file);
    stack_output.close();

    std::ofstream output1(output_file1);
    output1.close();

    std::ofstream output2(output_file2);
    output2.close();
}
