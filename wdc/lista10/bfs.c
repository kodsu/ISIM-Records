#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 

#define INF 1000000001
#define MDEP 10
void memory_error(){ 
    assert(1 == 0); 
    return; 
}
typedef struct{int st; int nd; int dep; } pair;  
typedef struct{int st; int nd;  } proper_pair; 
struct node{ 
    struct node* next; struct node* prev; 
    pair value; 
}; 

struct node* new_node(){ 
    struct node* nowy_node = (struct node*)malloc(sizeof(struct node));
    if (nowy_node == NULL) {
        memory_error(); 
    }
    return nowy_node;
}
struct queue{ 
    struct node* begin; struct node* end; 
}; 

bool queue_empty(struct queue* Q){ 
    if(Q->begin == NULL && Q->end == NULL) 
        return 1; 
    return 0; 
} 

void queue_push(struct queue* Q, pair P){ 
    if(Q->begin == NULL && Q->end == NULL){ 
        Q->begin = new_node();  
        Q->begin->value = P; 
        Q->begin->next = NULL; 
        Q->begin->next = NULL; 
        Q->end = Q->begin;
        return; 
    }
    if(Q->begin != NULL && Q->end != NULL){ 
        struct node* nowy = new_node(); 
        nowy->next = Q->end; 
        nowy->prev = NULL; 
        nowy->value = P; 
        Q->end->prev = nowy; 
        Q->end = nowy; 
        return;
    } 
    printf("xd"); 
    exit(0); 
    assert(2==0); 
    return; 
}

void queue_pop(struct queue*Q){ 
    if(Q->begin == NULL && Q->end == NULL){ 
        printf("popujesz pusta kolejke!\n"); 
        return; 
    }
    if(Q->begin == Q->end ){ 
        Q->begin = NULL; 
        free(Q->end); 
        Q->end = NULL; 
        return; 
    }
    struct node* buf = Q->begin->prev;  
    buf->next = NULL; 
    free(Q->begin); 
    Q->begin = buf;  
    return; 
} 

pair queue_front(struct queue* Q){ 
    if(Q->begin == NULL){ 
        printf("chcesz fronta pustej kolejki!\n");  
        exit(0); 
    } 
    return Q->begin->value; 
}

proper_pair roz[4] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}}; 

int n,m,q; 
void set_val(int n, int m, int tab[n+2][m+2], int val){ 
    for(int i =0; i < n+2; i++){ 
        for(int j = 0; j < m+2; j++) 
            tab[i][j] = val; 
    }
}  

void set_val2(int n, int m, int tab[n+2][m+2][MDEP], int val){ 
    for(int i =0; i < n+2; i++){ 
        for(int j = 0; j < m+2; j++){ 
            for(int k = 0; k < MDEP; k++) 
                tab[i][j][k] = val;
        }
    }
}  

void set_blocked(int n, int m, int blocked[n+2][m+2]){ 
    for(int j = 0; j < m+2; j++){ 
        blocked[0][j] = 1; 
        blocked[n+1][j] = 1; 
    } 
    for(int i = 0; i < n+2; i++){ 
        blocked[i][0] = 1; 
        blocked[i][m+1] = 1; 
    }
}

pair git_pair(int a, int b, int c){ 
    pair p = {a, b, c}; 
    return p; 
}
void runbfs(char start_val, int n, int m, int dist[n+2][m+2][MDEP], const char input[n+2][m+2], const int blocked[n+2][m+2], const int depth[n+2][m+2]){ 
    struct queue* Q = (struct queue*)malloc(sizeof(struct queue)); 
    if(Q == NULL)
        assert(10 == 1);   
    Q->begin = NULL; Q->end = NULL; 
    for(int i = 1; i <= n; i++){ 
        for(int j = 1; j <= m; j++){ 
            if(input[i][j] == start_val){ 
                dist[i][j][1] = 0;  
                queue_push(Q, git_pair(i, j, 1) ); 
            }
        }
    } 
    pair v; 
    while(!queue_empty(Q)){ 
        v = queue_front(Q); 
        queue_pop(Q);  
        if(blocked[v.st][v.nd]){ 
            printf("cos zes skurwil\n"); 
            //exit(0); 
            assert(1 == 0); 
        }
        if(v.dep != 0){ 
            if(dist[v.st][v.nd][v.dep-1] > dist[v.st][v.nd][v.dep]+1){ 
                dist[v.st][v.nd][v.dep-1] = dist[v.st][v.nd][v.dep]+1;  
                v.dep--; 
                queue_push(Q, v);  
            } 
            continue;
        }
        // v.dep == 0 
        for(int i = 0; i < 4; i++){ 
            if(!blocked[v.st+roz[i].st][v.nd+roz[i].nd]){ 
                if(dist[v.st+roz[i].st][v.nd+roz[i].nd][depth[v.st+roz[i].st][v.nd+roz[i].nd] -1] > dist[v.st][v.nd][v.dep]+1){ 
                    dist[v.st+roz[i].st][v.nd+roz[i].nd][depth[v.st+roz[i].st][v.nd+roz[i].nd] -1] = dist[v.st][v.nd][v.dep]+1;  
                    queue_push(Q, git_pair(v.st+roz[i].st, v.nd+roz[i].nd, depth[v.st+roz[i].st][v.nd+roz[i].nd] -1) ); 
                }
            }
        }
    } 
    free(Q); 
}  
int max(int a, int b){ 
    if(a >= b) 
        return a; 
    return b; 
}

int main(){  
    if(scanf("%d %d %d", &n, &m, &q) != 3) 
        return 0; 
    int dist[n+2][m+2][MDEP]; set_val2(n, m, dist, INF); 
    int dist_minus[n+2][m+2]; set_val(n, m, dist_minus, 0);   
    int dist_plus[n+2][m+2]; set_val(n, m, dist_plus, 0); 
    int depth[n+2][m+2]; set_val(n, m, depth, 0); 
    int blocked[n+2][m+2]; set_val(n, m, blocked, 0);
    set_blocked(n, m, blocked);   

    char sign; 
    char input[n+2][m+2];      
    // wczytywanie 
    for(int i = 1; i <= n; i++){ 
        for(int j = 1; j <= m; j++){ 
            if(scanf("%c", &sign) != 1) 
                return 0; 
            while(isspace(sign)) 
                if(scanf("%c", &sign) != 1) 
                    return 0; 
            input[i][j] = sign;  
            if(input[i][j] == 'X'){
                blocked[i][j] = 1; 
                depth[i][j] = 0;  
            }
            if(input[i][j]== '+' || input[i][j]== '-'){ 
                depth[i][j] = 1; 
            } 
            if(input[i][j] >= '1' && input[i][j] <= '9'){ 
                depth[i][j] = input[i][j] - '0'; 
            }
        }
    } 
    runbfs('+', n, m,dist, input, blocked, depth); 
    for(int i = 1; i <= n; i++){ 
        for(int j = 1; j <= m; j++) 
            dist_plus[i][j] = dist[i][j][0]; 
    }
    set_val2(n, m, dist, INF); 
    runbfs('-', n, m,dist, input, blocked, depth);   
    for(int i = 1; i <= n; i++){ 
        for(int j = 1; j <= m; j++) 
            dist_minus[i][j] = dist[i][j][0]; 
    }
   
    int a, b; 
    for(int i = 0; i < q; i++){ 
        if(scanf("%d%d", &a, &b) != 2)  
            return 0; 
        printf("%d\n", max(dist_plus[a][b], dist_minus[a][b]) ); 
    }
}   