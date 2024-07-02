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

vll A, B;

const int MN = 500009;  
int P[4*MN];  
void kmp_run(){
    vl s;    
    int wyn = 0;
    for(int i = 1; i < sz(B)- 1; i++){ 
        s.pb(B[i].st*100 + B[i].nd); 
    }  
    s.pb(-1); 
    for(auto x: A) 
        s.pb(x.st * 100 + x.nd); 
    P[0] = P[1] = 0; int pref; 
    for(int i = 2; i < sz(s); i++){ 
        pref = P[i-1]; 
        while(pref > 0 && s[i] != s[pref+1]) 
            pref = P[pref]; 
        if(s[i] == s[pref+1]) 
            pref++; 
        P[i] = pref; 
    }  
    int len = sz(B)-2; 
    for(int i = len+2; i < sz(s); i++){
        if(P[i] == len){
            // tutaj wyifować czy skrajne krotności się zgadzają 
            
        } 
    }
    cout << wyn; 
}

void case1(){ 
    int res = 0; 
    for(auto x : A){
        if(x.nd == B[0].nd && x.st >= B[0].st){
            // tutaj nie ++ tylko coś więcej w zależności od x.st   
            res++;  
        }
    } 
    cout << res; 
    return; 
} 

void case2(){ 
    int res = 0; 
    for(int i = 0; i < sz(A)-1; i++){ 
        if(A[i].nd == B[0].nd && A[i+1].nd == B[1].nd && A[i].st >= B[0].st && A[i+1].st >= B[i+1].st) 
            res++; 
    } 
    cout << res; 
    return; 
}
 
int main(){ 
    int n, m;  
    cin >> n >> m;  
    int liczba; string xd;  
    for(int i = 0; i < n; i++){  
        cin >> liczba >> xd; 
        if(!i){ 
            A.pb({liczba, xd[1]}); 
        } 
        else 
        { 
            if(A.back().nd == xd[1]) 
                A.back().st += liczba; 
            else 
                A.pb({liczba, xd[1]}); 
        }
    }
     for(int i = 0; i < m; i++){  
        cin >> liczba >> xd; 
        if(!i){ 
            B.pb({liczba, xd[1]}); 
        } 
        else 
        { 
            if(B.back().nd == xd[1]) 
                B.back().st += liczba; 
            else 
                B.pb({liczba, xd[1]}); 
        }
    } 
    if(sz(B) <= 2){ 
        // tutaj na pale lecimy sobie 
        if(sz(B) == 1){ 
            case1(); 
            return 0; 
        } 
        if(sz(B) == 2){ 
            case2(); 
            return 0; 
        }
    }
}