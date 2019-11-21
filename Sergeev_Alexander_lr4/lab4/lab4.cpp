//
// Created by alex on 11/7/19.
//

#include "lab4.h"

bool is_operator(char ch) {
    return (ch == '+') || (ch == '-') || (ch == '*');
}

bool is_operand(char ch) {
    return isalnum(ch);
}

void lab4::launch(string &str) {
    this->base = str;
    this->tree = new static_tree<char>(str, is_operator, is_operand);
    templ = "((*)(*)+)";
}

void lab4::rush() {
    auto temp = new static_tree<char>(templ, is_operator, is_operand);

    auto locator = new measuring_array<int>();
    int new_pos = tree->get_first_tree_by_template(temp, &locator);
    while (new_pos != -1) {
        auto sub_tree = tree->get_subtree(new_pos);
        auto f1 = sub_tree->get_subtree(3);
        auto f2 = sub_tree->get_subtree(4);
        auto f3 = sub_tree->get_subtree(5);
        auto f4 = sub_tree->get_subtree(6);

        if (f1->compare_to(f3)) {
            sub_tree->get(0)->setTrunk('*');
            sub_tree->get(2)->setTrunk('+');

            sub_tree->insert_tree(5, f2);
            sub_tree->insert_tree(1, f1);
        } else if (f2->compare_to(f4)) {
            sub_tree->get(0)->setTrunk('*');
            sub_tree->get(1)->setTrunk('+');

            sub_tree->insert_tree(2, f3);
        }
        tree->insert_tree(new_pos, sub_tree);

        new_pos = tree->get_first_tree_by_template(temp, &locator);
    }
}

void lab4::step(int* i) {
    switch (*i) {
        case 0:
            copy = tree;
            temp = new static_tree<char>(templ, is_operator, is_operand);
            tree = temp;
            state = "Tree mask for search built";
            break;

        case 1:
            tree = copy;
            locator = new measuring_array<int>();
            new_pos = tree->get_first_tree_by_template(temp, &locator);
            if (new_pos == -1) throw runtime_error("Matching tree not found.\nProgram finished correctly.");
            state = "Matching tree found at " + to_string(new_pos);
            break;
        case 2:
            copy = tree;
            sub_tree = tree->get_subtree(new_pos);
            tree = sub_tree;
            f1 = sub_tree->get_subtree(3);
            f2 = sub_tree->get_subtree(4);
            f3 = sub_tree->get_subtree(5);
            f4 = sub_tree->get_subtree(6);
            first_pair_equal = f1->compare_to(f3);
            second_pair_equal = f2->compare_to(f4);
            state = "Matching subtree built\n";
            if (first_pair_equal) state += "f1 = f3";
            if (second_pair_equal) state += "f2 = f4";
            break;
        case 3:
            if (first_pair_equal) {
                sub_tree->get(0)->setTrunk('*');
                sub_tree->get(2)->setTrunk('+');
            }
            if (f2->compare_to(f4)) {
                sub_tree->get(0)->setTrunk('*');
                sub_tree->get(1)->setTrunk('+');
            }
            state = "Subtree roots changed accordingly";
            break;
         case 4:
            if (first_pair_equal) {
                sub_tree->insert_tree(5, f2);
                sub_tree->insert_tree(1, f1);
            }
            if (second_pair_equal) {
                sub_tree->insert_tree(2, f3);
            }
            state = "Subtree branches changed accordingly";
            break;
         case 5:
            tree = copy;
            tree->insert_tree(new_pos, sub_tree);
            state = "Subtree inserted back to its position";
            break;
         case 6:
            new_pos = tree->get_first_tree_by_template(temp, &locator);
            if (new_pos == -1) {
                if (new_pos == -1) throw runtime_error("Matching tree not found.\nProgram finished correctly.");
            } else {
                *i = 1;
                state = "Matching tree found at " + to_string(new_pos);
            }
            break;
    }
}
