#ifndef RBTREE_H
#define RBTREE_H

#define COUNT 5
typedef struct RBTreeNode RBTreeNode;

void insertRBTNode(int value);
RBTreeNode *searchRBTNode(int value);
void deleteRBTNode(int value);
RBTreeNode *findMinRBT();
RBTreeNode *findMaxRBT();
int findHeightRBT(RBTreeNode *root);
int treeSizeRBT(RBTreeNode *root);
void inOrderTraversalRBT(RBTreeNode *root);
void preOrderTraversalRBT(RBTreeNode *root);
void postOrderTraversalRBT(RBTreeNode *root);

#endif //
