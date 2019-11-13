#include "lr_4_methods.h"
#include "lr_4_methods.cpp"

int main(int argc, const char *argv[])
{
    string forest;
    string bypass_width = "";
    string bin_tree = "(";
    cin >> forest;
    int *lvl = new int[100];
    string *arr_val = new string[100];
    int i_lvl = 1;
    int index = 1;

    TREE *tree = NULL;
    lvl[0] = -1;
    lvl[i_lvl] = -1;
    //test
    cout << "Errors:" << test_4(forest) << endl;

    //creat arrays
    create_4(i_lvl, lvl, arr_val, forest);
    for (int i = 0; i < i_lvl; i++)
        cout << lvl[i] << " -- " << arr_val[i] << endl;

    //add(tree);
    add_4(tree, i_lvl, lvl, arr_val, index);
    bypass_4(tree, bin_tree);
    cout << endl
         << bin_tree << endl;

    width_4(tree);

    return 0;
}

//(1(2(5)(6))(3(4)))
//(1(2(5(6))(3(4))))
//(1(2(5(8))(6(7))))
