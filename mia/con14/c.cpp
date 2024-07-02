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

const int MN = 2009; 
ld dp[MN][MN]; 
int n, t; ld p; 
int main(){ 
   cin >> n >> p >> t;  
   for(int i = 0; i <= t+1; i++) 
      for(int j = 0; j <= n+1; j++)  
            dp[i][j]= 0; 
    
    dp[0][0] = 1; 
    for(int ti = 0; ti < t; ti++){ 
        for(int k = 0; k < n; k++){ 
            dp[ti+1][k] += (1-p)*dp[ti][k]; 
            dp[ti+1][k+1] += p * dp[ti][k]; 
        }
        dp[ti+1][n] += dp[ti][n]; 
    } 
    ld res = 0;  
    // cout << fixed << setprecision(3); 
    // for(int i = 0; i <= n; i++){ 
    //     cout << dp[t][i] << " ";  
    // } 
    //cout << "\n"; 
    for(int i = 1; i <= n; i++){ 
        res += dp[t][i] * i; 
    } 
    cout << fixed << setprecision(15); 
    cout << res << "\n"; 
}