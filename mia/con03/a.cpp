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

const int MN = 505; 
ll id[MN];  
ll valid[MN]; 
ll G[MN][MN];  
ll n;  
ll d[MN][MN];  
ll ans[MN]; 
int main(){   
    cin >> n;  
    for(int i = 1; i <= n; i++){ 
        for(int j = 1; j <= n; j++) 
            cin >> G[i][j]; 
    } 
    for(int i = n; i >= 1; i--){ 
        cin >> id[i]; 
        valid[i] = id[i]; 
    }  
    // for(int i = 1; i <= n; i++) 
    //     cout << valid[i] << " "; 
    // cout << "\n"; 
    for(int i = 1; i <= n; i++){ 
        for(int j = 1; j <= n; j++) 
            d[i][j] = G[id[i]][id[j]]; 
    }   
    // cout << "\n"; 
    // for(int i = 1; i <= n; i++){ 
    //     for(int j = 1; j <= n; j++) 
    //         cout << d[i][j] << " "; 
    //     cout << "\n"; 
    // } 
    // cout << "\n"; 
    int k;  
    ll sum;  
    ans[n] = 0; 
    for(int k = 2; k<= n; k++){ 
        sum = 0; 
        for(int i =1; i <= k; i++){
            for(int j = 1; j <= k; j++){
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
            } 
        } 
        for(int i = 1; i <= k; i++){ 
            //relaksujemy k 
            for(int j = 1; j <= k; j++){ 
                d[j][k] = min(d[j][i] + d[i][k], d[j][k]); 
                d[k][j] = min(d[k][j], d[k][i]+d[i][j]);
            }
        }
        for(int i =1; i <= k; i++){
            for(int j = 1; j <= k; j++){
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
            } 
        } 
        for(int i = 1; i <= k; i++){ 
            //relaksujemy k 
            for(int j = 1; j <= k; j++){ 
                d[j][k] = min(d[j][i] + d[i][k], d[j][k]); 
                d[k][j] = min(d[k][j], d[k][i]+d[i][j]);
            }
        }    

        // for(int i = 1; i <= k; i++){ 
        //     for(int j = 1; j <= k; j++){ 
        //         d[i][j] = G[id[i]][id[j]]; 
        //     }
        // }
        // for(int l = k; l >= 1; l--){ 
        //     for(int i = 1; i <= k; i++){ 
        //         for(int j = 1; j <= k; j++)
        //             d[i][j] = min(d[i][j], d[i][l]+d[l][j]); 
        //     }
        // }
        for(int i = 1; i <= k; i++){ 
            for(int j = 1; j <= k; j++){
                sum += d[i][j];   
                if(i == j){ 
                    assert(d[i][j] == 0); 
                }
                //cout << d[i][j] << " "; 
            } 
            //cout << "\n"; 
        } 
        //cout << "\n\n"; 
        ans[n-k+1] = sum; 
    } 
    for(int i = 1; i <= n; i++) 
        cout << ans[i] << " "; 
}

