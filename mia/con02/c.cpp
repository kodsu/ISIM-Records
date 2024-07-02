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

char big[3]; 
char lit[29];  
bool used[200] = {0}; 
int main(){ 
	int n, p; cin >> n >> p;  
    string org; cin >> org;  

    if(p == 1){ 
        cout << "NO"; 
        return 0; 
    }

    if(p == 2){  
        if(n == 2){ 
            if(org == "ab"){ 
                cout << "ba"; 
                return 0; 
            } 
            if(org == "ba"){ 
                cout << "NO"; 
                return 0; 
            } 
        } 
        if(n == 1){ 
            if(org == "a"){ 
                cout << "b"; 
                return 0;
            } 
            if(org == "b"){ 
                cout << "NO"; 
                return 0; 
            }
        }
    }
    // liczymy najwiekszy mozliwy string 
    // zachodzi p>= 3
    for(int i = 0; i < 26; i++) 
        lit[i] = (char)('a' + i); 
    for(int i = 0; i < 3; i++){ 
        big[i] = lit[p-1-i]; 
        //cout << big[i] << " "; 
    }
    string najw; najw.resize(n); 
    for(int i = 0; i < n; i++){ 
        najw[i] = big[i%3]; 
    } 
    //cout << najw << "\n"; 
    if(najw == org){ 
        cout << "NO"; 
        return 0; 
    }
    string nowy = org;   
    int ind; int lim = 'a' + p;  
    bool found = 0; 
    for(int s = n-1; s > -1; s--){ 
        if(s -1 >= 0)
            used[org[s-1]] = 1; 
        if(s-2 >= 0)
            used[org[s-2]] = 1;  
        ind = 0; 
        for(int i = org[s]+1; i < lim; i++ ) 
            if(!used[i]){ 
                ind = i; 
                break; 
            }
        if(s -1 >= 0)
            used[org[s-1]] = 0; 
        if(s-2 >= 0)
            used[org[s-2]] = 0;
        if(!ind) 
            continue;  
        found = 1; 
        nowy[s] = char(ind); 
        for(int ss = s+1; ss < n; ss++){ 
            if(ss -1 >= 0)
                used[nowy[ss-1]] = 1; 
            if(ss-2 >= 0)
                used[nowy[ss-2]] = 1;  
            ind = 0; 
            for(int i = 'a'; i < lim; i++ ) 
                if(!used[i]){
                    ind = i;
                    break; 
                }
            nowy[ss] = char(ind); 
            if(ss -1 >= 0)
                used[nowy[ss-1]] = 0; 
            if(ss-2 >= 0)
                used[nowy[ss-2]] = 0;
        }   
        break; 
    } 
    //cout << found << "\n"; 
    cout << nowy; 
} 

