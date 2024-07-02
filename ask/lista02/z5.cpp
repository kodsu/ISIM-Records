#include <bits/stdc++.h>
#include <limits.h>
using namespace std; 

typedef unsigned long long ull;  

int f(int x){ 
    int bas = ((x >> 2) << 1) + (x >> 2); 
    int r = x - ((x >> 2) << 2);  
   // cout << "wywolanie : " << x << "\n"; 
   // cout << "bas = " << bas << "\n"; 
   // cout << "r = " << r << "\n"; 
   // cout << "wynik: " ;  
    return bas + (((r&3)>>1)&(r&1)) + ((r&2) >> 1); 
}
int main(){   
  // cout << f(1) << " " << f(4) << " " << f(6) << " " << f(19) << "\n"; 
  // cout << f(-1) << " " << f(-5) << " " << f(-13) << "\n";  
  int x; 
  while(1){ 
    cin >> x; 
    cout << f(x) << endl; 
   }
   
}