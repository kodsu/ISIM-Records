struct node{ 
    struct node* child[2];struct node* parent; char value; 
};  
void memory_error(); 
void print_tree(struct node* T, ll mess, int len); 
void remove_subtree(struct node* X);
struct node* generate_tree(char *napis, int length); 
char* code(char *napis, int len, struct node* top, int* newlen); 
char* decode(char *code, int code_length, struct node* top, int* newlen);