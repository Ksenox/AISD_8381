#include "isincorrectsymbols.h"


bool isIncorrectSymbols(QString input)
{
    QStringList list ;
    bool flag1 = false, flag2 = false, flag3 = false;
    for (int j=0;j<input.size();j++){
        list.push_back(QChar(input[j]));
    }
    for(int i=0;i<list.length();i++){
        if (!((list[i]>="0"&&list[i]<="9")||(list[i]>="a"&&list[i]<="z")||(list[i]>="A"&&list[i]<="Z")||list[i]=="("||list[i]==")"))
            return false;
    }
    for(int i=0;i<list.length();i++){
        if (list[i]=="(")
           flag1 = true;
        if (flag1 == true && list[i]==")"){
           flag2 = true;
           break;
        }
    }
    for(int i=0;i<list.length();i++){
        if (flag2 == true && list[i]!="(" && list[i]!=")")
           flag3 = true;
    }
    if (flag3 == true)
        return true;
    return false;
}

QString deleteSpaces(QString& input){
    QString out="";
        for (auto i = 0;i < input.length();i++){
            if (input[i]!=' ' && input[i]!='\n' && input[i]!='\t' )
                out.push_back(input[i]);
            }
    return out;
}
