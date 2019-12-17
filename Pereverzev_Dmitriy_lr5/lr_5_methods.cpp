#include "lr_5_methods.h"
struct TREE
{
    int value;
    TREE *left;
    TREE *right;
};


void push(TREE* &tree, int value)
{
    if(tree == NULL)
    {
        tree=new TREE;
        
        tree->value=value;
        tree->left=NULL;
        tree->right=NULL;
    }
    else
    {
        if(tree->value<value)
            push(tree->right, value);
        else if(tree->value>value)
            push(tree->left, value);
    }
    
    return;
}

void del_elem(TREE* &tree, int value)
{
    TREE** buffer;
    if(tree->left->value==value)
    {
        buffer=&tree->left;
        
    }
    else if(tree->right->value==value)
    {
        buffer=&tree->right;
        
    }
    
    //1 - no branches
    if((*buffer)->left==NULL && (*buffer)->right==NULL)
        (*buffer)=NULL;
    
    //2 - only left branch
    if((*buffer)->left!=NULL && (*buffer)->right==NULL)
        (*buffer)=(*buffer)->left;
    
    //3 - have right branch
    if((*buffer)->right!=NULL)
    {
        //3.1 - right leaf has no left branch
        if((*buffer)->right->left==NULL)
            (*buffer)=(*buffer)->right;
        
        //3.2 - right leaf has left branch
        else
        {
            TREE* &to_left=(*buffer)->right;
            while(to_left->left->left!=NULL)
                to_left=to_left->left;
            // _1
            to_left->left=to_left->left->right;
            // _2
            to_left=to_left->left;
            to_left->left=(*buffer)->left;
            to_left->right=(*buffer)->right;
            (*buffer)=to_left;
            
        }
    }
    
    
        
    
        
        
    
    
}

TREE*& find_elem(TREE* &tree, int value)
{
    TREE* exist=NULL;
    if(tree != NULL)
    {
        if(tree->value<value)
            exist=find_elem(tree->right, value);
        else if(tree->value>value)
            exist=find_elem(tree->left, value);
        else if(tree->value==value)
        {
            exist=tree;
            return exist;
            
        }
    }
    //del elem
    if(exist!=NULL)
    {
        del_elem(tree, value);
        exist=NULL;
    }
        
    return exist;
}
