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


const int ML = 500009; 
string s, t; 
int pref[ML]; 
int lps[ML*2]; 
void computeLPSArray()
{
    int len = 0;
    int M = sz(t); 
    string pat = t; 
    lps[0] = 0; // lps[0] is always 0
 
    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (len != 0) {
                len = lps[len - 1];
 
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    } 
    // for(int i = 0; i < M; i++) 
    //     cout << lps[i] << " ";
}



int main(){ 
    cin >> s >> t;   
     if(sz(s) < sz(t)){ 
        cout << s; 
        return 0; 
    }
    computeLPSArray();   
    int s1 = 0, s0 = 0;  
    for(int i = 0; i < sz(s); i++){ 
        if(s[i] == '0') 
            s0++; 
        else 
            s1++; 
    }
    int split = lps[sz(t)-1]; 
    string pref; 
    pref.resize(split); 
    string suf; 
    suf.resize(sz(t) - split);  
    for(int i = 0; i < split; i++) 
        pref[i] = t[i]; 
    for(int i = split; i < sz(t); i++) 
        suf[i-split] = t[i]; 
    //cout << split << " " << pref << " " << suf << "\n"; 

    int prefamo[2] = {0,0}; 
    int sufamo[2] = {0,0}; 
    for(auto x : pref){ 
        if(x == '0') 
            prefamo[0]++; 
        else 
            prefamo[1]++; 
    } 
    for(auto x : suf){ 
        if(x == '0') 
            sufamo[0]++; 
        else 
            sufamo[1]++; 
    }  

    if(prefamo[0] > s0 || prefamo[1] > s1){ 
        cout << s; 
        return 0; 
    }  
    cout << pref; 
    s0 -= prefamo[0]; 
    s1 -= prefamo[1]; 
    while(s1 >= sufamo[1] && s0 >= sufamo[0]){ 
        s1 -= sufamo[1]; s0 -= sufamo[0]; 
        cout << suf; 
    } 
    for(int i = 0; i < s0; i++) 
        cout << '0'; 
    for(int i = 0; i < s1; i++) 
        cout << '1'; 
}