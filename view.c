#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

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

void output(Node* node, int a){
  if(node == NULL)
    return;
  output(node->left, a);
  if(node->key <= a)
    printf("  %d", node->data);
  output(node->right, a);
}

void format_output(Node* node, int k){
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
