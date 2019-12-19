#ifndef CORE_H
#define CORE_H

#include <fstream>
#include <sstream>
#include <QPushButton>
#include "treap.h"
#include "myglwidget.h"
#include "outlog.h"


class core {
public:
    static const std::string PATH;

    // functions return: 0 - successful; 1 - error; -1 - forward execution required

    // 0 - nothing done, 1 - trees built
    // 10 - prepare to build trees step by step, 11 - first tree is buildind step by step, 12 - second tree is building step by step,
    // 20 - prepare to merge trees step by step, 21 - trees are merging step by step,
    // 30 - prepare to split trees step by step, 31 - trees are splitting step by step
    static int step_action;


    static int launch(MyGLWidget* mglw, std::string* input, bool ff, int tp);


    template<typename T>
    static int build_step(MyGLWidget* mglw1, MyGLWidget* mglw2);

    // mode 1 - building 2 trees showing both, mode 2 - building 1 tree showing both, mode 3 - building one tree showing none (mdlw1 -> mglw2)
    template<typename T>
    static int build_rush(MyGLWidget* mglw1, MyGLWidget* mglw2, int mode, bool from_val);


    template<typename T>
    static int merge_step(MyGLWidget* mglw1, MyGLWidget* mglw2);

    template<typename T>
    static int merge_rush(MyGLWidget* mglw1, MyGLWidget* mglw2);


    template<typename T>
    static int split_step(int pos, MyGLWidget* mglw1, MyGLWidget* mglw2);

    template<typename T>
    static int split_rush(int pos, MyGLWidget* mglw1, MyGLWidget* mglw2);


    template<typename T>
    static int mult(MyGLWidget* mglw);


    static int push(QPushButton* load_button, std::string* filename);

    static int pop(MyGLWidget* mglw1, MyGLWidget* mglw2, QPushButton* load_button, std::string* filename);

    static void clear_stack(QPushButton* back_button);


    static int type;

    static int split_maximum;

    template<typename T>
    static treap<T>* tree1;

    template<typename T>
    static treap<T>* tree2;

    static outlog* log;

private:
    static const std::string input_file;
    static const std::string output_file1;
    static const std::string output_file2;

    static const std::string stack_file;

    static int stack_size;


    static std::istream* in_stream;


    template<typename T>
    static T get_value(std::string* str);
    template<typename T>
    static treap_node<T>* get_node(std::string* str);


    static const std::string subitem_delimiter;
    static const std::string item_delimiter;  // number 2
    static const std::string range_delimiter; // number 4
    static const std::string tree_delimiter; // number 3
    static const std::string end_delimiter;  // number 1

    static std::string* read_tree(std::istream* stream, int* delim_num);
};


template<typename T>
treap<T>* core::tree1 = nullptr;

template<typename T>
treap<T>* core::tree2 = nullptr;


