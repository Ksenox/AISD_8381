#ifndef DECODINGANDCODINGHUUFMANALGORITHM_H
#define DECODINGANDCODINGHUUFMANALGORITHM_H
#include "bintree.h"
Node* getTreeFromSymbol(unsigned char symbol, Symbol **symbols);
void reverseCode(int *code,int codeSize);
int* codeOfNode(Node *node, int *n);
Node* addChild(Node *parent, int isZero, int isRoot, unsigned char symbol, int value, int order);
Node* addSymbol(unsigned char symbol, Node** zeroNode, Symbol **symbols);
void addCodeToOut(std::string&outp,std::string& resultCode,int codeSize,int*symbCode, char byte,bool flag);
void addAsciiToOut(std::string&outp,std::string& resultCode,int byte);
void encode(char* input, std::string& output, int inputSzie,BinTree* root,std::string& resultCode);



#endif // DECODINGANDCODINGHUUFMANALGORITHM_H
