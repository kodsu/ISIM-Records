// funkcja grająca za gracza losowego 
#include "gracz_losowy.h"

int los(int a, int b){ 
    return (a + (rand() % (b-a+1))); 
} 

char* ruch_losowego(char gracz, int n, char tab[n][n]){  
    int wsk = 0; gracz++; 
    for(int i = 0; i < n; i++){ 
        for(int j = 0; j < n; j++){ 
            if(tab[i][j] == 0){
                buf[wsk++] = &tab[i][j]; 
            }  
        }
    }  
    assert(wsk > 0);  
    return buf[los(0, wsk-1)]; 
}