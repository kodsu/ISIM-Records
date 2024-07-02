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

const int MN = 200005, INF = (int)1e9 + (int)123;  
struct node{ 
    int maks1=-1, maks2=-2; 
};  
const int B = (1 << 18), MTS = 2 * B + 12; 
node tree[MTS]; 
vi wyst[MN]; // lista wystapien goscia(po kolei)
int bid[MN], guy[MN]; 
int lastpoz[MN];  
int n; 
 
void buildtree(){ 
    for(int i = 1; i <= n; i++){  
        if(sz(wyst[i]))
            tree[i+B].maks1 = lastpoz[i];  
        tree[i+B].maks2 =-2; 
    } 

    int l, r;  
    for(int i =  B-1; i; i--){ 
        l = (i <<1); r = l+1; 
        if(tree[l].maks1 >= tree[r].maks1){ 
            tree[i].maks1 = tree[l].maks1; 
            tree[i].maks2 = max(tree[l].maks2, tree[r].maks1); 
        } 
        else 
        { 
            tree[i].maks1 = tree[r].maks1; 
            tree[i].maks2 = max(tree[r].maks2, tree[l].maks1); 
        } 
    }
} 

void change(int pos, int val){// zmieniamy tylko maks1, reszta zadziala
    pos += B; 
    tree[pos].maks1 = val;  
    int i = pos >> 1, l, r; 
    while(i){ 
        l = (i << 1), r = l +1; 
        if(tree[l].maks1 >= tree[r].maks1){ 
            tree[i].maks1 = tree[l].maks1; 
            tree[i].maks2 = max(tree[l].maks2, tree[r].maks1); 
        } 
        else 
        { 
            tree[i].maks1 = tree[r].maks1; 
            tree[i].maks2 = max(tree[r].maks2, tree[l].maks1); 
        }  
        i >>= 1; 
    } 
} 
// w8, to nie jest zmartiwenie to znaczy te rzezczy nam zawsze dzialaja 

int licz = 0; 
pii maksonseg(int a, int b){  
    a += B; b += B; 
    pii res = {-INF, -INF-3}; 
    while(a < b){   
        if(a & 1){ 
            if(tree[a].maks1 >= res.st){
                res.nd = res.st;  
                res.st = tree[a].maks1; 
                if(tree[a].maks2 > res.nd) 
                    res.nd = tree[a].maks2; 
            } 
            else 
            { 
                if(tree[a].maks1 > res.nd) 
                    res.nd = tree[a].maks1; 
            }
            a++; 
        } 
        if(!(b&1)){ 
            if(tree[b].maks1 >= res.st){  
                res.nd = res.st; 
                res.st = tree[b].maks1; 
                if(tree[b].maks2 > res.nd) 
                    res.nd = tree[b].maks2; 
            } 
            else 
            { 
                if(tree[b].maks1 > res.nd) 
                    res.nd = tree[b].maks1; 
            }
            b--; 
        } 
        a>>=1; b>>=1; 
    } 
    if(a == b){ 
         if(tree[a].maks1 >= res.st){
                res.nd = res.st;  
                res.st = tree[a].maks1; 
                if(tree[a].maks2 > res.nd) 
                    res.nd = tree[a].maks2; 
            } 
            else 
            { 
                if(tree[a].maks1 > res.nd) 
                    res.nd = tree[a].maks1; 
            }
    }
    //cout << res.st << " " << res.nd << "\n"; 
    return res; 
}


int main(){  
    BOOST
    cin >> n; 
    for(int i = 1; i <= n; i++){ 
        cin >> guy[i] >> bid[i]; 
        lastpoz[guy[i]] = i;  
        wyst[guy[i]].pb(i); 
    } 
    //for(int i = 1; i <= 3; i++) 
    //    cout << lastpoz[i] << "  "; 
    //cout << "\n\n\n";   
    for(int i = 1; i <= n; i++) 
        if(!lastpoz[i]) 
            lastpoz[i] = -1; 
    buildtree();
    vi zapyt; int pom;  
    int q; cin >> q; int k;  
    pii maksy; int winner, sec;  
    int l, r, s; 
    for(int gg = 0; gg < q; gg++){ 
        while(!zapyt.empty()) 
            zapyt.pop_back(); 
        cin >> k;  
        for(int i = 0; i < k; i++){ 
            cin >> pom; 
            zapyt.pb(pom); 
        }
        for(auto x : zapyt){ 
            change(x, -1); 
        } 
        maksy = maksonseg(1, n);

        //cout << "#test " << gg << "\n"; 
        //cout << tree[1+B].maks1 << " " << tree[1+B].maks2 << "\n"; 
        //cout << wyst[winner][sz(wyst[winner])-1] << " " << lastpoz[sec] << " " << winner << " " << sec << endl; 
        //cout << maksy.st << " " << maksy.nd <<endl; 

        if(maksy.st <= 0 && maksy.nd <= 0){ 
            cout << 0  << " " << 0<<"\n"; 
            for(auto x : zapyt)
                change(x, lastpoz[x]);
            continue; 
        }  
        winner = guy[maksy.st];  
        if(maksy.nd > 0) 
            sec  = guy[maksy.nd]; 
        if(maksy.st >0 && maksy.nd < 0){  
            if(sz(wyst[winner]) == 0){ 
                cout << 0  << " " << 0<<"\n"; 
                for(auto x : zapyt)
                    change(x, lastpoz[x]);
                continue; 
            }
            cout << winner << " " << bid[wyst[winner][0]] << "\n"; 
            for(auto x : zapyt)
                change(x, lastpoz[x]);
            continue; 
        }  
        // tutaj jest prawdziwa czesc problemowa 
        // sec istnieje i ma sie dobrze, winner tez  
        //cout << "#test " << gg << "\n"; 
        //cout << wyst[winner][sz(wyst[winner])-1] << " " << lastpoz[sec] << " " << winner << " " << sec << endl; 
        //cout << maksy.st << " " << maksy.nd <<endl; 
        assert(wyst[winner][sz(wyst[winner])-1] > lastpoz[sec]); 
        assert(lastpoz[sec] == maksy.nd);  
        l = 0, r = sz(wyst[winner])-1;  
        while(l < r){ 
            // 00 .. 0111 
            s = (l + r)>>1; 
            if(wyst[winner][s] >= lastpoz[sec]) 
                r = s; 
            else 
                l = s+1; 
        } 
        cout << winner << " " << bid[wyst[winner][l]] << "\n"; 
        for(auto x : zapyt)
                 change(x, lastpoz[x]);
    }
}
