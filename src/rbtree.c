#include "../lib/rbtree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct RBTreeNode {
    int value;
    struct RBTreeNode *parent;
    struct RBTreeNode *left;
    struct RBTreeNode *right;
    int color;
} RBTreeNode;

RBTreeNode *newNode(int value, RBTreeNode *parent) {
    RBTreeNode *create = (RBTreeNode *)(malloc(sizeof(RBTreeNode)));
    create->value = value;
    create->parent = parent;
    create->left = NULL;
    create->right = NULL;
    create->color = 1;
    return create;
}

// Check if the node is the leaf
int isLeaf(RBTreeNode *n) {
    if (n->left == NULL && n->right == NULL) {
	return 1;
    }
    return 0;
}

// Left Rotate
RBTreeNode *leftRotate(RBTreeNode *node) {
    RBTreeNode *parent = node->parent;
    RBTreeNode *grandParent = parent->parent;

    parent->right = node->left;
    if (node->left != NULL) {
	node->left->parent = parent;
    }
    node->parent = grandParent;
    parent->parent = node;
    node->left = parent;
    if (grandParent != NULL) {
	if (grandParent->right == parent) {
	    grandParent->right = node;
	} else {
	    grandParent->left = node;
	}
    }
    return node;
}

// Right Rotate
RBTreeNode *rightRotate(RBTreeNode *node) {
    RBTreeNode *parent = node->parent;
    RBTreeNode *grandParent = parent->parent;

    parent->left = node->right;
    if (node->right != NULL) {
	node->right->parent = parent;
    }
    node->parent = grandParent;
    parent->parent = node;
    node->right = parent;
    if (grandParent != NULL) {
	if (grandParent->right == parent) {
	    grandParent->right = node;
	} else {
	    grandParent->left = node;
	}
    }
    return node;
}

// Check the node after the insertion step
void insertFixup(RBTreeNode *node) {
    // If the node is the root
    if (node == NULL || node->parent == NULL) {
	return;
    }
    RBTreeNode *child = node;
    // If it is a black node or its parent is a black node
    if (node->color == 0 || (node->parent)->color == 0) {
	// Dont Do Anything
	return;
    }

    // Both parent and child are red
    // Check For Uncle
    RBTreeNode *parent = node->parent;
    RBTreeNode *grandParent = parent->parent;

    // If grandParent is NULL, then parent is the root.
    // Just make the root black.
    if (grandParent == NULL) {
	parent->color = 0;
	return;
    }

    // If both the children of the grandParent are red
    if (grandParent->right != NULL && (grandParent->right)->color == 1 &&
	grandParent->left != NULL && (grandParent->left)->color == 1) {
	// Make the grandParent red and both of its children black
	(grandParent->right)->color = 0;
	(grandParent->left)->color = 0;
	grandParent->color = 1;
	return;
    } else {
	// The only option left is rotation.
	RBTreeNode *greatGrandParent = grandParent->parent;
	// Right Case
	if (grandParent->right == parent) {
	    // Right Right Case
	    if (parent->right == node) {
		grandParent->right = parent->left;
		if (parent->left != NULL) {
		    (parent->left)->parent = grandParent;
		}
		parent->left = grandParent;
		grandParent->parent = parent;

		// Attach to existing Tree;
		parent->parent = greatGrandParent;
		if (greatGrandParent != NULL) {
		    if (greatGrandParent->left != NULL &&
			greatGrandParent->left == grandParent) {
			greatGrandParent->left = parent;
		    } else {
			greatGrandParent->right = parent;
		    }
		}

		// Change the colors
		parent->color = 0;
		grandParent->color = 1;
	    } else { // Right Left Case
		// First step -> Parent Child Rotation
		parent->left = child->right;
		if (child->right != NULL) {
		    (child->right)->parent = parent;
		}
		child->right = parent;
		parent->parent = child;

		// Second step -> Child and GrandParent Rotation
		grandParent->right = child->left;
		if (child->left != NULL) {
		    (child->left)->parent = grandParent;
		}
		child->left = grandParent;
		grandParent->parent = child;

		// Attach to the existing tree
		child->parent = greatGrandParent;
		if (greatGrandParent != NULL) {
		    if (greatGrandParent->left != NULL &&
			greatGrandParent->left == grandParent) {
			greatGrandParent->left = child;
		    } else {
			greatGrandParent->right = child;
		    }
		}

		// Change The Colors
		child->color = 0;
		grandParent->color = 1;
	    }
	} else { // Left Case
	    // Left Left Case
	    if (parent->left == node) {
		grandParent->left = parent->right;
		if (parent->right != NULL) {
		    (parent->right)->parent = grandParent;
		}
		parent->right = grandParent;
		grandParent->parent = parent;

		// Attach to existing Tree;
		parent->parent = greatGrandParent;
		if (greatGrandParent != NULL) {
		    if (greatGrandParent->left != NULL &&
			greatGrandParent->left == grandParent) {
			greatGrandParent->left = parent;
		    } else {
			greatGrandParent->right = parent;
		    }
		}

		// Change the colors
		parent->color = 0;
		grandParent->color = 1;
	    } else { // Left Right Case

		// First step -> Parent Child Rotation
		parent->right = child->left;
		if (child->left != NULL) {
		    (child->left)->parent = parent;
		}
		child->left = parent;
		parent->parent = child;

		// Second step -> Child and GrandParent Rotation
		grandParent->left = child->right;
		if (child->right != NULL) {
		    (child->right)->parent = grandParent;
		}
		child->right = grandParent;
		grandParent->parent = child;

		// Attach to the existing tree
		child->parent = greatGrandParent;
		if (greatGrandParent != NULL) {
		    if (greatGrandParent->left != NULL &&
			greatGrandParent->left == grandParent) {
			greatGrandParent->left = child;
		    } else {
			greatGrandParent->right = child;
		    }
		}

		// Change The Colors
		child->color = 0;
		grandParent->color = 1;
	    }
	}
    }
}

