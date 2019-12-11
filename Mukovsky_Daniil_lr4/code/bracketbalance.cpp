#include "bracketbalance.h"
#include <QStringList>
#include <QStack>
bool bracketBalance(QString input)
{
    QStringList lst;
    for (int i=0;i<input.size();i++){
        lst.push_back(QChar(input[i]));
    }
    QString list;
    QStack <QChar> st;
    for (int i=0;i<lst.size();i++){
        if (lst[i]=="("||lst[i]==")"){
            list.push_back(lst[i]);
        }
    }
    for (int j = 0;j<list.size();j++){
        if (list[j]=="("){
            st.push(list[j]);
            continue;
        }
        if (list[j]==")"){
            if (st.isEmpty())
                return false;
            if(st.top()=="(")
                st.pop();
            else
                return false;

        }
    }
    if (st.isEmpty())
        return true;
    return false;
}
