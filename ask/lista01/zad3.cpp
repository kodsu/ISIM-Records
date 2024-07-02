#include<bits/stdc++.h>

#define st first
#define nd second
#define pb(x) push_back(x)
#define pp(x) pop_back(x)
#define mp(a, b) make_pair(a, b)
#define all(x) (x).begin(), (x).end()
#define rev(x) reverse(all(x))
#define sor(x) sort(all(x))
#define sz(x) (int)(x).size()
#define rsz(x) resize(x)

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<pii > vii;
typedef vector<ll> vl;
typedef vector<pll> vll;
typedef string str;
#define BOOST ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL); 

struct A { 
    int8_t a; 
    void *b; 
    int8_t c; 
    int16_t d; 
};  
struct Aopt { 
    void *b; 
    int16_t d;
    int8_t a;  
    int8_t c; 
}; 
 

struct B{ 
    uint16_t a; 
    double b; 
    void *c; 
}; 
struct Bopt{ 
    double b; 
    void *c; 
    uint16_t a; 
}; 
 
int global_data = 1234; 
void hehe(){ 
    global_data++; 
    return; 
}
int main(){  
    A aobj; aobj.a = 5; aobj.b = (void*)hehe; aobj.c = 12; aobj.d = 1000; 
    //{5, (void*)hehe, 12, 1000}; 
    B bobj = {1230, 0.1234, (void*)&hehe}; 

    //cout << sizeof(int8_t) << " " << sizeof(void*) << " " << sizeof(int8_t) << " " << sizeof(int16_t)  << "\n"; 
    cout <<  sizeof(A) << " " << sizeof(Aopt) << "\n";  
    //cout << sizeof(int16_t) << " " << sizeof(double) << " " << sizeof(void*) << "\n"; 
    cout << sizeof(B) << " " << sizeof(Bopt) << "\n";   
    exit(0); 
    cout << (int)aobj.a << "\n"; 
    for(int i = 0; i < 24; i++){ 
        cout << i << " " << ( ((int)*(&aobj.a + i)) ) << "\n";  
    }
}