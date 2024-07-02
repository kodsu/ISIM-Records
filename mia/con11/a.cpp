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
    string s; int n; cin >>n; 
    cin >> s;   
    set<char> S; 
    if(n == 1){ 
        cout << s << s << "\n"; 
        return; 
    }
    s += (char)('a'-1);  
    int i=0;  
    if(n >= 2 && s[0] == s[1]){ 
        i = 0;  
        for(int j = 0; j <= i;j++) 
            cout << s[j]; 
        for(int j = i; j >= 0; j--) 
            cout << s[j]; 
        cout << "\n";
        return; 
    }
    for(int ki; i < n-1;i++){ 
        if(s[i] < s[i+1]) 
            break; 
    } 
    for(int j = 0; j <= i;j++) 
        cout << s[j]; 
    for(int j = i; j >= 0; j--) 
        cout << s[j]; 
    cout << "\n";
}

int main(){ 
    int t; cin >> t; 
    while(t--){ 
        solve(); 
    }
}