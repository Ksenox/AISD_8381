#include <bin_struct.h>

BinTree::BinTree(){
    Head = nullptr;
    Current = Head;
}
int BinTree::max_depth(Node *hd){
    if (hd == NULL) return 0;
    else{
        int lDepth = max_depth(hd->left);
        int rDepth = max_depth(hd->right);

        if (lDepth > rDepth)  return(lDepth + 1);
        else return(rDepth + 1);
    }
}
int BinTree::getsize(Node* p) // обертка для поля size, работает с пустыми деревьями (t=NULL)
{
    if( !p ) return 0;
    return p->size;
}

void BinTree::fixsize(Node* p) // установление корректного размера дерева
{
    p->size = getsize(p->left)+getsize(p->right)+1;
}

 Node* BinTree::rotateright(Node* p) // правый поворот вокруг узла p
{
    Node* q = p->left;
    if( !q ) return p;
    p->left = q->right;
    q->right = p;
    q->size = p->size;
    fixsize(p);
    return q;
}
Node* BinTree::rotateleft(Node* q) // левый поворот вокруг узла q
{
    Node* p = q->right;
    if( !p ) return q;
    q->right = p->left;
    p->left = q;
    p->size = q->size;
    fixsize(q);
    return p;
}
Node* BinTree::insertroot(Node* p, int k) // вставка нового узла с ключом k в корень дерева p
{
    if( !p ) return new Node(k);
    if( k < p->key )
    {
        p->left = insertroot(p->left,k);
        return rotateright(p);
    }
    else
    {
        p->right = insertroot(p->right,k);
        return rotateleft(p);
    }
}
Node* BinTree::insert(Node* p, int k) // рандомизированная вставка нового узла с ключом k в дерево p
{
    if( !p ) return new Node(k);
    if( rand()%(p->size+1)==0 )
        return insertroot(p,k);
    if( p->key>k )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    fixsize(p);
    return p;
}
Node*BinTree:: join(Node* p, Node* q) // объединение двух деревьев
{
    if( !p ) return q;
    if( !q ) return p;
    if( rand()%(p->size+q->size) < p->size )
    {
        p->right = join(p->right,q);
        fixsize(p);
        return p;
    }
    else
    {
        q->left = join(p,q->left);
        fixsize(q);
        return q;
    }
}
Node*BinTree::remove(Node* p, int k) // удаление из дерева p первого найденного узла с ключом k
{
    if( !p ) return p;
    if( p->key==k )
    {
        Node* q = join(p->left,p->right);
        delete p;
        return q;
    }
    else if( k<p->key )
        p->left = remove(p->left,k);
    else
        p->right = remove(p->right,k);
    return p;
}