template<typename T>
int core::build_rush(MyGLWidget* mglw1, MyGLWidget* mglw2, int mode, bool from_val) {
    log->notify(new std::string("Quick building treap in mode " + std::to_string(mode) + " from value " + std::to_string(from_val) + "..."));

    if (mode < 3) {
        mglw1->prepare_drawing();
        mglw2->prepare_drawing();
    }

    if (mode != 2) {
        free(tree1<T>);
        tree1<T> = new treap<T>();
    }
    if (mode < 2) {
        free(tree2<T>);
        tree2<T> = new treap<T>();
    }

    int prev_delim = 0;
    T prev;
    T processing;

    std::string* msg;

    int errno1 = -1, errno2 = -1;
    try {
        int delim_pos = 0;
        do {
            if (from_val) {
                tree1<T>->add(get_node<T>(read_tree(in_stream, &delim_pos)));
            } else {
                processing = get_value<T>(read_tree(in_stream, &delim_pos));
                tree1<T>->add(processing);
            }

            if (mode == 3) {
                if ((prev_delim == 4) && (!(std::is_same<T, std::string>::value))) {
                    log->notify(new std::string("Processing range..."));
                    for (T i = prev; i < processing; i += 1) {
                        tree1<T>->add(i);
                    }
                }

                prev_delim = delim_pos;
                prev = processing;
            }
        } while ((delim_pos != 1) && (delim_pos != 3) && (delim_pos != 0));
        if ((delim_pos == 0) && (mode < 2)) errno2 = 0;

    } catch (std::runtime_error re) {
        msg = new std::string(re.what());
        log->notify(msg);
        if (mode < 3) mglw1->declare(msg);
        return 1;
    } catch (int e) {
        if (mode == 2) errno2 = e;
        else errno1 = e;
    }

    if ((mode < 2) && (errno2 == -1)) {
        try {
            int delim_pos = 0;
            do {
                if (from_val) {
                    tree2<T>->add(get_node<T>(read_tree(in_stream, &delim_pos)));
                } else {
                    tree2<T>->add(get_value<T>(read_tree(in_stream, &delim_pos)));
                }
            } while ((delim_pos != 1) && (delim_pos != 0));

        } catch (std::runtime_error re) {
            msg = new std::string(re.what());
            log->notify(msg);
            mglw2->declare(msg);
            return 1;
        } catch (int e) {
            errno2 = e;
        }
    }

    if (mode < 3) {
        if (errno1 == -1) {
            mglw1->set_tree(tree1<T>, tree1<T>->get_root()->get_index());
            mglw1->show(&output_file1);
        } else {
            mglw1->declare(new std::string("Tree is empty."));
        }
        if (errno2 == -1) {
            mglw2->set_tree(tree2<T>, tree2<T>->get_root()->get_index());
            mglw2->show(&output_file2);
        } else {
            mglw2->declare(new std::string("Tree is empty."));
        }
    }

    if ((tree1<T> != nullptr) && (tree1<T>->get_root() != nullptr)) split_maximum = tree1<T>->get_root()->get_weight();
    else  split_maximum = 0;

    return 0;
}

template<typename T>
int core::merge_rush(MyGLWidget* mglw1, MyGLWidget* mglw2) {
    log->notify(new std::string("Quick merging treap..."));

    mglw1->prepare_drawing();
    mglw2->prepare_drawing();

    tree1<T>->merge(tree2<T>);
    tree2<T> = new treap<T>();

    if ((tree1<T> != nullptr) && (tree1<T>->get_root() != nullptr)) {
        mglw1->set_tree(tree1<T>, tree1<T>->get_root()->get_index());
        mglw1->show(&output_file1);
    } else {
        mglw1->declare(new std::string("Tree is empty."));
    }

    if ((tree2<T> != nullptr) && (tree2<T>->get_root() != nullptr)) {
        mglw2->set_tree(tree2<T>, tree2<T>->get_root()->get_index());
        mglw2->show(&output_file2);
    } else {
        mglw2->declare(new std::string("Tree is empty."));
    }

    if ((tree1<T> != nullptr) && (tree1<T>->get_root() != nullptr)) split_maximum = tree1<T>->get_root()->get_weight();
    else  split_maximum = 0;

    return 0;
}

template<typename T>
int core::split_rush(int pos, MyGLWidget* mglw1, MyGLWidget* mglw2) {
    log->notify(new std::string("Quick splitting treap..."));

    mglw1->prepare_drawing();
    mglw2->prepare_drawing();

    bool is = tree1<T>->split(pos, tree1<T>, tree2<T>);


    if ((tree1<T> != nullptr) && (tree1<T>->get_root() != nullptr)) {
        mglw1->set_tree(tree1<T>, tree1<T>->get_root()->get_index());
        mglw1->show(&output_file1);
    } else {
        mglw1->declare(new std::string("Tree is empty."));
    }

    if ((tree2<T> != nullptr) && (tree2<T>->get_root() != nullptr)) {
        mglw2->set_tree(tree2<T>, tree2<T>->get_root()->get_index());
        mglw2->show(&output_file2);
    } else {
        mglw2->declare(new std::string("Tree is empty."));
    }

    if ((tree1<T> != nullptr) && (tree1<T>->get_root() != nullptr)) split_maximum = tree1<T>->get_root()->get_weight();
    else  split_maximum = 0;

    if (!is) {
        return 1;
    } else return 0;
}


