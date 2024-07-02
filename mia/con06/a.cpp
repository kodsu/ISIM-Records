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

int hist[10]; 
void solve(){ 
    string s; 
    cin >> s; 
    bool par = 0; int sum=0;  
    bool pie = 0; 
    int val;  
    for(int i = 0; i < 10; i++) 
        hist[i] = 0; 
    for(int i = 0; i < sz(s); i++){ 
        val = s[i]-'0';  
        hist[val]++; 
        //if(val == 0 || val == 2 || val == 4 || val == 6 || val == 8) 
          //  par = 1;  
        if(val == 5 || val == 0) 
            pie = 1; 
        sum += val; 
    }  
    bool four = 0;  
    int fir, se;  
    //for(int i = 0; i < 10; i++)     
    //    cout << hist[i] << " "; 
    //cout << "\n";
    for(int i = 0; i < 100; i+=4){
        fir = i/10; 
        se = i%10;  
        //cout << fir << " " << se << "\n"; 
        if(fir == se){ 
            if(hist[fir]>= 2 && (se == 5 || se == 0)){
                four = 1;   
                //cout << fir << " " << se  << "\n"; 
                break; 
            }  
            continue; 
        } 
        if(fir != 5 && fir!=0 && (se == 5 || se == 0)){
            if(hist[fir]>= 1 && hist[se]>=1 ){ 
                four = 1; 
                //cout << fir << " " << se  << "\n"; 
                break; 
            }
        }  
        if(fir == 0 && hist[fir] >= 1 && hist[se]>=1 && (se == 5 || se == 0)){ 
            if(hist[0]==1 && hist[5] == 0) 
                continue;  
            //cout << fir << " " << se << "\n"; 
            four = 1;  
            break; 
        }
        if(fir == 5 && hist[fir]>= 1 && hist[se]>=1 && (se == 5 || se == 0)){ 
            if(hist[5] == 1 && hist[0] == 0) 
                continue;   
            //cout << fir << " " << se << "\n"; 
            four = 1;  
            break; 
        }
    } 
    if(pie && four && sum%3==0) 
        cout << "red\n"; 
    else 
        cout << "cyan\n";  
}

int main(){ 
    int t; 
    cin >> t; 
    while(t--){ 
        solve(); 
    }
    
}