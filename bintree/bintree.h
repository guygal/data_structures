#ifndef BINTREE_H
#define BINTREE_H

#include <stdlib.h>

#define HAS_LEFT(node) ((node)->left != NULL)
#define HAS_RIGHT(node) ((node)->right != NULL)
#define IS_LEAF(node) (!HAS_LEFT(node) && !HAS_RIGHT(node))
#define IS_ROOT(node) (!((node)->parent))

#define TABWIDTH 4

typedef struct StructBinNode
{
    struct StructBinNode *left, *right, *parent;
    int data;
} BinNode;

typedef struct
{
    BinNode *root;
    int size;
    int height;
} BinTree;

#include "extra/pair.h"
PAIR(BinNode *, int, Pair)

BinTree *createBinTree();
void printBinTree(BinTree *tree);
void printBinTreeByLevel(BinTree *tree);
void insertBinNode(int data, BinTree *tree);
BinNode *search(BinNode *root, int data);
void removeBinNode(BinNode **node, BinTree *tree);
void removeBinNodeByData(int data, BinTree *tree);
void clearBinTree(BinTree *tree);
void freeBinTree(BinTree **tree);
int isEmptyBinTree(BinTree *tree);

void traversalPreorder(BinNode *root, void (*f)(BinNode *, int));
void traversalInorder(BinNode *root, void (*f)(BinNode *, int));
void traversalPostorder(BinNode *root, void (*f)(BinNode *, int));
void traversalLevelorder(BinNode *root, void (*f)(BinNode *, int));

BinNode *createBinNode(int data, BinNode *parent,
                       BinNode *left, BinNode *right);
BinNode *findMin(BinNode *node);
void updateParent(BinTree *tree, BinNode **node, BinNode *value);
void printBinNode(BinNode *node, int height);
void freeBinNode(BinNode *node, int height);

#endif
