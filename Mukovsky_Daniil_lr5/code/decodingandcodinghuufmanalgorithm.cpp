#include "decodingandcodinghuufmanalgorithm.h"
Node* getTreeFromSymbol(char symbol, Symbol** symbols) {
    int i = symbol;
    Symbol* symbolPtr = symbols[i];
    if (!symbolPtr)
        return nullptr;
    return symbolPtr->tree;
}


void reverseCode(int* code, int codeSize) {
    if (code == nullptr) {
        return;
    }
    int* start = code;
    int* end = code + (codeSize - 1);
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int* codeOfNode(Node* node, int* n) {
    Node* current = node;

    int* code = new int[HOW_MANY_POSSIBLE_SYMBOLS * 2];

    int i = 0;

    while (!current->isRoot) {
        Node* parent = current->parent;
        code[i] = (parent->left == current) ? 0 : 1;
        current = current->parent;
        i++;
    }
    reverseCode(code, i);

    *n = i;
    return code;
}

Node* addChild(Node* parent, int isZero, int isRoot, char symbol, int value, bool isLast) {
    Node* node = new Node;
    node->isZero = isZero;
    node->isRoot = isRoot;
    node->isLast = isLast;
    node->isLeaf = 1;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->symbol = symbol;
    node->value = value;
    return node;
}

Node* addSymbol(char symbol, Node** zeroNode, Symbol** symbols) {
    Node* leftNode = addChild(*zeroNode, 1, 0, '\n', 0,false);
    Node* rightNode = addChild(*zeroNode, 0, 0, symbol, 0,false);

    (*zeroNode)->isZero = 0;
    (*zeroNode)->isLeaf = 0;
    (*zeroNode)->isLast = false;
    (*zeroNode)->left = leftNode;
    (*zeroNode)->right = rightNode;
    int i = symbol;
    symbols[i] = new Symbol;
    symbols[i]->symbol = symbol;
    symbols[i]->tree = rightNode;

    *zeroNode = leftNode;
    return rightNode;
}




template <typename T>
std::string NumberToString(T Number)
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}


void addCodeToOut(std::string& outp,std::string& resultCode, int codeSize, int* symbCode, char byte, bool flag) {
    outp=outp+"Current symbol: "+byte+"\n"+"Its code: ";
    for (int i = 0; i < codeSize; i++) {
        outp += NumberToString(symbCode[i]);
        resultCode += NumberToString(symbCode[i]);
    }
    if (flag){
        addAsciiToOut(outp,resultCode,byte);
    }
    outp+="\n";
}


void addAsciiToOut(std::string& outp,std::string& resultCode, int byte) {
    for (int i = 0; i < 8; i++) {
        int some = byte;
        some = some & 128;
        (some == 128) ? outp += "1" : outp += "0";
        (some == 128) ? resultCode += "1" : resultCode+= "0";
        byte <<= 1;
    }


}

void encode(char* input, std::string& output, int inputSize, BinTree* BT,std::string& resultCode) {
    Node* zeroNode = BT->getRoot();
    Symbol** symbols = new Symbol * [HOW_MANY_POSSIBLE_SYMBOLS];

    for (int j = 0; j < HOW_MANY_POSSIBLE_SYMBOLS; j++) {
        symbols[j] = nullptr;
    }
    bool flag = false;


    char currByte;
    Node* newNode = nullptr;
    Node* symbolTree = nullptr;
    for (int i = 0; i < inputSize; i++) {
        currByte = input[i];
        symbolTree = getTreeFromSymbol(currByte, symbols);
        if (symbolTree) {
            int codeSize;
            int* symbolCode = codeOfNode(symbolTree, &codeSize);
            addCodeToOut(output,resultCode, codeSize, symbolCode,currByte,false);
            BT->updateTree(symbolTree);
            flag = false;
            delete symbolCode;
        }
        else {
            int codeSize;
            int* zeroCode = codeOfNode(zeroNode, &codeSize);
            addCodeToOut(output,resultCode, codeSize, zeroCode,currByte,true);
           // addAsciiToOut(output, currByte);
            newNode = addSymbol(currByte, &zeroNode, symbols);
            BT->updateTree(newNode);
            flag = true;
            delete zeroCode;
        }
    }

    if (flag && newNode){
        newNode->isLast = true;
    }
    else if (!flag && symbolTree){
         symbolTree->isLast = true;
    }
    for (int j = 0; j < HOW_MANY_POSSIBLE_SYMBOLS; j++) {
        delete symbols[j];
    }
    delete[] symbols;
}
