#include <bits/stdc++.h> 

using namespace std; 

const uint32_t wykpos = 0x7F800000; 
const uint32_t mantispos = 0x007FFFFF;
const uint32_t signpos = (1 << 31);  
const int bias = 127; 
const int max_wyk = (1 << 9) - 1; 

float val(uint32_t x, int i){ 
    if(x & wykpos == wykpos){ // typ NaN albo INF 
        return x; 
    } 
    if(i == 0) 
        return x; 
    uint wykl = (wykpos & x) >> 23; 
    wykl -= bias; 
    if(i > 0){ 
        // handlowanie nieznormalizowanych
        if(wykl == 0){ 
            int mantis = x & mantispos; 
            mantis = (mantis << 1) & mantispos;
            x = (x & ~mantispos) | mantis;  
            if(x & (1 << 22)){ 
                wykl = 1; 
                x = x & ~wykpos; 
                x |= (wykl <<23);
            } 
            return val(x, i-1); 
        }
        // handlowanie zwyklych rzeczy 
        if(wykl < max_wyk -1){ 
            wykl += 1; 
            x &= ~wykpos; 
            x |= (wykl<<23); 
            return val(x, i-1); 
        }
        // handlowanie wybicia na INF
        if(wykl == max_wyk-1){ 
            x |= wykpos;  
            x &= ~mantispos; 
            return x; 
        }
    } 
    if(i < 0){ 
        if(wykl == 0){ // przesuwamy mantyse 
            uint mantis = mantispos & x;
            mantis >>= 1; 
            x = (x & ~mantispos) | mantis; 
            return val(x, i+1);  
        }
        if(wykl == 1){ // dodajemy jedynke
            uint mantis = mantispos & x;
            mantis >>= 1;  
            mantis |= (1 << 22); 
            x = (x & ~mantispos) | mantis;  
            x &= ~wykpos; 
            return val(x, i+1);  
        }
        // zwyklosc 
        wykl = (x & wykpos) >> 23; 
        wykl -= 1; 
        x = x & ~wykpos; 
        x |= wykl << 23; 
        return val(x, i+1); 
    }
}
int main(){ 
    int x = 15625 ; 
    for(int i = 15; i > -1; i--){ 
        cout << (bool)((1 << i)&x); 
    }
    // float x = 0.15625;
    // for(int i =15; i > -1; i--){ 
    //     cout << (bool)(x & (1 << i)); 
    // }  
    // cout << "\n"; 
}