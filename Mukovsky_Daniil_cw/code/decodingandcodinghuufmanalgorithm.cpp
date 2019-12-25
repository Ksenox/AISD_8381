#include "decodingandcodinghuufmanalgorithm.h"


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

Node* addChild(Node* parent, bool isZero, bool isRoot, char symbol, int value) {
    Node* node = new Node;
    node->isZero = isZero;
    node->isRoot = isRoot;
    node->isHere = false;
    node->isLast = false;
    node->isSwapped = false;
    node->isLeaf = true;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->symbol = symbol;
    node->value = value;
    return node;
}

Node* addSymbol(char symbol, Node** zeroNode) {
    Node* leftNode = addChild(*zeroNode, true, false, '\n', 0);
    Node* rightNode = addChild(*zeroNode, false, false, symbol, 0);

    (*zeroNode)->isZero = false;
    (*zeroNode)->isLeaf = false;
    (*zeroNode)->isLast = false;
    (*zeroNode)->isSwapped = false;
    (*zeroNode)->isHere = false;
    (*zeroNode)->left = leftNode;
    (*zeroNode)->right = rightNode;

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
    outp =outp+ "Symbol :["+byte+"]\nIts code: ";
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


void addNewNode(BinTree* tree,Node*& zeroNode,char symbol,std::string& output,std::string& resultCode){
    Node* symbolTree = nullptr;
    Node* newNode = nullptr;
    bool flag = false;
    if(tree->findNodeSymb(tree->getRoot(),symbolTree,symbol,flag)){
        int codeSize;
        int* symbolCode = codeOfNode(symbolTree, &codeSize);
        addCodeToOut(output,resultCode, codeSize, symbolCode,symbol,false);
        recalculationNodeValue(symbolTree);
        delete symbolCode;
    }
    else{
        int codeSize;
        int* zeroCode = codeOfNode(zeroNode, &codeSize);
        addCodeToOut(output,resultCode, codeSize, zeroCode,symbol,true);
        newNode = addSymbol(symbol, &zeroNode);
        recalculationNodeValue(newNode);
        delete zeroCode;
    }
    if (!flag && newNode){
        newNode->isLast = true;
    }
    else if (flag && symbolTree){
         symbolTree->isLast = true;
    }
}



void encode(char* input, std::string& output, int inputSize, BinTree* tree,std::string& resultCode) {
    Node* zeroNode = tree->getRoot();
    bool flag = false;
    char currByte;
    Node* newNode = nullptr;
    Node* symbolTree = nullptr;
    for (int i = 0; i < inputSize; i++) {
        currByte = input[i];
        symbolTree = nullptr;
        flag = false;
        if (tree->findNodeSymb(tree->getRoot(),symbolTree,currByte,flag)) {
            int codeSize;
            int* symbolCode = codeOfNode(symbolTree, &codeSize);
            addCodeToOut(output,resultCode, codeSize, symbolCode,currByte,false);
            recalculationNodeValue(symbolTree);
            while(tree->needUpdateTree()){
                tree->swapNodesForOrdering();
            }
            delete symbolCode;
        }
        else {
            int codeSize;
            int* zeroCode = codeOfNode(zeroNode, &codeSize);
            addCodeToOut(output,resultCode, codeSize, zeroCode,currByte,true);
            newNode = addSymbol(currByte, &zeroNode);
            recalculationNodeValue(newNode);
            while(tree->needUpdateTree()){
                tree->swapNodesForOrdering();
            }
            delete zeroCode;
        }

    }

    if (!flag && newNode){
        newNode->isLast = true;
    }
    else if (flag && symbolTree){
         symbolTree->isLast = true;
    }

}

char readByte(char* input,int& curIndex, int inputSize,std::string& output){
    int j =0;
    int result = 0;
    int multi = 128;
    for(int i = curIndex; i<inputSize&&j<8;i++){
        j++;
        if(input[i]=='1'){
            result+=multi;
            output+="1";
        }
        else{
            output+="0";
        }
        multi/=2;
    }
    curIndex+=8;
    char symb = result;
    return symb;
}

bool decode(char* input, std::string& output, int inputSize, BinTree* tree,std::string& resultCode){
    Node* node = tree->getRoot();
    Node* zeroNode;
    int i =0;
    char symb;
    while(i!=inputSize){
        node = tree->getRoot();
        output +="Code: ";
        while(!node->isLeaf && i<=inputSize){
            if (input[i] == '0'){
                node = node->left;
                output+="0";
            }else if(input[i] == '1'){
                node = node->right;
                output+="1";
            }
            if (i == inputSize) return false;
            i++;
        }

        if (!node->isLeaf) return false;
        if (node->isZero){
            if (inputSize<i+8) return false;
            symb = readByte(input,i,inputSize,output);
            tree->getZeroNode(tree->getRoot(),zeroNode);
            node = addSymbol(symb, &zeroNode);
            recalculationNodeValue(node);
        }
        else{
            symb = node->symbol;
            recalculationNodeValue(node);
        }

        output= output+"\nSymbol: ["+symb+"]\n";
        resultCode+=symb;
        while(tree->needUpdateTree()){
            tree->swapNodesForOrdering();
        }
    }
    return true;
}
bool readCurNode(char* input,int& currentInputLen,int inputLen,std::string& output,std::string& resultCode,Node*& curNode,BinTree* tree, int& diffCurrentInLen){
    char symb;
    diffCurrentInLen = currentInputLen;
    if (curNode->isZero){
        if (inputLen<currentInputLen+8){
            return false;
        }
        symb = readByte(input,currentInputLen,inputLen,output);
        Node* zeroNode = nullptr;
        tree->getZeroNode(tree->getRoot(),zeroNode);
        curNode = addSymbol(symb, &zeroNode);
        recalculationNodeValue(curNode);
        int some = currentInputLen - diffCurrentInLen;
        diffCurrentInLen = some;
    }
    else{
        symb = curNode->symbol;
        recalculationNodeValue(curNode);
        diffCurrentInLen = 0;
    }
    output= output+"\nSymbol: ["+symb+"]\n";
    resultCode+=symb;
    return true;
}

void readOneBit(Node*& curNode,std::string& output,char* input,int& currentInputLen){
    if (input[currentInputLen] == '0'){
        curNode = curNode->left;
        curNode->isHere = true;
        output+="0";
    }
    else{
        curNode = curNode->right;
        curNode->isHere = true;
        output+="1";
    }
    currentInputLen++;
    return;
}
