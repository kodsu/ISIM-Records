#include <bits/stdc++.h> 

using namespace std; 

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