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


int main(){  
    ll n; cin >> n; 
    if(n  < 5){ 
        cout << 0; 
        return 0; 
    }  
    ll res = n * (n-1)*(n-2)*(n-3)*(n-4); 
    for(ll i = 1; i <= 5; i++) 
        res /= i;   
    ll sil = 1; 
    for(int i = 1; i <= 5; i++) sil *= i; 
    cout << (res*res*sil); 
}
