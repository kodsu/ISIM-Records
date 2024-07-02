#include "gracz_ze_strategia.h"

char* ruch_deter(char gracz, int n, char tab[n][n]){  
    gracz++; 
    for(int i = 0; i < n; i++){ 
        for(int j = 0; j < n; j++){ 
            if(tab[i][j] == 0){
                return &tab[i][j]; 
            }
        }
    }  
    assert(0 == 1); 
    return &tab[0][0]; 
}