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
int val[MN]; 
int dp[MN];  
const int MOD = 1000000007;  
const int zakr = 1000009; 
vi dzielniki[zakr];  
bool done[zakr];  
int n; 
void build_dzielniki(int x){  
    if(done[x]) 
        return; 
    for(int i = 1; i*i < x; i++){ 
        if(x%i == 0){ 
            dzielniki[x].pb(i);  
            if(x/i <= n)
				dzielniki[x].pb(x/i); 
        }
    } 
    int pie = sqrt(x); 
    if(pie * pie == x && x%pie == 0) 
        dzielniki[x].pb(pie);  
    done[x] = 1; 
}
int main(){   
    dp[0] = 1; 
    cin >> n; 
    int x; 
    for(int i = 0; i < n; i++){ 
        cin >> x; 
        //for(int i = min(n, x); i > 0; i--){
        //     if(x%i == 0) 
        //        dp[i] = (dp[i] + dp[i-1])%MOD;  
        //}  
        build_dzielniki(x); 
        for(int j = sz(dzielniki[x])-1; j > -1; j--){  
            dp[dzielniki[x][j]] = (dp[dzielniki[x][j]] + dp[dzielniki[x][j]-1])%MOD; 
        }
    } 
    int sum = 0; 
    for(int i = 1; i <= n; i++){ 
        sum = (sum + dp[i])%MOD; 
    }  
    //cout << dp[1] << " " << dp[2] << "\n"; 
    cout << sum; 
}
