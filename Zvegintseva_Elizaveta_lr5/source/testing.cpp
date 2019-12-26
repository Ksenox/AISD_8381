#include "testing.h"


void generate_var_insert(string& question, string& answer, binTree &qtree, binTree &aTree, int difficulty)
{
    for (int i = 0; i < difficulty; i++)
    {
        int n = rand() % 100;
        question += to_string(n) + " ";
        qtree.insert(qtree.root, n);
    }
    question += "\n";
    aTree.root = qtree.copy(qtree.root);
    int v = rand() % 100;
    question += "Вставьте в данное бинарное дерево элемент " + to_string(v) + ", выпишите полученное дерево в скобочном представлении БДП\n";
    aTree.insert(aTree.root, v);
    answer += aTree.into_string(aTree.root) + "\n";
}

void generate_vars_insert(string& question, string& answer, int count, int difficulty)
{
    for (int i = 1; i <= count; i++) {
        binTree* qt = new binTree();
        binTree* at = new binTree();
        qt->root = nullptr;
        at->root = nullptr;
        // TODO описание задания и форматирование строк, чтоб красиво
        string current = "Вариант " + to_string(i) + ". Сложность варианта(количество элементов дерева): " + to_string(difficulty) + "\n" + "Дерево:\n";
        string one_issue = current;
        string one_answer = current;
        generate_var_insert(one_issue, one_answer, *qt, *at, difficulty);
        question += one_issue + "\n--------------\n";
        answer += one_answer + "\n--------------\n";
    }
}

void generate_var_remove(string& question, string& answer, binTree &qtree, binTree &aTree, int difficulty)
{
    int* va = new int[difficulty];
    for (int i = 0; i < difficulty; i++)
    {
        int n = rand() % 100;
        va[i] = n;
        question += to_string(n) + " ";
        qtree.insert(qtree.root, n);
    }
    question += "\n";
    aTree.root = qtree.copy(qtree.root);
    int v = va[rand() % difficulty];
    question += "Исключите из данного бинарного дерева элемент " + to_string(v) + ", выпишите полученное дерево в скобочном представлении БДП\n";
    aTree.remove(aTree.root, v);
    answer += aTree.into_string(aTree.root) + "\n";
}

void generate_vars_remove(string& question, string& answer, int count, int difficulty)
{
    for (int i = 1; i <= count; i++) {
        binTree* qt = new binTree();
        binTree* at = new binTree();
        qt->root = nullptr;
        at->root = nullptr;
        // TODO описание задания и форматирование строк, чтоб красиво
        string current = "Вариант " + to_string(i) + ". Сложность варианта(количество элементов дерева): " + to_string(difficulty) + "\n" + "Дерево:\n";
        string one_issue = current;
        string one_answer = current;
        generate_var_insert(one_issue, one_answer, *qt, *at, difficulty);
        question += one_issue + "\n--------------\n";
        answer += one_answer + "\n--------------\n";
    }
}


void file_write(string filename, string &data)
{
    cout << data;
    cout << &data;
    ofstream myfile;
    myfile.open(filename);
    myfile << data;
    myfile.close();
}
