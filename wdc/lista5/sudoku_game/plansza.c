// tutaj sa funkcje obslugujące planszzę 
// m in czy dany gracz wygrał na danej planszy 
// funkcję wypisująca stan planszy  

#include "plansza.h"
int super1[MAKS_SIZE * 4 + 5];  
int super2[MAKS_SIZE * 4 + 5];  

bool czy_wygral(char gracz, int n, char tab[n][n]){  
    int enough = n; if(5 < n) enough = 5; 
    // zwrocic tak jesli jakis rzad lub kolumna lub przekatna ma n znakow typu gracz  
    int ile = 0; 
     for(int i = 0; i < MAKS_SIZE*4 + 5; i++){ 
        super1[i] = 0; 
        super2[i] = 0;  
    } 
    for(int i = 0; i < n; i++){  
        for(int j = 0; j < n; j++) 
            if(tab[i][j] == gracz){ 
                super1[i-j+MAKS_SIZE*2]++; 
                super2[i+j+MAKS_SIZE*2]++; 
            } 
    } 
    for(int j = 0; j < n;  j++){ 
        ile = 0; 
        for(int i = 0; i < n; i++){ 
            if(tab[i][j] == gracz) 
                ile++; 
        } 
        if(ile == enough) 
            return 1; 
        ile = 0; 
        for(int i = 0; i < n; i++){ 
            if(tab[j][i] == gracz) 
                ile++; 
        } 
        if(ile == enough) 
            return 1; 
    } 
    for(int i = 0; i < MAKS_SIZE*4 + 5; i++){ 
        if(super1[i] == enough || super2[i] == enough) 
            return 1; 
    } 
    gracz++; 
    return 0; 
} 

void wypisz_plansze(int n, char tab[n][n]){ 
    for(int i = 0; i < n; i++){ 
        for(int j = 0; j < n; j++){ 
            if(tab[i][j] == 0) 
                printf("-");  
            else 
                printf("%c", tab[i][j]); 
        }
        printf("\n"); 
    } 
    printf("\n"); 
}