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

const int MN = 200009; 
int n; 
int G[MN]; 
int NG[MN]; 
vi pointers[MN];  
bool vis[MN];  
int degin[MN]; 

void dfstree(int v){ 
    vis[v] = 1; 
    for(auto x : pointers[v]){
        if(!vis[x])
            dfstree(x); 
    } 
}  
int found = 0; 
int pushed[MN]; 
void cykdfs(int v, int prev = -1){  
    pushed[v] = 1; 
    vis[v] = 1;  
   // pointers[v].pb(G[v]); 
    for(auto x : pointers[v]){  
        if(pushed[x] && x != prev)
            found = x; 
        if(!vis[x]) 
            cykdfs(x, v); 
    } 
    pushed[v] = 0; 
}
vi trerep;  
vi cyrep; 

int main(){ 
    cin >> n; 
    for(int i = 1; i <= n; i++){  
        cin >> G[i];  
        degin[G[i]]++;   
        if(G[i] != i)
            pointers[G[i]].pb(i);   
        if(G[i] != i) 
            pointers[i].pb(G[i]); 
        NG[i] = G[i]; 
    }  
  //  cout << "ojoj" << endl; 
    int d = 0, c = 0; 
    for(int i = 1; i <= n; i++){ 
        if(G[i] == i){ 
            d++; 
            trerep.pb(i);
            dfstree(i); 
        }
    }   
    //  for(auto x : trerep) 
    //     cout << x << " " ; 
    // cout << "\n"; 
   // cout << "hehe" << endl; 
    int x; 
    for(int i = 1; i <= n; i++){ 
        if(!vis[i]){  
            found = 0; 
            cykdfs(i);  
            //assert(found != 0); 
            if(found == 0) 
                found = i ; 
            c++;  
            cyrep.pb(found); 
        }
    }  
   // cout << "hehe2" << endl;  
    if(d >= 2){ 
        cout << d-1 + c << "\n"; 
    } 
    else 
        cout << c << "\n"; 
    for(int i = 1; i < trerep.size(); i++){ 
        NG[trerep[i]] = trerep[0]; 
    }
    if(sz(cyrep)> 0){ 
        //NG[cyrep[0]] = cyrep[0]; 
        for(auto y : cyrep){
            if(sz(trerep))
                NG[y] = trerep[0];  
            else 
                NG[y] = cyrep[0]; 
        }
    }  
   
    // for(auto x : cyrep) 
    //     cout << x << " " ; 
    //cout << "\n"; 
    for(int i = 1; i <= n; i++) 
        cout << NG[i] << " "; 
}
