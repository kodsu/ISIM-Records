#include<bits/stdc++.h>
#include <unistd.h> 
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
mt19937 gen(getpid());  
ll los(ll a, ll b){ 
	ll t = gen(); 
	t <<= 31; 
	t += gen() ; 
	return a + t % (b - a + 1); 
} 
const int MN = 1009; 

int main(){  
    const ll M_VAL = INT_MAX -1; 
    int S = 2000000, MAX_SIN = 1000000; 
	int M, Q; 
    M = los(2, 10); 
    Q = los(2, 2); 
    cout << M << " " << Q << "\n";
    vl val; val.resize(M+1);  

    for(int i = 1; i<= M; i++){   
        val[i] = los(0, min(MAX_SIN, S/2));  
        S -= val[i]; 
    }   
    val[los(1,M)]+=2; 

    for(int i = 1; i<= M; i++){ 
        cout << val[i] << " "; 
        for(int j = 0; j < val[i]; j++){ 
            cout << los(M_VAL/2, M_VAL) << " "; 
        } 
        cout << "\n"; 
    }
    int skad, dokad; 
    int len ; int a, b;  
    bool bylo = 0; 
    for(int i = 0; i < Q-1; i++){ 
        if(!los(0,1) && bylo){ 
            cout << "K\n";  
            bylo = 0;  
            continue; 
        }  
        bylo = 1; 
        cout << "R "; 
        skad = los(1,M);  
        while(val[skad] == 0){ 
            skad = los(1,M); 
        } 
        dokad = los(1,M); 
        cout << skad << " " << dokad << " "; 
        len = val[skad];  
        a = los(1, len); 
        b = los(a, len); 

        if(los(0,1)){
            cout << a << " ";  
            if(los(0,1)) 
                cout << b << "\n"; 
            else 
                cout << b - len- 1 << "\n";   
        }
        else {
            cout << a - len - 1 << " " << b -len - 1 << "\n"; 
        } 
        val[skad] -= (b-a+1); 
        val[dokad] += (b-a+1); 
    } 
    cout <<"K\n"; 
}
