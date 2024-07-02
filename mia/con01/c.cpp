#include<bits/stdc++.h> 

#define pb push_back 
#define st first 
#define nd second 
#define BOOST ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0); 

using namespace std; 
typedef long long ll; 
typedef vector<int> vi; 
typedef vector<ll> vl; 
typedef pair<int,int> pii; 
typedef vector<pii> vii; 
typedef pair<ll, ll> pll; 
typedef vector<pll> vll;  
const int MN = 1000009; 
ll prefa[MN]; 
ll sufb[MN];   
ll licz[MN];  
ll pot10b[MN] ;
int main(){ 
	string s; cin >> s;   
	int n = s.size();
	licz[0] = 0; licz[n+ 1] = 0;  
	for(int i = 1; i <= n; i++) 
		licz[i] = (int)(s[i-1] - '0'); 
	ll a, b; cin >> a >> b;  
	if(licz[1] == 0){ 
		cout << "NO"; 
		return 0; 
	}   
	pot10b[0] = 1; 
	for(int i = 1; i < MN; i++){ 
		pot10b[i] = (pot10b[i-1] * 10) %b; 
	} 
	prefa[0] = 0; 
	sufb[n+1] = 0; 
	for(int i = 1; i <= n; i++){ 
		prefa[i] = (10 * prefa[i-1] + licz[i]) %a; 
	} 
	for(int i = n; i > 0; i--){ 
		sufb[i] = (sufb[i+1] + pot10b[n-i] *licz[i])%b; 
	} 
	int miej = 0; 
	for(int i = 1; i < n; i++){ 
		if(licz[i+1] && prefa[i] == 0 && sufb[i+1] == 0) 
			miej = i; 
	} 
	if(!miej){ 
			cout << "NO"; 
			return 0; 
	}  
	cout << "YES\n"; 
	for(int i = 1; i <= miej; i++) 
		cout << licz[i]; 
	cout << "\n"; 
	for(int i = miej+1; i <= n; i++) 
		cout << licz[i] ; 
}
