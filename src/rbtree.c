#include "../lib/rbtree.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

struct RBTreeNode {
    int data;
    Color color;
    struct RBTreeNode *parent;
    struct RBTreeNode *left;
    struct RBTreeNode *right;
};

RBTreeNode *createRBTNode(int value) {
    RBTreeNode *newNode = (RBTreeNode *)malloc(sizeof(RBTreeNode));
    if (newNode == NULL) {
	printf("Error: Memory allocation failed.\n");
	return NULL;
    }

    newNode->data = value;
    newNode->color = RED; // New nodes are initially red
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

RBTreeNode *leftRotate(RBTreeNode *root, RBTreeNode *x) {
    RBTreeNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
	y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
	root = y;
    } else if (x == x->parent->left) {
	x->parent->left = y;
    } else {
	x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return root;
}

RBTreeNode *rightRotate(RBTreeNode *root, RBTreeNode *y) {
    RBTreeNode *x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
	x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
	root = x;
    } else if (y == y->parent->left) {
	y->parent->left = x;
    } else {
	y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
    return root;
}

// Insertion Fix-Up to maintain Red-Black Tree Properties
RBTreeNode *insertFixup(RBTreeNode *root, RBTreeNode *z) {
    while (z->parent != NULL && z->parent->color == RED) {
	if (z->parent == z->parent->parent->left) {
	    RBTreeNode *y = z->parent->parent->right;
	    if (y != NULL && y->color == RED) {
		z->parent->color = BLACK;
		y->color = BLACK;
		z->parent->parent->color = RED;
		z = z->parent->parent;
	    } else {
		if (z == z->parent->right) {
		    z = z->parent;
		    root = leftRotate(root, z);
		}
		z->parent->color = BLACK;
		z->parent->parent->color = RED;
		root = rightRotate(root, z->parent->parent);
	    }
	} else {
	    RBTreeNode *y = z->parent->parent->left; // Get the left sibling
	    if (y != NULL && y->color == RED) {
		z->parent->color = BLACK;
		y->color = BLACK;
		z->parent->parent->color = RED;
		z = z->parent->parent;
	    } else {
		if (z ==
		    z->parent->left) { // If z is on the left side of its parent
		    z = z->parent;
		    root = rightRotate(root, z);
		}
		z->parent->color = BLACK;
		z->parent->parent->color = RED;
		root = leftRotate(root, z->parent->parent);
	    }
	}
    }
    root->color = BLACK;
    return root;
}

// Insert a node into the Red-Black Tree
RBTreeNode *insertRBTNode(RBTreeNode *root, int value) {
    RBTreeNode *z = createRBTNode(value);
    RBTreeNode *y = NULL;
    RBTreeNode *x = root;

    while (x != NULL) {
	y = x;
	if (z->data < x->data) {
	    x = x->left;
	} else if (z->data > x->data) {
	    x = x->right;
	} else {
	    free(z);
	    return root;
	}
    }

    z->parent = y;
    if (y == NULL) {
	root = z;
    } else if (z->data < y->data) {
	y->left = z;
    } else {
	y->right = z;
    }

    return insertFixup(root, z);
}

// Helper function to replace one subtree as a child of its parent
RBTreeNode *transplant(RBTreeNode *root, RBTreeNode *u, RBTreeNode *v) {
    if (u->parent == NULL)
	root = v;
    else if (u == u->parent->left)
	u->parent->left = v;
    else
	u->parent->right = v;

    if (v != NULL)
	v->parent = u->parent;

    return root;
}

// Helper function to find the node with the minimum value in a subtree
RBTreeNode *minimumRBTNode(RBTreeNode *node) {
    while (node->left != NULL)
	node = node->left;
    return node;
}

// Fix the Red-Black Tree after deletion
RBTreeNode *deleteFixup(RBTreeNode *root, RBTreeNode *x) {
    while (x != root && (x == NULL || x->color == BLACK)) {
	if (x == x->parent->left) {
	    RBTreeNode *w = x->parent->right;
	    if (w != NULL && w->color == RED) {
		w->color = BLACK;
		x->parent->color = RED;
		root = leftRotate(root, x->parent);
		w = x->parent->right;
	    }
	    if ((w->left == NULL || w->left->color == BLACK) &&
		(w->right == NULL || w->right->color == BLACK)) {
		if (w != NULL)
		    w->color = RED;
		x = x->parent;
	    } else {
		if (w == NULL || w->right == NULL || w->right->color == BLACK) {
		    if (w->left != NULL)
			w->left->color = BLACK;
		    if (w != NULL)
			w->color = RED;
		    root = rightRotate(root, w);
		    w = x->parent->right;
		}
		if (w != NULL)
		    w->color = x->parent->color;
		x->parent->color = BLACK;
		if (w->right != NULL)
		    w->right->color = BLACK;
		root = leftRotate(root, x->parent);
		x = root;
	    }
	} else {
	    RBTreeNode *w = x->parent->left;
	    if (w != NULL && w->color == RED) {
		w->color = BLACK;
		x->parent->color = RED;
		root = rightRotate(root, x->parent);
		w = x->parent->left;
	    }
	    if ((w->right == NULL || w->right->color == BLACK) &&
		(w->left == NULL || w->left->color == BLACK)) {
		if (w != NULL)
		    w->color = RED;
		x = x->parent;
	    } else {
		if (w == NULL || w->left == NULL || w->left->color == BLACK) {
		    if (w->right != NULL)
			w->right->color = BLACK;
		    if (w != NULL)
			w->color = RED;
		    root = leftRotate(root, w);
		    w = x->parent->left;
		}
		if (w != NULL)
		    w->color = x->parent->color;
		x->parent->color = BLACK;
		if (w->left != NULL)
		    w->left->color = BLACK;
		root = rightRotate(root, x->parent);
		x = root;
	    }
	}
    }
    if (x != NULL)
	x->color = BLACK;
    return root;
}

// Delete a node from the Red-Black Tree
RBTreeNode *deleteRBTNode(RBTreeNode *root, int value) {
    RBTreeNode *z = searchRBTNode(root, value);
    if (z == NULL)
	return root;

    RBTreeNode *y = z;
    RBTreeNode *x;
    Color yOriginalColor = y->color;

    if (z->left == NULL) {
	x = z->right;
	root = transplant(root, z, z->right);
    } else if (z->right == NULL) {
	x = z->left;
	root = transplant(root, z, z->left);
    } else {
	y = minimumRBTNode(z->right);
	yOriginalColor = y->color;
	x = y->right;
	if (y->parent == z)
	    x->parent = y;
	else {
	    root = transplant(root, y, y->right);
	    y->right = z->right;
	    y->right->parent = y;
	}
	root = transplant(root, z, y);
	y->left = z->left;
	y->left->parent = y;
	y->color = z->color;
    }

    free(z);
    if (yOriginalColor == BLACK)
	root = deleteFixup(root, x);
    return root;
}

RBTreeNode *searchRBTNode(RBTreeNode *root, int value) {
    RBTreeNode *current = root;
    while (current != NULL && current->data != value) {
	if (value < current->data) {
	    current = current->left;
	} else {
	    current = current->right;
	}
    }
    return current;
}

int findMinRBT(RBTreeNode *root) {
    while (root->left != NULL) {
	root = root->left;
    }
    return root->data;
}

int findMaxRBT(RBTreeNode *root) {
    while (root->right != NULL) {
	root = root->right;
    }
    return root->data;
}

int findHeightRBT(RBTreeNode *root) {
    if (root == NULL) {
	return -1;
    }
    int leftHeight = findHeightRBT(root->left);
    int rightHeight = findHeightRBT(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int treeSizeRBT(RBTreeNode *root) {
    if (root == NULL) {
	return 0;
    }
    return 1 + treeSizeRBT(root->left) + treeSizeRBT(root->right);
}

void inOrderTraversalRBT(RBTreeNode *root) {
    if (root != NULL) {
	inOrderTraversalRBT(root->left);
	printf("%d ", root->data);
	inOrderTraversalRBT(root->right);
    }
}

void preOrderTraversalRBT(RBTreeNode *root) {
    if (root != NULL) {
	printf("%d ", root->data);
	preOrderTraversalRBT(root->left);
	preOrderTraversalRBT(root->right);
    }
}

void postOrderTraversalRBT(RBTreeNode *root) {
    if (root != NULL) {
	postOrderTraversalRBT(root->left);
	postOrderTraversalRBT(root->right);
	printf("%d ", root->data);
    }
}

void print2DUtilRBT(RBTreeNode *root, int space) {
    if (root == NULL)
	return;

    space += COUNT;

    print2DUtilRBT(root->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
	printf(" ");

    // Set text color based on the node's color
    if (root->color == RED) {
	printf("\033[31m"); // Set text color to red
    }

    printf("%d\x1b[0m\n",
	   root->data); // Reset text color after printing the value

    print2DUtilRBT(root->left, space);
}

void print2DRBT(RBTreeNode *root) { print2DUtilRBT(root, 0); }

void rbtreeMenu() {
    int treeChoice;
    RBTreeNode *root = NULL;
    do {
	printf("Red Black Tree Menu:\n");
	printf("1. Insert Node\t\t2. Search Node\t\t3. Delete Node (not "
	       "available yet)\n");
	printf("4. Find Minimum Value\t5. Find Maximum Value\t6. Height Of "
	       "Tree\n");
	printf("7. Size Of Tree\t\t8. In Order Traversal\t9. Pre-Order "
	       "Traversal\n");
	printf("10. Post-Order Traversal\t11. Visualize\t\t0. Back To Main "
	       "Menu\n");

	printf("Option: ");
	scanf("%d", &treeChoice);

	switch (treeChoice) {
	case 1:
	    printf("Enter a value to insert: ");
	    int value;
	    scanf("%d", &value);
	    root = insertRBTNode(root, value);
	    break;

	case 2:
	    printf("Enter a value to search: ");
	    scanf("%d", &value);
	    RBTreeNode *result = searchRBTNode(root, value);
	    if (result != NULL) {
		printf("Value found in the tree.\n");
	    } else {
		printf("Value not found in the tree.\n");
	    }
	    break;

	case 3:
	    printf("Enter a value to delete: ");
	    scanf("%d", &value);
	    root = deleteRBTNode(root, value);
	    break;

	case 4:
	    printf("Minimum value in the tree: %d\n", findMinRBT(root));
	    break;

	case 5:
	    printf("Maximum value in the tree: %d\n", findMaxRBT(root));
	    break;

	case 6:
	    printf("Height of the tree: %d\n", findHeightRBT(root));
	    break;

	case 7:
	    printf("Size of the tree: %d\n", treeSizeRBT(root));
	    break;

	case 8:
	    printf("In Order Traversal: ");
	    inOrderTraversalRBT(root);
	    printf("\n");
	    break;

	case 9:
	    printf("Pre-Order Traversal: ");
	    preOrderTraversalRBT(root);
	    printf("\n");
	    break;

	case 10:
	    printf("Post-Order Traversal: ");
	    postOrderTraversalRBT(root);
	    printf("\n");
	    break;

	case 11:
	    print2DRBT(root);
	    break;

	case 0:
	    break;

	default:
	    printf("Invalid menu choice. Please try again.\n");
	    break;
	}
    } while (treeChoice != 0);
}
