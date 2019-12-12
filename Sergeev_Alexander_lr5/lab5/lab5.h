#ifndef LAB5_H
#define LAB5_H

#include "rand_tree.h"
#include "myglwidget.h"
#include <iostream>
#include <fstream>
#include <sstream>

class lab5 {
public:
    static int launch(MyGLWidget* mglw, std::string* input, bool ff, int tp, bool step);

    template<typename T>
    static int launch_steps(MyGLWidget* mglw) {
        if (!tree1_stck<T>->isEmpty()) {
            auto val = tree1_stck<T>->pop();
            tree1<T>->add(val);

            mglw->set_tree(tree1<T>, val);
            mglw->show(&output_file);
            return 1;
        } else if (!tree2_stck<T>->isEmpty()) {
            auto val = tree2_stck<T>->pop();
            tree2<T>->add(val);

            mglw->set_tree(tree2<T>, val);
            mglw->show(&output_file);
            return 1;
        } else {
            free(tree1_stck<T>);
            tree1_stck<T> = nullptr;
            free(tree2_stck<T>);
            tree2_stck<T> = nullptr;

            mglw->set_tree(tree2<T>, tree2<T>->get_root()->get_state());
            mglw->show(&output_file);
            return 0;
        }
    }

    static int type;

    template<typename T>
    static rand_tree<T>* tree1;

    template<typename T>
    static rand_tree<T>* tree2;


    template<typename T>
    static int step(MyGLWidget* mglw) {
        if (stck<T> == nullptr) {
            stck<T> = new stack<tree_node<T>*>();
            stck<T>->push(tree2<T>->get_root());

            mglw->set_tree(tree1<T>, tree1<T>->get_root()->get_state());
            mglw->show(&output_file);
            return 1;

        } else if (!stck<T>->isEmpty()) {
            auto node = stck<T>->pop();

            tree1<T>->join(node, stck<T>);
            tree1<T>->get_root()->reset_weight();

            mglw->set_tree(tree1<T>, node->get_state());
            mglw->show(&output_file);

            free(node);
            return 1;

        } else {
            free(stck<T>);
            stck<T> = nullptr;

            mglw->set_tree(tree1<T>, tree1<T>->get_root()->get_state());
            mglw->show(&output_file);
            return 0;
        }
    }

    template<typename T>
    static int rush(MyGLWidget* mglw) {
        tree1<T>->join(tree2<T>->get_root(), nullptr);
        mglw->set_tree(tree1<T>, tree1<T>->get_root()->get_state());
        mglw->show(&output_file);
        return 0;
    }

    template<typename T>
    static int mult(MyGLWidget* mglw) {
        rand_tree<T>* new_tree = nullptr;
        long long int mid_size = 0;
        long long int theo_size = 0;

        for (int i = 0; i < 10000; i++) {
            auto tree_string = new std::string(input_str);
            new_tree = new rand_tree<T>(tree_string, nullptr);
            if (theo_size == 0) theo_size = new_tree->theory_depth();
            mid_size += new_tree->max_depth();
            free(new_tree);
            free(tree_string);
            new_tree = nullptr;
        }

        std::stringstream ss;
        ss << "Average depth of 10000 trees was " << mid_size / 10000 << "\nIdeal size is " << theo_size;
        auto msg = new std::string(ss.str());
        mglw->declare(msg);

        return 0;
    }


private:
    static const std::string input_file;
    static const std::string output_file;

    static std::string input_str;

    template<typename T>
    static stack<tree_node<T>*>* stck;

    template<typename T>
    static stack<T>* tree1_stck;
    template<typename T>
    static stack<T>* tree2_stck;
};

template<typename T>
stack<tree_node<T>*>* lab5::stck = nullptr;

template<typename T>
stack<T>* lab5::tree1_stck = nullptr;
template<typename T>
stack<T>* lab5::tree2_stck = nullptr;


template<typename T>
rand_tree<T>* lab5::tree1 = nullptr;

template<typename T>
rand_tree<T>* lab5::tree2 = nullptr;


#endif // LAB5_H