// To insert a node in the existing tree
void insertRBTNode(int value, RBTreeNode **root) {
    RBTreeNode *buffRoot = *root;
    while (buffRoot) {
	if (buffRoot->value == value) {
	    // Value already exists
	    return;
	} else if (buffRoot->value > value) {
	    // Go left
	    if (buffRoot->left != NULL) {
		buffRoot = buffRoot->left;
	    } else {
		// Insert The RBTreeNode
		RBTreeNode *toInsert = newNode(value, buffRoot);
		buffRoot->left = toInsert;
		buffRoot = toInsert;

		// Check For Double Red Problems
		break;
	    }
	} else {
	    // Go right
	    if (buffRoot->right != NULL) {
		buffRoot = buffRoot->right;
	    } else {
		// Insert The RBTreeNode
		RBTreeNode *toInsert = newNode(value, buffRoot);
		buffRoot->right = toInsert;
		buffRoot = toInsert;

		// Check For Double Red Problems
		break;
	    }
	}
    }

    while (buffRoot != *root) {
	insertFixup(buffRoot);
	if (buffRoot->parent == NULL) {
	    *root = buffRoot;
	    break;
	}
	buffRoot = buffRoot->parent;
	if (buffRoot == *root) {
	    buffRoot->color = 0;
	}
    }
}

