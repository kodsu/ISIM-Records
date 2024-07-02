#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#include "napis.h" 
// null pointer NULL
//struct cstring{ 
//    char *mess; int shift; 
//}; 


// tworzenie z inicjalizacja 

void blad_pamieci0(){ 
    printf("systemowy blad alokacji pamieci\n"); 
    return; 
}


void blad_pamieci1(){ 
    printf("systemowy blad alokacji pamieci\n"); 
    exit(1); 
}
struct cstring* create_cstring(char* napis, int przes){ 
    struct cstring* obj = (struct cstring*)malloc(sizeof(struct cstring)); 
    if(obj == NULL){ 
        blad_pamieci0();  
        //free(obj); 
        return NULL;  
    }
    obj->mess = (char*)malloc(strlen(napis)+1); 
    if(obj->mess == NULL){ 
        blad_pamieci0();  
        //free(obj->mess); 
        free(obj); 
        return NULL;  
    } 
    strcpy(obj->mess, napis); 
    obj->shift = przes; 
    return obj; 
} 
// usuwanie 
void remove_cstring(struct cstring* obj){ 
    free(obj->mess); 
    free(obj); 
}

// wypisanie szyfrem cezarta 
void print_shifted(struct cstring* obj){ 
    int len = strlen(obj->mess);  
    for(int i = 0; i < len; i++){  
        if(obj->mess[i] >= 'a' && obj->mess[i] <= 'z')
            printf("%c", (char) (((obj->mess[i])-'a'+obj->shift)%26 + 'a') );  
        else if(obj->mess[i] >= 'A' && obj->mess[i] <= 'Z') 
            printf("%c", (char) (((obj->mess[i])+-'A'+obj->shift)%26 + 'A'));  
        else
            putchar(obj->mess[i]);
    } 
    printf("\n"); 
    return; 
} 


// zwraca wartosc shifta
int get_shift(struct cstring* obj){ 
    return obj->shift; 
} 

// ustawia shifta na jakiegos
void set_shift(struct cstring* obj, int new_shift){ 
    obj->shift = new_shift; 
    return; 
} 

// ustawia napis na dany
bool set_messesage(struct cstring* obj, char* nowy_napis){ 
    if(strlen(obj->mess) == strlen(nowy_napis)){ 
        strcpy(obj->mess, nowy_napis); 
        return 1; 
    } 
    { 
        char* ptr = realloc(obj->mess, (strlen(nowy_napis)+1)*sizeof(char)); 
        if(ptr == NULL){ 
            blad_pamieci0();
            //free(ptr); 
            return 0; 
        } 
        obj->mess = ptr; 
        strcpy(obj->mess, nowy_napis); 
        return 1;  
    }  
}

// kopiuje napis przeshiftowany o nowym, zerowym shifcie
struct cstring* clone_shifted(struct cstring* obj){ 
    struct cstring * nowy_obj = create_cstring(obj->mess, obj->shift);  
    if(nowy_obj == NULL){ 
        return NULL; 
    }
    int len = strlen(nowy_obj->mess); 
    for(int i = 0; i < len; i++){ 
        if(obj->mess[i] >= 'a' && obj->mess[i] <= 'z')
            nowy_obj->mess[i] = (char) (((obj->mess[i])-'a'+obj->shift)%26 + 'a');  
        if(obj->mess[i] >= 'A' && obj->mess[i] <= 'Z') 
            nowy_obj->mess[i] = (char) (((obj->mess[i])-'A'+obj->shift)%26 + 'A');  
    } 
    return nowy_obj; 
} 