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

const int MN = 200005;  
const int INF = 1000000099; 
int a[MN]; 
int b[MN]; 

int main(){  
    BOOST
    int A, B; 
    cin >> A >> B; 
    a[0] = -INF; 
    for(int i = 1; i <= A; i++) 
        cin >> a[i]; 
    sort(a, a + A+1);  
    a[A+1] = INF; 
    int x;  
    int l  = 0, r = A, s; 
    for(int i = 0; i < B; i++){ 
        cin >> x;  
        l = 0, r = A+1; 
        while(l < r){ 
            // 111... 10...0
            s = ((l + r+1) >> 1); 
            if(a[s] <= x) 
                l = s; 
            else r = s-1; 
        } 
        cout << l << " " ; 
    }
}