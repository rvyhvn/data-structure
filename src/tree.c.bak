#include "../lib/bstree.h"
#include <stdio.h>
#include <stdlib.h>

struct BSTreeNode {
  int data;
  struct BSTreeNode *left;
  struct BSTreeNode *right;
};

BSTreeNode *createBSTNode(int value) {
  BSTreeNode *newNode = (BSTreeNode *)malloc(sizeof(BSTreeNode));
  if (newNode == NULL) {
    printf("Error: Memory allocation failed.\n");
    return NULL;
  }

  newNode->data = value;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

BSTreeNode *insertBSTNode(BSTreeNode *root, int value) {
  if (root == NULL) {
    return createBSTNode(value);
  }

  if (value < root->data) {
    root->left = insertBSTNode(root->left, value);
  } else if (value > root->data) {
    root->right = insertBSTNode(root->right, value);
  }

  return root;
}

BSTreeNode *searchBSTNode(BSTreeNode *root, int value) {
  if (root == NULL || root->data == value) {
    return root;
  }
  if (value < root->data) {
    return searchBSTNode(root->left, value);
  }
  return searchBSTNode(root->right, value);
}

BSTreeNode *deleteBSTNode(BSTreeNode *root, int value) {
  if (root == NULL) {
    return root;
  }
  if (value < root->data) {
    root->left = deleteBSTNode(root->left, value);
  } else if (value > root->data) {
    root->right = deleteBSTNode(root->right, value);
  } else {
    if (root->left == NULL) {
      BSTreeNode *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      BSTreeNode *temp = root->left;
      free(root);
      return temp;
    }
    int temp = findMinBST(root->right);
    root->data = temp;
    root->right = deleteBSTNode(root->right, temp);
  }
  return root;
}

int findMinBST(BSTreeNode *root) {
  while (root->left != NULL) {
    root = root->left;
  }
  return root->data;
}

int findMaxBST(BSTreeNode *root) {
  while (root->right != NULL) {
    root = root->right;
  }
  return root->data;
}

int findHeightBST(BSTreeNode *root) {
  if (root == NULL) {
    return -1;
  }
  int leftHeight = findHeightBST(root->left);
  int rightHeight = findHeightBST(root->right);
  return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int treeSizeBST(BSTreeNode *root) {
  if (root == NULL) {
    return 0;
  }
  return 1 + treeSizeBST(root->left) + treeSizeBST(root->right);
}

void inOrderTraversalBST(BSTreeNode *root) {
  if (root != NULL) {
    inOrderTraversalBST(root->left);
    printf("%d ", root->data);
    inOrderTraversalBST(root->right);
  }
}

void preOrderTraversalBST(BSTreeNode *root) {
  if (root != NULL) {
    printf("%d ", root->data);
    preOrderTraversalBST(root->left);
    preOrderTraversalBST(root->right);
  }
}

void postOrderTraversalBST(BSTreeNode *root) {
  if (root != NULL) {
    postOrderTraversalBST(root->left);
    postOrderTraversalBST(root->right);
    printf("%d ", root->data);
  }
}

void print2DUtilBST(BSTreeNode *root, int space) {
  if (root == NULL)
    return;

  space += COUNT;

  print2DUtilBST(root->right, space);

  printf("\n");
  for (int i = COUNT; i < space; i++)
    printf(" ");
  printf("%d\n", root->data);

  print2DUtilBST(root->left, space);
}

void print2DBST(BSTreeNode *root) { print2DUtilBST(root, 0); }

void bstreeMenu() {
  int treeChoice;
  BSTreeNode *root = NULL;
  do {
    printf("Binary Tree Menu:\n");
    printf("1. Insert\n");
    printf("2. Search\n");
    printf("3. Delete Node\n");
    printf("4. Find Minimum Value\n");
    printf("5. Find Maximum Value\n");
    printf("6. Height Of Tree\n");
    printf("7. Size Of Tree\n");
    printf("8. In Order Traversal\n");
    printf("9. Pre-Order Traversal\n");
    printf("10. Post-Order Traversal\n");
    printf("11. Visualize\n");
    printf("0. Back\n");
    printf("Option: ");
    scanf("%d", &treeChoice);

    switch (treeChoice) {
    case 1:
      printf("Enter a value to insert: ");
      int value;
      scanf("%d", &value);
      root = insertBSTNode(root, value);
      break;

    case 2:
      printf("Enter a value to search: ");
      scanf("%d", &value);
      BSTreeNode *result = searchBSTNode(root, value);
      if (result != NULL) {
        printf("Value found in the tree.\n");
      } else {
        printf("Value not found in the tree.\n");
      }
      break;

    case 3:
      printf("Enter a value to delete: ");
      scanf("%d", &value);
      root = deleteBSTNode(root, value);
      break;

    case 4:
      printf("Minimum value in the tree: %d\n", findMinBST(root));
      break;

    case 5:
      printf("Maximum value in the tree: %d\n", findMaxBST(root));
      break;

    case 6:
      printf("Height of the tree: %d\n", findHeightBST(root));
      break;

    case 7:
      printf("Size of the tree: %d\n", treeSizeBST(root));
      break;

    case 8:
      printf("In Order Traversal: ");
      inOrderTraversalBST(root);
      printf("\n");
      break;

    case 9:
      printf("Pre-Order Traversal: ");
      preOrderTraversalBST(root);
      printf("\n");
      break;

    case 10:
      printf("Post-Order Traversal: ");
      postOrderTraversalBST(root);
      printf("\n");
      break;

    case 11:
      print2DBST(root);
      break;

    case 0:
      break;

    default:
      printf("Invalid menu choice. Please try again.\n");
      break;
    }
  } while (treeChoice != 0);
}
