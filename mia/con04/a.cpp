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

const int MN = 205; 
int ans[205]; 
int per[205]; 
int ukl[205];  
int nukl[205]; 
int n; 
void run(){ 
    cin >> n; 
    for(int i = 0; i < MN; i++)     
        ans[i] = 0; 
    for(int i = 1; i <= n; i++){ 
        cin >> per[i];  
        ukl[i] = i; 
    } 
    for(int i = 1; i <= n+3; i++){ 
        for(int j = 1; j <= n; j++){ 
            nukl[per[j]] = ukl[j];  
        } 
        for(int j = 1; j <= n; j++){ 
            ukl[j] = nukl[j]; 
            if(ukl[j] == j && !ans[j]) 
                ans[j] = i; 
        }
    } 
    for(int i = 1; i<= n; i++) 
        cout << ans[i] << " "; 
    cout << "\n"; 
}

int main(){  
    BOOST
    int q; cin >> q; 
    for(int i = 0; i < q; i++){ 
        run(); 
    }
}