void checkForCase2(RBTreeNode *toDelete, int delete, int fromDirection,
		   RBTreeNode **root) {
    if (toDelete == (*root)) {
	(*root)->color = 0;
	return;
    }

    if (!delete &&toDelete->color == 1) {
	if (!fromDirection) {
	    if (toDelete->right != NULL) {
		toDelete->right->color = 1;
	    }
	} else {
	    if (toDelete->left != NULL) {
		toDelete->left->color = 1;
	    }
	}
	toDelete->color = 0;
	return;
    }

    // Get the sibling for further inspection
    RBTreeNode *sibling;
    RBTreeNode *parent = toDelete->parent;
    int locateChild = 0; // 0 if toDeleted is left of its parent else 1
    if (parent->right == toDelete) {
	sibling = parent->left;
	locateChild = 1;
    } else {
	sibling = parent->right;
    }

    // Case 2.1. i.e. if the any children of the sibling is red
    if ((sibling->right != NULL && sibling->right->color == 1) ||
	(sibling->left != NULL && sibling->left->color == 1)) {
	if (sibling->right != NULL && sibling->right->color == 1) {
	    // Sibling is left and child is right. i.e. LEFT RIGHT ROTATION
	    if (locateChild == 1) {
		int parColor = parent->color;

		// Step 1: Left rotate sibling
		sibling = leftRotate(sibling->right);

		// Step 2: Right rotate updated sibling
		parent = rightRotate(sibling);

		// Check if the root is rotated
		if (parent->parent == NULL) {
		    *root = parent;
		}

		// Step 3: Update the colors
		parent->color = parColor;
		parent->left->color = 0;
		parent->right->color = 0;

		// Delete the node (present at parent->right->right)
		if (delete) {
		    if (toDelete->left != NULL) {
			toDelete->left->parent = parent->right;
		    }
		    parent->right->right = toDelete->left;
		    free(toDelete);
		}
	    } else { // Sibling is right and child is also right. i.e. LEFT
		     // LEFT ROTATION

		int parColor = parent->color;

		// Left Rotate the sibling
		parent = leftRotate(sibling);

		// Check if the root is rotated
		if (parent->parent == NULL) {
		    *root = parent;
		}

		// Update Colors
		parent->color = parColor;
		parent->left->color = 0;
		parent->right->color = 0;

		// Delete the node (present at parent->left->left)
		if (delete) {
		    if (toDelete->right != NULL) {
			toDelete->right->parent = parent->left;
		    }
		    parent->left->left = toDelete->left;
		    free(toDelete);
		}
	    }
	} else {
	    // Sibling is right and child is left. i.e. RIGHT LEFT ROTATION
	    if (locateChild == 0) {
		int parColor = parent->color;

		// Step 1: Right rotate sibling
		sibling = rightRotate(sibling->left);

		// printf("%d - reached\n", sibling->val);
		// return;

		// Step 2: Left rotate updated sibling
		parent = leftRotate(sibling);

		// Check if the root is rotated
		if (parent->parent == NULL) {
		    *root = parent;
		}

		// Step 3: Update the colors
		parent->color = parColor;
		parent->left->color = 0;
		parent->right->color = 0;

		// Delete the node (present at parent->left->left)
		if (delete) {
		    if (toDelete->right != NULL) {
			toDelete->right->parent = parent->left;
		    }
		    parent->left->left = toDelete->right;
		    free(toDelete);
		}
	    } else { // Sibling is left and child is also left. i.e. RIGHT
		     // RIGHT ROTATION

		int parColor = parent->color;

		// Right Rotate the sibling
		parent = rightRotate(sibling);

		// Check if the root is rotated
		if (parent->parent == NULL) {
		    *root = parent;
		}

		// Update Colors
		parent->color = parColor;
		parent->left->color = 0;
		parent->right->color = 0;

		// Delete the node (present at parent->right->right)
		if (delete) {
		    if (toDelete->left != NULL) {
			toDelete->left->parent = parent->right;
		    }
		    parent->right->right = toDelete->left;
		    free(toDelete);
		}
	    }
	}
    } else if (sibling->color ==
	       0) { // Make the sibling red and recur for its parent

	// Recolor the sibling
	sibling->color = 1;

	// Delete if necessary
	if (delete) {
	    if (locateChild) {
		toDelete->parent->right = toDelete->left;
		if (toDelete->left != NULL) {
		    toDelete->left->parent = toDelete->parent;
		}
	    } else {
		toDelete->parent->left = toDelete->right;
		if (toDelete->right != NULL) {
		    toDelete->right->parent = toDelete->parent;
		}
	    }
	}

	checkForCase2(parent, 0, locateChild, root);
    } else { // Bring the sibling on top and apply 2.1 or 2.2 accordingly
	if (locateChild) { // Right Rotate

	    toDelete->parent->right = toDelete->left;
	    if (toDelete->left != NULL) {
		toDelete->left->parent = toDelete->parent;
	    }

	    parent = rightRotate(sibling);

	    // Check if the root is rotated
	    if (parent->parent == NULL) {
		*root = parent;
	    }

	    parent->color = 0;
	    parent->right->color = 1;
	    checkForCase2(parent->right, 0, 1, root);
	} else { // Left Rotate

	    toDelete->parent->left = toDelete->right;
	    if (toDelete->right != NULL) {
		toDelete->right->parent = toDelete->parent;
	    }
	    parent = leftRotate(sibling);

	    // Check if the root is rotated
	    if (parent->parent == NULL) {
		*root = parent;
	    }

	    printf("\nroot - %d - %d\n", parent->value, parent->left->value);

	    parent->color = 0;
	    parent->left->color = 1;
	    checkForCase2(parent->left, 0, 0, root);
	}
    }
}

