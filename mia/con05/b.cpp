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

const int MN = 100005;

int val[MN]; 
ll aktuval[MN]; 
ll n, S; 
ll aktuwyn; 
bool dasie(ll k){  
    if(k == 0) {aktuwyn = 0; return 1;} 
    aktuwyn = 0; 
    for(ll i = 0; i < n; i++){ 
        aktuval[i] = (i+1)*k + val[i]; 
    } 
    sort(aktuval, aktuval+n); 
    ll sum = 0; 
    for(int i =0; i < k;i++) 
        sum += aktuval[i]; 
    aktuwyn = sum; 
    if(sum <= S) 
        return 1; 
    return 0; 
}
int main(){ 
    BOOST
    cin >> n >> S; 
    for(int i = 0; i < n; i++) 
        cin >> val[i];  
    int l = 0, r = n, s; 
    while(l < r){ 
        s = (l + r + 1) >> 1; 
        if(dasie(s)) 
            l = s ;
        else 
            r = s-1; 
    } 
    dasie(l); 
    cout << l << " " << aktuwyn; 
}