#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 

typedef struct{ll st; ll nd;} pair; 

int n, m; 

int B[10]; 
int per[10]; 

int licz = 0;  
int lim; 
int substr[10]; 
void analizuj_per(){   
    bool good = 1;  

    int wsk = 0; 
    for(int mask = 0; mask < lim; mask++){ 
        if(__builtin_popcount(mask) != m) 
            continue; 
        wsk = 0; 
        for(int i = 0; i < n; i++){ 
            if(mask & (1 << i)) 
                substr[wsk++]=per[i]; 
        }
        good = 1; 
        for(int i = 0; i < m; i++){ 
            for(int j = i+1; j < m; j++){ 
                if(!((substr[i] > substr[j] && B[i] > B[j]) || (substr[i] < substr[j] && B[i] < B[j])) ){ 
                    good = 0; 
                    break; 
                }
            } 
            if(!good) 
                break; 
        } 
        if(good){ 
            licz++; 
            return; 
        }
    }
}

void gener_per(int wsk){  
    //printf("%d\n", wsk); 
    if(wsk == n){ 
        analizuj_per(); 
        return; 
    } 
    bool used[n]; 
    for(int i = 0; i <n; i++) 
        used[i] = 0; 
    for(int i = 0; i < wsk; i++) 
        used[per[i]-1] = 1; 
    for(int i = 0; i < n; i++){ 
        if(!used[i]){ 
            per[wsk] = i+1; 
            gener_per(wsk+1); 
            per[wsk] = 0; 
        }
    }
}


int main(){  
    if(scanf("%d%d", &n, &m) != 2) 
        return 2;     
    for(int i = 0; i < m; i++){ 
        if(scanf("%d", &B[i]) != 1) 
            return 1; 
    }
    lim = (1 << n); 
    gener_per(0);  
    printf("%d", licz);  

}   