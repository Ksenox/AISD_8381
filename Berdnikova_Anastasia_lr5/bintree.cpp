#include "bintree.h"

int max_depth(Node *n, int i)
{
    if (!n) return i;
    int l = max_depth(n->left, i + 1);
    int r = max_depth(n->right, i + 1);
    if (l > r) return l;
    else return r;
}

bool parse_tree(Node*& n, std::string &s, int &i) {
    if (s.size() < 1) return true;
    std::size_t current, previous = 0;
    current = s.find(' ');
    int num;
    while (current != std::string::npos) {
        try
        {
            num = stoi(s.substr(previous, current - previous));
        }
        catch (...)
        {
            return true;
        }
        previous = current + 1;
        current = s.find(' ', previous);
        insert_old(n, num);
    }
    try
    {
        num = stoi(s.substr(previous, current - previous));
    }
    catch (...)
    {
        return true;
    }
    insert_old(n, num);
    return false;
}

void insert_old(Node*& n, int data)
{
    if (!n)
    {
        n = new Node();
        n->data = data;
    }
    else if (n->data > data)
    {
        insert_old(n->left, data);
    }
    else if (n->data < data)
    {
        insert_old(n->right, data);
    }
}

void remove_old(Node *&n, int data)
{
    if (!n) return;
    if (data < n->data)
    {
        remove_old(n->left, data);
    }
    else if (data > n->data)
    {
        remove_old(n->right, data);
    }
    else
    {
        if (!n->left && n->right)
        {
            Node* temp = n->right;
            delete n;
            n = temp;
        }
        else if (!n->right && n->left)
        {
            Node* temp = n->left;
            delete n;
            n = temp;
        }
        else if (!n->right && !n->left)
        {
            delete n;
            n = nullptr;
        }
        else
        {
            Node* min = n->right;
            if (!min->left)
            {
                n->right = nullptr;
            }
            else
            {
                Node* t = min;
                while(t->left->left)
                {
                    t = n->left;
                }
                min = t->left;
                t->left = nullptr;
            }
            n->data = min->data;
            delete min;
        }
    }
}

Node *copy(Node *n)
{
    if (!n) return nullptr;
    Node* co = new Node();
    co->data = n->data;
    co->left = copy(n->left);
    co->right = copy(n->right);
    co->color = n->color;
    return co;
}

string into_string(Node *n)
{
    if (!n) return "";
    else return "(" + to_string(n->data) + into_string(n->left) + into_string(n->right) + ")";
}

void insert_step(array_list *&arr, Node*& root, Node *&n, int data)
{
    if (!n)
    {
        n = new Node();
        n->data = data;
        arr->push_back(copy(root));
    }
    else if (n->data > data)
    {
        n->color = QColor::fromRgb(0, 0, 255);
        arr->push_back(copy(root));
        n->color = QColor::fromRgb(0, 255, 0);
        insert_step(arr, root, n->left, data);
    }
    else if (n->data < data)
    {
        n->color = QColor::fromRgb(0, 0, 255);
        arr->push_back(copy(root));
        n->color = QColor::fromRgb(0, 255, 0);
        insert_step(arr, root, n->right, data);
    }
    else
    {
        arr->push_back(copy(root));
    }
}

void remove_step(array_list *&arr, Node*& root, Node *&n, int data)
{
    if (!n) return;
    if (data < n->data)
    {
        n->color = QColor::fromRgb(0, 0, 255);
        arr->push_back(copy(root));
        n->color = QColor::fromRgb(0, 255, 0);
        remove_step(arr, root, n->left, data);
    }
    else if (data > n->data)
    {
        n->color = QColor::fromRgb(0, 0, 255);
        arr->push_back(copy(root));
        n->color = QColor::fromRgb(0, 255, 0);
        remove_step(arr, root, n->right, data);
    }
    else
    {
        if (!n->left && n->right)
        {
            Node* temp = n->right;
            delete n;
            n = temp;
        }
        else if (!n->right && n->left)
        {
            Node* temp = n->left;
            delete n;
            n = temp;
        }
        else if (!n->right && !n->left)
        {
            delete n;
            n = nullptr;
        }
        else
        {
            Node* min = n->right;
            if (!min->left)
            {
                n->right = nullptr;
            }
            else
            {
                Node* t = min;
                while(t->left->left)
                {
                    t = n->left;
                }
                min = t->left;
                t->left = nullptr;
            }
            n->data = min->data;
            delete min;
        }
        arr->push_back(copy(root));
    }
}

int getsize(Node* p) // обертка для поля size, работает с пустыми деревьями (t=NULL)
{
    if( !p ) return 0;
    return p->size;
}

void fixsize(Node* p) // установление корректного размера дерева
{
    p->size = getsize(p->left)+getsize(p->right)+1;
}

Node* rotateright(Node* p) // правый поворот вокруг узла p
{
    Node* q = p->left;
    if( !q ) return p;
    p->left = q->right;
    q->right = p;
    q->size = p->size;
    fixsize(p);
    return q;
}

Node* rotateleft(Node* q) // левый поворот вокруг узла q
{
    Node* p = q->right;
    if( !p ) return q;
    q->right = p->left;
    p->left = q;
    p->size = q->size;
    fixsize(q);
    return p;
}

Node* insert_classic(Node* p, int k) // классическая вставка нового узла с ключом k в дерево p
{
    if( !p ) return new Node(k);
    if( p->data > k )
        p->left = insert_classic(p->left,k);
    else
        p->right = insert_classic(p->right,k);
    fixsize(p);
    return p;
}

Node* insertroot(Node* p, int k) // вставка нового узла с ключом k в корень дерева p
{
    if( !p ) return new Node(k);
    if( k < p->data )
    {
        p->left = insertroot(p->left,k);
        return rotateright(p);
    }
    else if ( k > p->data )
    {
        p->right = insertroot(p->right,k);
        return rotateleft(p);
    }
    else
    {
        return p;
    }
}

Node* insert(array_list*& arr, Node*& root, Node* p, int k) // рандомизированная вставка нового узла с ключом k в дерево p
{
    if( !p ) return new Node(k);
    p->color = QColor::fromRgb(0, 0, 255);
    arr->push_back(copy(root));
    p->color = QColor::fromRgb(0, 255, 0);
    if( rand()%(p->size+1)==0 )
    {
        return insertroot(p,k);
    }
    if( p->data>k )
        p->left = insert(arr, root, p->left,k);
    else if ( p->data<k )
        p->right = insert(arr, root, p->right,k);
    fixsize(p);
    return p;
}
//
Node* join(Node* p, Node* q) // объединение двух деревьев
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

Node* remove(array_list*& arr, Node*& root, Node* p, int k) // удаление из дерева p первого найденного узла с ключом k
{
    if( !p ) return p;
    p->color = QColor::fromRgb(0, 0, 255);
    arr->push_back(copy(root));
    p->color = QColor::fromRgb(0, 255, 0);
    if( p->data==k )
    {
        Node* q = join(p->left,p->right);
        delete p;
        return q;
    }
    else if( k<p->data )
    {

        p->left = remove(arr, root, p->left,k);
    }
    else if( k>p->data )
    {
        p->right = remove(arr, root, p->right,k);
    }
    return p;
}
