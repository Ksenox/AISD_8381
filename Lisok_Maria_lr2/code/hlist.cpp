#include "hlist.h"
bool HList::isAtom(const S_expr* s){
    if(!s){
        return false;
    }
    return s->getFlag();
}
bool HList::isNull(const S_expr* s){
    return s==nullptr;
}
S_expr* HList::head(const S_expr* s, string & result){
    if(s){
        if(!isAtom(s)){
            return s->getNode().pair.getHead();
        }
        else{
            result.append("Error: Head(atom) \n");
            return nullptr;
        }
    }
    else{
        result.append("Error: Head(nil) \n");
        return nullptr;
    }
}
S_expr* HList::tail(const S_expr* s, string & result){
    if(s){
        if(!isAtom(s)){
            return s->getNode().pair.getTail();
        }
        else{
            result.append("Error: Head(atom) \n");
            return nullptr;
        }
    }
    else{
        result.append("Error: Head(nil) \n");
        return nullptr;
    }
}
char HList::getAtom(const S_expr* s, string & result){
    if(isAtom(s)){
        return s->getNode().element;
    }
    else{
        result.append("Error: getAtom(s) for !isAtom(s)");
        return 0;
    }
}
S_expr* HList::makeAtom(const char x){
    S_expr* s = new S_expr;
    s->setFlag(true);
    s->setNodeElement(x);
    return s;
}
int HList::read_s_expr(S_expr*& s, string list, string & result){
    int i=0;
    while(list[i]==' '){
        i++;
    }
    if(list[i] != '('){
        result.append("Error!!!Expression must begin with (\n");
        return 1;
    }
    if(read(list[i], s, list, i, result)){
        return 1;
    }
    return 0;
}
int HList::read(char prev, S_expr*& s, string & list, int i, string & result){
    if(prev == ')') {
        result.append(" ! List.Error. List can't begin with )\n");
        return 1;
    }
    else if(prev != '('){
        s = makeAtom(prev);
    }
    else{
        if(read_seq (s, list, i, result))
            return 1;
    }
    return 0;
}
int HList::read_seq(S_expr*& s, string & list, int i, string & result){
    S_expr* p1, *p2;
    i++;
    while(list[i] == ' '){
        i++;
    }

    if(list[i] == ')'){
        s = nullptr;
    }else if(i>=list.length()){
        result.append("Error. It isn't ) in exspression\n");
        return 1;
    }
    else{
        if(read(list[i], p1, list, i, result))
            return 1;
        if(read_seq(p2, list, i, result))
            return 1;
        s = cons(p1, p2, result);
    }
    return 0;
}
void HList::destroy(S_expr* s, string & result){
    if(s){
        if(!isAtom(s)){
            destroy(head(s, result), result);
            destroy(tail(s, result), result);
        }
        delete s;
    }
}
S_expr* HList::cons(S_expr* head, S_expr* tail, string & result){
    S_expr* s;
    if(isAtom(tail)){
        result.append("Error tail(nil)\n");
        return nullptr;
    }
    else{
        s = new S_expr();
        s->setFlag(false);
        s->node.pair.head=head;
        s->node.pair.tail=tail;
        return s;
    }
}























