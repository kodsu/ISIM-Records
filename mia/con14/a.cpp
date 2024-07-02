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

int pos[12][30]= {}; 
int K = 15; 
int main(){ 
    pos[0][K] = 1; 
    string wla; 
    string xd;  
    cin >> wla >> xd; 
    int gpos = K; 
    for(auto x : wla){ 
        if(x == '+') 
            gpos++; 
        else 
            gpos--; 
    }
    char dir; int diff; 
    for(int p = 0; p < sz(xd); p++){ 
        if(xd[p] == '+') 
            diff = 1;  
        if(xd[p] == '-') 
            diff = -1; 
        if(xd[p] == '?') 
            diff = 0; 
        if(diff != 0){ 
            for(int k = 0; k < 30; k++){ 
                if(k+diff>=0 && k+diff < 30) 
                    pos[p+1][k+diff] += pos[p][k] ; 
            }
        }
        else{ 
            for(int k = 1; k < 29; k++){ 
                if(pos[p][k]){
                    pos[p+1][k+1] += pos[p][k]; 
                    pos[p+1][k-1] += pos[p][k]; 
                }
            }
        }
    }
    ld dziel = 0; ld good; 
    good = pos[sz(xd)][gpos]; 
    for(int i = 0; i < 30; i++) 
        dziel += pos[sz(xd)][i]; 
    for(int i = 0; i < 30; i++){ 
        //cout << i << " " << pos[sz(xd)][i] << "\n"; 
    } 
    //cout << gpos << "\n"; 
    cout << fixed << setprecision(10); 
    cout << good/dziel; // << " " << dziel;  
}