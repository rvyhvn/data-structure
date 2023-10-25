#ifndef RBTREE_H
#define RBTREE_H

#define COUNT 5
typedef struct RBTreeNode RBTreeNode;

void insertRBTNode(int value, RBTreeNode **root);
RBTreeNode *searchRBTNode(int value, RBTreeNode *root);
void deleteRBTNode(int value, RBTreeNode **root);
RBTreeNode *findMinRBT(RBTreeNode *root);
RBTreeNode *findMaxRBT(RBTreeNode *root);
int findHeightRBT(RBTreeNode *root);
int treeSizeRBT(RBTreeNode *root);
void inOrderTraversalRBT(RBTreeNode *root);
void preOrderTraversalRBT(RBTreeNode *root);
void postOrderTraversalRBT(RBTreeNode *root);

#endif //
