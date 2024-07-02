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

const ll mod = 998244353;   
const int MN = 5005; 
ll sil[MN];  
ll odwsil[MN];  
void build_data(){  
    sil[0] = 1; 
    for(ll i = 1; i < MN; i++){ 
        sil[i] = (sil[i-1] * i)%mod; 
    }
    odwsil[5000] = 150031294; 
    for(ll i = 5000; i > 0; i--){ 
        odwsil[i-1] = (odwsil[i] * i)%mod; 
    } 
    // cout << odwsil[1] << " " << odwsil[0]; 
}
ll amo_bij(ll x, ll y){ 
    ll res = 0;  
    if(x > y) 
        swap(x,y);  
    ll fir, sec;  

    for(ll k = 0; k <= x; k++){ 
        fir = (odwsil[x-k] * odwsil[y-k])%mod; 
        fir = (fir * odwsil[k])%mod; 
        res = (res + fir)%mod; 
    } 
    res = (res * sil[x])%mod; 
    res = (res *sil[y])%mod;  
    return res; 
}
int main(){  
    build_data();  
    ll a, b, c; 
    cin >> a >> b >> c; 
    ll wyn = amo_bij(a,b) ; 
    wyn = (wyn * amo_bij(b,c))%mod; 
    wyn = (wyn * amo_bij(a, c) )%mod;  
    cout << wyn ;   

}
