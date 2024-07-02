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


const int MN = 5009; 
ll sil[MN];  
const ll mod = 1000000007;  

ll pot(ll a, ll n){  
    if(n == 0) 
        return 1;  
    ll x = pot(a, n/2); 
    if(n%2 == 0) 
        return (x * x)% mod; 
    return ((x *x)%mod * a)%mod; 
}

ll odwmod(ll a){ 
    return pot(a, mod-2); 
}

vl amo; 
int main(){ 
    //cout << pot(5, 2) << " " << pot(5, 3) << " " << pot(5, 4); 
    int k; cin >> k; 
    amo.resize(k);  
    for(int i = 0; i < k; i++) 
        cin >> amo[i];  
    sil[0] = 1; 
    for(ll i = 1; i < MN; i++){ 
        sil[i] = (sil[i-1] * i)%mod; 
    }
    ll aktures = 1; 
    ll lacz = amo[0];  
    ll d; 
    for(int i = 1; i < k; i++){  
        if(amo[i] == 1){ 
            lacz++; 
            continue; 
        }

        aktures = (aktures *sil[lacz+amo[i]-1])%mod; 
        aktures = (aktures * odwmod(sil[lacz]))%mod; 
        aktures = (aktures * odwmod(sil[amo[i]-1]))%mod;  
        lacz += amo[i]; 
    }    
    cout << aktures; 
}