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

const int MN = 1000009; 

bool sito[MN]; 
void build_sito(){ 
    sito[0]=sito[1] = 1;  
    for(int i = 2; i <= MN; i++){ 
        if(!sito[i]){ 
            for(int j = 2*i; j <= MN; j+=i) 
                sito[j] = 1; 
        }
    }
}

int main(){ 
    build_sito(); 
    int n; cin >> n;  
    ll pie;  
    ll val; 
    for(int i = 0; i < n; i++){ 
        cin >> val; pie = sqrt(val);  
        if(pie * pie == val){ 
            if(!sito[pie]) 
                cout << "YES\n"; 
            else 
                cout << "NO\n"; 
        } 
        else 
            cout << "NO\n"; 
    }
}