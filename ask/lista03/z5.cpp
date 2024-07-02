#include<bits/stdc++.h> 
#include<limits.h> 
#include<unistd.h> 

using namespace std; 

typedef long long ll; 
bool check2(int x, int y){ 
    double dx = x; double dy = y; 
    return (dx - dy == double(x - y)); 
}

bool check4(int x, int y, int z){ 
    double dx = x, dy = y, dz = z;  
    return ( (dx*dy)*dz == dx *(dy * dz)); 
}
void history(){ 
    cout << check2(INT_MIN, INT_MAX);  // <- kontrprzyklad dla 2 
    cout << check4(1000000432 , 1000000009 , 1000000123) << "\n";  // <- kontrprzyklad dla 4 

}   


mt19937 gen(getpid());  

ll los(ll a, ll b){ 
    ll res = gen(); 
    res <<= 31; res += gen(); 
    return a + res%(b-a+1) * ((gen() & 1) ? -1: 1 ); 

}  

bool check5(int x, int z){ 
    double dx = x; 
    double dz = z; 
    return dx/dx == dz/dz; 
}
void generating(){ 
    int tests = 1000000;   
    int a, b, c; 
    //cout << check4(1000000432 , 1000000009 , 1000000123) << "\n"; 
    for(int i = 0; i < tests; i++){ 
        a = los(0, INT_MAX);  b = los(0, INT_MAX); c = los(0, INT_MAX); 
        if(!check4(a, b, c)){  
            cout << i << "\n"; 
            cout << a << " " << b << " " << c <<  "\n"; 
            exit(0); 
        }
    }
}

int main(){   
    uint32_t x = 12; 
    cout << x ; 
   // cout << check5(0, 1) << "\n"; 
}