#include "utils_cli.h"

int utils_cli::execute(int argc, char *argv[])
{
    std::cout << "Starting in console mode..." << std::endl;
    utils_tree<int>* tree = nullptr;
    for(int i = 0; i < argc; i++) {
        if(!strcmp("console", argv[i]) || !strcmp("-console", argv[i]) || !strcmp("-c", argv[i])) continue;
        std::cout << "Tree found: " << argv[i] << std::endl;
        std::string s = argv[i];
        tree = new utils_tree<int>(s);
    }
    if (!tree)
    {
        std::cout << "Thee is empty" << std::endl;
        return 1;
    }
    std::cout << tree->node_string() << std::endl;
    std::cout << "Insertion: 5" << std::endl;
    tree->insertbalanced(5);
    std::cout << tree->node_string() << std::endl;
    std::cout << "Insertion: 7" << std::endl;
    tree->insertbalanced(7);
    std::cout << tree->node_string() << std::endl;
    std::cout << "Insertion: 13" << std::endl;
    tree->insertbalanced(13);
    std::cout << tree->node_string() << std::endl;
    std::cout << "Removing: 4" << std::endl;
    tree->removebalanced(4);
    std::cout << tree->node_string() << std::endl;
    std::cout << "Removing: 13" << std::endl;
    tree->removebalanced(13);
    std::cout << tree->node_string() << std::endl;
    std::cout << "Removing: 8" << std::endl;
    tree->removebalanced(8);
    std::cout << tree->node_string() << std::endl;

//    char com;
//    do
//    {
//        std::cout << "1 - insert" << std::endl << "2 - remove" << std::endl;
//        std::cin >> com;
//        if (com == '1') {
//            std::cout << "What to insert?" << std::endl;
//            int i;
//            std::cin >> i;
//            tree->insertbalanced(i);
//        }
//        else if (com == '2') {
//            std::cout << "What to remove?" << std::endl;
//            int i;
//            std::cin >> i;
//            tree->removebalanced(i);
//        }
//        else {
//            std::cout << "Unknown command" << std::endl;
//        }
//        std::cout << tree->node_string() << std::endl;
//    } while (com != 'e');
    delete tree;
    return 0;
}
