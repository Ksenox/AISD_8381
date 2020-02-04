#include "huffman.h"

Huffman::Huffman()
{

}

MinHeapNode* Huffman::newNode(char data, unsigned freq)
{
    MinHeapNode* temp = new MinHeapNode;
    temp->left = temp->right = nullptr;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

MinHeap* Huffman::createMinHeap(unsigned capacity) {

    MinHeap* minHeap = new MinHeap;
    // current size is 0
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}
void Huffman::swapMinHeapNode( MinHeapNode** a, MinHeapNode** b){
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void Huffman::minHeapify(MinHeap* minHeap, int idx){

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left <static_cast<int>(minHeap->size) && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < static_cast<int>(minHeap->size) && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int Huffman::isSizeOne(MinHeap* minHeap){
    return (minHeap->size == 1);
}

MinHeapNode* Huffman::extractMin(MinHeap* minHeap) {
    MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0]
        = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

void Huffman::insertMinHeap( MinHeap* minHeap, MinHeapNode* minHeapNode) {

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void Huffman::buildMinHeap( MinHeap* minHeap){
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int Huffman::isLeaf( MinHeapNode* root){
    return !(root->left) && !(root->right);
}

MinHeap* Huffman::createAndBuildMinHeap(char data[], int freq[], int size){

    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

MinHeapNode* Huffman::buildHuffmanTree(string input){
    int len = static_cast<int>(input.length());
    char *data = new char[len];
    int *freq = new int[len];
    int size = 0;
    take_data_freq(input,data,freq, &size);

    MinHeapNode *left, *right, *top;

    // Step 1: Create a min heap of capacity
    // equal to size. Initially, there are
    // modes equal to size.
     MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap)) {

        // Step 2: Extract the two minimum
        // freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3: Create a new internal
        // node with frequency equal to the
        // sum of the two nodes frequencies.
        // Make the two extracted node as
        // left and right children of this new node.
        // Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        top = newNode('*', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    // Step 4: The remaining node is the
    // root node and the tree is complete.
    return extractMin(minHeap);
}
string Huffman::printArr(int *arr, int n)
{
    string out;
    int i;
    for (i = 0; i < n; ++i){
        if(arr[i] == 1 )
            out.append(1,'1');
        else if(arr[i] == 0)
            out.append(1,'0');
    }
    out+= "\n";
    return out;
}

string Huffman::printCodes( MinHeapNode* root, int *arr, int top){

    string out;

    if (root->left) {
        arr[top] = 0;
        out += printCodes(root->left, arr, top + 1);
    }

    if (root->right) {

        arr[top] = 1;
        out += printCodes(root->right, arr, top + 1);
    }

    if (isLeaf(root)) {
        out+= '\t';
        out += root->data;
        out +='\t';
        out += "->";
        out += '\t';
        out += printArr(arr, top);
    }
    return out;
}

string Huffman::decode(MinHeapNode* root, string s, int *fl)
{
    *fl = 1;
    string ans = "";
    string step ;
    int id = 1;
    struct MinHeapNode* curr = root;
    int len = static_cast<int>(s.size());
    for (int i=0; i < len; i++)
    {
        if (s[i] == '0')
           curr = curr->left;
        else
           curr = curr->right;
        if (curr->left==nullptr and curr->right==nullptr)
        {
            if(i == len -1)
                *fl = 0;
            step += "Step " + std::to_string(id) + ":      ";
            id++;
            ans += curr->data;
            step += ans;
            step += "   ";
            step.append(s,i+1,len-i-1);
            step += '\n';
            curr = root;
        }
    }
    string buffer = "Result :";
    buffer += '\t';
    buffer += s + "   ->   ";
    ans = ans + '\n';
    ans = buffer + ans;
    ans += '\n';
    ans += step;
    return ans;
}

void Huffman::take_data_freq(string input, char* data, int* freq, int* size){
    int id = 1;
    data[0] = input[0];
    for(int i = 0; i <static_cast<int>(input.length()) ; i++){
        int flag = 0;
        for(int j = 0; j < id; j++){
            if(data[j] == input[i]){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            data[id] = input[i];
            id++;
        }
    }
    *size = id;
    data[id] = '\0';
    freq[id] = '\0';
    for(int i = 0; i < id; i++){
        freq[i] = count(input.begin(),input.end(),data[i]);
    }
    return;
}
