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


int nast[5000]; 

int main(){ 
    int n; cin >> n; 
    for(int i = 1; i<= n; i++) 
        cin >> nast[i];  
    int b, c; bool found = 0; 
    for(int i = 1; i <= n; i++){ 
        b = nast[i]; 
        c = nast[b]; 
        if(i == nast[c]){ 
            found = 1; 
            cout << "YES\n"; 
            return 0; 
        }
    } 
    if(!found){ 
        cout << "NO\n"; 
    }
}