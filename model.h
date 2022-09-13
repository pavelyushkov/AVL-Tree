#ifndef MODEL_H
#define MODEL_H

void freeTree(Node* node);
unsigned int get_integer();
Node* find_max(Node* node);
Node* find_by_key(Node* node, unsigned int key);
Node* delete_element(Node* node, int key);
Node* balance(Node* node);
Node* get_min_from_key(Node* node, Node* res, int a);
Node* add_element(Node* node, unsigned int key, unsigned int data);
void write_to_file(Node* node, FILE* file);
void load_from_file(Tree* tree, FILE* file);
Tree* create_tree();

#endif //MODEL_H
