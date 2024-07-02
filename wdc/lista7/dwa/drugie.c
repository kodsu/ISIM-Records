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

// 0 - ^ 
// 1 - | 
// 2 - & 

int result(int n, int m, int T[n][m]){ 
  
    bool dp[4096][n][m][3]; 
    int beg = 0; 
    for(int i = 0; i < 4096; i++){ 
        for(int ii = 0; ii < n; ii++){ 
            for(int j = 0; j < m; j++){ 
                for(int jj = 0; jj < 3; jj++){ 
                    dp[i][ii][j][jj] = 0; 
                }
            }
        }
    }  

    int res = 0; 
    for(int v = 0; v < 4096; v++){  
        int i = n-1, j = m-1; 
        if(dp[v][i][j][0] || dp[v][i][j][1] || dp[v][i][j][2]) {
            //printf("%d\n", v); 
            res++; 
        }
    } 
    dp[beg^T[0][0]][0][0][0] = 1; 
    dp[beg|T[0][0]][0][0][1] = 1; 
    dp[beg&T[0][0]][0][0][2] = 1; 
    int a, b; int A, B;  
    for(int i = 1; i < m; i++){ 
        a = 0; b = i;  
        A = 0; B = i-1; 
        for(int v = 0; v < 4096; v++){
            if(dp[v][A][B][0]){ 
                dp[v|T[a][b]][0][i][1] = 1;
                dp[v&T[a][b]][0][i][2] = 1; 
            } 
            if(dp[v][A][B][1]){ 
                dp[v^T[a][b]][0][i][0] = 1;
                dp[v&T[a][b]][0][i][2] = 1; 
 
            } 
            if(dp[v][A][B][2]){ 
                dp[v^T[a][b]][0][i][0] = 1;
                dp[v|T[a][b]][0][i][1] = 1;                
            }
        }
    }
     for(int i = 1; i < n; i++){ 
        a = i; b = 0; 
        A = i-1; B = 0; 
        for(int v = 0; v < 4096; v++){
            if(dp[v][A][B][0]){ 
                dp[v|T[a][b]][a][b][1] = 1;
                dp[v&T[a][b]][a][b][2] = 1; 
            } 
            if(dp[v][A][B][1]){ 
                dp[v^T[a][b]][a][b][0] = 1;
                dp[v&T[a][b]][a][b][2] = 1; 

            } 
            if(dp[v][A][B][2]){ 
                dp[v^T[a][b]][a][b][0] = 1;
                dp[v|T[a][b]][a][b][1] = 1;                
            }
        }
    }  
    for(int i = 1; i < n; i++){ 
        for(int j = 1; j < m; j++){ 
            for(int v = 0; v < 4096; v++){ 
                a = i, b = j; 
                A = i-1, B = j; 
                if(dp[v][A][B][0]){ 
                    dp[v|T[a][b]][a][b][1] = 1;
                    dp[v&T[a][b]][a][b][2] = 1; 
                } 
                if(dp[v][A][B][1]){ 
                    dp[v^T[a][b]][a][b][0] = 1;
                    dp[v&T[a][b]][a][b][2] = 1; 
    
                } 
                if(dp[v][A][B][2]){ 
                    dp[v^T[a][b]][a][b][0] = 1;
                    dp[v|T[a][b]][a][b][1] = 1;                
                }
                // drugi "poprzednik" 
                a = i, b = j; 
                A = i, B = j-1; 
                 if(dp[v][A][B][0]){ 
                    dp[v|T[a][b]][a][b][1] = 1;
                    dp[v&T[a][b]][a][b][2] = 1; 
                } 
                if(dp[v][A][B][1]){ 
                    dp[v^T[a][b]][a][b][0] = 1;
                    dp[v&T[a][b]][a][b][2] = 1; 
    
                } 
                if(dp[v][A][B][2]){ 
                    dp[v^T[a][b]][a][b][0] = 1;
                    dp[v|T[a][b]][a][b][1] = 1;                
                }
            }
        }
    }
     res = 0; 
    for(int v = 0; v < 4096; v++){  
        int i = n-1, j = m-1; 
        if(dp[v][i][j][0] || dp[v][i][j][1] || dp[v][i][j][2]) {
            //printf("%d\n", v); 
            res++; 
        }
    } 

    return res; 
}


int main(){  
    int n, m; 
    scanf("%d%d", &n, &m);  
    int T[n][m]; 
    for(int i = 0; i < n; i++){ 
        for(int j = 0; j < m;j++) 
            scanf("%d", &T[i][j]); 
    }
    int wyn = result(n, m, T); 
    printf("%d\n", wyn); 

}