// To delete a node from the tree
void deleteRBTNode(int value, RBTreeNode **root) {
    RBTreeNode *buffRoot = *root;

    // Search for the element in the tree
    while (1) {
	if (value == buffRoot->value) {
	    // RBTreeNode Found
	    break;
	}

	if (value > buffRoot->value) {
	    if (buffRoot->right != NULL) {
		buffRoot = buffRoot->right;
	    } else {
		printf("RBTreeNode Not Found!!!");
		return;
	    }
	} else {
	    if (buffRoot->left != NULL) {
		buffRoot = buffRoot->left;
	    } else {
		printf("RBTreeNode Not Found!!!");
		return;
	    }
	}
    }

    RBTreeNode *toDelete = buffRoot;

    // Look for the leftmost of right node or right most of left node
    if (toDelete->left != NULL) {
	toDelete = toDelete->left;
	while (toDelete->right != NULL) {
	    toDelete = toDelete->right;
	}
    } else if (toDelete->right != NULL) {
	toDelete = toDelete->right;
	while (toDelete->left != NULL) {
	    toDelete = toDelete->left;
	}
    }

    if (toDelete == *root) {
	*root = NULL;
	return;
    }

    // Swap the values
    buffRoot->value = toDelete->value;
    toDelete->value = value;

    // Checking for case 1
    if (toDelete->color == 1 ||
	(toDelete->left != NULL && toDelete->left->color == 1) ||
	(toDelete->right != NULL && toDelete->right->color == 1)) {
	// if it is a leaf
	if (toDelete->left == NULL && toDelete->right == NULL) {
	    // Delete instantly
	    if (toDelete->parent->left == toDelete) {
		toDelete->parent->left = NULL;
	    } else {
		toDelete->parent->right = NULL;
	    }
	} else { // else its child should be red

	    // Check for the exitstence of left node
	    if (toDelete->left != NULL) {
		// The node should be right to its parent
		toDelete->parent->right = toDelete->left;
		toDelete->left->parent = toDelete->parent;
		toDelete->left->color = 1;
	    } else { // else the right node should be red
		toDelete->parent->left = toDelete->right;
		toDelete->right->parent = toDelete->parent;
		toDelete->right->color = 1;
	    }
	}

	// Remove the node from memory
	free(toDelete);
    } else { // Case 2
	checkForCase2(toDelete, 1, ((toDelete->parent->right == toDelete)),
		      root);
    }
}

void inOrderTraversalRBT(RBTreeNode *root) {
    if (root != NULL) {
	inOrderTraversalRBT(root->left);
	if (root->color == 1) {
	    printf("\033[31m%d \033[0m", root->value);

	} else {
	    printf("%d ", root->value);
	}
	inOrderTraversalRBT(root->right);
    }
}

void preOrderTraversalRBT(RBTreeNode *root) {
    if (root != NULL) {
	if (root->color == 1) {
	    printf("\033[31m%d \033[0m", root->value);

	} else {
	    printf("%d ", root->value);
	}

	preOrderTraversalRBT(root->left);
	preOrderTraversalRBT(root->right);
    }
}

void postOrderTraversalRBT(RBTreeNode *root) {
    if (root != NULL) {
	postOrderTraversalRBT(root->left);
	postOrderTraversalRBT(root->right);
	if (root->color == 1) {
	    printf("\033[31m%d \033[0m", root->value);

	} else {
	    printf("%d ", root->value);
	}
    }
}

void checkBlack(RBTreeNode *temp, int c) {
    if (temp == NULL) {
	printf("%d ", c);
	return;
    }
    if (temp->color == 0) {
	c++;
    }
    checkBlack(temp->left, c);
    checkBlack(temp->right, c);
}

// Search for a node with a specific value in the Red-Black Tree
RBTreeNode *searchRBTNode(int value, RBTreeNode *root) {
    RBTreeNode *current = root;
    while (current != NULL) {
	if (value == current->value) {
	    return current; // Node found
	} else if (value < current->value) {
	    current = current->left; // Go left
	} else {
	    current = current->right; // Go right
	}
    }
    return NULL; // Node not found
}

