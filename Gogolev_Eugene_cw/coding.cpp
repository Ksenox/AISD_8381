#include "coding.h"

void generate_pack(types t, methods m, int length, int count, string &issue, string &answer) {
    for (int i = 0; i < count; i++) {
        // TODO описание задания и форматирование строк, чтоб красиво
        string current = "Variant " + to_string(i) + "\n";
        string one_issue = current;
        string one_answer = current;
        generate_var(t, m, length, one_issue, one_answer);
        issue += one_issue + "\n----------------\n";
        answer += one_answer + "\n----------------\n";
    }
}

void generate_var(types t, methods m, int length, string &issue, string &answer) {
    string current_issue = "";
    issue += "Apply operation to the text:\n";
    for (int i = 0; i < length; i++) {
        current_issue += 'a' + rand() % ('z' - 'a');
    }
    string res_freqs = "Frequences:\n";
    string res_codes = "Codes:\n";
    string res = "Encoded text:\n";
    switch (m) {
    case haffman:
        encode_haffman(current_issue, res_freqs, res_codes, res);
        switch (t) {
        case coding:
            issue += "\nHaffman encoding\n";
            issue += current_issue;
            answer += res_freqs + res_codes + res;
            break;
        case decoding:
            issue += "\nHaffman decoding\n";
            issue += res_freqs + res;
            answer += res_codes + current_issue;
            break;
        }
        break;
    case fano_shennon:
        encode_fano_shennon(current_issue, res_freqs, res_codes, res);
        switch (t) {
        case coding:
            issue += "\nFano Shennon encoding\n";
            issue += current_issue;
            answer += res_freqs + res_codes + res;
            break;
        case decoding:
            issue += "\nFano Shennon decoding\n";
            issue += res_freqs + res;
            answer += res_codes + current_issue;
            break;
        }
        break;
    }
}

void encode_haffman(string &input, string& res_freqs, string& res_codes, string& res) {
    //Freqs
    char* chars = new char[input.length()];
    int* freqs = new int[input.length()];
    int count = 0;
    calc_freqs(input, chars, freqs, count);
    for (int i = 0; i < count; i++) {
        string s(1, chars[i]);
        res_freqs += s + ":\t" + to_string(freqs[i]) + "\n";
    }
    //Encoding
    string* result_codes = new string[count];
    char* result_chars = new char[count];
    HuffmanCodes(res_codes, result_chars, result_codes, chars, freqs, count);
    //Result
    for (int i = 0; i < input.length(); i++) {
        for (int k = 0; k < count; k++) {
            if (result_chars[k] == input[i]) {
                res += result_codes[k];
                break;
            }
        }
    }
}

void encode_fano_shennon(string &input, string& res_freqs, string& res_codes, string& res) {
    //Freqs
    char* chars = new char[input.length()];
    int* freqs = new int[input.length()];
    int count = 0;
    calc_freqs(input, chars, freqs, count);
    node* nodes = new node[count];
    for (int i = 0; i < count; i++) {
        string s(1, chars[i]);
        res_freqs += s + ":\t" + to_string(freqs[i]) + "\n";
        nodes[i].sym = chars[i];
        nodes[i].pro = freqs[i];
        nodes[i].top = -1;
    }
    //Encoding
    shannon(0, count - 1, nodes);
    for (int i = 0; i < count; i++) {
        string s(1, nodes[i].sym);
        res_codes += s + ":\t";
        for (int j = 0; j <= nodes[i].top; j++) nodes[i].code += to_string(nodes[i].arr[j]);
        res_codes += nodes[i].code + "\n";
    }
    //Result
    for (int i = 0; i < input.length(); i++) {
        for (int k = 0; k < count; k++) {
            if (nodes[k].sym == input[i]) {
                res += nodes[k].code;
                break;
            }
        }
    }
}

void write_to_file(string filename, string &data) {
    cout << data;
    cout << &data;
    ofstream myfile;
    myfile.open(filename);
    myfile << data;
    myfile.close();
}

void calc_freqs(string &input, char chars[], int freqs[], int& count)
{
    for (int i = 0; i < input.length(); i++) {
        int k;
        for (k = 0; k < count; k++) {
            if (chars[k] == input[i]) {
                freqs[k]++;
                break;
            }
        }
        if (k == count) {
            chars[count] = input[i];
            freqs[count] = 1;
            count++;
        }
    }
    //bubble
    for (int i = 0; i < count - 1; i++) {
        for (int k = 0; k < count - i - 1; k++) {
            if (freqs[k] > freqs[k+1]) {
                int temp = freqs[k];
                freqs[k] = freqs[k+1];
                freqs[k+1] = temp;
                char temp2 = chars[k];
                chars[k] = chars[k+1];
                chars[k+1] = temp2;
            }
        }
    }
}


// Haffman encoding

MinHeapNode* newNode(char data, unsigned freq) {
    MinHeapNode* temp = new MinHeapNode;
    temp->left = temp->right = nullptr;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* minHeap = new MinHeap;
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = new MinHeapNode*[minHeap->capacity];
    return minHeap;
}

void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

MinHeapNode* extractMin(MinHeap* minHeap) {
    MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(MinHeap* minHeap, MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i) minHeapify(minHeap, i);
}

MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i) minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    MinHeapNode *left, *right, *top;
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        // '$' is a special value for internal nodes, not used
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void printArr(string& code, int arr[], int n) {
    for (int i = 0; i < n; ++i) code += to_string(arr[i]);
}

void printCodes(string& result, char codes_chars[], string* codes, int& ind, MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(result, codes_chars, codes, ind, root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(result, codes_chars, codes, ind, root->right, arr, top + 1);
    }
    if (!(root->left) && !(root->right)) {
        string s(1, root->data);
        result += s + ": ";
        codes_chars[ind] = root->data;
        printArr(codes[ind], arr, top);
        result += codes[ind] + "\n";
        ind++;
    }
}

void HuffmanCodes(string& result, char result_chars[], string result_codes[], char data[], int freq[], int size) {
    MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[256];
    int top = 0;
    int ind = 0;
    printCodes(result, result_chars, result_codes, ind, root, arr, top);
}

// Fano-Shennon

void shannon(int l, int h, node p[]) {
    int pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
    int i, k = 0, j;
    if ((l + 1) == h || l == h || l > h) {
        if (l == h || l > h)
            return;
        p[h].arr[++(p[h].top)] = 0;
        p[l].arr[++(p[l].top)] = 1;
        return;
    }
    else {
        for (i = l; i <= h - 1; i++) pack1 = pack1 + p[i].pro;
        pack2 = pack2 + p[h].pro;
        diff1 = pack1 - pack2;
        if (diff1 < 0) diff1 = diff1 * -1;
        j = 2;
        while (j != h - l + 1) {
            k = h - j;
            pack1 = pack2 = 0;
            for (i = l; i <= k; i++) pack1 = pack1 + p[i].pro;
            for (i = h; i > k; i--) pack2 = pack2 + p[i].pro;
            diff2 = pack1 - pack2;
            if (diff2 < 0) diff2 = diff2 * -1;
            if (diff2 >= diff1) break;
            diff1 = diff2;
            j++;
        }
        k++;
        for (i = l; i <= k; i++) p[i].arr[++(p[i].top)] = 1;
        for (i = k + 1; i <= h; i++) p[i].arr[++(p[i].top)] = 0;

        shannon(l, k, p);
        shannon(k + 1, h, p);
    }
}

