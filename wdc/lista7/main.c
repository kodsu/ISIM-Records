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

int main(){ 
    struct cstring* przyklad; 
    przyklad = create_cstring("heheHEHE", 1);  
    if(przyklad == NULL){ 
        blad_pamieci1(); 
    }
    print_shifted(przyklad); 
    printf("%d", get_shift(przyklad));  
    printf("\n"); 
    set_shift(przyklad, 4);  
    print_shifted(przyklad); 
    set_messesage(przyklad, "ABCabcABC"); 
    set_shift(przyklad, 0); 
    print_shifted(przyklad); 
    set_shift(przyklad, 2); 

    struct cstring* dr; 
    dr = clone_shifted(przyklad); 
    if(dr == NULL){ 
        blad_pamieci1(); 
    } 
    print_shifted(dr); 

}