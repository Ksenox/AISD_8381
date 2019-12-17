#include<functionstree.h>

QString delSpace (QString rowInput){
    QString out="";
    for (auto i = 0;i < rowInput.length();i++){
        if (rowInput[i]!=' ' && rowInput[i]!='\n' && rowInput[i]!='\t' )
            out.push_back(rowInput[i]);
        }
    return out;
}

QStringList mySplit(QString rowInput){
    QString st = delSpace(rowInput);
    auto i = 0;
    QStringList out={};
    QString tmp="";
    for(;i<st.length();i++){
        if (st[i] == ')' || st[i] == '(') out.push_back(QString(st[i]));
        else {
            for (; st[i]!=')' && st[i]!='(' ;i++){
                tmp.push_back(st[i]);
            }
            out.push_back(tmp);
            out.push_back(QString(st[i]));
            tmp.clear();
        }
    }
    return out;
}
