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


const int MN = 200009; 
int add[MN]; 
int wyst[MN];
vi wy; // liczba wystapien 
vi val;   
int main(){ 
    int n, q; 
    cin >> n >> q; 
    val.resize(n); 
    for(int i = 1; i <= n; i++) 
        cin >> val[i-1];  
    int a, b; 
    for(int i = 0;i < q; i++){  
        cin >> a >> b; 
        add[a] += 1; 
        add[b+1] -= 1; 
    }
    int buf = 0;  
    wy.resize(n); 
    for(int i = 1; i <= n; i++){ 
        buf += add[i]; 
        wy[i-1] = buf; 
    }
    sor(wy); 
    sor(val); 
    ll res = 0; ll aktu; 
    for(int i = 0; i < n; i++){ 
        aktu = wy[i]; aktu *= val[i]; 
        res += aktu; 
    } 
    cout << res; 
}