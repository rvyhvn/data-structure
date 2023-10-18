#include "../lib/rbtree.h"
#include <stdio.h>
#include <stdlib.h>

struct RBTreeNode {
    int data;
    struct RBTreeNode *left;
    struct RBTreeNode *right;
    int color;
};

RBTreeNode *createNode(int value) {
    RBTreeNode *newNode = (RBTreeNode *)malloc(sizeof(RBTreeNode));
    if (newNode == NULL) {
	fprintf(stderr, "Memory allocation failed.");
	return NULL;
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = 1; // New nodes are always red
    return newNode;
}

RBTreeNode *leftRotate(RBTreeNode *root, RBTreeNode *node) {
    RBTreeNode *rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    rightChild->color = node->color;
    node->color = 1;
    return rightChild;
}

RBTreeNode *rightRotate(RBTreeNode *root, RBTreeNode *node) {
    RBTreeNode *leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    leftChild->color = node->color;
    node->color = 1;
    return leftChild;
}

void flipColors(RBTreeNode *node) {
    node->color = 1 - node->color;
    if (node->left != NULL)
	node->left->color = 1 - node->left->color;
    if (node->right != NULL)
	node->right->color = 1 - node->right->color;
}

RBTreeNode *insertRBTNode(RBTreeNode *root, int value) {
    if (root == NULL) {
	return createNode(value);
    }

    if (value < root->data) {
	root->left = insertRBTNode(root->left, value);
    } else if (value > root->data) {
	root->right = insertRBTNode(root->right, value);
    } else {
	// Duplicate value, do nothing
	return root;
    }

    if (root->right != NULL && root->right->color == 1) {
	root = leftRotate(root, root);
    }
    if (root->left != NULL && root->left->color == 1 &&
	root->left->left != NULL && root->left->left->color == 1) {
	root = rightRotate(root, root);
    }
    if (root->left != NULL && root->left->color == 1 && root->right != NULL &&
	root->right->color == 1) {
	flipColors(root);
    }

    return root;
}
