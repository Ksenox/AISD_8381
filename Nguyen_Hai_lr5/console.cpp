#include "console.h"

console::console()
{

}
int console::checkErr(QString input, QString encode){
    if(input.size() == 0 || encode.size() == 0)
        return 3;
    static QString russian = RUSSIAN;
    foreach(const QChar & ch, russian) {
            if(input.contains(ch)) {
                return 1;
            }
    }
    for(int i = 0; i < encode.length(); i++){
        if(encode[i] != '0' && encode[i] != '1')
            return 2;
    }
    return 0;
}
int console::CountDeep(MinHeapNode *root)
{
    if (root == nullptr)
        return 0;
    int cl = CountDeep(root->left);
    int cr = CountDeep(root->right);
    return 1 + ((cl>cr)?cl:cr);
}

QGraphicsScene* console::Paint(string data){
    QGraphicsScene *scene = new QGraphicsScene;
    string input = data;
    MinHeapNode *root = huffman.buildHuffmanTree(input);
    int deeptree = CountDeep(root);

    scene->clear();
    QPen pen;
    QColor color;
    color.setRgb(174, 227, 232);
    pen.setColor(color);
    QBrush brush (color);
    QFont font("Helvetica [Cronyx]", 9, 10,false);
    pen.setWidth(3);


    int wDeep = static_cast<int>(pow(2, deeptree));
    int hDelta = 60;
    int wDelta = 8;
    int width = (wDelta*wDeep)/2;
    treePainter(scene, root, width/2, hDelta, wDelta, hDelta, pen, brush, font, wDeep);

    return scene;


}

void console::treePainter(QGraphicsScene *&scene, MinHeapNode *root, int w, int h, int wDelta, int hDelta, QPen &pen, QBrush &brush, QFont &font, int depth)
{

    if (root == nullptr)
        return ;
    string out;
    out += root->data;
    QGraphicsTextItem *textItem = new QGraphicsTextItem;
    textItem->setPos(w, h);// set toa do (x;y) cua nut
    textItem->setPlainText(QString::fromStdString(out));
    textItem->setFont(font);
    scene->addEllipse(w-wDelta/2, h, wDelta*5/2, wDelta*5/2, pen, brush); // Tạo hình tròn của các nút
    if (root->left != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w-(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    if (root->right != nullptr)
        scene->addLine(w+wDelta/2, h+wDelta, w+(depth/2)*wDelta+wDelta/2, h+hDelta+wDelta, pen);
    scene->addItem(textItem);
    treePainter(scene, root->left, w-(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    treePainter(scene, root->right, w+(depth/2)*wDelta, h+hDelta, wDelta, hDelta, pen, brush, font, depth/2);
    return ;
}

string console::analize(string data){
    string out;
    out += "ANALIZE : \n";
    int ch[MAX_TREE_HT], top = 0;
    out += huffman.printCodes(huffman.buildHuffmanTree(data),ch,top);
    return out;
}

string  console::result(string input,string encode, int *fl){
    return huffman.decode(huffman.buildHuffmanTree(input),encode,fl);
}

