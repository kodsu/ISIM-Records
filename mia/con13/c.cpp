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

const int K = 100;  
const int MN = 300009; 
ll dp[MN][K];  
ll wi[MN];  
int n;  
void build_dp(){ 
    for(int k = 1; k < K; k++){ 
        for(int i = n; i; i--){ 
            if(i + k > n) 
                dp[i][k] = wi[i]; 
            else 
                dp[i][k] = dp[i+k][k] + wi[i]; 
        }
    }
}
int main(){  
    cin >> n;     
    for(int i = 1; i <= n; i++) 
        cin >> wi[i] ;
    build_dp(); 
    int q; cin >> q; ll res = 0;  
    int a, b; 
    for(int i = 0; i < q; i++){ 
        cin >> a >> b; 
        if(b < K){ 
            cout << dp[a][b] << "\n"; 
            continue; 
        }  
        res = 0; 
        for(int k = a; k <= n; k+=b) 
            res += wi[k]; 
        cout << res << "\n"; 
    }
}