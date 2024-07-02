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
const int B = (1 << 17), MTS = 2 * B + 12; 

pair<pii, int> queries[MN]; 
int n; 
unordered_set<int> values; set<int> time_values; 
vector<int> id_val;  
unordered_map<int, int> conv;   
unordered_map<int,int> time_conv; 
vector<pii> Q[MN];  
vector<int> Qid[MN];  
int ans[MN]; 

void read(){ 
    cin >> n;  
    values.reserve(n); 
    for(int i = 0; i < n; i++){ 
        cin >> queries[i].st.st >> queries[i].st.nd >> queries[i].nd; 
        values.insert(queries[i].nd);  
        time_values.insert(queries[i].st.nd); 
    }
    int id = 0; 
    time_conv.reserve(sz(time_values)); 
    for(auto x: time_values){ 
        time_conv[x] = id++; 
    }

    for(auto x : values) 
        id_val.pb(x); 
    conv.reserve(sz(values)); 
    id = 0; 
    for(auto x : values) 
        conv[x] = id++; 
    pii buf; 
    for(int i = 0 ; i < n; i++){ 
        buf = queries[i].st;
        buf.nd = time_conv[buf.nd]; 
        Q[conv[queries[i].nd]].pb(buf);  
        Qid[conv[queries[i].nd]].pb(i); 
    } 
    for(int i = 0; i < n; i++) 
        ans[i] = -1; 
} 

int tree[MTS]; 

int sum_on_seg(int a, int b){ 
    a += B; b += B; int res = 0; 
    while(a < b){ 
        if(a & 1) res+= tree[a++];
        if(!(b&1)) res += tree[b--]; 
        a >>= 1; b >>= 1; 
    } 
    if(a == b) 
        res += tree[a]; 
    return res; 
}

void add_in_point(int pos, int val){ 
    pos += B; 
    while(pos){ 
        tree[pos] += val; 
        pos >>=1 ; 
    } 
    return; 
}

void zeruj(int pos){ 
    pos += B; 
    while(pos){ 
        tree[pos] = 0;
        pos >>=1;  
    } 
    return; 
}

void run_val(int x){ 
    if(sz(Q[x]) == 0) 
        return;
    vi czysc; 
    for(int i = 0; i < sz(Q[x]); i++){ 
        if(Q[x][i].st == 1){ // dodaj
            add_in_point(Q[x][i].nd, 1); 
            czysc.pb(Q[x][i].nd); 
        } 
        if(Q[x][i].st == 2){ // odejmij
            add_in_point(Q[x][i].nd, -1);  
            czysc.pb(Q[x][i].nd); 
        } 
        if(Q[x][i].st == 3){ // odpowiedz
            ans[Qid[x][i]] = sum_on_seg(0, Q[x][i].nd); 
        }
    } 
    for(auto y: czysc)
        zeruj(y); 
}

int main(){  
    read();
    for(int i = 0; i < n; i++) 
        run_val(i); 
    for(int i = 0; i < n; i++){ 
        if(ans[i] != -1) 
            cout << ans[i] << "\n"; 
    }  
    return 0; 
}