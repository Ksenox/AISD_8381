#include<bintree.h>
#include<functionstree.h>
#include<cmath>
BinTree::BinTree(){
    Head = new Node;
    Head->data = "";
    Current = Head;
}

Node* BinTree::createTree(QStringList tokens){
    Node* finalNode = new Node;
    if(tokens.size()==2) return finalNode;
    int i =1;
    QString ltree = "";
    QString rtree = "";

    finalNode->data = tokens[i++];
    int index_i = i;    /* Индекс открывающей скобки левого поддерева */
    if(tokens[i] == "("){
        auto openBrackets = 1;
        auto closeBrackets = 0;

        while (openBrackets != closeBrackets) {
            i++;
            if (tokens[i] == "("){
                openBrackets++;
            }
            else if (tokens[i] == ")"){
                closeBrackets++;
            }

        }

        for (;index_i<=i; index_i++){
            ltree.append(tokens[index_i]);
        }
        finalNode->left = createTree(mySplit(ltree));

        i++;

        if (tokens[i] == ")"){      /* Если правого поддерева нет (достигнут конец строки после структуры левого поддерева*/
            return finalNode;
        }

        int index_j = i;    /* Индекс открывающей скобки левого поддерева */
        if(tokens[i] == "("){
            auto openBrackets = 1;
            auto closeBrackets = 0;

            while (openBrackets != closeBrackets) {
                i++;
                if (tokens[i] == "("){
                    openBrackets++;
                }
                else if (tokens[i] == ")"){
                    closeBrackets++;
                }

            }

            for (;index_j<=i; index_j++){
                rtree.append(tokens[index_j]);
            }
            finalNode->right = createTree(mySplit(rtree));
        }


    }
    return finalNode;
}
int BinTree::max_depth(Node *hd){
    if((hd == NULL) || (hd->data == '^')) return 0;
    else{
        int lDepth = max_depth(hd->left);
        int rDepth = max_depth(hd->right);

        if (lDepth > rDepth)  return(lDepth + 1);
        else return(rDepth + 1);
    }
}
int BinTree::count_node(Node *hd, int depth, int cur, int count){

    if(cur == depth){
         if(hd->data == '^') return 0;
         else return 1;
    }
    else {
       if(hd->left == nullptr && hd->right != nullptr )
            return count_node(hd->right, depth, cur + 1, count);
       else if (hd->right == nullptr && hd->left != nullptr )
            return count_node(hd->left, depth, cur + 1, count);
       else if(hd->right != nullptr && hd->left != nullptr)
        return count_node(hd->left, depth, cur + 1, count) + count_node(hd->right, depth, cur + 1, count);
    }

}
QGraphicsScene *graphic(BinTree *tree, QGraphicsScene *&scene, int depth)
{
    if (tree == nullptr)
        return scene;
    scene->clear();
    QPen pen;
    QColor color;
    color.setRgb(220, 220, 220);
    pen.setColor(color);
    QBrush brush (color);
    QFont font;
    font.setFamily("Tahoma");
    pen.setWidth(3);
    int wDeep = static_cast<int>(pow(2, depth + 2));
    int hDelta = 70;
    int wDelta = 15;
    font.setPointSize(wDelta);
    int width = (wDelta*wDeep)/2;
    treePainter(scene, tree->Head, width/2, hDelta, wDelta, hDelta, pen, brush, font, wDeep);
    return scene;
}

int treePainter(QGraphicsScene *&scene, Node *node, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth)
{
    if ((node == nullptr) || (node->data == '^'))
        return 0;
    QString out;
    out += node->data;
    QGraphicsTextItem *textItem = new QGraphicsTextItem;
    textItem->setPos(w, h);
    textItem->setPlainText(out);
    textItem->setFont(font);
    scene->addEllipse(w-wDelta/2, h, wDelta*5/2, wDelta*5/2, pen, brush);
    if ((node->left != nullptr) && (node->left->data != '^') )
        scene->addLine(w+wDelta/2, h+wDelta, w-(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    if (node->right != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w+(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    scene->addItem(textItem);
    treePainter(scene, node->left, w-(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    treePainter(scene, node->right, w+(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    return 0;
}







