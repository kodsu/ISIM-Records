#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>

struct cstring{ 
    char *mess; int shift; 
}; 


// tworzenie z inicjalizacja 

struct cstring* create_cstring(char* napis, int przes); 
// usuwanie 
void remove_cstring(struct cstring* obj); 

// wypisanie szyfrem cezarta 
void print_shifted(struct cstring* obj); 


// zwraca wartosc shifta
int get_shift(struct cstring* obj); 

// ustawia shifta na jakiegos
void set_shift(struct cstring* obj, int new_shift); 

// ustawia napis na dany
bool set_messesage(struct cstring* obj, char* nowy_napis);

// kopiuje napis przeshiftowany o nowym, zerowym shifcie
struct cstring* clone_shifted(struct cstring *);  

void blad_pamieci0(); 
void blad_pamieci1(); 
