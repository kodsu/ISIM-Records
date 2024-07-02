#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 

typedef struct{ll st; ll nd;} pair; 

ll sufit(ll a, ll b){ // zwraca sufit z a/b 
    if(a%b == 0) 
        return a/b; 
    return a/b+1; 
} 

ll gcd(ll a, ll b){ 
    if(b == 0) 
        return a; 
    return gcd(b, a%b); 
}
 
void wypisz_ost(pair x){ 
    printf("%lld/%lld\n", x.st, x.nd); 
} 

void wypisz_nieost(pair x){ 
    printf("%lld/%lld + ", x.st, x.nd); 
}

int main(int argc, char *argv[]){   
    //printf("%ld %ld\n", strlen(argv[1]), strlen(argv[2]));   
    //printf("%d\n", argc); 
    if(argc > 4 || argc < 3){ 
        fprintf(stderr, "%s", "Nieprawidlowa liczba argumentow wywolania\n"); 
        return 1;       
    }    
    ll A, B; 
    if(argc == 3){ 
        char *endptr; 
        A = strtol(argv[1], &endptr, 10); 
        if(*endptr != '\0'){ 
            fprintf(stderr, "Niepoprawny format liczby na wejsicu\n");  
            return 1; 
        }
        B = strtol(argv[2], &endptr, 10); 
        if(*endptr != '\0'){ 
            fprintf(stderr, "Niepoprawny format liczby na wejsicu\n");  
            return 1; 
        }
    } 
    if(argc == 4){ 
        int ind = -1; 
        for(int i = 1; i <= 3; i++){ 
            if(strlen(argv[i]) == 1 && argv[i][0] == 'N'){ 
                ind = i; break; 
            }
        } 
        if(ind == -1){ 
            fprintf(stderr, "Niepoprawny format danych wejsciowych\n");  
            return 1; 
        }
        char *endptr; 
        int aind, bind; 
        if(ind == 1) {aind = 2; bind = 3; } 
        if(ind == 2) {
            fprintf(stderr, "Niepoprawny format danych wejsciowych\n");  
            return 1;
            aind = 1; bind = 3; } 
        if(ind == 3){aind = 1; bind = 2; }  
        A = strtol(argv[aind], &endptr, 10); 
        if(*endptr != '\0'){ 
            fprintf(stderr, "Niepoprawny format liczby na wejsicu\n");  
            return 1; 
        }
        B = strtol(argv[bind], &endptr, 10); 
        if(*endptr != '\0'){ 
            fprintf(stderr, "Niepoprawny format liczby na wejsicu\n");  
            return 1; 
        }
    } 
    //printf("%lld %lld\n", A, B);  
    if(A > B){ 
        fprintf(stderr, "Niepoprawne dane - licznik wiekszy niz mianownik\n");  
        return 1; 
    }   
    if(A < 0 || B < 0){ 
        fprintf(stderr, "Niepoprawne dane - podano liczbe ujemna\n");  
        return 1; 
    }
    ll dziel = gcd(A, B); 
    A /= dziel; B /= dziel; 
    pair res = {A, B}; 
    if(A == 0 || A ==1){ 
        wypisz_ost(res); 
        return 0; 
    }  
    pair nowy; ll a;// ll buf; 
    while(res.st != 1){  
        a = sufit(res.nd, res.st); 
        nowy.st = 1; nowy.nd = a;   
        wypisz_nieost(nowy);  
        //res = {a * res.st - res.nd, a * res.nd}; 
        res.st = a * res.st - res.nd; res.nd = a * res.nd;
        dziel = gcd(res.st, res.nd); 
        res.st /= dziel; res.nd /= dziel; 
    } 
    wypisz_ost(res); 
}