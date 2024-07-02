#include<stdio.h>   
#include<math.h> 
#include <stdlib.h>
#include<stdbool.h> 
typedef long long ll; 

#define MAKS_L 20000100
#define MAKS_SIZ 1100000 
static int dzielnik[MAKS_L] = {0};  
static bool parzysta[MAKS_L] = {0}; 
int wartosci[MAKS_SIZ] = {0}; 
static char histogram[MAKS_L] = {0};  
int indeksy[MAKS_SIZ] = {0};  
int ile_wygranych[MAKS_SIZ] = {0}; 
int ile_roz = 0;  

int to_clear[MAKS_SIZ] = {0};  
int clear_len = 0; 
void add_to_h(int v){  
    to_clear[clear_len++] = v; 
    if(histogram[v] == 0) 
        ile_roz++; 
    histogram[v]++; 
} 
void subtract_from_h(int v){ 
    if(histogram[v] == 1) 
        ile_roz--; 
    histogram[v]--; 
}
void clear_histogram(){  
    ile_roz = 0; 
    for(int i = 0; i < clear_len; i++){ 
        histogram[to_clear[i]] = 0; 
    } 
    clear_len = 0; 
}

void sito(){ 
    for(int i = 2; i * i < MAKS_L; i++){ 
        if(!dzielnik[i]){ 
            for(int j = 2*i; j < MAKS_L; j+=i) 
                dzielnik[j] = i; 
        }
    }
    for(int i = 2; i < MAKS_L; i++){ 
        if(dzielnik[i] == 0) 
            dzielnik[i] = i; 
    }
}

void build_parzysta(){ 
    parzysta[0] = 1; 
    parzysta[1] = 1;  
    int wsk; 
    for(int i = 2; i < MAKS_L; i++){ 
        wsk = i; 
        while(wsk != 1){ 
            add_to_h(dzielnik[wsk]); 
            wsk /= dzielnik[wsk]; 
        } 
        parzysta[i] = (ile_roz%2 == 0); 
        clear_histogram(); 
    }
}

// abs(x) <- wartosc bezwzgledna z x 

void wyp(int x){ 
    printf("%d \n", x); 
}
int main(void){ 
    sito(); 
    build_parzysta();   
    // for(int i = 0; i < 50; i++){ 
    //     printf("%d %d\n", i, parzysta[i]); 
    // }
    // wyp(parzysta[8]); 
    // wyp(parzysta[28]); 
    // wyp(parzysta[30]); 
    int k; 
    scanf("%d", &k); 
    //   if(k > 10){ 
    //     printf("-1"); 
    //     return 0;
    // }
    int len = (1 << k); 
    for(int i = 0; i < len; i++){ 
        indeksy[i] = i;  
        scanf("%d", &wartosci[i]); 
    }
    for(int run = 0; run < k; run++){ 
        for(int i = 0; i < len; i+= 2){  
            //wyp(wartosci[indeksy[i]] - wartosci[indeksy[i+1]]);  
            //printf("%d %d\n", indeksy[i], indeksy[i+1]); 
            if(parzysta[abs(wartosci[indeksy[i]] - wartosci[indeksy[i+1]])]){  
                ile_wygranych[indeksy[i]]++; 
                indeksy[(i >> 1)] = indeksy[i];
            } 
            else 
            { 
                ile_wygranych[indeksy[i+1]]++; 
                indeksy[(i >> 1)] = indeksy[i+1]; 
            }
        }  
        // for(int i = 0; i < len; i++)   
        //     printf("%d ", indeksy[i]); 
        // printf("\n"); 
        len >>= 1; 
    }  
    len = (1 << k); 
    for(int i = 0; i < len; i++ ){ 
        printf("%d ", ile_wygranych[i]); 
    }
}

