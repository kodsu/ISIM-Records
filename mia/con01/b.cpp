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
int amo[10] = {0};  
int req[10];  
int jest[10] = {0}; 
vi v[3];  
int g[3][10]; 
bool poss[1009]; 
int main(){ 
	int n; cin >> n;   
	poss[0] = 1; 
	int num = 0; 
	for(int i = 0; i <n; i++){  
		for(int k = 0; k < 6; k++){ 
			cin >> num; 
			g[i][num] = 1; 
		}   
	}   
	
	if(n == 3){  
		for(int i = 0; i < 10; i++){ 
			for(int j = 0; j < 10; j++){ 
				for(int k = 0; k < 10; k++){ 
					if(g[0][i] && g[1][j] && g[2][k]){ 
						poss[100*i + 10*j+k] = 1;  
						poss[100*i + 10*k+j] = 1;  
						poss[100*j + 10*i+k] = 1; 
						poss[100*j + 10*k+i] = 1; 
						poss[100*k + 10*j+i] = 1; 
						poss[100*k + 10*i+j] = 1; 
					} 
				} 
			} 
		}  
		int a, b; 
		for(int i = 0; i < 10; i++){ 
			for(int j = 0; j < 10; j++){  
				
				a = 0; b = 1; 
				if(g[a][i] && g[b][j]){ 
					poss[10*i + j] = 1;  
					poss[10*j + i] = 1;  
				}
				a = 0; b = 2; 
				if(g[a][i] && g[b][j]){ 
					poss[10*i + j] = 1;  
					poss[10*j + i] = 1;  
				}
				a = 1; b = 2; 
				if(g[a][i] && g[b][j]){ 
					poss[10*i + j] = 1;  
					poss[10*j + i] = 1;  
				}
			} 
		} 
		for(int i = 0; i < 10; i++){ 
			for(int k = 0; k < n; k++){ 
				if(g[k][i]) 
					poss[i] = 1; 
			} 
		} 
	}
	if(n == 2){  
		
		int a, b; 
		for(int i = 0; i < 10; i++){ 
			for(int j = 0; j < 10; j++){ 
				a = 0, b = 1; 
				if(g[a][i] && g[b][j]){ 
					poss[10*i + j] = 1;  
					poss[10*j + i] = 1;  
				}
			} 
		} 
		for(int i = 0; i < 10; i++){ 
			for(int k = 0; k < n; k++){ 
				if(g[k][i]) 
					poss[i] = 1; 
			} 
		} 
	}
	if(n == 1){  
		
		for(int i = 0; i < 10; i++){ 
			for(int k = 0; k < n; k++){ 
				if(g[k][i]) 
					poss[i] = 1; 
			} 
		} 
	} 
	int res = 0; 
	for(int i = 1; i <= 999; i++){ 
		if(poss[i]) 	
			res = i; 
		else 
			break; 
	} 
	cout << res; 
		
	
}
