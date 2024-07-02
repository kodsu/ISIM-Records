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

int n, m; 
struct event{ 
    int a, b, id, typ; 
}; 
const int MN = 200005, ME = 2 * MN; 
event E[MN]; 

bool cmp(event A, event B){ 
    if(A.a != B.a) 
        return (A.a < B.a); 
    if(A.b != B.b) 
        return (A.b < B.b); 
    if(A.typ != B.typ) 
        return (A.typ < B.typ); 
    return (A.id < B.id); 
} 
// typ 1 - polaczenie 
// typ 0- most do dodania
pii cor[MN]; 
int len[MN];  
int wziety[MN];  
int zrobiony[MN];
stack <int> ms; 
int main(){ 
    int n, m; cin >> n >> m; 
    for(int i = 0; i < n; i++){ 
        cin >> cor[i].st >> cor[i].nd; 
    } 
    for(int i = 0; i < m; i++) 
        cin >> len[i]; 
    int id = 0; 
    for(int i = 0; i < n-1; i++){ 
        E[id].a = cor[i+1].st - cor[i].nd; 
        E[id].b = cor[i+1].nd - cor[i].st; 
        E[id].id = i; 
        E[id].typ = 1; 
        id++; 
    } 
    for(int i = 0; i < m; i++){ 
       // E[id].a = len[i]; 
        E[id].b = len[i]; 
        E[id].id = i+1; 
        E[id].typ = 0;  
        id++; 
    } 
    sort(E, E+id, cmp);  
    for(int i = 0; i < id; i++){ 
        if(E[i].typ == 1){ 
            if(ms.empty()){ 
                cout << "No"; 
                return 0; 
            }
            wziety[E[i].id] = ms.top(); 
            ms.pop(); 
        } 
        else 
            ms.push(E[i].id); 
    } 
    cout << "Yes\n"; 
    for(int i = 0; i < n-1; i++) 
        cout << wziety[i] << " "; 
}