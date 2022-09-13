#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "readline.h"
#include "struct.h"
#include "view.h"
#include "model.h"

void timing(){
  Tree* tree = create_tree();
  srand(time(NULL));
  for(int i = 0; i < 100000; ++i){
    tree->parent = add_element(tree->parent, rand(), rand());
  }
  for(int i = 100000; i <= 400000; i += 10000){
    clock_t B = clock();
    for(int j = 0; j < i; ++j){
      Node* elem = find_by_key(tree->parent, rand());
    }
    clock_t C = clock();
    printf("\nfind:   %d\n", (C-B)/CLOCKS_PER_SEC);
    freeTree(tree->parent);
  }
}

int main(){
  timing();
  return 0;
  unsigned int check = 10;
  Tree* tree = create_tree();
  while(check != 0){
    menu();
    printf("\nYour input: ");
    check = get_integer();
    if(check == 1){
      printf("\nEnter key:  ");
      unsigned int key = get_integer();
      printf("\nEnter data:  ");
      unsigned int data = get_integer();
      tree->parent = add_element(tree->parent, key, data);
      printf("\nElement added\n");
    }
    else if(check == 2){
      if(tree->parent == NULL)
        printf("\nTree is empty\n");
      else{
        printf("\nEnter key:  ");
        unsigned int key = get_integer();
        Node* tmp = find_by_key(tree->parent, key);
        if(tmp == NULL)
          printf("\nNo element with this key\n");
        else{
          tree->parent = delete_element(tree->parent, key);
          printf("\nElement deleted\n");
        }
      }
    }
    else if(check == 3){
      if(tree->parent == NULL)
        printf("\nTree is empty\n");
      else{
        printf("\nEnter 1 to special output and 0 to output all tree:  ");
        unsigned int k;
        while(1){
          k = get_integer();
          if(k == 0 || k == 1)
            break;
          else
            printf("\nWrong input. Try again:   ");
        }
        if(k == 1){
          printf("\nEnter key:  ");
          unsigned int key = get_integer();
          printf("\n");
          output(tree->parent, key);
          printf("\n");
        }
        else{
          printf("\n");
          output(tree->parent, (find_max(tree->parent))->key + 1);
          printf("\n");
        }
      }
    }
    else if(check == 4){
      if(tree->parent == NULL)
        printf("\nTree is empty\n");
      else{
        printf("\nEnter key:  ");
        unsigned int key = get_integer();
        Node* elem =  find_by_key(tree->parent, key);
        if(elem == NULL)
          printf("\nNo element with this key\n");
        else{
          printf("\nElement with this key:  ");
          printf("   %d", elem->data);
          printf("\n");
        }
      }
    }
    else if(check == 5){
      if(tree->parent == NULL)
        printf("\nTree is empty\n");
      else{
        printf("\nEnter key:  ");
        unsigned int key = get_integer();
        Node* res = (Node*) malloc(sizeof(Node));
        res->key = (find_max(tree->parent))->key + 1;
        res->data = res->key;
        res = get_min_from_key(tree->parent, res, key);
        printf("\nMin from elem:   %d\n", res->data);
      }
    }
    else if(check == 6){
      printf("\n\n\n\n\n");
      format_output(tree->parent, 0);
      printf("\n\n\n");
    }
    else if(check == 7){
      char* name = readline("\nEnter name of file:  ");
      FILE* file = fopen(name, "rb");
      if(file == NULL)
        printf("\nFile open error\n");
      else{
        freeTree(tree->parent);
        free(tree);
        tree = create_tree();
        load_from_file(tree, file);
        fclose(file);
      }
      free(name);
    }
    else if(check == 8){
      char* name = readline("\nEnter name of file:  ");
      FILE* file = fopen(name, "w+b");
      fseek(file, 0, SEEK_SET);
      write_to_file(tree->parent, file);
      fclose(file);
      free(name);
      printf("\nTree recorded\n");
    }
  }
  freeTree(tree->parent);
  free(tree);
  printf("\nFinished!\n");
  return 0;
}
