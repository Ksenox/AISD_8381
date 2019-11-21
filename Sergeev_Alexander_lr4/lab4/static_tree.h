#ifndef UNTITLED1_STATIC_TREE_H
#define UNTITLED1_STATIC_TREE_H


#include "measuring_array.h"
#include "tree_node.h"

template<typename T>
class static_tree : public measuring_array<tree_node<T>*> {
private:
    const static char LOSS = '#';
    const static char REPL = '%';

    static_tree();

    bool is_operator(char ch); // defines if the given is a supported math operator
    int getBracketPos(string& str); // returns a position between two bracket blocks in a string, e.g. getBracketPos("(abc)(abc)") = 4

public:
    static_tree(string& str, bool (*is_operator)(char ch), bool (*is_operand)(char ch));
    virtual ~static_tree();

    int get_first_tree_by_template(static_tree<T>* templ, measuring_array<int>** location = nullptr); // get first tree matching tree template
    static_tree<T>* get_subtree(measuring_array<int>* location); // returns a tree build from this tree with a locations map
    static_tree<T>* get_subtree(unsigned int pos); // returns a tree build from this tree starting from a specific node
    bool compare_to(static_tree<T>* another); // compares tree with a tree
    void delete_subtree(unsigned int pos); // deletes tree from given element
    void insert_tree(unsigned int pos, static_tree<T>* sub_tree); // inserts an element into the tree

    string to_tree_string(); // prints tree graphic
    string to_infix_string(); // prints infix form of the tree
};



template<typename T>
static_tree<T>::static_tree(string& str, bool (*is_operator)(char), bool (*is_operand)(char)) : measuring_array<tree_node<T>*>() {
    auto passer = new measuring_array<string*>(); // strings representing the current tree level
    passer->add(&str);

    while (!passer->is_empty()) { // while there are strings to add to this tree level
        string curr = *(passer->get(0)); // getting new element to add to the tree
        curr = curr.substr(1, curr.size() - 2); // removing brackets

        if ((curr.size() > 1) && (is_operator(curr[curr.size() - 1]))) { // if it is not a leaf
            auto node = new tree_node<T>(curr[curr.size() - 1], false); // creating tree node
            this->add(node);

            int br_pos = getBracketPos(curr); // place where the string representations of two branches meet
            auto child1 = new string(curr.substr(0, br_pos + 1)); // adding first branch representation to queue
            passer->add(child1);
            auto child2 = new string(curr.substr(br_pos + 1, curr.size() - br_pos - 2)); // adding second branch representation to queue
            passer->add(child2);

        } else if ((curr.size() == 1) && ((is_operand(curr[curr.size() - 1])) || (is_operator(curr[curr.size() - 1])))) { // if it is a leaf
            auto node = new tree_node<T>(curr[0], true); // creating tree node
            this->add(node);

        } else { //TODO: add other error conditions;
            throw runtime_error("String wrongly formatted!");
        }

        passer->remove(0); // removing the first, already added element from the queue
    }
}

template<typename T>
static_tree<T>::static_tree() : measuring_array<tree_node<T>*>() {}



template<typename T>
int static_tree<T>::getBracketPos(string &str) {
    int br_counter = 0; // quantity of opened brackets passed
    for (unsigned long i = 0; i < str.size(); ++i) {
        switch (str[i]) {
            case '(':
                br_counter++;
                break;
            case ')':
                br_counter--;
                if (br_counter == 0) {
                    return (int) i;
                }
                break;
        }
    }
    throw runtime_error("String wrongly formatted!"); // if the place was not found
}

template<typename T>
bool static_tree<T>::is_operator(char ch) {
    return (ch == '+') || (ch == '-') || (ch == '*');
}

template<typename T>
static_tree<T>::~static_tree() {}