// Find the minimum value node in the Red-Black Tree
RBTreeNode *findMinRBT(RBTreeNode *root) {
    if (root == NULL) {
	return NULL;
    }
    while (root->left != NULL) {
	root = root->left;
    }
    return root;
}

// Find the maximum value node in the Red-Black Tree
RBTreeNode *findMaxRBT(RBTreeNode *root) {
    if (root == NULL) {
	return NULL;
    }
    while (root->right != NULL) {
	root = root->right;
    }
    return root;
}

// Function to find the height of the Red-Black Tree
int findHeightRBT(RBTreeNode *root) {
    if (root == NULL) {
	return -1; // Height of an empty tree is -1
    } else {
	int leftHeight = findHeightRBT(root->left);
	int rightHeight = findHeightRBT(root->right);
	return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}

// Function to find the size (number of nodes) of the Red-Black Tree
int treeSizeRBT(RBTreeNode *root) {
    if (root == NULL) {
	return 0;
    } else {
	return treeSizeRBT(root->left) + treeSizeRBT(root->right) + 1;
    }
}

#define COUNT 5

void print2DUtilRBT(RBTreeNode *root, int space) {
    if (root == NULL)
	return;

    space += COUNT;

    print2DUtilRBT(root->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
	printf(" ");

    // Set text color based on the node's color
    if (root->color == 1) {
	printf("\033[31m"); // Set text color to red
    }

    printf("%d\x1b[0m\n",
	   root->value); // Reset text color after printing the value

    print2DUtilRBT(root->left, space);
}

void print2DRBT(RBTreeNode *root) { print2DUtilRBT(root, 0); }

int rbtreeMenu() {
    RBTreeNode *root = NULL;
    int scanValue, choice = 1;
    while (choice) {
	print2DRBT(root);
	printf("\n");
	printf("1: Insert\t\t2: Delete\t\t3: search\t\t4:Visualize\n"
	       "5: Inorder Traversal\t\t6: Preorder Traversal\t\t7: Postorder "
	       "Traversal\n"
	       "8: Find Minimum\t\t9: Find Maximum\t\t10: Find Height\t\t11: "
	       "Find Size\n"
	       "0: Back To Main Menu\n"
	       "Please Enter the Choice: ");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
	    printf("Please Enter A Value to insert: ");
	    scanf("%d", &scanValue);
	    if (root == NULL) {
		root = newNode(scanValue, NULL);
		root->color = 0;
	    } else {
		insertRBTNode(scanValue, &root);
	    }
	    printf("Successfully Inserted %d in the tree.\n", scanValue);
	    break;
	case 2:
	    printf("Please Enter A Value to Delete: ");
	    scanf("%d", &scanValue);
	    deleteRBTNode(scanValue, &root);
	    printf("Successfully Deleted %d in the tree.\n", scanValue);
	    break;
	case 3:
	    printf("Please Enter A Value to Search: ");
	    scanf("%d", &scanValue);
	    if (searchRBTNode(scanValue, root) != NULL) {
		printf("%d is present in the tree\n", scanValue);
	    } else {
		printf("%d is not present in the tree.", scanValue);
	    }
	    break;
	case 4:
	    printf("Visualization: \n");
	    print2DRBT(root);
	    break;
	case 5:
	    printf("Inorder Traversal: ");
	    inOrderTraversalRBT(root);
	    printf("\n");
	    break;
	case 6:
	    printf("Preorder Traversal: ");
	    preOrderTraversalRBT(root);
	    printf("\n");
	    break;
	case 7:
	    printf("Postorder Traversal: ");
	    postOrderTraversalRBT(root);
	    printf("\n");
	    break;
	case 8:
	    printf("Minimum Value: %d\n", findMinRBT(root)->value);
	    break;
	case 9:
	    printf("Maximum Value: %d\n", findMaxRBT(root)->value);
	    break;
	case 10:
	    printf("Height of the tree: %d\n", findHeightRBT(root));
	    break;
	case 11:
	    printf("Size of the tree: %d\n", treeSizeRBT(root));
	    break;
	case 0:
	    break;
	default:
	    printf("Invalid menu choice. Please try again.\n");
	    break;
	}
    }
    return 0;
}
