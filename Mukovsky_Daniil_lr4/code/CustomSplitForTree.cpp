#include "CustomSplitForTree.h"
using namespace std;

QStringList splitForTree(QString stringTree){
    QString st = stringTree;
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
