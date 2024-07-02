#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 

typedef struct{ll st; ll nd;} pair; 

#define MVAl 4096

//ll pref[MAKS_N][MAKS_N]; 
//ll val[MAKS_N][MAKS_N];  
 

// 0 - ^ 
// 1 - | 
// 2 - &
int result(int n, int m, int T[n][m]){ 
    bool dp [4096][n][m][3];  
    int beg = 0; 
    for(int i = 0; i < 4096; i++){ 
        for(int ii = 0; ii < n; ii++){ 
            for(int j = 0; j < m; j++){ 
                for(int jj = 0; j < 3; j++){ 
                    dp[i][ii][j][jj] = 0; 
                }
            }
        }
    }
    dp[beg^T[0][0]][0][0][0] = 1; 
    dp[beg|T[0][0]][0][0][1] = 1; 
    dp[beg&T[0][0]][0][0][2] = 1; 
    int a, b; 
    for(int i = 1; i < m; i++){ 
        a = 0; b = i-1; 
        for(int v = 0; v < 4096; v++){
            if(dp[v][a][b][0]){ 
                dp[v|T[a][b]][0][i][1] = 1;
                dp[v&T[a][b]][0][i][2] = 1; 
            } 
            if(dp[v][a][b][1]){ 
                dp[v^T[a][b]][0][i][0] = 1;
                dp[v&T[a][b]][0][i][2] = 1; 
 
            } 
            if(dp[v][a][b][2]){ 
                dp[v^T[a][b]][0][i][0] = 1;
                dp[v|T[a][b]][0][i][1] = 1;                
            }
        }
    }
    for(int i = 1; i < n; i++){ 
        a = i-1; b = 0; 
        for(int v = 0; v < 4096; v++){
            if(dp[v][a][b][0]){ 
                dp[v|T[a][b]][i][0][1] = 1;
                dp[v&T[a][b]][i][0][2] = 1; 
            } 
            if(dp[v][a][b][1]){ 
                dp[v^T[a][b]][i][0][0] = 1;
                dp[v&T[a][b]][i][0][2] = 1; 
 
            } 
            if(dp[v][a][b][2]){ 
                dp[v^T[a][b]][i][0][0] = 1;
                dp[v|T[a][b]][i][0][1] = 1;                
            }
        }
    }  
    for(int i = 1; i < n; i++){ 
        for(int j = 1; j < n; j++){ 
            for(int v = 0; v < 4096; v++){ 
                a = i-1, b = j; 
                if(dp[v][a][b][0]){ 
                    dp[v|T[a][b]][i][j][1] = 1;
                    dp[v&T[a][b]][i][j][2] = 1; 
                } 
                if(dp[v][a][b][1]){ 
                    dp[v^T[a][b]][i][j][0] = 1;
                    dp[v&T[a][b]][i][j][2] = 1; 
    
                } 
                if(dp[v][a][b][2]){ 
                    dp[v^T[a][b]][i][j][0] = 1;
                    dp[v|T[a][b]][i][j][1] = 1;                
                }
                // drugi "poprzednik" 
                a = i, b = i-1; 
                if(dp[v][a][b][0]){ 
                    dp[v|T[a][b]][i][j][1] = 1;
                    dp[v&T[a][b]][i][j][2] = 1; 
                } 
                if(dp[v][a][b][1]){ 
                    dp[v^T[a][b]][i][j][0] = 1;
                    dp[v&T[a][b]][i][j][2] = 1; 
    
                } 
                if(dp[v][a][b][2]){ 
                    dp[v^T[a][b]][i][j][0] = 1;
                    dp[v|T[a][b]][i][j][1] = 1;                
                }
            }
        }
    }
    int res = 0; 
    for(int v = 0; v < 4096; v++){  
        int i = n-1, j = m-1; 
        if(dp[v][i][j][0] || dp[v][i][j][1] || dp[v][i][j][2]) 
            res++; 
    } 
    return res; 
}


int main(){  
    int n, m; 
    scanf("%d%d", &n, &m);  
    int T[n][m]; 
    int wyn = result(n, m, T); 
    printf("%d\n", wyn); 

}