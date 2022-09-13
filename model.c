#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readline.h"
#include "struct.h"

void freeTree(Node* node){
  if(node == NULL)
    return;
  freeTree(node->left);
  freeTree(node->right);
  free(node);
  node = NULL;
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

Node* find_max(Node* node){
  if(node != NULL)
    while(node->right != NULL){
      node = node->right;
    }
  return node;
}

Node* find_min(Node* node){
  if(node){
    Node* elem = node;
    while(elem->left != NULL)
      elem = elem->left;
    return elem;
  }
  return NULL;
}

int height(Node *node) {
    if(node){
      int lh = height(node->left);
      int rh = height(node->right);
      if(lh > rh)
        return lh + 1;
      else
        return rh + 1;
    }
    else
      return 0;
}

Node* right_rotate(Node *par){
    Node *node = par->left;
    Node *und = node->right;
    node->right = par;
    par->left = und;
    par->height = height(par);
    node->height = height(node);
    return node;
}

Node* left_rotate(Node *par){
    Node *node = par->right;
    Node *und = node->left;
    node->left = par;
    par->right = und;
    par->height = height(par);
    node->height = height(node);
    return node;
}

Node* add_element(Node* node, unsigned int key, unsigned int data){
    if(!node){
      Node* tmp = (Node*) malloc(sizeof(Node));
      tmp->key = key;
      tmp->data = data;
      tmp->left = NULL;
      tmp->right = NULL;
      tmp->height = 0;
      return tmp;
    }
    if(key > node->key)
      node->right = add_element(node->right, key, data);
    else if(key < node->key)
      node->left = add_element(node->left, key, data);
    else if(key == node->key){
      node->data = data;
      return node;
    }
    node->height = height(node);
    int balance = 0;
    if(node){
      balance = height(node->left) - height(node->right);
    }
    if((balance > 1) && (key > node->left->key)){
      node->left =  left_rotate(node->left);
      return right_rotate(node);
    }
    else if ((balance < -1) && (key < node->right->key)){
      node->right = right_rotate(node->right);
      return left_rotate(node);
    }
    else if((balance > 1) && (key < node->left->key))
      return right_rotate(node);
    else if ((balance < -1) && (key > node->right->key))
      return left_rotate(node);
    return node;
}

Node* find_by_key(Node* node, unsigned int key){
  Node* res;
  if(node == NULL)
    return NULL;
  else{
    if(key == node->key)
      return node;
    else if(key < node->key)
      res = find_by_key(node->left, key);
    else if(key > node->key)
      res = find_by_key(node->right, key);
    return res;
  }
}

Node* delete_element(Node* node, int key){
  if(node){
    if(key < node->key)
      node->left = delete_element(node->left, key);
    else if(key > node->key)
      node->right = delete_element(node->right, key);
    else if(key == node->key){//нашли нужный
      if((node->left == NULL) || (node->right == NULL)){// хотя бы одного потомка нету
        Node* tmp;
        if(node->left != NULL)// если есть левый
          tmp = node->left;
        else
         tmp = node->right;  //иначе правый
        if(tmp == NULL){//если и правого нету то делаем равным null
          tmp = node;
          node = NULL;
        }
        else{// если есть то копируем
          node->key = tmp->key;
          node->data = tmp->data;
          node->height = tmp->height;
          node->left = tmp->left;
          node->right = tmp->right;
          node->root = tmp->root;
        }
       free(tmp);
      }
      else{// если оба есть
        Node* tmp = find_min(node->right);
        node->key = tmp->key;
        node->data = tmp->data;
        node->right = delete_element(node->right, tmp->key);
      }
    }
    if (!node)
      return node;
    node->height = height(node);
    int balance = 0;
    if(node)
      balance = (height(node->left) - height(node->right));
    if(balance > 1 && (height(node->left->left) >= height(node->left->right)))
      return right_rotate(node);
    else if (balance > 1 && height(node->left->left) < height(node->left->right)){
      node->left = left_rotate(node->left);
      return right_rotate(node);
    }
    else if(balance < -1 && (height(node->right->left) <= height(node->right->right)))
      return left_rotate(node);
    else if(balance < -1 && height(node->right->left) > height(node->right->right)){
      node->right = right_rotate(node->right);
      return left_rotate(node);
    }
    return node;
  }
  return NULL;
}

Node* get_min_from_key(Node* node, Node* res, int a){
  if(node == NULL)
    return res;
  res = get_min_from_key(node->left, res, a);
  if((node->key > a) && (res->key > node->key))
    res = node;
  res = get_min_from_key(node->right, res, a);
  return res;
}

void write_to_file(Node* node, FILE* file){
  if(node == NULL)
    return;
  else{
    fwrite(&node->key, 4, 1, file);
    fwrite(&node->data, 4, 1, file);
    write_to_file(node->left, file);
    write_to_file(node->right, file);
  }
}

void load_from_file(Tree* tree, FILE* file){
  int c = 0;
  unsigned int key, data;
  fseek(file, 0, SEEK_END);
  int fsize = ftell(file);
  fseek(file, 0, SEEK_SET);
  while(ftell(file) <= fsize - 1){
    fread(&key, 4, 1, file);
    fread(&data, 4, 1, file);
    tree->parent = add_element(tree->parent, key, data);
  }
  return;
}

Tree* create_tree(){
  Tree* tree = (Tree*) malloc(sizeof(Tree));
  tree->parent = NULL;
  return tree;
}
