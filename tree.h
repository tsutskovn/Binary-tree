#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>


#define CHECK_TREE_ERROR(tree)                           \
                    if (TreeVerify(tree) != TREE_OK)     \
                        {                                \
                        ON_DUMP                          \
                            (                            \
                            TreeDump(tree);              \
                            )                            \
                        return tree->status;             \
                        }


#ifdef DUMP
    #define ON_DUMP(...) __VA_ARGS__
    #define TreeDump(tree_ptr) TreeDumpFunction(tree_ptr, __FILE__, __PRETTY_FUNCTION__, __LINE__);

#else
    #define ON_DUMP(...)
#endif

typedef char* Tree_type;


typedef int Type_error;


enum Tree_status
    {
    TREE_OK                       = 0,
    TREE_IS_NULL                  = 1 << 0,
    TREE_ROOT_IS_NULL             = 1 << 1,
    NODE_PTR_IS_NULL              = 1 << 2,  
    TREE_CANT_HAVE_THIS_CHILD     = 1 << 3,
    TREE_SIZE_LESS_THAN_ZERO      = 1 << 4,
    TREE_LINKING_ERROR            = 1 << 5,
    NUMBER_OF_ERROR               = 6
    };


struct Node 
    {
    Node* left;
    Node* right;
    Node* parent;
    Tree_type data;
    };


struct Tree 
    {
    Node* root;
    size_t size;
    Type_error status;
    };


enum Child
    {
    L_CHILD = 0,
    R_CHILD = 1,
    };


struct Text
    {
    char* Buf;
    long long BufSize;
    };


static FILE* graph_file = NULL;

static FILE* logfile = NULL;

const int MAX_COMMAND_LENGTH = 125;

#define print(...) fprintf(graph_file, __VA_ARGS__)

#define SPECIFICATOR_TYPE "%s "


struct TREE_STATUS
    {
    Tree_status CodeError;
    const char* NameError;
    };


const TREE_STATUS ErrorMas[] = 
    {
    {TREE_OK,                     "NO ERROR"},
    {TREE_IS_NULL,                "TREE_IS_NUL"},
    {TREE_ROOT_IS_NULL,           "TREE_ROOT_IS_NULL"},
    {NODE_PTR_IS_NULL,            "NODE_PTR_IS_NULL"},
    {TREE_CANT_HAVE_THIS_CHILD,   "TREE_CANT_HAVE_THIS_CHILD"},
    {TREE_SIZE_LESS_THAN_ZERO,    "TREE_SIZE_LESS_THAN_ZERO"},
    {TREE_LINKING_ERROR,          "TREE_LINKING_ERROR"}
    };


void TreeCtor(Tree* tree);

Node* TreeNodeCtor(Tree_type data);

Type_error TreeInsert(Tree* tree, Node* node, Tree_type data, Child child);

Type_error TreeDelete(Tree* tree, Node* node);

Type_error TreePrefixPrint(Tree* tree, Node* node, FILE* file);

Type_error TreePostfixPrint(Tree* tree, Node* node, FILE* file);

Type_error TreeInfixPrint(Tree* tree, Node* node, FILE* file);

bool TreeVerify(Tree* tree);

Type_error TreeDtor(Tree* tree); 

void TreeDumpFunction(Tree* tree, const char* path, const char* signature, unsigned line); 

void NodeDump(Node* node, size_t* number_of_node, Child child, const char* color);

void PrintGraphEdge(size_t from, size_t to, Child child, const char* color); 

void PrintGraphNode(Node* node, size_t* number_of_node, Child child, const char* color); 

long long GetFileSize(FILE* file);

void FileInput(FILE* file, Text* data);

Type_error GetString(Tree* tree, char** ptr, char* end_ptr, char** string);

Type_error PrefixReadTree(Tree* tree, Node* node, char** ptr, char* end_ptr);

Type_error TreeRead(Tree* tree, Text* data);

Type_error CheckTreeLinks(Tree* tree, Node* node);
