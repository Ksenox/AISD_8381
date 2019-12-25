#include "console.h"

console::console()
{

}
int console::checkErr(QString data){
    int flagErr;
    string input = data.toStdString();
    flagErr = CheckErr(input,input.length());
    return flagErr;
}
QGraphicsScene* console::Analize(QString data){
    QGraphicsScene *scene = new QGraphicsScene;

    string input = data.toStdString();
    Forest *forest = takeforest(input,input.length());
    BinTree *bintree = createBTFromForest(forest);
    string out;
    out += "ANALIZE";
    out += "\n\nTrees of the forest:\n";
    for(int i = 0; i <forest->count; i++){
        out += "\n\tTree " + std::to_string(i+1)+":\t";
        takeInfoOfNode(forest->tree[i]->root,out);


    }
    out += "\n\nElements of the forest in horizontal order (in width):\n\t";
    for(int i = 0; i <forest->count; i++){
        out += "\n\tTree " + std::to_string(i+1)+":\t";
        for(int j = 0; j <= forest->tree[i]->deep; j++){
            takeInfoByDeep(forest->tree[i]->root,j,out);
        }
    }
    out+= "\n\nNatural representation of the forest by a binary tree :\n\n\t";

    takeInfoBT(bintree->root,out);
    scene->addText(QString::fromStdString(out));
    return scene;
}

QGraphicsScene* console::Console(QString data){
    QGraphicsScene *scene = new QGraphicsScene;

    string input = data.toStdString();


    Forest *forest = takeforest(input,input.length()
                                );
    BinTree *bintree = createBTFromForest(forest);
    scene->clear();
    QPen pen;
    QColor color;
    color.setRgb(174, 227, 232);
    pen.setColor(color);
    QBrush brush (color);
    QFont font("Helvetica [Cronyx]", 8, 10,false);
    pen.setWidth(2);


    int wDeep = static_cast<int>(pow(2, bintree->deep)+2);
    int hDelta = 50;
    int wDelta = 4;
    int width = (wDelta*wDeep)/2;
    treePainter(scene, bintree->root, width/2, hDelta, wDelta, hDelta, pen, brush, font, wDeep);

    return scene;


}


void console::treePainter(QGraphicsScene *&scene, BinNode *binnode, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth)
{

    if (binnode == nullptr)
        return ;
    string out;
    out += binnode->info;
    QGraphicsTextItem *textItem = new QGraphicsTextItem;
    textItem->setPos(w, h);// set toa do (x;y) cua nut
    textItem->setPlainText(QString::fromStdString(out));
    textItem->setFont(font);
    //scene->addEllipse(w-wDelta/2, h, wDelta*5/2, wDelta*5/2, pen, brush); // Tạo hình tròn của các nút
    if (binnode->left != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w-(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    if (binnode->right != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w+(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    scene->addItem(textItem);
    treePainter(scene, binnode->left, w-(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    treePainter(scene, binnode->right, w+(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    return ;
}
