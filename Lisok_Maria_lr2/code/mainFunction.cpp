#include "hlist.h"
bool explore(S_expr* list1, S_expr* list2){
    HList hlist;
    if(!list1 && !list2)
        return true;
    if(!list1 || !list2)
        return false;
    if(hlist.isAtom(list1) && hlist.isAtom(list2)){
        cout << "Found atoms." <<endl;
        cout << list1->getNode().element << "\t" << list2->getNode().element << endl;
        if(list1->getNode().element == list2->getNode().element){
            cout << "Atoms are identical." << endl;
            return true;
        }
        else
            cout << "Atoms are different." << endl;
    }

    if(!hlist.isAtom(list1) && !hlist.isAtom(list2)){
        cout << "Found hierarchical lists." << endl;
        if(!explore(list1->getNode().pair.getHead(), list2->getNode().pair.getHead()))
            return false;
        else
            return explore(list1->getNode().pair.getTail(), list2->getNode().pair.getTail());
    }
    return false;
}
