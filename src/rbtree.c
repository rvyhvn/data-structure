#include "../lib/rbtree.h"
#include <stdio.h>
#include <stdlib.h>

enum nodeColor {
  RED,
  BLACK
};

struct RBTreeNode {
  int value, color;
  struct RBTreeNode *link[2];
};

struct RBTreeNode *root = NULL;

// Create a red-black tree node
struct RBTreeNode *createNode(int value) {
  struct RBTreeNode *newnode;
  newnode = (struct RBTreeNode *)malloc(sizeof(struct RBTreeNode));
  newnode->value = value;
  newnode->color = RED;
  newnode->link[0] = newnode->link[1] = NULL;
  return newnode;
}

// Insert a node into the red-black tree
void insertRBTNode(int value) {
  // (Same as your 'insertion' function)
  struct RBTreeNode *stack[98], *ptr, *newnode, *xPtr, *yPtr;
  int dir[98], ht = 0, index;
  ptr = root;
  if (!root) {
    root = createNode(value);
    return;
  }

  stack[ht] = root;
  dir[ht++] = 0;
  while (ptr != NULL) {
    if (ptr->value == value) {
      printf("Duplicates Not Allowed!!\n");
      return;
    }
    index = (value - ptr->value) > 0 ? 1 : 0;
    stack[ht] = ptr;
    ptr = ptr->link[index];
    dir[ht++] = index;
  }
  stack[ht - 1]->link[index] = newnode = createNode(value);
  while ((ht >= 3) && (stack[ht - 1]->color == RED)) {
    if (dir[ht - 2] == 0) {
      yPtr = stack[ht - 2]->link[1];
      if (yPtr != NULL && yPtr->color == RED) {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        ht = ht - 2;
      } else {
        if (dir[ht - 1] == 0) {
          yPtr = stack[ht - 1];
        } else {
          xPtr = stack[ht - 1];
          yPtr = xPtr->link[1];
          xPtr->link[1] = yPtr->link[0];
          yPtr->link[0] = xPtr;
          stack[ht - 2]->link[0] = yPtr;
        }
        xPtr = stack[ht - 2];
        xPtr->color = RED;
        yPtr->color = BLACK;
        xPtr->link[0] = yPtr->link[1];
        yPtr->link[1] = xPtr;
        if (xPtr == root) {
          root = yPtr;
        } else {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    } else {
      yPtr = stack[ht - 2]->link[0];
      if ((yPtr != NULL) && (yPtr->color == RED)) {
        stack[ht - 2]->color = RED;
        stack[ht - 1]->color = yPtr->color = BLACK;
        ht = ht - 2;
      } else {
        if (dir[ht - 1] == 1) {
          yPtr = stack[ht - 1];
        } else {
          xPtr = stack[ht - 1];
          yPtr = xPtr->link[0];
          xPtr->link[0] = yPtr->link[1];
          yPtr->link[1] = xPtr;
          stack[ht - 2]->link[1] = yPtr;
        }
        xPtr = stack[ht - 2];
        yPtr->color = BLACK;
        xPtr->color = RED;
        xPtr->link[1] = yPtr->link[0];
        yPtr->link[0] = xPtr;
        if (xPtr == root) {
          root = yPtr;
        } else {
          stack[ht - 3]->link[dir[ht - 3]] = yPtr;
        }
        break;
      }
    }
  }
  root->color = BLACK;
}

// Search a node in the red-black tree
struct RBTreeNode* searchRBTNode(int value) {
  struct RBTreeNode *current = root;
  while (current != NULL) {
    if (current->value == value) {
      return current;
    } else if (value < current->value) {
      current = current->link[0];
    } else {
      current = current->link[1];
    }
  }
  return NULL;
}

// Delete a node from the red-black tree
void deleteRBTNode(int value) {
  // (Same as your 'deletion' function)
struct RBTreeNode *stack[98], *ptr, *xPtr, *yPtr;
  struct RBTreeNode *pPtr, *qPtr, *rPtr;
  int dir[98], ht = 0, diff, i;
  enum nodeColor color;

  if (!root) {
    printf("Tree not available\n");
    return;
  }

  ptr = root;
  while (ptr != NULL) {
    if ((value - ptr->value) == 0)
      break;
    diff = (value - ptr->value) > 0 ? 1 : 0;
    stack[ht] = ptr;
    dir[ht++] = diff;
    ptr = ptr->link[diff];
  }

  if (ptr->link[1] == NULL) {
    if ((ptr == root) && (ptr->link[0] == NULL)) {
      free(ptr);
      root = NULL;
    } else if (ptr == root) {
      root = ptr->link[0];
      free(ptr);
    } else {
      stack[ht - 1]->link[dir[ht - 1]] = ptr->link[0];
    }
  } else {
    xPtr = ptr->link[1];
    if (xPtr->link[0] == NULL) {
      xPtr->link[0] = ptr->link[0];
      color = xPtr->color;
      xPtr->color = ptr->color;
      ptr->color = color;

      if (ptr == root) {
        root = xPtr;
      } else {
        stack[ht - 1]->link[dir[ht - 1]] = xPtr;
      }

      dir[ht] = 1;
      stack[ht++] = xPtr;
    } else {
      i = ht++;
      while (1) {
        dir[ht] = 0;
        stack[ht++] = xPtr;
        yPtr = xPtr->link[0];
        if (!yPtr->link[0])
          break;
        xPtr = yPtr;
      }

      dir[i] = 1;
      stack[i] = yPtr;
      if (i > 0)
        stack[i - 1]->link[dir[i - 1]] = yPtr;

      yPtr->link[0] = ptr->link[0];

      xPtr->link[0] = yPtr->link[1];
      yPtr->link[1] = ptr->link[1];

      if (ptr == root) {
        root = yPtr;
      }

      color = yPtr->color;
      yPtr->color = ptr->color;
      ptr->color = color;
    }
  }

  if (ht < 1)
    return;

  if (ptr->color == BLACK) {
    while (1) {
      pPtr = stack[ht - 1]->link[dir[ht - 1]];
      if (pPtr && pPtr->color == RED) {
        pPtr->color = BLACK;
        break;
      }

      if (ht < 2)
        break;

      if (dir[ht - 2] == 0) {
        rPtr = stack[ht - 1]->link[1];

        if (!rPtr)
          break;

        if (rPtr->color == RED) {
          stack[ht - 1]->color = RED;
          rPtr->color = BLACK;
          stack[ht - 1]->link[1] = rPtr->link[0];
          rPtr->link[0] = stack[ht - 1];

          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            stack[ht - 2]->link[dir[ht - 2]] = rPtr;
          }
          dir[ht] = 0;
          stack[ht] = stack[ht - 1];
          stack[ht - 1] = rPtr;
          ht++;

          rPtr = stack[ht - 1]->link[1];
        }

        if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
          (!rPtr->link[1] || rPtr->link[1]->color == BLACK)) {
          rPtr->color = RED;
        } else {
          if (!rPtr->link[1] || rPtr->link[1]->color == BLACK) {
            qPtr = rPtr->link[0];
            rPtr->color = RED;
            qPtr->color = BLACK;
            rPtr->link[0] = qPtr->link[1];
            qPtr->link[1] = rPtr;
            rPtr = stack[ht - 1]->link[1] = qPtr;
          }
          rPtr->color = stack[ht - 1]->color;
          stack[ht - 1]->color = BLACK;
          rPtr->link[1]->color = BLACK;
          stack[ht - 1]->link[1] = rPtr->link[0];
          rPtr->link[0] = stack[ht - 1];
          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            stack[ht - 2]->link[dir[ht - 2]] = rPtr;
          }
          break;
        }
      } else {
        rPtr = stack[ht - 1]->link[0];
        if (!rPtr)
          break;

        if (rPtr->color == RED) {
          stack[ht - 1]->color = RED;
          rPtr->color = BLACK;
          stack[ht - 1]->link[0] = rPtr->link[1];
          rPtr->link[1] = stack[ht - 1];

          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            stack[ht - 2]->link[dir[ht - 2]] = rPtr;
          }
          dir[ht] = 1;
          stack[ht] = stack[ht - 1];
          stack[ht - 1] = rPtr;
          ht++;

          rPtr = stack[ht - 1]->link[0];
        }
        if ((!rPtr->link[0] || rPtr->link[0]->color == BLACK) &&
          (!rPtr->link[1] || rPtr->link[1]->color == BLACK)) {
          rPtr->color = RED;
        } else {
          if (!rPtr->link[0] || rPtr->link[0]->color == BLACK) {
            qPtr = rPtr->link[1];
            rPtr->color = RED;
            qPtr->color = BLACK;
            rPtr->link[1] = qPtr->link[0];
            qPtr->link[0] = rPtr;
            rPtr = stack[ht - 1]->link[0] = qPtr;
          }
          rPtr->color = stack[ht - 1]->color;
          stack[ht - 1]->color = BLACK;
          rPtr->link[0]->color = BLACK;
          stack[ht - 1]->link[0] = rPtr->link[1];
          rPtr->link[1] = stack[ht - 1];
          if (stack[ht - 1] == root) {
            root = rPtr;
          } else {
            stack[ht - 2]->link[dir[ht - 2]] = rPtr;
          }
          break;
        }
      }
      ht--;
    }
  }
}

