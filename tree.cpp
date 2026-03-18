#include "tree.h"


void TreeCtor(Tree* tree)
    {   
    tree->status = TREE_OK;

    tree->root = (Node*)calloc(1, sizeof(Node));

    tree->root->left = tree->root->right = tree->root->parent = nullptr;

    tree->size = 0;
    }


Node* TreeNodeCtor(Tree_type data) 
    {
    Node* new_node = (Node*)calloc(1, sizeof(Node));

    new_node->data = data;

    new_node->left = new_node->right = new_node->parent = nullptr;

    return new_node;
    }


Type_error TreeInsert(Tree* tree, Node* node, Tree_type data, Child child) 
    { 
    CHECK_TREE_ERROR(tree);
 
    Node* new_node = TreeNodeCtor(data);

    if (tree->size == 0) 
        {
        tree->root = new_node;
        }

    if (node == nullptr) 
        {
        return NODE_PTR_IS_NULL;
        }

    if (child == L_CHILD) 
        {
        new_node->parent = node;

        node->left = new_node;
        }  

    else if (child == R_CHILD) 
        {
        new_node->parent = node;

        node->right = new_node;
        } 

    else
        {
        tree->status |= TREE_CANT_HAVE_THIS_CHILD;

        return TREE_CANT_HAVE_THIS_CHILD; 
        } 

    tree->size++;

    CHECK_TREE_ERROR(tree);
    
    return tree->status;
    }


Type_error TreeDelete(Tree* tree, Node* node)  
    {
    if (node == nullptr) 
        {
        return NODE_PTR_IS_NULL;
        }

    if (node->left) 
        {
        TreeDelete(tree, node->left);
        }

    if (node->right) 
        {
        TreeDelete(tree, node->right);
        }

    node->right  = nullptr;

    node->left   = nullptr;

    node->parent = nullptr;

    free(node);  
 
    tree->size--; 

    return tree->status;  
    }


Type_error TreePrefixPrint(Tree* tree, Node* node, FILE* file)
    {
    CHECK_TREE_ERROR(tree);
    
    if (node == nullptr) 
        {
        tree->status |= NODE_PTR_IS_NULL;

        return NODE_PTR_IS_NULL;
        }
    
    fprintf(file, "(");

    fprintf(file, SPECIFICATOR_TYPE, node->data);

    if (node->left) 
        {
        TreePrefixPrint(tree, node->left, file);
        }

    if (node->right)
        {
        TreePrefixPrint(tree, node->right, file);
        }

    fprintf(file, ")");

    CHECK_TREE_ERROR(tree);

    return tree->status;
    }



Type_error TreePostfixPrint(Tree* tree, Node* node, FILE* file)
    {
    CHECK_TREE_ERROR(tree);

    if (node == nullptr) 
        {
        tree->status |= NODE_PTR_IS_NULL;

        return NODE_PTR_IS_NULL;
        }

    fprintf(file, "(");

    if (node->left)
        {
        TreePostfixPrint(tree, node->left, file);
        }   

    if (node->right) 
        {      
        TreePostfixPrint(tree, node->right, file);
        }

    fprintf(file, SPECIFICATOR_TYPE, node->data);  

    fprintf(file, ")");

    CHECK_TREE_ERROR(tree);

    return tree->status;
    }


Type_error TreeInfixPrint(Tree* tree, Node* node, FILE* file)
    {
    CHECK_TREE_ERROR(tree);

    if (node == nullptr) 
        {
        tree->status |= NODE_PTR_IS_NULL;

        return NODE_PTR_IS_NULL;
        }


    fprintf(file, "(");

    if (node->left) 
        {
        TreeInfixPrint(tree, node->left, file);
        }


    fprintf(file, SPECIFICATOR_TYPE, node->data);

    if (node->right) 
        {
        TreeInfixPrint(tree, node->right, file);
        }


    fprintf(file, ")");
      
    CHECK_TREE_ERROR(tree);

    return tree->status;
    }



Type_error TreeDtor(Tree* tree) 
    {
    if (tree->root == nullptr) 
        {
        tree->status |= TREE_ROOT_IS_NULL;

        return TREE_ROOT_IS_NULL;
        }

    TreeDelete(tree, tree->root);

    tree->root = nullptr;

    tree->size = 0;

    return tree->status;
    }



Type_error CheckTreeLinks(Tree* tree, Node* node)
    {    
    if (node->left != nullptr && node->right != nullptr && (node->left->parent != node || node->right->parent != node))
        {
        tree->status |= TREE_LINKING_ERROR;
        return TREE_LINKING_ERROR;
        }

    if (node->left != nullptr)
        CheckTreeLinks(tree, node->left);
    
    if (node->right != nullptr)
        CheckTreeLinks(tree, node->right);

    return TREE_OK;
    }



bool TreeVerify(Tree* tree) 
    {
    if (tree == nullptr) 
        {
        tree->status |= TREE_IS_NULL;
        }

    if (tree->root == nullptr) 
        {
        tree->status |= TREE_ROOT_IS_NULL;
        }

    else 
        {
        CheckTreeLinks(tree, tree->root);
        }

    if (tree->size < 0) 
        {
        tree->status != TREE_SIZE_LESS_THAN_ZERO;
        }

    return tree->status;
    }


