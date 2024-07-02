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


int hs[30], ht[30]; 
bool Array(){ 
    for(int i = 0; i < 26; i++){ 
        if(hs[i] != ht[i]) 
            return 0; 
    } 
    return 1;
}  
string s, t; 
bool automation(){ 
    int wsk = 0; 
    for(int i = 0; i < sz(s); i++){ 
        if(s[i] == t[wsk]){ 
            wsk++; 
            if(wsk == sz(t)) 
                return 1; 
        }
    } 
    return 0; 
} 

bool both(){ 
    for(int i = 0; i < 26; i++){ 
        if(hs[i] < ht[i]) 
            return 0; 
    } 
    return 1;
}
int main(){ 
    cin >> s >> t; 
    for(int i= 0; i < 30; i++){ 
        hs[i] = 0; ht[i] = 0;
    } 
    for(int i = 0; i < sz(s); i++){ 
        hs[s[i]-'a']++; 
    } 
    for(int i = 0; i < sz(t); i++){ 
        ht[t[i] - 'a']++; 
    } 
    if(Array()){ 
        cout << "array"; 
        return 0; 
    } 
    if(automation()){ 
        cout << "automaton"; 
        return 0; 
    } 
    if(both()){ 
        cout << "both"; 
        return 0; 
    } 
    cout << "need tree"; 
}