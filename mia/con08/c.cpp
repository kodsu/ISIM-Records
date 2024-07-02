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


string s; 
const int MK = 504;
int dp[MK]; 
int n, m, k; 
int pref[MK];  
int zysk[MK];  
int czas = 0; 
void process(){ 
    pref[0] = 0; 
    cin >> s; 
    int lf = 0, pf = 0; 
    for(int i = 0; i < m; i++){ 
        if(s[i] == '1') 
            pref[i+1] = pref[i] +1; 
        else 
            pref[i+1] = pref[i]; 
    }  
    pref[m+1] = pref[m]; 
    int dodczas = m;  
    for(int i = 0; i < m; i++){ 
        if(s[i] == '0'){
            dodczas--;  
            lf++; 
        }
        else 
            break; 
    } 
    if(dodczas == 0){ 
        return; 
    }
    if(dodczas != 0){ 
        for(int i = m-1; i> -1; i--){ 
            if(s[i] == '0'){ 
                dodczas--;  
                pf++; 
            }
            else 
                break; 
        } 
    } 
    czas += dodczas; 
    for(int i = 0; i < m+1; i++){ 
        zysk[i] = 0;
    } 
    int koszt; 
    for(int l = 0; l <= m; l++){ 
        for(int r = l+1; r <= m+1; r++){ 
            koszt = pref[l] + pref[m] - pref[r-1]; 
            zysk[koszt] = max(zysk[koszt], l + m-r+1-lf-pf); 
        }
    }
    // for(int i = 0; i <= m; i++){ 
    //     cout << zysk[i] << " "; 
    // }      cout << "\n"; 

    for(int i = k; i >= 0; i--){  
        for(int j = 1; j <= m; j++){ 
            if(i - j < 0) 
                break;  
            dp[i] = max(dp[i], dp[i-j] + zysk[j]); 
        }
        //dp[i+j] = max(dp[i+j], dp[i]+ zysk[j]); 
    }
}
int main(){  
    cin >> n >> m >> k; 
    for(int i = 0; i <n; i++){ 
        process(); 
    } 
    //cout << czas << " " << dp[k] << "\n"; 
    cout << max(czas - dp[k], 0); 
}