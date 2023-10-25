#ifndef BSTREE_H
#define BSTREE_H

#define COUNT 5
typedef struct BSTreeNode BSTreeNode;

BSTreeNode *insertBSTNode(BSTreeNode *root, int value);
BSTreeNode *searchBSTNode(BSTreeNode *root, int value);
BSTreeNode *deleteBSTNode(BSTreeNode *root, int value);
int findMinBST(BSTreeNode *root);
int findMaxBST(BSTreeNode *root);
int findHeightBST(BSTreeNode *root);
int treeSizeBST(BSTreeNode *root);
void inOrderTraversalBST(BSTreeNode *root);
void preOrderTraversalBST(BSTreeNode *root);
void postOrderTraversalBST(BSTreeNode *root);

#endif //
