#include "forest.h"

// Viết 1 hàm loại bỏ dấu cách trong dữ liệu đầu vào

Forest *takeForest(char* arr, int len){
    int countTree = CountTree(arr,len);
    Forest *forest = createForest(countTree);// Khoi tao countTree Tree

    int i = 1;
    for(int j = 0; j < forest->count; j++){
        //Crete root of tree
        int deep = DeepOfTree(arr,i,len);
        int total = BranchOfNode(arr,i,len);
        Node *root = createNode(arr[i],true,total);
        if(total>0){
            i+=2;
        }
        AppendNode(root,arr,i,len,true,total);
        forest->tree[j]->root = root;
        forest->tree[j]->deep = deep;
    }

    return forest;
}


Node *AppendNode(Node *node,char* arr,int& i,int len, bool isAlpha,int total){// i = vi tri cua root
    /* ket thuc ham nay , gia tri cua i = vi tri cua root of second tree*/
    if(total == 0){
        if(isalpha(arr[i+1]))
            i++;
        else {
            i++;
            while(arr[i] == ')'){
                i++;
            }
        }
        return node;
    }
    for(int k = 0; k < total; k++){
        Node *temp = new Node;
        int countNode = BranchOfNode(arr,i,len);
        temp = createNode(arr[i],isAlpha,countNode);
        if(countNode > 0){
            i+=2;
        }
        AppendNode(temp,arr,i,len,isAlpha,countNode);
        node->Tnode[k] = temp;
    }
    return node;
}
int DeepOfTree(char *arr, int i , int len){// i = vi tri cua root cua tree
    if(arr[i+1]!='(')
        return 0;
    int delta = 0;
    int deep = delta;
    int flag = i;
    for(int j = i; j<len; j++){
        if(arr[j] == '('){
            delta += 1;
            deep = delta>deep?delta:deep;
        }
        else if(arr[j] == ')')
            delta -= 1;
        if(delta == 0 && j != flag)
            return deep+1;
    }
}

/* function checked */
int CountTree(char* arr, int len){
        int countTree = 0;
        int Delta = 0; //hieu cua ( va )
        for(int i = 0; i < len; i++){
                if(arr[i] == '(')
                        Delta += 1;
                else if(arr[i] == ')')
                        Delta -= 1;
                if(Delta == 1 && arr[i] != ')')
                        countTree += 1;
        }

        return countTree-1;
}


int CheckErr(char *arr, int len){

    for(int i = 0; i < len; i++){
        if(isalpha(arr[i]) == false && arr[i] != ')' && arr[i] != '(')
            return 3; // 3- Input incorrect
    }
    if(!isalpha(arr[1]))
        return 5;

    int count = 0;
    for(int i  = 0; i < len; i++){
        if(count < 0)
            return 4; // thua dau ')'
        if(arr[i] == '(')
            count++;
        else if(arr[i] == ')')
            count--;
        if(count == 0 && i <len -1)
            return 6;
    }
    if(count != 0)
                return 1; // 1- thieu ( hoac )

    for(int i = 0; i < len; i++){
        if(arr[i] =='(' && arr[i+1] == ')')
            return 2; // 2- tree empty
    }

    return 0;
}


/*Function checked*/
int BranchOfNode(char *arr, int i, int len){// i = vi tri cua Root cua Tree
        int count = 0;
        int flag = i;
        int delta = 0;
        if(arr[i+1] != '(') // TH ab => branch = 0
                return 0;
        else{
                for(int j = i+1; j < len ; j++){
                        if(arr[j] == '(')
                                delta += 1;
                        else if(arr[j] == ')'){
                                delta -= 1;
                                if(delta == 0 && j != flag)
                                        return count;
                        }
                        else if(isalpha(arr[j]) && delta == 1){
                                count++;
                        }
                }
        }
}


Forest *createForest(int count){
    Forest *forest = new Forest;
    forest->count = count;
    forest->tree = new (Tree*);
    for(int i = 0; i<count; i++){
        forest->tree[i] = new Tree;
        forest->tree[i] = createTree();
    }
    return forest;
}

Tree *createTree(){
    Tree *tree = new Tree;
    tree->root = nullptr;
    tree->deep = 0;
    return tree;
}

Node *createNode(char info,bool isAlpha, int total){
    Node *node = new Node;
    node->info = info;
    node->isLeaf = isAlpha;
    node->total = total;
    node->Tnode = new (Node*);
        for(int j = 0; j < total; j++){
            node->Tnode[j] = new Node;
                node->Tnode[j] = nullptr;
        }
    return node;
}
void takeInfoOfNode(Node *root, string &out){
        out += "( ";
        out.append(1,root->info);
        out+=" ";
        for(int i = 0; i < root->total; i++){
                takeInfoOfNode(root->Tnode[i],out);
        }
        out += ") ";
}

