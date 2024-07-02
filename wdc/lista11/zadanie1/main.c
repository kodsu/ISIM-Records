#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 
#include "huffman.h"



int main(){  
    int c; 
    char* napis = malloc(1*sizeof(char)); 
    int len = 0;  
    char* buf; 
    while((c = getchar())!= EOF){ 
        len++; 
        buf = realloc(napis, len *sizeof(char)); 
        if(buf == NULL) 
            memory_error(); 
        napis = buf; 
        napis[len-1] = c; 
    } 
    struct node* T = generate_tree(napis, len); 
    if(T == NULL) 
        memory_error(); 
    for(int i = 0; i < len; i++){ 
        printf("%c", napis[i]); 
    } 
    printf("\n"); 
    print_tree(T, 0,0);  
    printf("\n");
    int code_len = 0; char* bin_code; 
    bin_code = code(napis, len, T, &code_len); 
    if(bin_code == NULL) 
        memory_error(); 
    // tutaj wypisujemy zakodowana wiadomosc 
    for(int i = 0; i < code_len; i++) 
        printf("%c", bin_code[i]); 
    printf("\n"); 

    // tutaj dekodujemy zakodowana wiadomosc 
    char* messesage; int mess_len; 
    messesage = decode(bin_code, code_len, T, &mess_len); 
    if(messesage == NULL) 
        memory_error();  

    // tutaj wypisujemy wiadomosc, powinna byc rowna oryginalnej 
    for(int i = 0; i < mess_len; i++){ 
        printf("%c", messesage[i]); 
    } 
    printf("\n"); 

    // porownojemy rozmiary 
    char input_b[256]; int ile_roz = 0;  
    for(int i = 0; i < 256; i++) 
        input_b[i] = 0; 
    for(int i = 0; i < len; i++){
        if(input_b[(int)napis[i]] == 0) 
            ile_roz++; 
        input_b[(int)napis[i]]++; 
    }
    int log_ceil = 0, pom =1; 
    while(pom< ile_roz){
        pom<<=1; 
        log_ceil++; 
    } 
    printf("Uczciwy rozmiar wejscia: %d\n", len*log_ceil);  
    printf("Rozmiar zakodowanej wiadomosci: %d\n", code_len); 
    // zwalniamy pamiec
    remove_subtree(T); 
    free(bin_code); 
    free(messesage); 
    free(napis); 
}   