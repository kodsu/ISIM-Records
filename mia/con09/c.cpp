#include<bits/stdc++.h>

#define st first
#define nd second
#define pb push_back
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


int n, m; 
const int MN = 52; 
vii G[MN];  
int deg[MN];  
int kolor[MN*MN]; 
bool vis[MN]; 
int ile = 0; 
void dfs(int x){ 
    vis[x] = 1;  
    ile++; 
    for(auto v: G[x]){ 
        if(!vis[v.st]){ 
            dfs(v.st); 
        }
    }
} 
int sign[MN]; int cur; 

void dfs2(int v){ 
    sign[v] = cur; 
    for(auto x : G[v]){ 
        if(!sign[x.st]){ 
            dfs2(x.st); 
        }
    }
}

int ziom[MN]; 
void run(){ 
    set<pair<int, int> > S; 
    cin >> n >> m;  
    for(int i = 0; i < m+2; i++) 
        kolor[i] = 0;  
    for(int i = 0; i <= n; i++) 
        deg[i] = 0;  
    for(int i = 0; i <= n; i++) 
        vis[i] = 0; 
     for(int i = 1; i<= n; i++){ 
        G[i].clear();   
        sign[i] = 0; 
        ziom[i] = 0; 
    } 
    int a, b;  
    vii kraw;  
    for(int i  =1; i <= m; i++){ 
        cin >> a >> b;  
        kraw.pb({a,b}); 
        deg[a]++; 
        deg[b]++; 
        G[a].pb({b, i}); 
        G[b].pb({a,i}); 
    } 
    int mistrz = 0; 
    for(int i = 1; i <= n; i++){ 
        if(deg[i] != n-1){ 
            mistrz = i; 
            break; 
        }
    } 
    if(!mistrz){  
        mistrz = 1; 
        // do poprawki 
        vis[mistrz] = 1; ile = 0; 
        dfs(1); 
            // trzy kolory; 
            int k = 3; //cout << k << "\n"; 
            int ind = 0; 
            for(auto x : G[mistrz]){  
                ind++; 
                if(ind%2){ 
                    kolor[x.nd] = 1;
                    ziom[x.st] = 1;  
                } 
                else{ 
                    kolor[x.nd] = 2;  
                    ziom[x.st] = 2;
                } 
            }
            ind = 1; 
            for(auto x : kraw){  
                if(x.st == mistrz || x.nd == mistrz){ 
                    kolor[ind++] = ziom[x.st + x.nd - mistrz]; 
                } 
                else 
                    kolor[ind++] = 3; 
            }
            cout << k << "\n";  
            for(int i = 1; i <= m; i++) 
                cout << kolor[i] << " "; 
            cout << "\n";  
            return; 
    } 

    int ind = 1; 
    for(auto x : kraw){ 
        if(x.st == mistrz || x.nd == mistrz) 
            kolor[ind++] = 1; 
        else 
            kolor[ind++] = 2; 
    }
    cout << 2 << "\n"; 
    for(int i = 1; i <= m; i++)  
        cout << kolor[i] << " "; 
    cout << "\n";  
    return; 
}
int main(){ 
    int t; cin >> t; 
    while(t--){ 
        run(); 
    }
}