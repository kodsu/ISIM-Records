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

int main(){ 
	ll n, x, y; 
    cin >> n >> x >> y; 
    string s; cin >> s; 
    vi values; int aktu = 0; 
    for(int i = 0;i < sz(s); i++){ 
        if(s[i] == '0') 
            aktu++; 
        if(s[i] == '1') {
            if(aktu!= 0){ 
                values.pb(aktu); 
                aktu = 0; 
            }
        }
    } 
    if(aktu != 0) 
        values.pb(aktu);  

    if(sz(values) == 0){ 
        cout << 0; 
        return 0; 
    }  
    // cout << sz(values) << "\n";  
    // for(auto x : values) 
    //     cout << x << " " ; 
    // cout << "\n"; 
    ll ile = values.size(); 
    cout << y + min(x,y)*(ile-1); 
} 

