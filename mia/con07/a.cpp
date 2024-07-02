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


void run(){ 
    string A, B; 
    cin >> A >> B; 
    if(B == "a"){ 
        cout << 1 << "\n"; 
        return;
    } 
    bool contain = 0; 
    for(int i = 0; i < sz(B); i++){ 
        if(B[i] == 'a'){ 
            contain = 1; 
        }
    } 
    if(contain){ 
        cout << -1 << "\n";  
        return; 
    } 
    ll res = 1;  
    for(int i = 0; i < sz(A); i++) 
        res <<= 1; 
    cout << res << "\n"; 
}
int main(){  
    //BOOST
    int t; cin >> t; 
    while(t--){ 
        run(); 
    }   
}