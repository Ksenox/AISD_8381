#include "console.h"

console::console()
{

}

string console::take_string(int *flag){
    string question ;
    int num = *flag;
    srand (time(NULL));
    int random = rand()%3 +1;

    if(num == 11){
        if(random == 1)
            question = "hello";
        else if (random == 2)
            question = "where";
        else
            question = "letsgoo";
    }

    else if(num == 12){
        if(random == 1)
            question = "corlorfullsunshine";
        else if(random == 2)
            question = "whenthecitylightsup";
        else
            question = "xmasnoitsexamatettest";
    }

    else if (num == 13) {
        if(random == 1)
            question = "jcuocsongnaycobietbaonhieuthucanphaithuchiend";
        else if(random == 2)
            question = "vivaydunglangphithoigianvatuoitrecuabanokay";
        else
            question = "dochilamaycauxamlethoijustdoititwillbefinepqzm";
    }

    *flag = random;
    return question;
}

string console::take_encode(int num, int random){
    string encode ;
    if (num == 11) {
        if(random == 1)
            encode = "110111100111";
        else if(random == 2)
            encode = "1110110100111";
        else
            encode = "11010010100010";
    }

    else if (num == 12) {
        if(random == 1)
            encode = "1100110100011101010011011000001000111010111010";
        else if(random == 2)
            encode = "01110011100001000001101010100010001110111111000110";
        else
            encode = "000000010010001000000011001000101101110111100001101000101";
    }

    else{
        if(random == 1)
            encode = "1101100010011111011111000011111110110100001000101101011110101111110100111010000111011111101101111110";
        else if(random == 2)
            encode = "0011011000110001100111010101111101111011100100100111010011011010011101110101111111101110010011000110";
        else
            encode = "11111110111110101110011011110101110100110011100010111010100110001110001010000011010001110011000101";
    }
    return encode;
}

string console::create_question_text(string str1, string str2, int fl){
    string question = "";

    if(fl == 1){
        question += "\n>  Encode the following character using Huffman method :";
        question += "\n\n";
        question += "   '" + str1 + "'";
    }
    else {
        question += "\n>  Decode the following code by Huffman method :";
        question += "\n\n";
        question += "   '" + str2 + "'";
        question += "\n";
        question += "\n>  Use the input character string :";
        question += "\n\n";
        question += "   '" + str1 + "'";
    }
    return question;
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
    int wDelta = 7;
    int width = (wDelta*wDeep)/2;
    treePainter(scene, root, width/2, hDelta, wDelta, hDelta, pen, brush, font, wDeep);
    free(root);
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
    MinHeapNode *minheap = huffman.buildHuffmanTree(data);
    out += huffman.printCodes(minheap,ch,top);
    free(minheap);
    return out;
}

string  console::result(string input,string encode,string youranswer){
    return huffman.decode(huffman.buildHuffmanTree(input),encode,youranswer);
}

string console::take_encode(string input,string youranswer){
        string out;
        int ch[MAX_TREE_HT], top = 0;
        MinHeapNode *minheap = huffman.buildHuffmanTree(input);
        out += huffman.take_encode(minheap,ch,top,input);
        string buffer = "";
        buffer += "> Your answer :  ";
        buffer += youranswer + "\n\n";
        buffer += "> Result :  ";
        buffer += out + "\n\n";
        if(out == youranswer)
            buffer += "\t-> Answer is correct!";
        else
            buffer += "\t-> The answer inccorect!";

        free(minheap);
        return buffer;
}

void console::free(MinHeapNode* minheap){
    if(minheap == nullptr)
        return;

    free(minheap->left);
    free(minheap->right);

    delete minheap;
}
