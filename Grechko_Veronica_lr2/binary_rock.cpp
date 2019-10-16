#include "binary_rock.h"
#include <QFileDialog>
#include <QMessageBox>

binary_rock::binary_rock()
{
}
int binary_rock::Weight(BinRock *rock){
    int weig = 0;
    if(rock->right->plum->isPlum) weig += rock->right->plum->uni.weight;
    else Weight(rock->right->plum->uni.child);
    if(rock->left->plum->isPlum) weig += rock->left->plum->uni.weight;
    else Weight(rock->left->plum->uni.child);
    return weig;
}
bool binary_rock::Balanced(BinRock *rock){
    bool stateRight =true , stateLeft = true;
    int momentR = 0;
    int momentL = 0;
    if(rock->right->plum->isPlum){
        momentR = rock->right->lenght * rock->right->plum->uni.weight;
    }
    else {
        stateRight = Balanced(rock->right->plum->uni.child);
        momentR = rock->right->lenght * Weight(rock->right->plum->uni.child);
    }
    if(rock->left->plum->isPlum){
        momentL = rock->left->lenght * rock->left->plum->uni.weight;
    }
    else {
        stateLeft = Balanced(rock->left->plum->uni.child);
        momentL = rock->left->lenght * Weight(rock->left->plum->uni.child);
    }
    return momentL == momentR && stateRight && stateLeft;
}
void binary_rock::push(Side &side){
    side.plum = new Plum;
    side.plum->isPlum = false;
    side.plum->uni.child = new BinRock;
    side.plum->uni.child->left = new Side;
    side.plum->uni.child->right = new Side;
}
void binary_rock::parseString (std::string str, Side &side){
    int count_br = 0;
    int state = 0;
    for(unsigned int i = 1; i < str.length() - 1; i++){
        if (str[i] == '(') count_br++;
        else if (str[i] == ')') count_br--;
        else if (count_br == 0 && str[i] == ' '){
            std::string leftOne = str.substr(1, i - 1);
            std::string rightOne = str.substr(i + 1, str.length() - i - 2);

            if (leftOne[0] == '(' && rightOne[0] == '(') {
                push(side);
                parseString(leftOne, *(side.plum->uni.child->left));
                parseString(rightOne, *(side.plum->uni.child->right));
            }
            else if (rightOne[0] == '(') {
                char* end;
                double len = strtod(leftOne.c_str(), &end);
                if(!len) state = 1;
                side.lenght = (int)len;
                parseString(rightOne, side);
            }
            else{
                char* end;
                double len_s = strtod(leftOne.c_str(), &end);
                if(!len_s) state = 1;
                side.lenght = (int)len_s;
                double len_p = strtod(rightOne.c_str(), &end);
                if(!len_p) state = 1;
                side.plum = new Plum;
                side.plum->isPlum = true;
                side.plum->uni.weight = (int)len_p;
            }
        }
      }
    if(state){
        QMessageBox::warning(NULL,"Error", "Incorect input");
        exit(1);
  }
}




