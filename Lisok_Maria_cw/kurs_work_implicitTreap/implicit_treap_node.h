#ifndef BINARYTREAP_H
#define BINARYTREAP_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <QDebug>
#include <chrono>
#include "otherfunc.h"
#define ONE_NODE 1
#define RAND_FACTOR 20000000

using namespace std;
typedef unsigned long ul;

template<class TYPE>
class ImplicitTreapNode
{
public:
    ImplicitTreapNode();
    ~ImplicitTreapNode();
    ImplicitTreapNode(const TYPE* _data, ul _priority = std::rand() % RAND_FACTOR);

    static ImplicitTreapNode* Merge(bool flag,ImplicitTreapNode* _left, ImplicitTreapNode* _right);                  // Merging two treaps. Need agree with: keys of one of treaps needs to be bigger, than keys of another Treap.

    static void Split(ImplicitTreapNode* _node, size_t _index, bool flag, ImplicitTreapNode*& _left, ImplicitTreapNode*& _right, size_t _add = 0);             // Splits up treap. First output treap has all keys smaller than keys of the second one.

    static void Clear(ImplicitTreapNode*& _treap);                                   // Destroy root this and all childs.
    static size_t SizeOf(ImplicitTreapNode* _treap);                                // Returns mSizeOf field of _treap

    ImplicitTreapNode* Insert(const TYPE* mData, size_t _index,bool, ul _prior = std::rand() % RAND_FACTOR);
    ImplicitTreapNode* Remove(size_t _index);                                             // Remove Node from NON EMPTY Treap by key.

    static void PrintData(ImplicitTreapNode* _node);
    static void PrintData(ImplicitTreapNode* _node, std::string& out);
    static void Display(ImplicitTreapNode* _node, size_t _depth = 0);
    static void Display(ImplicitTreapNode* _node, std::string& out, size_t _depth = 0);

    TYPE& GetData(size_t _index);                                                    // Returns key of node by index in upping order of keys.

    inline void RecalcSizeOf();                                                    // Recalculate SizeOf
    inline void AddData(const TYPE* _data);
    static size_t iterationsSplit;
    static size_t iterationsMerge;
    static size_t height(ImplicitTreapNode<TYPE>*);
    ImplicitTreapNode* getMLeft(){
        return mLeft;
    }
    void copy(ImplicitTreapNode<TYPE>*, ImplicitTreapNode<TYPE>*);
private:

    ImplicitTreapNode* mLeft;
    ImplicitTreapNode* mRight;

    ul mPriority;
    size_t mSizeOf;                                                         // Count of subtreaps + 1 (root exactly)

    TYPE* mData;

};

//______________________________________NODE_METHODS___________________________________________//

//____CONSTRUCTORS____//
template<class TYPE> size_t ImplicitTreapNode<TYPE>::iterationsSplit;
template<class TYPE> size_t ImplicitTreapNode<TYPE>::iterationsMerge;

template<class TYPE>
ImplicitTreapNode<TYPE>::ImplicitTreapNode()
{
    mSizeOf = ONE_NODE;
    mLeft = nullptr;
    mRight = nullptr;
    mData = nullptr;
    mPriority = 0;
    iterationsSplit = 0;
    iterationsMerge = 0;
}
template<class TYPE>
size_t ImplicitTreapNode<TYPE>::height(ImplicitTreapNode<TYPE>* node){
    if (node == NULL)
        return 0;
    else
    {

        int lDepth = height(node->mLeft);
        int rDepth = height(node->mRight);

        /* use the larger one */
        if (lDepth > rDepth)
            return(lDepth + 1);
        else
            return(rDepth + 1);
    }
}

template<class TYPE>
void ImplicitTreapNode<TYPE>::copy(ImplicitTreapNode<TYPE> * dest, ImplicitTreapNode<TYPE> *src)
{
    if(!src){
        dest = nullptr;
        return;
    }
    cout << "Copy" << src->data << endl;
    dest = new ImplicitTreapNode<TYPE> {src->mData, src->mPriority};
    copy(dest->left, src->left);
    copy(dest->right, src->right);

}
template<class TYPE>
ImplicitTreapNode<TYPE>::~ImplicitTreapNode()
{
    delete mData;
}

template<class TYPE>
ImplicitTreapNode<TYPE>::ImplicitTreapNode(const TYPE* _data, ul _priority) : ImplicitTreapNode()
{
    AddData(_data);
    mPriority = _priority;
}

//____TREAP_EDITING____//

template<class TYPE>
ImplicitTreapNode<TYPE>* ImplicitTreapNode<TYPE>::Merge(bool flag, ImplicitTreapNode* _left, ImplicitTreapNode* _right)
{

    ImplicitTreapNode<TYPE>* result;
    if(flag){
        iterationsMerge++;
    }
    if (!_right)
        return _left;
    if (!_left)
        return _right;
    else if (_left->mPriority > _right->mPriority)
    {
        _left->mRight = Merge(flag, _left->mRight, _right);
        result = _left;
    }
    else
    {
        _right->mLeft = Merge(flag, _left, _right->mLeft);
        result = _right;
    }

    result->RecalcSizeOf();
    return result;
}

