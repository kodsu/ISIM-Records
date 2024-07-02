#include <bits/stdc++.h>
#include <limits.h>
using namespace std; 

typedef unsigned long long ull;  


int main(){   
    int x = 312423; int y = 9458537; 
    x = x^y; 
    y = x^y; 
    x = x^y; 
    cout << x << " " << y << "\n"; 
}