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
const int MN = 205; 
ll przekp[MN*2], przekl[MN*2]; 
const int C = 101; 
int val[MN][MN]; 
ll wyn[MN][MN]; 

void solve(){ 
	int n, m; 
	cin >> n >> m;  
	for(int i = 0; i < 2 * MN; i++){ 
		przekl[i] = 0; 
		przekp[i] = 0; 
	}
	for(int i = 0; i < n; i++){ 
		for(int j = 0; j < m; j++){ 
			cin >> val[i][j]; 
			przekp[i+j] += val[i][j]; 
			przekl[i-j+C] += val[i][j]; 
		} 
	}   
	ll res = 0; 
	for(int i = 0; i < n; i++){ 
		for(int j = 0; j < m; j++){ 
			res = max(res,  przekp[i+j]+ przekl[i-j+C] - val[i][j]); 
		} 
	}		
	cout << res<< "\n"; 
}

int main(){ 
	int t; cin >> t; 
	while(t--){ 
		solve(); 
	} 
}
