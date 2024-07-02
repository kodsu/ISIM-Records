#include<bits/stdc++.h> 

using namespace std; 
typedef long double ld; 
typedef long long ll; 



ld trapez_method(ld a, ld b, int n, function<ld(ld)> g){ 
    ld step = (b-a)/n;
    ld sum = g(b) + g(a);  
    ld base = a + step; 
    for(int i = 1; i < n; i++){ 
        sum += 2 * g(base); 
        base += step; 
    } 
    return sum/(2 *n); 
}

ld simpson_method(ld a, ld b, int n, function<ld(ld)> g){ 
    ld step = (b-a)/(2*n) ;  
    ld sum = g(a) + g(b); 
    ld base = a + step; 
    for(int i = 1; i < 2*n ; i++){ 
        if(i&1) 
            sum += 4*g(base); 
        else 
            sum += 2*g(base); 
        base += step; 
    } 
    return sum/(6*n);
}

ld fun(ld x){ 
    return 4/(1 + x*x); 
}

int main(){ 
    cout << fixed << setprecision(10); 
    cout << "trapez: " << trapez_method(0, 1, 60, fun) << "\n"; 
    cout << "simpson: " << simpson_method(0, 1, 30, fun) << "\n";  
}