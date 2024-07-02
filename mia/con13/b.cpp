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
int tab[MN]; 
int val[MN]; 
ll pref1[MN]; 
ll pref2[MN];  
int main(){  
    int n ; cin >> n; 
    for(int i = 0; i < n; i++){ 
        cin >> tab[i]; 
        val[i] = tab[i]; 
    }
    sort(val, val + n); 
    pref1[0] = pref2[0] = 0; 
    for(int i = 1; i <= n; i++){ 
        pref1[i] = pref1[i-1] + tab[i-1]; 
        pref2[i] = pref2[i-1] + val[i-1]; 
    } 
    int q; cin >> q; int l, r; int typ; 
    for(int i = 0; i < q; i++){ 
        cin >> typ >> l >> r; 
        if(typ == 1) 
            cout << pref1[r]-pref1[l-1] << "\n"; 
        if(typ == 2) 
            cout << pref2[r] - pref2[l-1] << "\n"; 
    }
}