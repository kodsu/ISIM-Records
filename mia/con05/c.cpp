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

const int MN = 100005;

int n, l; 
unordered_set<int> S; 
int x, y; 

bool dasie0(int v){ 
    for(auto z : S){ 
        if(S.find(z+v) != S.end()) 
            return 1; 
        if(S.find(z-v) != S.end()) 
            return 1; 
    } 
    return 0; 
}  

int znaleziony=-1; 

bool poprawny(int c){ 
    return (0<= c && c <= l); 
}

bool dasie1(){  
    int nowy; 
    for(auto z : S){ 
        if(poprawny(z-x)){ 
            nowy = z-x; 
            if(S.find(nowy+y) != S.end()) 
                {znaleziony = nowy; return 1; }
            if(S.find(nowy-y) != S.end()) 
                {znaleziony = nowy; return 1; }
        }
        if(poprawny(z+x)){ 
            nowy = z+x; 
            if(S.find(nowy+y) != S.end()) 
                {znaleziony = nowy; return 1; }
            if(S.find(nowy-y) != S.end()) 
                {znaleziony = nowy; return 1; }
        }
        if(poprawny(z-y)){ 
            nowy = z-y; 
            if(S.find(nowy+x) != S.end()) 
                {znaleziony = nowy; return 1; }
            if(S.find(nowy-x) != S.end()) 
                {znaleziony = nowy; return 1; }
        }
        if(poprawny(z+y)){ 
            nowy = z+y; 
            if(S.find(nowy+x) != S.end()) 
                {znaleziony = nowy; return 1; }
            if(S.find(nowy-x) != S.end()) 
                {znaleziony = nowy; return 1; }
        }
    }
    return 0 ;
}

int main(){ 
    cin >> n >> l >> x >> y;  
    int buf; 
    for(int i = 0; i < n; i++){ 
        cin >> buf; 
        S.insert(buf); 
    }
    bool rx = dasie0(x), ry = dasie0(y); 
    if(rx && ry){ 
        cout << 0; 
        return 0; 
    } 
    if(rx || ry){ 
        if(rx){ 
            cout << 1 << "\n"; 
            cout << y; 
            return 0; 
        } 
        if(ry){ 
            cout << 1 << "\n"; 
            cout << x; 
            return 0; 
        }
    }  
    if(dasie1()){ 
        cout << 1<<"\n" << znaleziony;  
        return 0; 
    } 
    cout << 2 << "\n"; 
    cout << x << " " << y; 
}
