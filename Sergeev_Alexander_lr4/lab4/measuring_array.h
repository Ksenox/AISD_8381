#ifndef UNTITLED1_MEASURING_ARRAY_H
#define UNTITLED1_MEASURING_ARRAY_H


#include "bits/stdc++.h"

using namespace std;

#define END_SYMBOL -1
#define MIN_OCCUPATION 10

template <typename T>
class measuring_array {
private:
    int occupation;

    void checkSizeStability();

protected:
    T* array;
    int length;

public:
    measuring_array();
    virtual ~measuring_array();

    void add(T element, int pos = END_SYMBOL);
    void add_all(measuring_array<T>* other);
    void remove(int pos = END_SYMBOL);
    void replace(T element, int pos = END_SYMBOL);
    void replace(T element, T* replacer);
    T get(int pos);
    int get_length();
    bool is_empty();
    bool contains(T element);
    int find_first(T element);
    void clear();

    string to_string();
};



template<typename T>
void measuring_array<T>::add(T element, int pos) {
    if ((pos == END_SYMBOL) || (pos == length)) {
        length++;
        checkSizeStability();
        array[length - 1] = element;

    } else if ((pos >= 0) && (pos < length)) {
        length++;
        checkSizeStability();
        for (int i = length - 2; i >= pos; --i) {
            array[i+1] = array[i];
        }
        array[pos] = element;

    } else {
        throw runtime_error("Position of element inserting in measuring array is not in its bounds");
    }
}

template<typename T>
void measuring_array<T>::add_all(measuring_array<T>* other) {
    for (int i = 0; i < other->get_length(); ++i) {
        add(other->get(i));
    }
}

template<typename T>
void measuring_array<T>::remove(int pos) {
    if ((pos == END_SYMBOL) || (pos == length)) {
        length--;
        checkSizeStability();

    } else if ((pos >= 0) && (pos < length)) {
        for (int i = pos+1; i < length; ++i) {
            array[i-1] = array[i];
        }
        length--;
        checkSizeStability();

    } else {
        throw runtime_error("Position of element removing from measuring array is not in its bounds");
    }
}

template<typename T>
void measuring_array<T>::replace(T element, int pos) {
    if ((pos >= 0) && (pos < length)) {
        array[pos] = element;

    } else {
        throw runtime_error("Position of element replacing in measuring array is not in its bounds");
    }
}

template<typename T>
void measuring_array<T>::replace(T element, T* replacer) {
    for (int i = 0; i < length; ++i) {
        if (element == array[i]) {
            array[i] = *replacer;
            break;
        }
    }
}

template<typename T>
void measuring_array<T>::checkSizeStability() {
    if (length < 0) throw runtime_error("Measuring array minimum size reached and crossed!");
    if (length > occupation) {
        occupation += occupation/2 > 0 ? occupation/2 : MIN_OCCUPATION;
        array = (T*) realloc(array, (size_t) occupation * sizeof(T*));
    } else if ((length < occupation/2) && (length > MIN_OCCUPATION)) {
        occupation -= occupation/3;
        array = (T*) realloc(array, (size_t) occupation * sizeof(T*));
    }
}

template<typename T>
T measuring_array<T>::get(int pos) {
    if ((pos >= 0) && (pos < length)) {
        return array[pos];

    } else {
        throw runtime_error("Position of element getting in measuring array is not in its bounds");
    }
}

template<typename T>
int measuring_array<T>::get_length() {
    return length;
}

template<typename T>
bool measuring_array<T>::is_empty() {
    return get_length() == 0;
}

template<typename T>
bool measuring_array<T>::contains(T element) {
    for (int i = 0; i < length; ++i) {
        if (array[i] == element) return true;
    }
    return false;
}

template<typename T>
int measuring_array<T>::find_first(T element) {
    for (int i = 0; i < length; ++i) {
        if (array[i] == element) return i;
    }
    return -1;
}

template<typename T>
void measuring_array<T>::clear() {
    int prev_len = length;
    for (int i = 0; i < prev_len; ++i) {
        remove();
    }
}

template<typename T>
string measuring_array<T>::to_string() {
    string sig;
    for (int i = 0; i < length; ++i) {
        ostringstream ss;
        ss << array[i] << " ";
        sig += ss.str();
    }
    sig += "-> " + to_string(length) + "/" + to_string(occupation);
    return sig;
}



template<typename T>
measuring_array<T>::measuring_array() {
    this->array = (T*) calloc(0, sizeof(T*));
    this->length = 0;
    this->occupation = 0;
}

template<typename T>
measuring_array<T>::~measuring_array() {
    free(this->array);
    this->length = 0;
    this->occupation = 0;
}


#endif //UNTITLED1_MEASURING_ARRAY_H
