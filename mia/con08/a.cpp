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
    string s;
    cin >> s; 
    ll res = 0; 
    if(s[0] == '0' || s[0] == '4' || s[0] == '8') 
        res = 1; 
    ll bylo = 1;  
    int val; 
    for(int i = 0; i < sz(s)-1; i++){ 
        val = 10 * ((int)s[i]-'0') + s[i+1]-'0'; 
        if(val % 4 == 0) 
            res += bylo;  
        val = s[i+1] - '0'; 
        if(val%4 == 0) 
            res++; 
        bylo++; 
    }  
    cout << res; 
}