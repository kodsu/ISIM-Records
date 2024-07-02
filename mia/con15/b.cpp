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

int main(){ 
    cin >> A.st >> A.nd >> B.st >> B.nd >> C.st >> C.nd; 
    pll AB = {B.st - A.st, B.nd - A.nd}; 
    pll AC = {C.st - A.st, C.nd - A.nd}; 
    if(det(AB, AC) != 0){ 
        if(dist(A,B) == dist(B,C)) 
            cout << "Yes\n";  
        else 
            cout << "No\n"; 
        return 0; 
    } 
    if(A.st == C.st && A.nd == C.nd){ 
        cout << "Yes\n"; 
        return 0;
    } 
    cout << "No\n"; 
    return 0;  
}