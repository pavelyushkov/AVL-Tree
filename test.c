#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "readline.h"
#include <string.h>
#include <ctype.h>


struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get the height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return 1+max(height(N->left), height(N->right));
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 0;  // new node is initially added at leaf
    return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = height(y);
    x->height = height(x);

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = height(x);
    y->height = height(y);

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
struct Node* insert(struct Node* node, int key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = height(node);

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

unsigned int get_integer(){
  unsigned int res = 0;
  int q, i, flag = 1;
  char* input = NULL;
  while(flag == 1){
   if(input != NULL)
      free(input);
    input = readline("");
    if(input == NULL)
      return 0;
    q = strlen(input);
    for(i = 0; i < q; i++){
      if(!isdigit(input[i])){
        printf("\nWrong input. Try again:   ");
        flag = 1;
        break;
      }
      if(i == (q - 1))
        flag = 0;
    }
    res = atoi(input);
    if(res < 0){
      printf("\nWrong input. Try again:   ");
      flag = 1;
    }
  }
  free(input);
  return res;
}


void menu(){
  printf("\nEnter 1 to add element");
  printf("\nEnter 2 to delete element");
  printf("\nEnter 3 to output tree");
  printf("\nEnter 4 to find element");
  printf("\nEnter 5 to special find");
  printf("\nEnter 6 to format output");
  printf("\nEnter 7 to read tree from file");
  printf("\nEnter 8 to write tree into file");
  printf("\nEnter 0 to end\n");
}

void format_output(struct Node* node, int k){
  if(node == NULL)
    return;
 else{
    format_output(node->left, k + 1);
    for(int i = 0; i < k; ++i){
      printf("      ");
    }
    printf("%d\n\n", node->key);
    format_output(node->right, k + 1);
  }
}

/* Driver program to test above function*/
int main()
{
  struct Node *root = NULL;
  int check = 10;
  while(1){
    menu();
    printf("\nYour input: ");
    check = get_integer();
    if(check == 1){
      printf("\nEnter key:  ");
      unsigned int key = get_integer();
      root = insert(root, key);
    }
    else if(check == 0)
      return 0;
    else if(check == 6){
      format_output(root, 0);
    }
  }

  return 0;
}