template<typename T>
int static_tree<T>::get_first_tree_by_template(static_tree<T>* templ, measuring_array<int>** location) {
    if (location == nullptr) {
        auto lock = new measuring_array<int>; // an array containing positions of found elements of subtree
        location = &lock;
    }
    auto inspected = new measuring_array<int>(); // an array containing positions of elements that match template root but were proofed wrong roots
    bool no_occurences; // no roots were met

    do {
        (*location)->clear();
        int expected_child_pos = 1; // position of the first child of this node
        int templ_iterator = 0; // iterator of the template tree
        bool matches = false; // fits with template
        no_occurences = true;

        for (int i = 0; i < this->get_length(); ++i) {
            auto node = this->get(i);

            if (no_occurences && (node->get_trunk() == templ->get(templ_iterator)->get_trunk()) && (!inspected->contains(i))) { // new possible root found
                inspected->add(i); // it is added to inspected
                no_occurences = false;
                matches = true;
                (*location)->add(i); // it is added to location
            }

            if ((*location)->contains(i)) { // new child of possible root found
                if (node->get_trunk() == templ->get(templ_iterator)->get_trunk()) { // child meets all the requirements
                    if ((!node->is_leaf()) && (!templ->get(templ_iterator)->is_leaf())) { // both this node and template nodes are leaves
                        int children_pos = i + expected_child_pos;
                        (*location)->add(children_pos); // expected children added to location map
                        (*location)->add(children_pos + 1);
                    }
                    templ_iterator++;
                } else {
                    matches = false;
                    break;
                }
            }

            if (!node->is_leaf()) expected_child_pos += 2; // adding two lacunas to the map as children of a leaf

            expected_child_pos--;
        }

        if (matches) return (*location)->get(0);

    } while (!no_occurences);

    (*location)->clear();
    return -1;
}

template<typename T>
static_tree<T>* static_tree<T>::get_subtree(measuring_array<int>* location) {
    auto sub_tree = new static_tree<T>();
    for (int i = 0; i < location->get_length(); ++i) {
        sub_tree->add(this->get(location->get(i)));
    }
    return sub_tree;
}

template<typename T>
static_tree<T>* static_tree<T>::get_subtree(unsigned int pos) {
    auto sub_tree = new static_tree<T>();
    auto children = new measuring_array<int>();
    children->add(pos);
    int expected_child_pos = 1;

    if (pos >= this->get_length()) throw runtime_error("Subtree index not in tree!");

    for (int i = 0; i < this->get_length(); ++i) {
        tree_node<T> node = *(this->get(i));

        if (children->contains(i)) {
            sub_tree->add(this->get(i));

            if (!node.is_leaf()) {
                int children_pos = i + expected_child_pos;
                children->add(children_pos);
                children->add(children_pos + 1);
            }

        }

        if (!node.is_leaf()) expected_child_pos += 2; // adding two lacunas to the map as children of a leaf

        expected_child_pos--;
    }

    return sub_tree;
}

template<typename T>
bool static_tree<T>::compare_to(static_tree<T>* another) {
    if (this->get_length() != another->get_length()) return false;
    bool same = true;

    for (int i = 0; i < this->get_length(); ++i) {
        same &= (this->get(i)->get_trunk() == another->get(i)->get_trunk());
    }

    return same;
}

template<typename T>
void static_tree<T>::delete_subtree(unsigned int pos) {
    auto marked = new measuring_array<int>(); // indexes marked for deletion
    marked->add(pos);
    int expected_child_pos = 1;

    if (pos >= this->get_length()) throw runtime_error("Deleting index not in tree!");

    for (int i = 0; i < this->get_length(); ++i) {
        tree_node<T> node = *(this->get(i));

        if (marked->contains(i)) {
            marked->remove(0);

            if (!node.is_leaf()) {
                int children_pos = i + expected_child_pos;
                marked->add(children_pos);
                marked->add(children_pos + 1);
            }

            if (i == pos) {
                auto new_node = new tree_node<T>(LOSS, true);
                this->replace(new_node, i); // first entry node is replaced with a special sign node not to disbalance tree
            } else {
                this->remove(i);
                for (int j = 0; j < marked->get_length(); ++j) marked->replace(marked->get(j) - 1, j); // after the element was deleted all elements moved left so their deletion indexes should be moved too
                i--; // to check this index again
            }
        }

        if (!node.is_leaf()) expected_child_pos += 2; // adding two lacunas to the map as children of a leaf

        expected_child_pos--;
    }
}