template<typename T>
int core::build_step(MyGLWidget* mglw1, MyGLWidget* mglw2) {
    log->notify(new std::string("Building treap step-by-step..."));

    mglw1->prepare_drawing();
    mglw2->prepare_drawing();

    int result = -1;
    std::string* msg;

    if (step_action == 10) {
        tree1<T> = new treap<T>();
        tree2<T> = new treap<T>();

        msg = new std::string("Tree is empty.");
        mglw1->declare(msg);
        mglw2->declare(msg);

        step_action = 11;
        return result;
    }

    treap_node<T>* processing;

    if (step_action == 11) {
        try {
            int delim_pos = 0;

            processing = new treap_node<T>(get_value<T>(read_tree(in_stream, &delim_pos)));
            tree1<T>->add(processing);

            if ((delim_pos == 0) || (delim_pos == 1)) {
                step_action = 1;
                mglw1->set_tree(tree1<T>, processing->get_index());
                mglw1->show(&output_file1);
                mglw2->declare(new std::string("Tree is empty."));
                return 0;
            } else if (delim_pos == 3) step_action = 12;

        } catch (std::runtime_error re) {
            msg = new std::string(re.what());
            log->notify(msg);
            mglw1->declare(msg);
            return 1;
        }

        mglw1->set_tree(tree1<T>, processing->get_index());
        mglw1->show(&output_file1);
        msg = new std::string("Tree is empty.");
        mglw2->declare(msg);

    } else if (step_action == 12) {
        try {
            int delim_pos = 0;

            processing = new treap_node<T>(get_value<T>(read_tree(in_stream, &delim_pos)));
            tree2<T>->add(processing);

            if ((delim_pos == 0) || (delim_pos == 1)) {
                step_action = 1;
                result = 0;
            }

        } catch (std::runtime_error re) {
            msg = new std::string(re.what());
            log->notify(msg);
            mglw1->declare(msg);
            return 1;
        }

        mglw1->set_tree(tree1<T>, tree1<T>->get_root()->get_index());
        mglw1->show(&output_file1);
        mglw2->set_tree(tree2<T>, processing->get_index());
        mglw2->show(&output_file2);
    }

    if ((tree1<T> != nullptr) && (tree1<T>->get_root() != nullptr)) split_maximum = tree1<T>->get_root()->get_weight();
    else  split_maximum = 0;

    return result;
}

template<typename T>
int core::merge_step(MyGLWidget* mglw1, MyGLWidget* mglw2) {
    log->notify(new std::string("Merging treap step-by-step..."));

    mglw1->prepare_drawing();
    mglw2->prepare_drawing();

    int result = -1;

    if (step_action == 20) {
        std::string tree(*(tree2<T>->to_string(0)));
        std::stringstream* ss = new std::stringstream(tree);
        in_stream = ss;

        step_action = 21;
        return result;
    }

    treap_node<T>* processing;

    if (step_action == 21) {
        try {
            int delim_pos = 0;

            processing = get_node<T>(read_tree(in_stream, &delim_pos));
            tree1<T>->add(processing);

            if ((delim_pos == 0) || (delim_pos == 1)) {
                tree2<T> = new treap<T>;
                step_action = 1;
                result = 0;
            }

        } catch (std::runtime_error re) {
            auto msg = new std::string(re.what());
            log->notify(msg);
            mglw1->declare(msg);
            return 1;
        } catch (...) {
            step_action = 1;
            tree2<T> = new treap<T>;
            result = 0;
        }

    }

    if (step_action == 1) {
        mglw2->declare(new std::string("Tree is empty."));
        if ((tree1<T> != nullptr) && (tree1<T>->get_root() != nullptr)) {
            mglw1->set_tree(tree1<T>, tree1<T>->get_root()->get_index());
            mglw1->show(&output_file1);
        } else {
            mglw1->declare(new std::string("Tree is empty."));
        }
    } else {
        mglw2->set_tree(tree2<T>, processing->get_index());
        mglw2->show(&output_file2);
        mglw1->set_tree(tree1<T>, processing->get_index());
        mglw1->show(&output_file1);
    }

    if ((tree1<T> != nullptr) && (tree1<T>->get_root() != nullptr)) split_maximum = tree1<T>->get_root()->get_weight();
    else  split_maximum = 0;

    return result;
}

