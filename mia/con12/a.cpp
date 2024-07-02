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

void solve(){ 
    int a, b,c; 
    cin >> a >> b >> c; 
    int fir = c/2 + c%2 + a; 
    int sec = c/2 + b; 
    if(fir > sec) 
        cout << "First\n"; 
    else 
        cout << "Second\n"; 
}

int main(){ 
    int t; cin >> t; 
    while(t--){ 
        solve(); 
    }
}