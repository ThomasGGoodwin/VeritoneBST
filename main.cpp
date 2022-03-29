#include <iostream>
#include "BSTree.h"

int main(int argc, char** argv)
{
    BSTree tree;
    tree.insert(12);
    tree.insert(11);
    tree.insert(90);
    tree.insert(82);
    tree.insert(7);
    tree.insert(9);

    std::cout << tree;

    auto p = tree.maximum_depth_nodes();

    std::cout << "Depth: " << p.second << std::endl;
    std::cout << "Values at depth: ";
    for(int i : p.first)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}