#include "tree.h"


int main()
    {    
    Tree tree = {};

    TreeCtor(&tree);

    Text data = {};

    FILE* file_input = fopen("tree.txt", "r");

    FileInput(file_input, &data);

    TreeRead(&tree, &data);

    fclose(file_input);

    FILE* file_out = fopen("tree_out.txt", "w");

    TreePrefixPrint(&tree, tree.root, file_out);

    fclose(file_out);

    TreeDump(&tree);

    TreeDtor(&tree);

    return 0;
    }