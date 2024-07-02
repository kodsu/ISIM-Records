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
const ll INF = (ll)1e18 + (ll)123; 

ll fun(ll x){ 
    int res = 0; 
    while(x){ 
        res++; 
        x>>= 1; 
    } 
    return res; 
}
void solve(){ 
    int n; cin >> n; 
    ll mini = INF, maxi = -INF;  
    ll buf; 
    for(int i = 0; i< n; i++){ 
        cin >> buf; 
        if(buf < mini) 
            mini = buf; 
        if(buf > maxi) 
            maxi = buf; 
    } 
    int res = fun(maxi - mini); 
    cout << res << "\n";   
    if(res == 0) 
        return; 
    if(res <= n){ 
        for(int i = 0;i < res; i++) 
            cout << 0 << ' ';  
        //cout << 1; 
        cout << "\n"; 
    }
}
int main(){ 
   int t; cin >> t; 
   while(t--){ 
        solve(); 
   }
}
