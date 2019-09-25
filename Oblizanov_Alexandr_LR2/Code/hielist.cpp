#include "hielist.h"


int createHieList(HieList *list)
{
    list->head = nullptr;
    list->last = nullptr;
    return 0;
}

int appendNext(HieList *list, char in)
{
    HieElem *next = new HieElem;
    next->haveChild = 0;
    next->next = nullptr;
    next->parent = nullptr;
    next->info = in;
    if (list->head == nullptr)
    {
        list->head = next;
        list->last = next;
        next->prev = nullptr;
    }
    else
    {
        list->last->next = next;
        next->prev = list->last;
        list->last = next;
    }
    return 0;
}

int appendChild(HieList *list, HieElem *child, int &err)
{
    if (err)
        return 1;
    if (child == nullptr)
    {
        err = BAD_CHILD;
        return 1;
    }
    HieElem *next = new HieElem;
    next->haveChild = 1;
    next->next = nullptr;
    next->parent = nullptr;
    list->last->next = next;
    next->prev = list->last;
    next->child = child;
    child->parent = next;
    list->last = next;
    return 0;
}

HieElem *createHieFromStr(string &in, unsigned long long &ptr, int &err)
{
    HieList list;
    createHieList(&list);
    while (in[ptr] != ')' && in[ptr] != '\0')
    {
        if (in[ptr] == ' ')
        {
            ptr++;
            continue;
        }
        if (in[ptr] == '(')
        {
            ptr++;
            if (list.head == nullptr)
            {
                err = BAD_PARENT;
                return list.head;
            }
            appendChild(&list, createHieFromStr(in, ptr, err), err);
            if (err)
            {
                return list.head;
            }
        }
        else
        {
            appendNext(&list, in[ptr]);
            ptr++;
        }
    }
    if (in[ptr] == '\0')
    {
        err = NO_CLOSE;
    }
    if (in[ptr] == ')')
        ptr++;
    return list.head;
}

int printRecursion(HieElem *temp, string &out)
{
    if (temp != nullptr)
    {
        if (temp->haveChild == 0)
        {
            out += " ";
            out += temp->info;
            out += " ";
        }
        else
        {
            out += "{";
            printRecursion(temp->child, out);
            out += "}";
        }
        printRecursion(temp->next, out);
    }
    return 0;
}

int checkPrefix(HieElem *head, int &err)
{
    bool infVar = false;
    HieElem *temp = head;
    if (temp == nullptr)
    {
        err = EMPTY;
        return 1;
    }
    if (temp->haveChild == 1)
    {
        err = BAD_PARENT;
        return 1;
    }
    if (temp->info == '=')
    {
        infVar = true;
    }
    else if (temp->info != '+' && temp->info != '!' && temp->info != '*')
    {
        err = NO_OPERATOR;
        return 1;
    }

    if (temp->next == nullptr)
    {
        err = NO_OPERAND;
        return 1;
    }
    temp = temp->next;
    int numVar = 0;
    while (temp != nullptr)
    {
        if (temp->haveChild)
        {
            if (checkPrefix(temp->child, err))
                return err;
            numVar++;
        }
        else if (isalnum(temp->info) == 0)
        {
            err = BAD_OPERAND;
            return 1;
        }
        else
            numVar++;
        temp = temp->next;
    }
    if (infVar && numVar != 2)
    {
        err = BAD_EQUIVALENT;
        return 1;
    }
    return 0;
}

string getList(HieElem *head)
{
    string out;
    out += "{";
    printRecursion(head, out);
    out += "}";
    return out;
}

int deleteList(HieElem *head)
{
    if (head == nullptr)
        return 0;
    HieElem *temp = head;
    while (temp != nullptr)
    {
        temp = temp->next;
        delete head;
        head = temp;
    }
    return 0;
}
