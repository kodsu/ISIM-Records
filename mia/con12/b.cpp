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

void solve(){ 
    vi v; int n; cin >> n; 
    v.resize(n); 
    for(int i = 0; i < n; i++) 
        cin >> v[i]; 
    bool same_jedynki = 1; 
    for(int i = 0; i < n; i++) 
        if(v[i] != 1) 
            same_jedynki = 0; 
    if(same_jedynki){ 
        if(n%2 == 0) 
            cout << "Second\n"; 
        else 
            cout << "First\n"; 
        return; 
    } 
    for(int i = 0; i < n; i++){ 
        if(v[i] != 1){ 
            if(i %2 == 0){ 
                cout << "First\n"; 
                return; 
            } 
            else  
            { 
                cout << "Second\n"; 
                return; 
            }
        }
    }
}

int main(){ 
    int t; cin >> t; 
    while(t--){ 
        solve(); 
    }
}