#include "../lib/tree.h"
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
  int data;
  struct TreeNode *left;
  struct TreeNode *right;
};

TreeNode *createNode(int value) {
  TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
  if (newNode == NULL) {
    printf("Error: Memory allocation failed.\n");
    return NULL;
  }

  newNode->data = value;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

TreeNode *insert(TreeNode *root, int value) {
  if (root == NULL) {
    return createNode(value);
  }

  if (value < root->data) {
    root->left = insert(root->left, value);
  } else if (value > root->data) {
    root->right = insert(root->right, value);
  }

  return root;
}

TreeNode *search(TreeNode *root, int value) {
  if (root == NULL || root->data == value) {
    return root;
  }
  if (value < root->data) {
    return search(root->left, value);
  }
  return search(root->right, value);
}

TreeNode *deleteNode(TreeNode *root, int value) {
  if (root == NULL) {
    return root;
  }
  if (value < root->data) {
    root->left = deleteNode(root->left, value);
  } else if (value > root->data) {
    root->right = deleteNode(root->right, value);
  } else {
    if (root->left == NULL) {
      TreeNode *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      TreeNode *temp = root->left;
      free(root);
      return temp;
    }
    int temp = findMin(root->right);
    root->data = temp;
    root->right = deleteNode(root->right, temp);
  }
  return root;
}

int findMin(TreeNode *root) {
  while (root->left != NULL) {
    root = root->left;
  }
  return root->data;
}

int findMax(TreeNode *root) {
  while (root->right != NULL) {
    root = root->right;
  }
  return root->data;
}

int findHeight(TreeNode *root) {
  if (root == NULL) {
    return -1;
  }
  int leftHeight = findHeight(root->left);
  int rightHeight = findHeight(root->right);
  return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int treeSize(TreeNode *root) {
  if (root == NULL) {
    return 0;
  }
  return 1 + treeSize(root->left) + treeSize(root->right);
}

void inOrderTraversal(TreeNode *root) {
  if (root != NULL) {
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
  }
}

void preOrderTraversal(TreeNode *root) {
  if (root != NULL) {
    printf("%d ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
  }
}

void postOrderTraversal(TreeNode *root) {
  if (root != NULL) {
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->data);
  }
}

void print2DUtil(TreeNode *root, int space) {
  if (root == NULL)
    return;

  space += COUNT;

  print2DUtil(root->right, space);

  printf("\n");
  for (int i = COUNT; i < space; i++)
    printf(" ");
  printf("%d\n", root->data);

  print2DUtil(root->left, space);
}

void print2D(TreeNode *root) { print2DUtil(root, 0); }

void treeMenu() {
  int treeChoice;
  TreeNode *root = NULL;
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
      root = insert(root, value);
      break;

    case 2:
      printf("Enter a value to search: ");
      scanf("%d", &value);
      TreeNode *result = search(root, value);
      if (result != NULL) {
        printf("Value found in the tree.\n");
      } else {
        printf("Value not found in the tree.\n");
      }
      break;

    case 3:
      printf("Enter a value to delete: ");
      scanf("%d", &value);
      root = deleteNode(root, value);
      break;

    case 4:
      printf("Minimum value in the tree: %d\n", findMin(root));
      break;

    case 5:
      printf("Maximum value in the tree: %d\n", findMax(root));
      break;

    case 6:
      printf("Height of the tree: %d\n", findHeight(root));
      break;

    case 7:
      printf("Size of the tree: %d\n", treeSize(root));
      break;

    case 8:
      printf("In Order Traversal: ");
      inOrderTraversal(root);
      printf("\n");
      break;

    case 9:
      printf("Pre-Order Traversal: ");
      preOrderTraversal(root);
      printf("\n");
      break;

    case 10:
      printf("Post-Order Traversal: ");
      postOrderTraversal(root);
      printf("\n");
      break;

    case 11:
      print2D(root);
      break;

    case 0:
      break;

    default:
      printf("Invalid menu choice. Please try again.\n");
      break;
    }
  } while (treeChoice != 0);
}
