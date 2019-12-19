#include "tree.h"
#include <QGraphicsScene>

Tree::Tree()
{

}


char Tree::ret_val(){
    return val;
}
Tree* Tree::ret_l(){
    return left;
}
Tree* Tree::ret_r(){
    return right;
}
Tree* Tree::ret_parent(){
    return parent;
}
void Tree::get_val(char a){
    val = a;
}

void Tree::get_l(Tree* a){
    left = a;
}

void Tree::get_r(Tree* a){
    right = a;
}

void Tree::get_parent(Tree* a){
    parent = a;
}

void Tree::create_node(char val)
{
    if(!this->right){
        this->right = new Tree;
        this->right->val = val;
        this->right->parent = this;
    }
    else{
        this->left = new Tree;
        this->left->val = val;
        this->left->parent = this;
    }
}


std::string Tree::print_node(){

    std::stringstream ss;

    int flag = 0;
    if(parent!=nullptr && (val==43 || val==45) && (parent->val==42 || parent->val==47)){
        flag = 1;
        ss << "(";
    }

    if(left){
        ss << left->print_node();
    }

    std::string s;
    s.insert(0, 1, val);
    ss << s;

    if(right){
        ss << right->print_node();
    }

    if(flag)
        ss << ")";
    return ss.str();
}


//void Tree::drawNode(QGraphicsScene *scene, x, y){
//    int width = 40;
//    int height = 40;

//    x0 = x - width/2;
//    y0 = y - height/2;

//    QRect gNode(x0, y0, width, height);

//    scene->addRect(gNode);

//    int d = depth;

//    if(left){
//        left->drawNode(scene, x - 30*d, y + 30);
//    }
//    if(right){
//        right->drawNode(scene, x + 30*d, y + 30);
//    }
//}

int Tree::deepmax()
{
    int LHeight;
    if(left){
        LHeight = left->deepmax();
    } else LHeight = 0;

    int RHeight;
    if(right){
        RHeight = right->deepmax();
    } else RHeight = 0;

    return std::max(LHeight+1, RHeight+1);
}

void Tree::displaytree(Dialog *dialog, int deep, int maxdeep, int prevx, int prevy, int posx, int posy)
{
    dialog->displaynode(val, deep, maxdeep, prevx, prevy, posx, posy);
    if(left)
        left->displaytree(dialog, deep + 1, maxdeep, posx, posy, posx - (dialog->elemwidth*std::pow(2, maxdeep-deep)), posy + 2*dialog->elemheight);
    if(right)
        right->displaytree(dialog, deep + 1, maxdeep, posx, posy, posx + (dialog->elemwidth*std::pow(2, maxdeep-deep)), posy + 2*dialog->elemheight);
}
