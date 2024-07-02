#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 
#include "huffman.h"
// struct node{ 
//     struct node* child[2];struct node* parent; char value; 
// };  
void memory_error(){ 
    fprintf(stderr, "Błąd alokacji pamięci dla nowego węzła.\n");
    exit(EXIT_FAILURE);
}

struct node* new_node(){ 
    struct node* newNode = (struct node*)malloc(sizeof(struct node)); 
    if(newNode == NULL){ 
        memory_error(); 
    } 
    newNode->child[0] = NULL;
    newNode->child[1] = NULL;
    newNode->parent = NULL;
    return newNode; 
}  

void remove_node(struct node* myNode){ 
    free(myNode); 
    return; 
} 

void remove_subtree(struct node* X){ 
    if(X->child[0] != NULL){ 
        remove_subtree(X->child[0]); 
    } 
    if(X->child[1]!= NULL) 
        remove_subtree(X->child[1]); 
    remove_node(X); 
}

void setNode(struct node* myNode, struct node* parent, struct node* leftChild, struct node* rightChild, char value){ 
    if(myNode == NULL) 
        memory_error(); 
    myNode->parent = parent; 
    myNode->child[0] = leftChild; 
    myNode->child[1] = rightChild; 
    myNode->value = value; 
    return; 
}

struct node* generate_tree(char *napis, int length){ 
    // generuje całe drzewo i zwraca wskaźnik na korzen 
    char licznosc[256];  
    for(int i = 0; i < 256; i++) 
        licznosc[i] = 0; 
    for(int i = 0; i < length; i++) 
        licznosc[(int)napis[i]]++;

    int liczba_bas = 0; 
    for(int i = 0; i < 256; i++){ 
        if(licznosc[i] != 0){
            liczba_bas++;   
            //printf("%c - %d || ", (char)i, licznosc[i]); 
        } 
    } 
    //printf("\n"); 
    int siz = liczba_bas*2 + 5; 
    struct node* przej[siz]; 
    bool aktualnosc[siz];  
    int krot[siz]; 
    for(int i = 0; i < siz; i++){
        krot[i] = 0; 
        aktualnosc[i] = 0; 
    }  

    int wsk = 0; 
    for(int znak = 0; znak < 256; znak++){ 
        if(licznosc[znak] != 0){ 
            // tutaj sobie tworzymy liscia 
            przej[wsk] = new_node();  
            if(przej[wsk] == NULL) 
                memory_error(); 
            krot[wsk] = licznosc[znak]; 
            aktualnosc[wsk] = 1; 
            setNode(przej[wsk], NULL, NULL, NULL, (char)znak); 
            wsk++; 
        }
    } 

    int min1, min2, id1, id2;  
    int INF = 1000000000; 
    
    for(int i = 0; i < liczba_bas-1; i++){ 
        min1 = INF+1, min2 = INF+2; 
        id1 =-1, id2 = -2;  
        for(int j = 0; j < wsk; j++){ 
            if(!aktualnosc[j]) 
                continue; 
            if(krot[j] < min1){ 
                min2 = min1; 
                id2 = id1; 
                id1 = j; 
                min1 = krot[j]; 
            } 
            else if(krot[j] < min2){ 
                min2 = krot[j]; 
                id2 = j; 
            }
        } 

        assert(min1 < INF && min2 < INF && id1 >= 0 && id2 >= 0); 
        if(!(min1 < INF && min2 < INF && id1 >= 0 && id2 >= 0)){ 
            printf("i: %d min1: %d min2: %d  id1: %d id2: %d",i, min1,min2, id1, id2);
            memory_error();  
        } 
        // teraz w miejsce wsk mergujemy id1 i id2 
        aktualnosc[id1] = 0; 
        aktualnosc[id2] = 0; 
        przej[wsk] = new_node(); 
        setNode(przej[wsk], NULL, przej[id1], przej[id2], 0); 
        przej[id1]->parent = przej[wsk]; 
        przej[id2]->parent = przej[wsk]; 
        krot[wsk] = krot[id1]+krot[id2]; 
        aktualnosc[wsk] = 1;
        wsk++;  
    }
    return przej[wsk-1]; 
}
 
// w lewo dostajemy 0, a w prawo dostajemy 1 
void print_tree(struct node* T, ll mess, int len){ 
    if(T->child[0] != NULL){ 
        print_tree(T->child[0], mess<<1, len+1); 
    } 
    if(T->child[1] != NULL){ 
        print_tree(T->child[1], (mess<<1) + 1, len+1); 
    } 
    if(T->child[0] == NULL && T->child[1] == NULL){ 
        // tutaj ladnie wypisujemy w konwencji 0:a:100:b:101:c:110:d:111:e
        for(ll i = len-1; i >-1 ; i--){ 
            if((1 << i) & mess) 
                putchar('1'); 
            else 
                printf("0");  
        } 
        printf(":%c:", T->value); 
    }
}

void tree_dfs(struct node* T, ll mess, int len, ll* sign_code, char* sign_len){ 
     if(T->child[0] != NULL){ 
        tree_dfs(T->child[0], mess<<1, len+1, sign_code, sign_len); 
    } 
    if(T->child[1] != NULL){ 
        tree_dfs(T->child[1], (mess<<1) + 1, len+1, sign_code, sign_len); 
    } 
    if(T->child[0] == NULL && T->child[1] == NULL){ 
        sign_code[(int)T->value] = mess; 
        sign_len[(int)T->value] = len;   
        
    }
}

char* code(char *napis, int length, struct node* top, int* newlen){ 
    ll sign_code[256]; 
    char sign_length[256];    

    for(int i = 0; i < 256; i++){ 
        sign_code[i] = 0; 
        sign_length[i] = 0; 
    }

    tree_dfs(top, 0, 0, sign_code, sign_length);    
    
    int code_length = 0;  
    for(int i = 0; i < length; i++){  
        code_length += sign_length[(int)napis[i]]; 
    } 
    char* code = malloc((code_length)*sizeof(char));
    if(code == NULL) 
        return NULL; 
        //memory_error();  
    int wsk = 0; 
    for(int i = 0; i < length; i++){  
        //printf("%c %d  ", napis[i], sign_length[(int)napis[i]]);

        for(int j = sign_length[(int)napis[i]]-1; j>-1; j--){ 
            if(sign_code[(int)napis[i]] & ((ll)1 << j)) 
                code[wsk++] = '1'; 
            else 
                code[wsk++] = '0'; 
        }
    } 
    *newlen = code_length; 
    return code; 
}

char* decode(char *code, int code_length, struct node* top, int* newlen){ 
    char *messesage = malloc(1*sizeof(char));   
    if(messesage == NULL) 
        return NULL; 
    //memory_error(); 
    int wsk = 0;  
    struct node* T; 
    int mess_len = 0;  char *buf; 
    while(wsk < code_length){  
        buf = realloc(messesage, (mess_len+1)*sizeof(char)); 
        if(buf == NULL) 
            return NULL; 
            //memory_error();
        messesage = buf;  
        T = top;  
        while(!(T->child[0] == NULL && T->child[1]== NULL)){ 
            if(code[wsk++] == '0') 
                T = T-> child[0]; 
            else 
                T = T->child[1]; 
        }
        messesage[mess_len++] = T->value; 
    } 
    *newlen = mess_len; 
    return messesage; 
}