void NodeDump(Node* node, size_t* number_of_node, Child child, const char* color) 
    {
    PrintGraphNode(node, number_of_node, child, color);

    size_t current_number_of_node = *number_of_node;

    if (node->left)
        {
        PrintGraphEdge(current_number_of_node, ++(*number_of_node), L_CHILD, "lime");

        NodeDump(node->left, number_of_node, L_CHILD, "lime");
        }

    if (node->right)
        {
        PrintGraphEdge(current_number_of_node, ++(*number_of_node), R_CHILD, "aqua");

        NodeDump(node->right, number_of_node, R_CHILD, "aqua");
        } 
    }


void PrintGraphEdge(size_t from, size_t to, Child child, const char* color) 
    {
    print("node%d->node%d [color = \"%s\"];\n", from, to, color);
    }


void PrintGraphNode(Node* node, size_t* number_of_node, Child child, const char* color) 
    {
    print("node%d[shape=record, style=filled, fillcolor=\"%s\", label=\" {ADDRESS: %p | DATA: %s | PARENT: %p | LEFT: %p | RIGHT: %p}\"];\n", 
                                              *number_of_node, color, node, node->data, node->parent, node->left, node->right);
    }


void TreeDumpFunction(Tree* tree, const char* path, const char* signature, unsigned line) 
    {
    logfile = fopen("logfile.html", "a");

    fprintf(logfile, "<pre>\n");

    fprintf(logfile, "<font size = \"+1\">path: %s\n</font>", path);

    fprintf(logfile, "<font size = \"+1\">in function: %s\n</font>", signature);

    fprintf(logfile, "<font size = \"+1\">line: %d\n</font>", line);

    if (tree->status != TREE_OK) 
        {
        for (size_t j = 0; j < NUMBER_OF_ERROR; j++)
            {
            if ((tree->status & (1 << j)))
                {
                fprintf(logfile, "<font color = \"red\">ERROR: %s\n</font>", ErrorMas[j + 1].NameError);
                }
            }
        }

    else 
        {
        size_t number_of_node = 0;

        graph_file = fopen("dotfile1.dot", "wb");

        static int dump_number = 1;

        print("digraph struct {bgcolor=RosyBrown rankdir = HR\n\n\n");

        print("Info[shape=record, style=filled, fillcolor=\"grey\", label=\"SIZE: %d\", fontcolor = \"black\", fontsize = 20];\n", tree->size);

        print("label = \"tree_dump from function %s, Tree/%s:%d\";\n", signature, path, line);

        NodeDump(tree->root, &number_of_node, L_CHILD, "red");

        print("\n\n}");

        fclose(graph_file);

        char shell_command[MAX_COMMAND_LENGTH] = "";
            sprintf(shell_command, "dot -Tpng dotfile1.dot -o graph%d.png", dump_number);
            system(shell_command);

        fprintf(logfile, "<img  width=\"1100px\" height=\"600px\" src=\"graph%d.png\">", dump_number);

        fprintf(logfile, ".\n");

        fprintf(logfile, ".\n");

        fprintf(logfile, ".\n");
                
        fclose(logfile);

        dump_number++;
        } 
    }


long long GetFileSize(FILE* file)
    {
    assert(file);

    long long start = ftell(file);
    fseek(file, start, SEEK_END);

    long long bufsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    return bufsize;
    }



void FileInput(FILE* file, Text* data)
    {
    data->BufSize = GetFileSize(file);

    data->Buf = (char*)calloc(data->BufSize + 1, sizeof(char));

    fread(data->Buf, sizeof(char), data->BufSize, file);

    data->Buf[data->BufSize] = '\0';

    fclose(file);
    }



Type_error GetString(Tree* tree, char** ptr, char* end_ptr, char** string)
    {
    assert(*ptr);
    assert(end_ptr);

    *string = *ptr;

    size_t number =  0;

    while (*(*ptr + 1) != ')' && *(*ptr + 1) != '(')
        {
        (*string)[number++] = **ptr;

        (*ptr)++;
        }

    (*string)[number] = '\0';
    
    return tree->status;
    }


Type_error PrefixReadTree(Tree* tree, Node* node, char** ptr, char* end_ptr)
    {
    CHECK_TREE_ERROR(tree);

    while (*ptr <= end_ptr)
        {
        if (**ptr == '(')
            {
            (*ptr)++;

            char* string = nullptr;

            GetString(tree, ptr, end_ptr, &string);
            
            (*ptr)++;

            if (node == nullptr)
                {
                TreeInsert(tree, node, string, L_CHILD);

                node = tree->root;
                }

            else if (node->left == nullptr)
                {
                TreeInsert(tree, node, string, L_CHILD);

                node = node->left;
                }

            else
                {
                TreeInsert(tree, node, string, R_CHILD);

                node = node->right;
                }
            }

        else if (**ptr == ')')
            {
            (*ptr)++;

            if (node == tree->root)
                {
                break;
                }

            node = node->parent;
            }
        }

    CHECK_TREE_ERROR(tree);
    
    return tree->status;
    }



Type_error TreeRead(Tree* tree, Text* data)
    {
    char* ptr = data->Buf;

    char* end_ptr = data->Buf + data->BufSize - 1;

    ptr = data->Buf;

    PrefixReadTree(tree, tree->root, &ptr, end_ptr);
    
    return tree->status;
    }