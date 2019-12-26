#ifndef CODING_H
#define CODING_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

enum methods {
    haffman,
    fano_shennon
};

enum types {
    coding,
    decoding
};

void generate_pack(types t, methods m, int length, int count, string& issue, string& answer);
void generate_var(types t, methods m, int length, string& issue, string& answer);
void encode_haffman(string &input, string& res_freqs, string& res_codes, string& res);
void encode_fano_shennon(string& input, string& res_freqs, string& res_codes, string& res);
void write_to_file(string filename, string& data);

void calc_freqs(string& input, char chars[], int freqs[], int& count);

// Haffman

struct MinHeapNode {
    char data;
    int freq;
    MinHeapNode *left, *right;
};

struct MinHeap {
    int size;
    int capacity;
    MinHeapNode** array;
};

MinHeapNode* newNode(char data, unsigned freq);
MinHeap* createMinHeap(unsigned capacity);
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int idx);
MinHeapNode* extractMin(MinHeap* minHeap);
void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode);
void buildMinHeap(MinHeap* minHeap);
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);
MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);
void printArr(string& code, int arr[], int n);
void printCodes(string& result, char codes_chars[], string* codes, int& ind, MinHeapNode* root, int arr[], int top);
void HuffmanCodes(string& result, char codes_chars[], string result_codes[], char data[], int freq[], int size);

// Fano-Shennon

struct node {
    char sym; //char
    int pro; //freq
    int arr[20];//tree depth
    int top;
    string code;
};

void shannon(int l, int h, node p[]);

#endif // CODING_H
