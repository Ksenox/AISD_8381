#include "forest.h"

Forest *takeforest(string str, int len){
    int countTree = CountTree(str,len);
    Forest *forest = createForest(countTree);//создать пустый лес
    int index = 0;
    for(int i = 0; i < forest->count; i++){
        int deep = DeepOfTree(str,index,len);
        string rootInfo = takeString(str,index,len);
        int total;
        if(deep == 0)
            total = 0;// Neu deepTree = 0 thi sau khi doc ham rootInfo index = vi tri dau tien cua Tree tiep theo
        else
            total = BranchOfNode(str,index,len);

        Node *root = createNode(rootInfo,total);
        AppendNode(root,str,index,len,total);
        forest->tree[i]->root = root;
        forest->tree[i]->deep = deep;
    }
    return forest;
}

Node *AppendNode(Node *root,string str, int &index,int len,int total){// index = vi tri dau tien cua cay con
    if(!total)
        return root;
    for(int i = 0; i < total; i++){
        int deep = DeepOfTree(str,index,len);
                string rootInfo = takeString(str,index,len);
                int total2;
                if(deep == 0)
                        total2 = 0;
                else
                        total2 = BranchOfNode(str,index,len);
                Node *temp = createNode(rootInfo,total2);
        AppendNode(temp,str,index,len,total2);
        root->Tnode[i] = temp;
        if(i == total -1)
            index++;
    }
    return root;
}

Node *createNode(string info, int total){
    Node *node = new Node;
    node->info = info;
    node->total = total;
    if(!total)
        node->Tnode = nullptr;
    node->Tnode = new (Node*);
    for(int j = 0; j < total; j++){
                node->Tnode[j] = new Node;
                node->Tnode[j] = nullptr;
        }
        return node;
}

int BranchOfNode(string str, int index, int len){//index = vi tri dau tien cua cay con
    int Delta = 0;
    int branch = 0;
    int i;
    for(i = index; i <len; i++){
        if(str[i] == '(')
            Delta++;
        else if(str[i] == ')')
            Delta--;
        if(Delta == 0)
            branch++;
        else if(Delta < 0)
            return branch;
    }
}

string takeString(string str,int &index,int len){
    string temp;
    int flag = index;
    for(index; index < len; index++){
        if(str[index] == '('){
            if(flag == index)
                continue;
            else
                            return temp;
        }
        else if(str[index] == ')'){ //  Lưu ý rằng đã kiểm tra lỗi empty :()
            index++;
            return temp;
        }
        else{
            temp.append(1,str[index]);
        }
    }
}

/*checked*/
int DeepOfTree(string str, int index, int len){// index = vi tri dau tien cua cay
        int Delta = 0;
        int deep = 0;
        for(int i = index; i < len; i++){
                if(str[i] == '('){
                        Delta += 1;
                        deep = Delta>deep?Delta:deep; // độ sâu  = max của delta - 1
                }
                else if(str[i] == ')')
                        Delta -= 1;
                if(Delta == 0)
                        return deep-1;
        }
}

Forest *createForest(int count){
    Forest *forest = new Forest;
        forest->count = count;
        forest->tree = new (Tree*);
        for(int i = 0; i<count; i++){
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


int CheckErr(string str, int len){
    int flagErr = 0;
    int Delta = 0;
    bool flagindex = false;

    for(int i = 0; i < len-2; i++){
        if( (str[i] == '(' || str[i] == ')') && str[i+1] == ' ' && (str[i+2] == '(' || str[i+2] == ')'))
            return 2;
    }

    for(int i = 0; i < len; i++){
        if(str[i] == '(')
            Delta++;
        else if (str[i] == ')') {
            Delta--;
        }
        if(Delta<0)
            return 1;// thua hoac thieu dau ( va )
        if(Delta > 0)
            flagindex = true;
    }
    if(Delta != 0 || flagindex == false)
        return 1;

    for(int i = 0; i < len-1; i++){
        if( (str[i] == '(' && str[i+1] == ')')
         || (str[i] == ')' && (str[i+1] != ')' && str[i+1] != '(')))
            return 1;
    }

    return flagErr;
}


/*checked*/
int CountTree(string str, int len){
    int countTree = 0;
    int Delta = 0;// Hieu cua '(' va ')'
    for(int i = 0; i < len; i++){
        if(str[i] == '(')
            Delta++;
        else if(str[i] == ')')
            Delta--;
        if(Delta == 0)
            countTree++;
    }
    return countTree;
}

void takeInfoOfNode(Node *root, string &out){
        out += "( ";
        out += root->info;
        out+=" ";
        for(int i = 0; i < root->total; i++){
                takeInfoOfNode(root->Tnode[i],out);
        }
        out += ") ";
}
