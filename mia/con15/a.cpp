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


ll dist(pll E, pll F){ 
    return (E.st - F.st)*(E.st-F.st)+(E.nd -F.nd)*(E.nd-F.nd); 
}
pll A, B, C; 
int main(){ 
    int n; cin >> n; 
    ll ares;  
    ld wyn; 
    for(int i = 0 ; i < n; i++){ 
        cin >> A.st >> A.nd; 
        cin >> B.st >> B.nd; 
        cin >> C.st >> C.nd; 
        ares = 0; 
        if(A.nd == B.nd && C.nd < B.nd)
            ares += dist(A, B); 
        if(A.nd == C.nd && B.nd < C.nd) 
            ares += dist(A, C); 
        if(B.nd == C.nd && A.nd < C.nd) 
            ares += dist(B,C); 
        wyn = ares; 
        wyn = sqrt(wyn); 
        cout << fixed << setprecision(15); 
        cout << wyn << "\n"; 
    }
}