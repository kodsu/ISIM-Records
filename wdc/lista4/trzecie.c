#include<stdio.h>   
#include<math.h> 
#include <stdlib.h>
#include<stdbool.h> 
typedef long long ll; 

ll gcd(ll a, ll b){ 
    if(b == 0) 
        return a; 
    return gcd(b, a%b); 
}

typedef struct {
    ll st;
    ll nd;
} pair;

ll lcm(ll a, ll b){ 
    return (a/gcd(a,b))*b; 
}

pair dodaj(pair A, pair B){ 
    ll doc = lcm(A.nd, B.nd); 
    A.st *= doc/A.nd; 
    B.st *= doc/B.nd; 
    pair res = {A.st+B.st, doc};   
    ll dziel = gcd(res.st, res.nd); 
    res.st/= dziel; res.nd/= dziel; 
    return res; 
}

pair czytaj(ll dziel){ 
    //pair wyn = {0, 1};  
    int typ; 
    scanf("%d", &typ); 
    if(typ == 0){
        pair wyn = {0,1}; 
        return wyn; 
    }  
    if(typ == 1){ 
        pair wyn = {1, dziel}; 
        return wyn; 
    } 
    if(typ == 2){ 
        pair wyn = {0, 1}; pair pom; 
        for(int i = 0; i < 4; i++){ 
            pom = czytaj(dziel*4); 
            wyn = dodaj(wyn, pom); 
        } 
        return wyn; 
    }  
    pair wyn = {-1, -1}; 
    return wyn;  
}

int main(void){ 
    pair res = czytaj(1); 
    printf("%lld/%lld", res.st, res.nd); 
}