template<class TYPE>
void ImplicitTreapNode<TYPE>::Split(ImplicitTreapNode* _node, size_t _index, bool flag, ImplicitTreapNode*& _left, ImplicitTreapNode*& _right, size_t _add)
{

    if (!_node)
    {
        _left = _right = nullptr;
        return;
    }
    if(flag){
        iterationsSplit++;
    }
    size_t curr_index = 1 + SizeOf(_node->mLeft);
    if (_index <= curr_index) {
        Split(_node->mLeft, _index,flag, _left, _node->mLeft, _add);
        _right = _node;
        _node->RecalcSizeOf();
    }
    else {
        Split(_node->mRight, _index-curr_index, flag, _node->mRight, _right, _add);
        _left = _node;
        _node->RecalcSizeOf();
    }
}

template<class TYPE>
ImplicitTreapNode<TYPE>* ImplicitTreapNode<TYPE>::Insert(const TYPE* _data, size_t _index,bool flag, ul _prior)
{
    ImplicitTreapNode* _l = nullptr;
    ImplicitTreapNode* _r = nullptr;
    ImplicitTreapNode* _in = new ImplicitTreapNode(_data, _prior);
    Split(this, _index,flag, _l, _r);
    return Merge(false, Merge(false,_l, _in), _r);
}

template<class TYPE>
ImplicitTreapNode<TYPE>* ImplicitTreapNode<TYPE>::Remove(size_t _index)
{
    ImplicitTreapNode<TYPE>* _r = nullptr;
    ImplicitTreapNode<TYPE>* _l = nullptr;
    ImplicitTreapNode<TYPE>* _el = nullptr;
    Split(this, _index, false, _l, _r);
    Split(_r, 1, false, _el, _r);
    delete _el;
    _el = nullptr;
    return Merge(false, _l, _r);
}

template<class TYPE>
void ImplicitTreapNode<TYPE>::Clear(ImplicitTreapNode<TYPE>*& _treap)
{
    if(_treap)
    {
        if(_treap->mLeft)
            Clear(_treap->mLeft);
        if(_treap->mRight)
            Clear(_treap->mRight);

        delete _treap;
        _treap = nullptr;
    }
}

//____SIZE____//

template<class TYPE>
size_t ImplicitTreapNode<TYPE>::SizeOf(ImplicitTreapNode* _treap)
{
    return !_treap ? 0 : _treap->mSizeOf;
}

template<class TYPE>
void ImplicitTreapNode<TYPE>::RecalcSizeOf()
{
    mSizeOf = SizeOf(mLeft) + SizeOf(mRight) + ONE_NODE;
}

template<class TYPE>
void ImplicitTreapNode<TYPE>::AddData(const TYPE* _data)
{
    mData = new TYPE;
    std::memmove(mData, _data, sizeof (TYPE));
}

template<class TYPE>
TYPE& ImplicitTreapNode<TYPE>::GetData(size_t _index)
{
    ImplicitTreapNode<TYPE>* _node = this;
    size_t _add = 0;
    size_t curr_index = _add + SizeOf(_node->mLeft);
    while (_index != curr_index)
    {
        if(_index < curr_index)
            _node = _node->mLeft;

        else if(_index > curr_index) {
            _add = _add + 1 + SizeOf(_node->mLeft);
            _node = _node->mRight;
        }
        curr_index = _add + SizeOf(_node->mLeft);
    }
    return *_node->mData;
}

//____PRINTING____//

template<class TYPE>
void ImplicitTreapNode<TYPE>::PrintData(ImplicitTreapNode* _node)
{
    if (!_node)
        return;
    PrintData(_node->mLeft);
    std::cout << *_node->mData << ", ";
    PrintData(_node->mRight);
}

template<class TYPE>
void ImplicitTreapNode<TYPE>::PrintData(ImplicitTreapNode* _node, std::string& out)
{
    if (!_node)
        return;
    PrintData(_node->mLeft, out);
    out += std::to_string(*_node->mData);
    out += "(";
    out += std::to_string(_node->mPriority);
    out += ") -> ";
    PrintData(_node->mRight, out);
}

template<class TYPE>
void ImplicitTreapNode<TYPE>::Display(ImplicitTreapNode* _node, size_t _depth)
{
    if (_node)
    {
        Display(_node->mRight, _depth+1);
        print_tabs(_depth);
        std::cout <<*_node->mData<<" ("<< _node->mPriority<<")\n";
        Display(_node->mLeft, _depth+1);
    }
}

template<class TYPE>
void ImplicitTreapNode<TYPE>::Display(ImplicitTreapNode* _node, std::string& out, size_t _depth)
{
    if (_node)
    {
        Display(_node->mRight, out, _depth+1);
        for(size_t it = 0; it < _depth; it++)
            out += '\t';
        out += std::to_string(*_node->mData);
        out += " (";
        out += std::to_string(_node->mPriority);
        out += ")\n";
        Display(_node->mLeft, out, _depth+1);
    }
}

#endif // BINARYTREAP_H