template<typename T>
void static_tree<T>::insert_tree(unsigned int pos, static_tree<T>* sub_tree) {
    auto insertion_places = new measuring_array<int>();
    insertion_places->add(pos);
    int expected_child_pos = 1;
    int sub_tree_iterator = 0;

    if (pos >= this->get_length()) throw runtime_error("Inserting index not in tree!");
    if (!this->get(pos)->is_leaf()) delete_subtree(pos); // if selected node is not a leaf all its children will be deleted

    for (int i = 0; i < this->get_length(); ++i) {
        if (insertion_places->contains(i)) {
            insertion_places->remove(0);
            tree_node<T> node = *(sub_tree->get(sub_tree_iterator));

            if (!node.is_leaf()) {
                int children_pos = i + expected_child_pos;
                insertion_places->add(children_pos);
                insertion_places->add(children_pos + 1);
            }

            if (i == pos) {
                this->replace(sub_tree->get(sub_tree_iterator), i);
            } else {
                this->add(sub_tree->get(sub_tree_iterator), i);
            }
            sub_tree_iterator++;
        }

        if (!this->get(i)->is_leaf()) expected_child_pos += 2; // adding two lacunas to the map as children of a leaf

        expected_child_pos--;
    }

    for (; sub_tree_iterator < sub_tree->get_length(); ++sub_tree_iterator) { // if there are some nodes left in the sub_tree, we can add them as-is, it is safe
        this->add(sub_tree->get(sub_tree_iterator));
    }
}



template<typename T>
string static_tree<T>::to_tree_string() {
    auto arr = new measuring_array<string*>(); // array of strings representing tree levels
    auto expected_nodes = new measuring_array<bool>(); // string representing map of nodes (with 1) and lacunas (with 0) in current and next tree level
    auto next_expected = new measuring_array<bool>();
    expected_nodes->add(true);

    arr->add(new string()); // adding new string level representation
    for (int i = 0; i < this->get_length(); ++i) {
        if (expected_nodes->is_empty()) { // the current level is empty
            expected_nodes->add_all(next_expected); // switching level maps
            next_expected->clear();
            arr->add(new string()); // adding new string level representation
        }

        if (expected_nodes->get(0)) { // if there is a real node
            tree_node<T> node = *(this->get(i)); // getting node
            ostringstream ss;
            ss << node.get_trunk(); // writing its contents to stream
            *(arr->get(arr->get_length() - 1)) += ss.str(); // adding the node value to string representation

            if (node.is_leaf()) { // adding two lacunas to the map as children of a leaf
                next_expected->add(false);
                next_expected->add(false);
            } else { // adding two children to the map as children of a non-leaf node
                next_expected->add(true);
                next_expected->add(true);
            }

        } else {
            next_expected->add(false);
            next_expected->add(false);
            *(arr->get(arr->get_length() - 1)) += " "; // adding a long enough lacuna representation to representation string
            i--; // "unreading" a tree node as lacuna is not a tree node
        }

        expected_nodes->remove(0); // erasing first (represented) symbol from the map
        *(arr->get(arr->get_length() - 1)) += REPL; // adding a space between nodes
    }

    string res;
    string offset, gap = "   ";
    for (int j = arr->get_length() - 1; j >= 0; --j) { // binding if string representations
        arr->get(j)->pop_back();

        size_t index = arr->get(j)->find(REPL);
        while (index != string::npos) {
            arr->get(j)->replace(index, 1, gap);
            index += gap.length();
            index = arr->get(j)->find(REPL, index);
        }

        if (j < arr->get_length() - 1) offset += gap.substr(0, gap.length() / 4 + 1);
        *(arr->get(j)) = offset + *(arr->get(j));

        gap += gap + " ";

        res.insert(0, *(arr->get(j)) + "\n");
    }

    return res;
}

template<typename T>
string static_tree<T>::to_infix_string() {
    measuring_array<string*> repr;
    string* part;
    for (int i = 0; i < this->get_length(); ++i) {
        tree_node<T> node = *(this->get(i));

        ostringstream ss;
        ss << node.get_trunk();

        if (this->get(i)->is_leaf()) {
            part = new string(ss.str());
        } else {
            part = new string("(" + string(1, REPL) + " " + ss.str() + " " +  string(1, REPL) + ")");
        }

        repr.add(part);
    }

    for (int j = repr.get_length() - 1; j >= 0; --j) {
        for (int i = j - 1; i >= 0; --i) {
            int index = repr.get(i)->find_last_of(REPL);
            if (index != string::npos) {
                repr.get(i)->replace(index, 1, *(repr.get(j)));
                break;
            }
        }
    }

    return *(repr.get(0));
}


#endif //UNTITLED1_STATIC_TREE_H
