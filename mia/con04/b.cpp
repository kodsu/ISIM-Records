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
ll curlen[MN]; 

int main(){  
    BOOST
    ll n , m , l;  
    cin >> n >> m >> l; 
    for(int i = 1;i  <= n; i++) 
        cin >> curlen[i]; 
    int aktuwyn = 0; 
    bool roz = 0; 
    for(int i = 1; i <= n; i++ ){ 
        if(!roz){ 
            if(curlen[i] > l){ 
                roz = 1; 
                aktuwyn++; 
            }
        }
        else 
        { 
            if(curlen[i] <= l){ 
                roz= 0; 
            }
        }
    } 
    int typ;  
    int pos; ll d; 
    for(int k = 0; k < m; k++){ 
        cin >> typ; 
        if(typ ==0){ 
            cout << aktuwyn << "\n"; 
        } 
        if(typ == 1){ 
            cin >> pos >> d; 
            if(curlen[pos] > l){
                curlen[pos]+=d; 
                continue;   
            }
            if(curlen[pos] + d <= l){
                curlen[pos]+=d;  
                continue;  
            } 
            curlen[pos]+=d; 
            if(pos == 1){ 
                if(curlen[2] <= l) 
                    aktuwyn++;  
                continue;
            } 
            if(pos == n){ 
                if(curlen[n-1] <= l) 
                    aktuwyn++;  
                continue;
            } 
            if(curlen[pos-1] > l && curlen[pos+1] > l){
                aktuwyn--;  
                continue; 
            } 
            if(curlen[pos-1] <= l && curlen[pos+1] <= l){
                aktuwyn++;
                continue; 
            }  
            // wiekszy, mniejszy, aktuwyn = aktuwyn; 
        }
    }
}