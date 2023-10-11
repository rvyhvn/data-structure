#ifndef TREE_H
#define TREE_H

typedef struct TreeNode TreeNode;

TreeNode *insert(TreeNode *root, int value);
TreeNode *search(TreeNode *root, int value);
TreeNode *deleteNode(TreeNode *root, int value);
int findMin(TreeNode *root);
int findMax(TreeNode *root);
int findHeight(TreeNode *root);
int treeSize(TreeNode *root);
void inOrderTraversal(TreeNode *root);
void preOrderTraversal(TreeNode *root);
void postOrderTraversal(TreeNode *root);

#endif //
