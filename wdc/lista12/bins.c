#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 
#define siz 200009
#define AMO 128  
#define INF 100000009
#pragma GCC diagnostic ignored "-Wunused-result"
int* tab[AMO]; 
int rozm[AMO];  
int asiz[AMO]; 

void memory_error(){ 
    assert(1 == 0); 
    exit(3); 
}

void extend(int ind){ 
    rozm[ind] *= 2; 
    tab[ind] = (int*)realloc(tab[ind], rozm[ind]*sizeof(int)); 
    if(tab[ind] == NULL) 
        memory_error(); 
}

void push_back(int ind, int val){ 
    if(asiz[ind] == rozm[ind]) 
        extend(ind); 
    tab[ind][asiz[ind]++] = val; 
}
void init(){ 
    for(int i = 0; i < AMO; i++){ 
        asiz[i] = 0; 
        rozm[i] = 4; 
        tab[i] = (int*)malloc(sizeof(int) * rozm[i]);        
        if(tab == NULL) 
            memory_error(); 
    }
}

bool is_white(char c){ 
    return (c == ' ' || c == '\n' || c == '\t');
}
int n,q;  

int search(int ind, int val){ // zwraca w posortowanej tab[ind] najmniejsza wartosc >= val
    int l = 0, r = asiz[ind]-1;  int s; 
    while(l < r){ 
        s =  (l + r) >> 1;
        if(tab[ind][s] >= val) 
            r = s; 
        else   
            l = s+1;  
    } 
    return tab[ind][l]; 
} 

int search_pos(int ind, int val){ // zwraca w posortowanej tab[ind] najmniejsza wartosc >= val
    int l = 0, r = asiz[ind]-1;  int s; 
    while(l < r){ 
        s =  (l + r) >> 1;
        if(tab[ind][s] >= val) 
            r = s; 
        else   
            l = s+1;  
    } 
    return l; 
}  

int main(){  
    init(); 
    scanf("%d%d", &n, &q);
    char c; 
    for(int i = 0; i < n; i++){ 
        scanf("%c", &c); 
        while(is_white(c))
            scanf("%c", &c);  
        push_back(c, i);   
        //printf("%d %d\n", c, i);    
    } 
    //assert(7 == 11); 
    for(int i = 0; i < AMO; i++){ 
        push_back(i, INF);
    }
    int type; char X, Y; int k; int a, b; 

    for(int i = 0; i < q; i++){ 
        scanf("%d", &type); 
        if(type == 1){ 
            scanf("%d %c", &k, &X); 
            if(asiz[(int)X] > k){ 
                printf("%d\n", tab[(int)X][k-1]); 
            } 
            else 
                printf("BRAK\n"); 
        } 
        if(type == 2){ 
            // od pozycji k w prawo, ktorego goscia spotkamy pierwszego 
            scanf("%d %c %c", &k, &X, &Y);
            a = search(X, k); 
            b = search(Y, k);  
           // printf("%d %d" , a, b); 
            if( a == b  && b == INF){ 
                printf("BRAK\n"); 
                continue;
            }  
            if(a <= b)  
                printf("%c\n", X); 
            else 
                printf("%c\n",Y); 
        } 
        if(type == 3){ 
            scanf(" %c %d %d", &X, &a, &b); 
            k = search_pos(X, a) - search_pos(X, b+1); 
            printf("%d\n", -k);
        }
    }
}