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

const int MN = 100009; 
vi G[MN]; 
ld dp[MN]; 
bool vis[MN]; 

void dfs(int v){ 
    dp[v] = 0;  
    vis[v] = 1; 
    int licz = 0; 
    for(auto x : G[v]){ 
        if(!vis[x]){ 
            dfs(x); 
            licz++; 
            dp[v] += dp[x] + 1; 
        }
    }  
    if(licz)
        dp[v] /= licz; 
}
int main(){ 
    int n; 
    cin >> n; int a,b; 
    for(int i = 1; i < n; i++){ 
        cin >> a >> b; 
        G[a].pb(b); 
        G[b].pb(a); 
    }  
    dfs(1); 
    cout << fixed << setprecision(15); 
    cout << dp[1] << "\n"; 
}