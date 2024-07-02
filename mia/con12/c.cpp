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

ll pot[62]; 
ll amo_on_pref(ll x, int pos){ 
    if(!(x & (((ll)1) << pos))){ 
        return ((x - x%pot[pos+1])/ 2); 
    } 
    return ((x - x%pot[pos+1])/ 2) + (x %pot[pos]) + 1; 

}
ll xor_on_seg(ll a, ll b){
   ll res = 0; ll amo; 
   for(ll i = 0; i < 59; i++){ 
        amo = amo_on_pref(b, i) - amo_on_pref(a-1, i);  
        if(amo &1){ 
            res |= ((ll)1 << i); 
        }
   } 
   return res; 
}

int main(){ 
    pot[0] = 1; 
    for(int i = 1; i < 62; i++) 
        pot[i] = (pot[i-1] << 1); 
    int n; 
    cin >> n; ll x, m; 
    ll res = 0; 
    for(int i = 0; i < n; i++){ 
        cin >> x >> m; 
        res ^= xor_on_seg(x, x + m -1); 
    } 
    if(res == 0) 
        cout << "bolik"; 
    else 
        cout << "tolik"; 
    
}