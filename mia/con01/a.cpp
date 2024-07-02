
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
int main(){ 
	int n; cin >> n;  
	int num = 0; 
	for(int i = 0; i <n; i++){  
		for(int k = 0; k < 6; k++){ 
			cin >> num; 
			jest[num]++; 
		}  
		for(int k = 0; k < 10; k++){ 
			if(jest[k]) 
				amo[k]++; 
			jest[k] = 0; 
		}
	}  
	int res = 0;  
	int k = 0;  
	bool good ; 
	for(int i = 1; i < 1000; i++){ 
		k = i; 
		for(int j = 0; j < 10;j++) 
			req[j] = 0; 
		while(k){ 
			req[k%10]++; 
			k/= 10;  
		}  
		good = 1; 
		for(int  j = 0; j < 10; j++){ 
			if(req[j] > amo[j]){ 
				good = 0; 
				break; 
			} 
		} 
		if(!good) 
			break;  
		else 
			res = i; 
	} 
	cout << res; 
}
