#include "family.h"


void Family::addWord(QString &name){
    bool here = false;
    for(auto tmp: all_names){
        if (tmp == name) {here = true; break;}
    }
    if(!here) all_names.push_back(name);
}


void Family::split(QString& row){
    families.push_back(QVector<QString>());
    QStringList list_of_strings = row.split(' ');
    if (list_of_strings.length()==0) throw WRONG_STRING;
    for (auto str:list_of_strings){
        if(str != ""){
            families[number].push_back(str);
            addWord(str);
        }
    }
    number++;
}



void Family::input(QString in){
    split(in);

}

bool Family::is_parent(QString p1, QString p2){
    for (auto & familie : families) {
        if (p1==familie[0]){
            for (auto j = 1; j <familie.size() ; ++j) {
                if (p2 == familie[j]) return true;
            }
        }
    }
    return false;
}


bool Family::is_relative(const QString& p1, const QString& p2, int deep){
    if (p1==p2) return false;
    if (is_parent(p1,p2) || is_parent(p2,p1)) return true;
    if (deep>3) return false;
    for( auto Z : all_names)
    {
        if (is_relative(p1,Z,deep+1) && is_relative(Z,p2,deep+1)) return true;
    }
    return false;
}
