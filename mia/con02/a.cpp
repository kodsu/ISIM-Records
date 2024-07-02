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
	int n, a, b; 
    cin >> n >> a >> b; 
    string s; cin >> s; 
    vi values; int aktu = 0; 
    for(int i = 0;i < sz(s); i++){ 
        if(s[i] == '.') 
            aktu++; 
        else {
            if(aktu){ 
                values.pb(aktu); 
                aktu = 0; 
            }
        }
    }
    if(aktu) 
        values.pb(aktu); 
    int wyn = 0; 
    if(a > b) 
        swap(a,b); 
    for(auto x : values){ 
        if(a > x/2){ 
            a -= x/2; 
            wyn += x/2; 
        }
        else 
        { 
            wyn += a; 
            a = 0 ;
        } 
        if(b > (x+1)/2){ 
            b -= (x+1)/2; 
            wyn += (x+1)/2; 
        } 
        else 
        { 
            wyn += b; 
            b = 0; 
        }
        if(a > b) 
            swap(a,b); 
    } 
    cout << wyn << "\n"; 
} 

