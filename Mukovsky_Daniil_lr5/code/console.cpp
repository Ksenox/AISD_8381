#include "console.h"
#include <QFile>
#include "decodingandcodinghuufmanalgorithm.h"

int consoleMain(){
    QFile file("C:\\Users\\miair\\Desktop\\Results_lr5\\input.txt"); // создаем объект класса QFile
    QString in;
    if (!file.open(QIODevice::ReadOnly))
        return 1 ;
    int i =0;
    in = file.readAll();
    int inputLen = in.size();
    char* input = new char[in.length()+1];
    for (i =0;i<in.length();i++){
        input[i] = in[i].toLatin1();
    }
    input[i] = '\0';

    std::string resultCode = "";
    std::string output = "";
    BinTree* tree = new(BinTree);


    encode(input, output, inputLen, tree,resultCode);

    delete[] input;

    output = output +"\n"+"Result code:\n"+resultCode;

    QString answ = QString::fromStdString(output);

    Node* root = tree->getRoot();
    tree->freeMem(root);

    QFile out("C:\\Users\\miair\\Desktop\\Results_lr5\\output.txt");
    if (out.open(QIODevice::WriteOnly)){
        out.write(answ.toUtf8());
    }
    out.close();
    return 0;
}
