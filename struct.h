#ifndef STRUCT_H
#define STRUCT_H

typedef struct Node {
  int height;
  unsigned int key;
  unsigned int data;
  struct Node* root;
  struct Node* right;
  struct Node* left;
} Node;

typedef struct Tree {
  Node* parent;
} Tree;

#endif // STRUCT_H
