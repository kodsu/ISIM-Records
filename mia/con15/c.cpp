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
ll det(pll W, pll V){ 
    return W.st *V.nd - W.nd * V.st; 
} 

ld dpl(pll G, pll A, pll B){ 
    pll V = {A.st - G.st, A.nd - G.nd}; 
    pll W = {B.st - G.st, B.nd - G.nd}; 
    ld d = dist(A, B);   
    d = sqrtl(d);  
    return (fabsl(det(V,W))/d); 
}

vll points; 
int main(){ 
    ld res = 0; 
    int n; cin >> n;  
    pll x; 
    for(int i = 0; i < n; i++){ 
        cin >> x.st >> x.nd; 
        points.pb(x); 
    } 
    res = dpl(points[1], points[0], points[2])/2; 
    for(int i= 1; i + 2 < sz(points); i++){ 
        res = min(res, dpl(points[i+1], points[i], points[i+2])/2); 
    } 
    res = min(res, dpl(points[0], points[sz(points)-1], points[1])/2);  
    res = min(res, dpl(points[sz(points)-1],points[0],  points[sz(points)-2])/2);
    cout << fixed << setprecision(20) << res; 
}