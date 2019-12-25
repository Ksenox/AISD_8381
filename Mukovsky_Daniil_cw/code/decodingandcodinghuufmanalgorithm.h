#ifndef DECODINGANDCODINGHUUFMANALGORITHM_H
#define DECODINGANDCODINGHUUFMANALGORITHM_H
#include "bintree.h"
//Node* getTreeFromSymbol(unsigned char symbol, Symbol **symbols);
void reverseCode(int *code,int codeSize);
int* codeOfNode(Node *node, int *n);
Node* addChild(Node *parent, bool isZero, bool isRoot, char symbol, int value, bool isLast);
Node* addSymbol(char symbol, Node** zeroNode);
void addCodeToOut(std::string&outp,std::string& resultCode,int codeSize,int*symbCode, char byte,bool flag);
void addAsciiToOut(std::string&outp,std::string& resultCode,int byte);
void encode(char* input, std::string& output, int inputSzie,BinTree* root,std::string& resultCode);
void addNewNode(BinTree* tree,Node*& zeroNode,char symbol,std::string& output,std::string& resultCode);
bool decode(char* input, std::string& output, int inputSize, BinTree* tree,std::string& resultCode);
char readByte(char* input,int& curIndex, int inputSize,std::string& output);
void readOneBit(Node*& curNode,std::string& output,char* input,int& currentInputLen);
bool readCurNode(char* input,int& currentInputLen,int inputLen,std::string& output,std::string& resultCode,Node*& curNode,BinTree* tree,int& diffCurrentInLen);
#endif // DECODINGANDCODINGHUUFMANALGORITHM_H
