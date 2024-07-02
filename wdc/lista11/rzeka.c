#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 
#define siz 200009
#define S 18

int n, q; 
int amo[siz]; 
int tree[siz][2]; 
int jump[siz][S];  
bool blocked[siz][S];  
int dep[siz]; 
int pre[siz]; int post[siz]; 

bool anc(int a, int b){ 
    return (pre[a] <= pre[b] && post[b] <= post[a]); 
} 

int tim = 0; 

void zeruj(){ 
    for(int i = 0; i < siz; i++){
        amo[i] = 0; 
        for(int j = 0; j < S; j++) 
            blocked[i][j] = 0; 
    }
}

void dfs(int v){ 
    pre[v] = tim++; 
    for(int k = 0; k < amo[v]; k++){  
        dep[tree[v][k]] = dep[v] +1; 
        dfs(tree[v][k]); 
    } 
    post[v] = tim++; 
}

void build_jump(){ 
    for(int k = 1; k < S; k++){ 
        for(int i = 1; i<= n; i++){ 
            jump[i][k] = jump[jump[i][k-1]][k-1]; 
            blocked[i][k] = blocked[jump[i][k-1]][k-1] || blocked[i][k-1]; 
        }
        //jump[1][k] = 1; 
    }
}

bool impossible; 

int LCA(int a, int b){  
    impossible = 0; 
    int jumper = a; int id = S -1; 
    while(id> -1){ 
        if(!anc(jump[jumper][id], b)){ 
            impossible |= blocked[jumper][id]; 
            jumper = jump[jumper][id]; 
        } 
        id--; 
    }
    if(!anc(jumper, b)){
        impossible |= blocked[jumper][0]; 
        jumper = jump[jumper][0]; 
    } 
    id = S-1; jumper = b; 
    while(id > -1){ 
        if(!anc(jump[jumper][id], a)){ 
            impossible |= blocked[jumper][id]; 
            jumper = jump[jumper][id]; 
        } 
        id--; 
    } 
    //printf("%d\n", jumper); 
    if(!anc(jumper, a)){
        impossible |= blocked[jumper][0]; 
        jumper = jump[jumper][0]; 
    } 
    return jumper; 
}

int main(){  
    scanf("%d%d", &n, &q);  
    int a, b; int t; 
    for(int i = 0; i < n-1; i++){ 
        scanf("%d%d%d", &a, &b, &t); 
        tree[a][amo[a]++] = b;  
        blocked[b][0] = t; 
        jump[b][0] = a; 
    } 
    jump[1][0] = 1 ;
    dep[1] = 0; 
    dfs(1);  
    build_jump();  
    //LCA(2, 5); 
    //exit(0); 
    int lca; 
    for(int i = 0; i < q; i++){ 
        scanf("%d%d", &a, &b); 
        lca = LCA(a, b); 
        if(impossible){ 
            printf("mission impossible\n"); 
            continue;
        }
        printf("%d\n", dep[a] + dep[b] - 2 * dep[lca]); 
    }
}