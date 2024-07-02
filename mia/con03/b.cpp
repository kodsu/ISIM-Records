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
const int INF = (int)1e9 + (int)123; 
int dp[10000]; 
unordered_map<int, int> M; //da sie  i w maksymalnie ilu; 
int main(){   
    int n; int t[3]; 
    cin >> n >> t[0] >> t[1] >> t[2];  
    for(int i = 0; i < 10000; i++) 
        dp[i] = 0; 
    for(int i = 0; i < 3; i++){ 
        for(int j = 0; j <= n; j++){
            if(dp[j] || j == 0) 
            dp[j+t[i]] = max(dp[j+t[i]], dp[j] + 1);  
        }
    } 
    cout << dp[n]; 
}

