#ifndef RBTREE_H
#define RBTREE_H

#define COUNT 5
typedef struct RBTreeNode RBTreeNode;

RBTreeNode *insertRBTNode(RBTreeNode *root, int value);
RBTreeNode *searchRBTNode(RBTreeNode *root, int value);
RBTreeNode *deleteRBTNode(RBTreeNode *root, int value);
int findMinRBT(RBTreeNode *root);
int findMaxRBT(RBTreeNode *root);
int findHeightRBT(RBTreeNode *root);
int treeSizeRBT(RBTreeNode *root);
void inOrderTraversalRBT(RBTreeNode *root);
void preOrderTraversalRBT(RBTreeNode *root);
void postOrderTraversalRBT(RBTreeNode *root);

#endif //