// Find the minimum value node in the red-black tree
struct RBTreeNode* findMinRBT() {
  struct RBTreeNode *current = root;
  if (current == NULL) {
    return NULL;
  }
  while (current->link[0] != NULL) {
    current = current->link[0];
  }
  return current;
}

// Find the maximum value node in the red-black tree
struct RBTreeNode* findMaxRBT() {
  struct RBTreeNode *current = root;
  if (current == NULL) {
    return NULL;
  }
  while (current->link[1] != NULL) {
    current = current->link[1];
  }
  return current;
}

// Find the height of the red-black tree
int findHeightRBT(RBTreeNode* node) {
  if (node == NULL) return -1;
  int leftHeight = findHeightRBT(node->link[0]);
  int rightHeight = findHeightRBT(node->link[1]);
  return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Find the size of the red-black tree (number of nodes)
int treeSizeRBT(struct RBTreeNode* node) {
  if (node == NULL) return 0;
  return 1 + treeSizeRBT(node->link[0]) + treeSizeRBT(node->link[1]);
}

// In-order traversal of the red-black tree
void inOrderTraversalRBT(struct RBTreeNode* node) {
  if (node) {
    inOrderTraversalRBT(node->link[0]);
    printf("%d  ", node->value);
    inOrderTraversalRBT(node->link[1]);
  }
}

// Pre-order traversal of the red-black tree
void preOrderTraversalRBT(struct RBTreeNode* node) {
  if (node) {
    printf("%d  ", node->value);
    preOrderTraversalRBT(node->link[0]);
    preOrderTraversalRBT(node->link[1]);
  }
}

// Post-order traversal of the red-black tree
void postOrderTraversalRBT(struct RBTreeNode* node) {
  if (node) {
    postOrderTraversalRBT(node->link[0]);
    postOrderTraversalRBT(node->link[1]);
    printf("%d  ", node->value);
  }
}

void print2DUtilRBT(RBTreeNode *root, int space) {
    if (root == NULL)
        return;

    space += COUNT;

    print2DUtilRBT(root->link[1], space); // Print right subtree

    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");

    // Display the node's value and color (RED or BLACK)
    if (root->color == RED) {
        printf("\033[31m%d (R)\033[0m\n", root->value); // Print in red color for red nodes
    } else {
        printf("\033[30m%d (B)\033[0m\n", root->value); // Print in black color for black nodes
    }

    print2DUtilRBT(root->link[0], space); // Print left subtree
}

void print2DRBT(RBTreeNode *root) {
    print2DUtilRBT(root, 0);
}

// Driver code
int rbtreeMenu() {
  int ch, value;
  struct RBTreeNode* foundNode;

  while (1) {
    printf("1. Insertion\t2. Deletion\t3. Search\n");
    printf("4. Find Min\t5. Find Max\t6. Height\n");
    printf("7. Tree Size\t8. In-order\t9. Pre-order\t10. Post-order\n");
    printf("11. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch) {
      case 1:
        printf("Enter the element to insert: ");
        scanf("%d", &value);
        insertRBTNode(value);
        break;
      case 2:
        printf("Enter the element to delete: ");
        scanf("%d", &value);
        deleteRBTNode(value);
        break;
      case 3:
        printf("Enter the element to search: ");
        scanf("%d", &value);
        foundNode = searchRBTNode(value);
        if (foundNode)
          printf("Element found in the tree.\n");
        else
          printf("Element not found in the tree.\n");
        break;
      case 4:
        foundNode = findMinRBT();
        if (foundNode)
          printf("Minimum element in the tree: %d\n", foundNode->value);
        else
          printf("Tree is empty.\n");
        break;
      case 5:
        foundNode = findMaxRBT();
        if (foundNode)
          printf("Maximum element in the tree: %d\n", foundNode->value);
        else
          printf("Tree is empty.\n");
        break;
      case 6:
        printf("Height of the tree: %d\n", findHeightRBT(root));
        break;
      case 7:
        printf("Size of the tree: %d\n", treeSizeRBT(root));
        break;
      case 8:
        printf("In-order traversal: ");
        inOrderTraversalRBT(root);
        printf("\n");
        break;
      case 9:
        printf("Pre-order traversal: ");
        preOrderTraversalRBT(root);
        printf("\n");
        break;
      case 10:
        printf("Post-order traversal: ");
        postOrderTraversalRBT(root);
        printf("\n");
        break;
      case 11:
        exit(0);
      default:
        printf("Invalid choice.\n");
        break;
    }
    printf("\n");
  }
  return 0;
}

