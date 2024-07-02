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

const ll mod = 1000000007;    
int k, t; 
const int MRES = 100000, MID = 100002;  
ll spos[MRES] = {0};  
void zrob_krok(){ 
    ll aktu = 0; 
    // robimy poczatek i koniec tak madrze prefiksowo - sufiksowo 
    for(int i = 0; i < 2*k)
}
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

int main(){  
    ll a, b, k, t; 
    cin >> a >> b >> k >> t; 
    spos[MID] = 1; 
    for(int i = 0; i < t; i++) 
        zrob_krok(); 
}   