template<typename T>
int core::split_step(int pos, MyGLWidget* mglw1, MyGLWidget* mglw2) {
    log->notify(new std::string("Splitting treap step-by-step..."));

    mglw1->prepare_drawing();
    mglw2->prepare_drawing();

    int result = -1;

    if (step_action == 30) {
        if ((tree1<T> != nullptr) && (tree1<T>->get_root() != nullptr)) {
            tree2<T> = new treap<T>;

            std::string tree(*(tree1<T>->to_string(pos)));
            std::stringstream* ss = new std::stringstream(tree);
            in_stream = ss;

            step_action = 31;
        } else {
            step_action = 1;
            result = 1;
        }
        return result;
    }

    treap_node<T>* processing;

    if (step_action == 31) {
        try {
            int delim_pos = 0;

            processing = get_node<T>(read_tree(in_stream, &delim_pos));
            tree2<T>->add(processing);

            if ((delim_pos == 0) || (delim_pos == 1)) {
                long long init_size = tree1<T>->get_weight();
                for (long long i = init_size; i > (init_size - tree2<T>->get_weight()); i--) {
                    tree1<T>->remove(i);
                }

                step_action = 1;
                result = 0;
            }

        } catch (std::runtime_error re) {
            auto msg = new std::string(re.what());
            log->notify(msg);
            mglw1->declare(msg);
            return 1;
        } catch (...) {
            log->notify(new std::string("Error during splitting!"));
            result = 1;
        }

    }

    if ((tree1<T> != nullptr) && (tree1<T>->get_root() != nullptr)) {
        mglw1->set_tree(tree1<T>, processing->get_index());
        mglw1->show(&output_file1);
    } else {
        mglw1->declare(new std::string("Tree is empty."));
    }

    if ((tree2<T> != nullptr) && (tree2<T>->get_root() != nullptr)) {
        mglw2->set_tree(tree2<T>, processing->get_index());
        mglw2->show(&output_file2);
    } else {
        mglw2->declare(new std::string("Tree is empty."));
    }

    if ((tree1<T> != nullptr) && (tree1<T>->get_root() != nullptr)) split_maximum = tree1<T>->get_root()->get_weight();
    else  split_maximum = 0;

    return result;
}


template<typename T>
int core::mult(MyGLWidget* mglw) {
    log->notify(new std::string("Multiple treap building researching..."));

    mglw->prepare_drawing();

    long long int mid_size = 0;
    long long int theo_size = 0;

    for (int i = 0; i < 100; i++) {
        long long first_pos = in_stream->tellg();
        int result = build_rush<T>(nullptr, nullptr, 3, false);

        in_stream->clear();

        long long length = in_stream->tellg() - first_pos;
        for (long long i = 0; i < length; i++) in_stream->unget();
        if (result != 0) return 1;

        if (theo_size == 0) theo_size = tree1<T>->theory_depth();
        mid_size += tree1<T>->max_depth();
        free(tree1<T>);
        tree1<T> = nullptr;

        log->notify(new std::string("Building tree nuber " + std::to_string(i) + "..."));
    }

    std::stringstream ss;
    ss << "Average depth of 100 trees was " << mid_size / 100 << "\nIdeal size is " << theo_size;
    auto msg = new std::string(ss.str());
    log->notify(msg);
    mglw->declare(msg);

    return 0;
}


template<typename T>
T core::get_value(std::string* str) {
    log->notify(new std::string("Reading value for new tree node: " + *str + "..."));

    std::stringstream ss;
    T value;

    ss << *str;
    if (!(ss >> value)) {
        throw std::runtime_error("Node value can not be read!");
    }

    return value;
}

template<typename T>
treap_node<T>* core::get_node(std::string* str) {
    log->notify(new std::string("Reading new tree node: " + *str + "..."));

    unsigned long long pos = str->find(';');
    std::stringstream ss1, ss2;

    T value;
    double index = 0;

    if (str->empty()) {
        throw 1;
    }

    ss1 << (*str).substr(1, pos);
    ss2 << (*str).substr(pos + 1, (str->length() - 2 - pos));
    if (!(ss1 >> value)) {
        throw std::runtime_error("Node value can not be read!");
    }
    if (!(ss2 >> index)) {
        throw std::runtime_error("Node index can not be read!");
    } else if (index == 0.0) {
        throw 0;
    }

    return new treap_node<T>(value, index);
}


#endif // CORE_H
