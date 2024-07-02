#include <bits/stdc++.h>
#include <limits.h>
using namespace std; 

typedef unsigned long long ull;  
void d_test(){ 
    int k = INT_MAX; k  = -k; 
    cout << k << "\n"; 
    exit(0); 
} 
void e_test(){ 
    int k = INT_MIN; 
    k = -k; 
    cout << k << "\n"; 
    exit(0); 
} 
void f_test(){ 
    int k = 0; 
    cout << ((k | -k) >> 31) << "\n"; 
    exit(0); 
} 
void g_test(){ 
    int x = (1 << 30), y = x; 
    cout << ((x + y == (uint32_t)x + (uint32_t)y) ? "true" : "false") << "\n"; 
    
    exit(0); 
}  
#include <unistd.h> 
mt19937 gen(getpid()); 

int los() { 
    int ans = gen(); 
    ans <<= 16; 
    ans += gen(); 
    return ans; 
} 

void h_test(){  
    vector <int> values = {INT_MIN, INT_MAX, 0, 1, -1, INT_MIN + 1, INT_MAX -1, 2, 4, 8, 16, 32, 64, 1 << 30, 1 << 31}; 
    for(int i = 0; i < 1000; i++) 
        values.push_back(los()); 
    for(auto x : values){ 
        for(auto y: values){ 
            if( x * ~y + (uint32_t)y * (uint32_t)x != -x){ 
                cout << x <<" " << y << "\n"; 
                cout << x * ~y + (uint32_t)y * (uint32_t)x << "\n"; 
                cout << (unsigned) (-x) << "\n"; 
                exit(0); 
            }
        }
    }  
    cout << "Dobrze jest\n";  
    exit(0); 
} 


int main(){   
    h_test(); 
    g_test(); 
   ull x = (1 << 16) -100; 
   for(int i = 0; i < 10000000; i++){ 
        if( (x*x) & ((ull)1 << 31)) { 
            cout << x << "\n"; 
            cout << x * x << "\n"; 
            exit(0); 
        } 
   }
}