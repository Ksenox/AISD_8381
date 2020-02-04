#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define MAX_TREE_HT 100


typedef struct MinHeapNode{
    char data;
    unsigned freq;
    MinHeapNode *left, *right;
}MinHeapNode;

typedef struct MinHeap{
    unsigned size;
    unsigned capacity;
    MinHeapNode** array;
}MinHeap;

class huffman
{
public:
    huffman();
    MinHeapNode* newNode(char data, unsigned freq);
    MinHeap* createMinHeap(unsigned capacity);
    void swapMinHeapNode( MinHeapNode** a, MinHeapNode** b);
    void minHeapify(MinHeap* minHeap, int idx);
    int isSizeOne(MinHeap* minHeap);
    MinHeapNode* extractMin(MinHeap* minHeap) ;
    void insertMinHeap( MinHeap* minHeap, MinHeapNode* minHeapNode);
    void buildMinHeap( MinHeap* minHeap);
    int isLeaf( MinHeapNode* root);
    MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);
    MinHeapNode* buildHuffmanTree(string input);
    string decode(MinHeapNode* root, string s,string youranswer);
    void take_data_freq(string input, char* data, int* freq, int* size);
    string printCodes( MinHeapNode* root, int arr[], int top);
    string printArr(int arr[], int n);
    string take_encode(MinHeapNode* root, int *arr, int top,string input);
    string take_encode_3(int *arr, int n);
    string take_encode_2(MinHeapNode* root, int *arr, int top, char input);
};

#endif // HUFFMAN_H
