//lr2.3
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct BinKor;

//Груз ::= Гирька | БинКор
struct Load {
    bool isWeight;
    union {
        int weight;
        BinKor* binKor;
    } data;
};

//Плечо ::= (Длина Груз)
struct Side {
    short length;
    Load* load;
};

//БинКор ::= (Плечо Плечо)
struct BinKor {
    Side* right;
    Side* left;
};

short Length (const BinKor bk) {
    short result = 0;
    if (bk.right) {
        result += bk.right->length;
        if (bk.right->load && !bk.right->load->isWeight) result += Length(*bk.right->load->data.binKor);
    }
    if (bk.left) {
        result += bk.left->length;
        if (bk.left->load && !bk.left->load->isWeight) result += Length(*bk.left->load->data.binKor);
    }
    return result;
}

void Skip (std::string& str, int n) {
    if (str.length() >= n) {
        str = str.substr(n);
    }
}

short GetNumber (string& str) {
    string strnum = "";
    while (isdigit(str[0])) {
        strnum += str[0];
        Skip(str, 1);
    }
    return stoi(strnum);
}

BinKor* ScanBinKor (string& input);

// short|BinKor
Load* ScanLoad (string& input) {
    Load* load = new Load;
    load->isWeight = input[0] != '(';
    if (load->isWeight) {
        load->data.weight = GetNumber(input);
    }
    else {
        load->data.binKor = ScanBinKor(input);
    }
    return load;
}

// (short Load)
Side* ScanSide (string& input) {
    Side* side = new Side;
    Skip(input, 1);
    side->length = GetNumber(input);
    Skip(input, 1);
    side->load = ScanLoad(input);
    Skip(input, 1);
    return side;
}

// (Side Side)
BinKor* ScanBinKor (string& input) {
    BinKor* binKor = new BinKor;
    Skip(input, 1);
    binKor->left = ScanSide(input);
    Skip(input, 1);
    binKor->right = ScanSide(input);
    Skip(input, 1);
    return binKor;
}

int main () {
    string input = "((2 2) (1 1))";
    /*cout << Length(*ScanBinKor(input)) << endl;
    input = "((1 ((11 11) (12 12))) (2 2))";
    cout << Length(*ScanBinKor(input)) << endl;
    input = "((1 ((11 11) (12((121 121) (122 122))))) (2 ((21 21) (22 22))))";
    cout << Length(*ScanBinKor(input)) << endl;*/
    cout << "Please enter binkor in the following format: ((a b) (c d))\nwhere a, c are whole numbers\nb, d - whole numbers or binkors" << endl;
    cin >> input; // Ручной ввод
    cout << Length(*ScanBinKor(input)) << endl;
    return 0;
}