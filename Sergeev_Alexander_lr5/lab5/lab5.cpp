#include "lab5.h"


const std::string lab5::input_file = "/home/alex/Documents/current/alg_lab5/lab5/in.txt";
const std::string lab5::output_file = "/home/alex/Documents/current/alg_lab5/lab5/out.png";

const std::string tree_divider = " = ";

int lab5::type = 0;

std::string lab5::input_str = "";


int lab5::launch(MyGLWidget* mglw, std::string* input, bool ff, int tp, bool step) {
    mglw->prepare_drawing();

    std::string tree_string;
    if (ff) {
        std::ifstream is;
        if (input->empty()) {
            is = std::ifstream(input_file);
        } else {
            is = std::ifstream(*input);
        }

        if (is && !is.fail()) {
            getline(is, tree_string);
        } else {
            auto msg = new std::string("File can not be opened :(");
            mglw->declare(msg);
            return 1;
        }
    } else {
        if (input->empty()) {
            auto msg = new std::string("The input was empty.");
            mglw->declare(msg);
            return 1;
        } else {
            tree_string = *input;
        }
    }

    unsigned long long div = tree_string.find(tree_divider);
    if (div == std::string::npos) {
        auto msg = new std::string("String for only one tree was provided.");
        mglw->declare(msg);
        return 1;
    }

    std::string first = tree_string.substr(0, div);
    std::string second = tree_string.substr(div + tree_divider.length(), tree_string.length() - 1);
    if (first.empty() || second.empty()) {
        auto msg = new std::string("The input for one of the trees was empty.");
        mglw->declare(msg);
        return 1;
    }
    input_str = tree_string.replace(div, tree_divider.length(), ", ");

    type = tp;

    try {
        switch (type) {
            case 0: {
                if (step) {
                    tree1_stck<std::string> = new stack<std::string>();
                    tree2_stck<std::string> = new stack<std::string>();
                }
                tree1<std::string> = new rand_tree<std::string>(&first, tree1_stck<std::string>);
                tree2<std::string> = new rand_tree<std::string>(&second, tree2_stck<std::string>);
                break;
            }
            case 1: {
                if (step) {
                    tree1_stck<char> = new stack<char>();
                    tree2_stck<char> = new stack<char>();
                }
                tree1<char> = new rand_tree<char>(&first, tree1_stck<char>);
                tree2<char> = new rand_tree<char>(&second, tree2_stck<char>);
                break;
            }
            case 2: {
                if (step) {
                    tree1_stck<int> = new stack<int>();
                    tree2_stck<int> = new stack<int>();
                }
                tree1<int> = new rand_tree<int>(&first, tree1_stck<int>);
                tree2<int> = new rand_tree<int>(&second, tree2_stck<int>);
                break;
            }
            case 3: {
                if (step) {
                    tree1_stck<double> = new stack<double>();
                    tree2_stck<double> = new stack<double>();
                }
                tree1<double> = new rand_tree<double>(&first, tree1_stck<double>);
                tree2<double> = new rand_tree<double>(&second, tree2_stck<double>);
                break;
            }
        }

    } catch (std::runtime_error re) {
        auto msg = new std::string(re.what());
        mglw->declare(msg);
        return 1;
    }

    std::string* msg;
    if (step) {
        msg = new std::string("Both strings successfully loaded. We are ready 2 build.");
    } else {
        msg = new std::string("Both trees successfully loaded. We are ready 2 go.");
    }

    mglw->declare(msg);
    return ((step) ? (2) : (0));
}



