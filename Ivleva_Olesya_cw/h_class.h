#include <iostream>
#include <string>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;

template <class Key, class Value> class Hash_cl
{
    struct Hash {
        Key key1;
        Value value1;
        int h_func = 0;
        int flag_repeat = 0;
        int fl_del = 0;
    };


    int size = 100;
    Hash *val = new Hash[size];
    int last_added = -1;
    int last_repeat = -1;


public:

    int get_size() {
        return size;
    }

    int get_last_added() {
        return last_added;
    }

    int get_last_repeat() {
        return last_repeat;
    }

    void reset_last_repeat() {
        last_repeat = -1;
    }

    void delete_all(){
        for (int i = 0; i < size; i++) {
            val[i].key1 = "";
            val[i].value1 = "";
            val[i].h_func = 0;
            val[i].flag_repeat = 0;
            val[i].fl_del = 0;
        }
    }

    void resize(int sum) {
        Hash *arr = new Hash[sum];
        for (int i = 0; i < size; i++) {
            arr[i] = val[i];
        }
        delete[] val;
        val = arr;
        size = sum;
    }


    void do_hash_str(Key key, Value value, int h_sum, string &output) {
        if (h_sum >= size){
            resize(h_sum+100);
        }
        if (val[h_sum].h_func == 0) {
            val[h_sum].key1 = key;
            val[h_sum].value1 = value;
            val[h_sum].h_func = h_sum;
            last_added = h_sum;
        } else {
            int i = h_sum;
            while (val[i].h_func != 0){
                if (val[i].key1 == key) {
                    last_repeat = i;
                    output += key;
                    output += "\t:\tyes\n";
                    if (val[i].key1 == key && val[i].value1 == value) {
                        val[i].flag_repeat += 1;
                    }
                    return;
                }
                i++;
            }
            val[i].key1 = key;
            val[i].value1 = value;
            val[i].h_func = h_sum;
            last_added = i;
           }
    }

    void do_hash_del(Key key, Value value, int h_sum){
        int i = h_sum;
        while (i < size){
            if (val[i].key1 == key && val[i].value1 == value) {
                if(val[i].flag_repeat > 0){
                    val[i].flag_repeat--;
                    if (get_last_repeat() == i)
                        last_repeat = -1;
                    return;
                }
                val[i].key1 = "";
                val[i].value1 = "";
                val[i].h_func = 0;
                if (get_last_repeat() == i)
                    last_repeat = -1;
                return;
            }
            i++;
        }
    }

    void delete_elem(Key key, Value value, int h_sum){
        int i = h_sum;
        while (i < size){
            if (val[i].key1 == key && val[i].value1 == value) {
                val[i].fl_del += 1;
                return;
            }
            i++;
        }
    }

    void reset_elem(Key key, Value value, int h_sum){
        int i = h_sum;
        while (i < size){
            if (val[i].key1 == key && val[i].value1 == value) {
                val[i].fl_del -= 1;
                return;
            }
            i++;
        }
    }


    void print_hash(string &output) {
        for (int i = 0; i < size; i++) {
            if (val[i].h_func != 0 && val[i].fl_del == 0) {
                output += to_string(val[i].h_func);
                output +="\t";
                output += val[i].key1;
                output +="\t";
                output +=val[i].value1;
                output +="\n";
              }
          }
    }

    Hash operator[](unsigned int index){
        return val[index];
    }

};


