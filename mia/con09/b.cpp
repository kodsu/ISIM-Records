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


const int MN = 100009; 
vi G[MN]; 
int deg[MN];  
int n, m; 

bool isbus = 0, isstar = 0, isring = 0; 
void bus(){ 
    int ile1 = 0, ile2 = 0; 
    for(int i = 1; i <= n; i++){ 
        if(deg[i] == 1) 
            ile1++; 
        if(deg[i] == 2) 
            ile2++;
    } 
    if(n-1 == m && ile1 == 2 && ile2 == n-2) 
        isbus = 1; 
} 

void star(){ 
    int ileyo = 0; 
    int ile1 = 0; 
    for(int i = 1; i <= n; i++){ 
        if(deg[i] == n-1){ 
            ileyo++; 
        } 
        if(deg[i] == 1) 
            ile1++; 
    } 
    if(n-1 == m && ileyo == 1 && ile1 == n-1) 
        isstar = 1; 
}

void ring(){ 
    int ile2 = 0; 
    for(int i = 1; i <= n; i++){ 
        if(deg[i] == 2) 
            ile2++; 
    } 
    if(m == n && ile2 == n) 
        isring = 1;  
    //cout << ile2 << "\n"; 
} 

int main(){ 
    cin >> n >>m ; 
    int a, b;  
    //cout << n << " " << m; 
    for(int i = 0; i < m; i++){ 
        cin >> a >> b; 
        deg[a]++; 
        deg[b]++; 
        G[a].pb(b); 
        G[b].pb(a); 
    } 
    bus(); 
    star(); 
    ring();  
    int war = 0; 
    if(isbus) war++; 
    if(isstar)war++; 
    if(isring)war++;  
    if(war > 1){ 
        cout << "unknown topology\n";  
        return 0; 
    } 
    if(war == 1){ 
        if(isbus){ 
            cout << "bus topology\n"; 
            return 0; 
        } 
        if(isring){ 
            cout << "ring topology\n"; 
            return 0; 
        } 
        if(isstar){ 
            cout << "star topology\n"; 
            return 0;     
        }
    } 
    cout << "unknown topology\n"; 
    return 0; 
}