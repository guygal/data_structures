#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

BinTree *createBinTree()
{
    BinTree *tree = (BinTree *)malloc(sizeof(BinTree));
    if (tree == NULL) {
        fprintf(stderr, "Failed to allocate memory for a binary tree\n");
        return NULL;
    }
    tree->root = NULL;
    tree->size = 0;
    return tree;
}

Node *createBinNode(int data, Node *parent, Node *left, Node *right)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Failed to allocate memory for a binary node\n");
        return NULL;
    }

    node->data = data;
    node->parent = parent;
    node->left = left;
    node->right = right;

    return node;
}

void insert1(int data, Node **node, Node *parent)
{
    if (node == NULL)
        return;

    if (*node == NULL) {
        *node = createBinNode(data, parent, NULL, NULL);
        return;
    }

    if (data < (*node)->data)
        insert1(data, &((*node)->left), *node);
    else
        insert1(data, &((*node)->right), *node);
}

void insertBinNode(int data, BinTree *tree)
{
    Node **root = &(tree->root);

    if (root == NULL)
        return;

    if (*root == NULL) {
        *root = createBinNode(data, NULL, NULL, NULL);
        if (*root == NULL)
            return;
    } else {
        insert1(data, root, (*root)->parent);
    }

    ++(tree->size);
}

void traversalPreorder(Node *root, void (*f)(Node *, int), int level)
{
    f(root, level);

    if (root == NULL)
        return;

    traversalPreorder(root->left, f, level + 1);
    traversalPreorder(root->right, f, level + 1);
}

void traversalInorder(Node *root, void (*f)(Node *, int), int level)
{
    if (root != NULL)
        traversalInorder(root->left, f, level);
    
    f(root, level);

    if (root != NULL)
        traversalInorder(root->right, f, level);
}

void traversalPostorder(Node *root, void (*f)(Node *, int), int level)
{
    if (root != NULL)
        traversalInorder(root->left, f, level);
    
    if (root != NULL)
        traversalInorder(root->right, f, level);

    f(root, level);
}

void traversalLevelorder(Node *root, void (*f)(Node *, int))
{
    int level = 0;  // TODO: calculate each node's level
    Queue *q = createQueue();
    Node *n = NULL;
    pushQueue(q, root);
    while (!isEmptyQueue(q)) {
        n = popQueue(q);
        f(n, level);
        if (n->left != NULL)
            pushQueue(q, n->left);
        if (n->right != NULL)
            pushQueue(q, n->right);
    }
    freeQueue(&q);
}

/*Node *search(Node *root, int data)
{
    if (root == NULL || root->data == data)
        return root;

    if (root->data > data)
        return search(root->left, data);
    else
        return search(root->right, data);
}*/

Node *search(Node *root, int data)
{
    while (root != NULL && root->data != data) {
        if (root->data > data)
            root = root->left;
        else
            root = root->right;
    }
    return root;
}

Node *findMin(Node *node)
{
    if (node == NULL)
        return NULL;

    while (HAS_LEFT(node))
        node = node->left;
    return node;
}

// updates parent's pointer before removal
void updateParent(Node **node, Node *value)
{
    if (node == NULL)
        return;

    if ((*node)->parent == NULL)
        return;

    if ((*node)->parent->left == *node)
        (*node)->parent->left = value;
    else
        (*node)->parent->right = value;

    if (value != NULL)
        value->parent = (*node)->parent;
}

void removeBinNode(Node **node, BinTree *tree)
{
    if (node == NULL || *node == NULL)
        return;

    if (IS_LEAF(*node)) {
        // 1. Deleting a leaf (node with no children):
        // Deleting a leaf is easy, as we can simply remove it from the tree.
        updateParent(node, NULL);
        free((void *)*node);
    } else if (HAS_LEFT(*node) && !HAS_RIGHT(*node)) {
        // 2. Deleting a node with one child:
        // Remove the node and replace it with its child.
        updateParent(node, (*node)->left);
        free((void *)*node);
    } else if (!HAS_LEFT(*node) && HAS_RIGHT(*node)) {
        updateParent(node, (*node)->right);
        free((void *)*node);
    } else {  //  HAS_LEFT(*node) && HAS_RIGHT(*node)
        // 3. Deleting a node with two children:
        // Do not delete "node". Find the smallest (the leftest) child of
        // the right node's subtree (call him "m") and copy from "m" to "node"
        // all data (not including left, right or parent pointers) to "node".
        // Remove m.
        Node *m = findMin((*node)->right);
        (*node)->data = m->data;
        removeBinNode(&m, tree);
    }

    --(tree->size);
}

void removeBinNodeByData(int data, BinTree *tree)
{
    Node *f = search(tree->root, data);

    if (f == NULL)
        fprintf(stderr, "Unable to find node %d\n", data);
    else
        removeBinNode(&f, tree);
}

void printBinNode(Node *node, int level)
{
    int i;
    //for (i = 0; i < level * TABWIDTH; ++i)
    for (i = level * TABWIDTH; i > 0; --i)
        printf(" ");

    if (node == NULL)
        printf("NULL\n");
    else
        printf("%d\n", node->data);
}

void printBinTree(BinTree *tree)
{
    printf("\nPreorder traversal:\n");
    traversalPreorder(tree->root, &printBinNode, 0);
}

void printBinTreeByLevel(BinTree *tree)
{
    printf("\nQueue-based level order traversal:\n");
    traversalLevelorder(tree->root, &printBinNode); 
}

void freeBinNode(Node *node, int level)
{
    if (node != NULL)
        free((void *)node);
}

void clearBinTree(BinTree *tree)
{
    if (tree == NULL || tree->root == NULL || tree->size == 0)
        return;

    traversalPostorder(tree->root, &freeBinNode, 0);
    tree->size = 0;
}

void freeBinTree(BinTree **tree)
{
    clearBinTree(*tree);
    free((void *)*tree);
    tree = NULL;
}

int isEmptyTree(BinTree *tree)
{
    return tree->size == 0;
}