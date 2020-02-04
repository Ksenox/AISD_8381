#include "huffman.h"

huffman::huffman()
{

}

MinHeapNode* huffman::newNode(char data, unsigned freq)
{
    MinHeapNode* temp = new MinHeapNode;
    temp->left = temp->right = nullptr;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

MinHeap* huffman::createMinHeap(unsigned capacity) {

    MinHeap* minHeap = new MinHeap;
    // current size is 0
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}
void huffman::swapMinHeapNode( MinHeapNode** a, MinHeapNode** b){
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void huffman::minHeapify(MinHeap* minHeap, int idx){

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

int huffman::isSizeOne(MinHeap* minHeap){
    return (minHeap->size == 1);
}

MinHeapNode* huffman::extractMin(MinHeap* minHeap) {
    MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0]
        = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

void huffman::insertMinHeap( MinHeap* minHeap, MinHeapNode* minHeapNode) {

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void huffman::buildMinHeap( MinHeap* minHeap){
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int huffman::isLeaf( MinHeapNode* root){
    return !(root->left) && !(root->right);
}

MinHeap* huffman::createAndBuildMinHeap(char data[], int freq[], int size){

    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

MinHeapNode* huffman::buildHuffmanTree(string input){
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

string huffman::printArr(int *arr, int n)
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

string huffman::printCodes( MinHeapNode* root, int *arr, int top){

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
        out += " -> ";
        out += printArr(arr, top);
    }
    return out;
}

string huffman::take_encode(MinHeapNode* root, int *arr, int top, string input){
    string out;
    int len = input.size();
    for(int i = 0; i < len; i++){
        out += take_encode_2(root,arr,top,input[i]);
    }
    return out;
}

string huffman::take_encode_2(MinHeapNode* root, int *arr, int top, char input){
    string out;
    if (root->left) {
        arr[top] = 0;
        out += take_encode_2(root->left, arr, top + 1,input);
    }

    if (root->right) {

        arr[top] = 1;
        out += take_encode_2(root->right, arr, top + 1,input);
    }

    if (isLeaf(root) && input == root->data) {
        out += take_encode_3(arr,top);
    }
    return out;
}

string huffman::take_encode_3(int *arr, int n)
{
    string out;
    int i;
    for (i = 0; i < n; ++i){
        if(arr[i] == 1 )
            out.append(1,'1');
        else if(arr[i] == 0)
            out.append(1,'0');
    }
    return out;
}
string huffman::decode(MinHeapNode* root, string s,string youranswer)
{
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
            step += "+  Step " + std::to_string(id) + ":      ";
            id++;
            ans += curr->data;
            step += ans;
            step += "   ";
            step.append(s,i+1,len-i-1);
            step += '\n';
            curr = root;
        }
    }
    string buffer = ">   Check :   \n\n";
    buffer += "\t+Your answer : ";
    buffer += youranswer;
    buffer += "\n\t+Result : ";
    buffer += ans;
    if(ans == youranswer)
        buffer += "\n\n\t->Your answer is correct!\n\n";
    else
        buffer += "\n\n\t->Your answer inccorect!\n\n";

    buffer += ">   Steps:\n\n";
    buffer += step;
    return buffer;
}

void huffman::take_data_freq(string input, char* data, int* freq, int* size){
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
