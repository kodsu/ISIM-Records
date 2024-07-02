#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 

typedef struct{int st; int nd;} pair; 

int N, M;  
int H, W, G, S; 

int tab[11][11];  
char stoi[11][11];
int zost[11][11]; 
pair wyw[11][11];   // kogo wywolac bedac w polu [a][b] 
// z [n-1][m-1] wywolujemy n,m ktore jest ostatnim(konczy nam rekurencje )
pair roz[8] = {{-1,2}, {-1, -2}, {1, 2}, {1, -2}, {2, -1}, {2, 1}, {-2, 1}, {-2, -1}};  
pair next[4] = {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}}; 
// tab[a][b] - ile figur atakuje pole [a][b] 
// stoi[a][b] - czy jakas figura stoi na polu [a][b]
int aH=0, aW=0, aG=0, aS=0; 
bool wieza(int a, int b){ // sprawdza czy mozna postawic wieze na polu a,b [czy w jej zakresie atakowania nie stoi zadna inna figura]
    for(int i = 0; i < M; i++) 
        if(stoi[a][i]) 
            return 0; 
    for(int j = 0; j < N; j++) 
        if(stoi[j][b]) 
            return 0;  
    return 1; 
} 

void mark_wieza(int a, int b, int val){ 
    for(int i = 0; i < M; i++) 
        tab[a][i] += val; 
    for(int j = 0; j < N; j++) 
        tab[j][b] += val; 
    tab[a][b] -= val;  
    return; 
}

bool goniec(int a, int b){ // analogicznie dla gonca 
   int c, d; 
   for(int i = 0; i < 4; i++){ 
        c = a + next[i].st; d = b + next[i].nd; 
        while( 0 <= c && c < N && 0 <= d && d < M){ 
            if(stoi[c][d]) 
                return 0; 
            c += next[i].st; d += next[i].nd; 
        }
   } 
   return 1; 
}

void mark_goniec(int a, int b, int val){ 
    int c, d; 
    for(int i = 0; i < 4; i++){ 
         c = a + next[i].st; d = b + next[i].nd; 
         while( 0 <= c && c < N && 0 <= d && d < M){ 
            tab[c][d] += val; 
            c += next[i].st; d += next[i].nd; 
         }
    } 
}

bool hetman(int a, int b){ 
    if(!wieza(a,b)) 
        return 0; 
    if(!goniec(a,b)) 
        return 0; 
    return 1; 
} 
void mark_hetman(int a, int b, int val){ 
    mark_goniec(a, b, val); 
    mark_wieza(a,b, val); 
}
bool skoczek(int a, int b){ // analogicznie dla skoczka 
    if(tab[a][b]) 
        return 0; 
     for(int i = 0; i < 8; i++){ 
        if(0<= a+roz[i].st && a+roz[i].st < N && 0<=b+roz[i].nd && b+roz[i].nd < M){ 
            if(stoi[a+roz[i].st][b+roz[i].nd]) 
                return 0;
        }
    } 
    return 1; 
}

void mark_skoczek(int a, int b, int val){ 
     for(int i = 0; i < 8; i++){ 
        if(0<= a+roz[i].st && a+roz[i].st < N  && 0<=b+roz[i].nd && b+roz[i].nd < M){ 
            tab[a+roz[i].st][b+roz[i].nd] += val; 
        }
    } 
}  
void wypisz_stoi(){  
    printf("%d %d\n", N, M); 
    for(int i= 0; i < N; i++){ 
        for(int j= 0; j < M; j++){  
            if(stoi[i][j])
                printf("%c", stoi[i][j]); 
            else 
                printf(".");  
        } 
        printf("\n"); 
    }
}
int wynik = 0; 
void rekur(int A, int B){    
      
    if(aH == H && aS == S && aG == G && aW == W){  
        //printf("%d %d\n", aS, S); 
        wynik++; 
        //printf("%d %d\n", A, B); 
        //wypisz_stoi();  
        //printf("\n"); 
        return; 
    }
    if(A == N && B == M) 
        return;  
    if(H-aH + S-aS+G-aG+W-aW > zost[A][B]) 
         return; 
    rekur(wyw[A][B].st, wyw[A][B].nd); 

    // printf("%d %d\n", A, B); 
    // wypisz_stoi(); 
    // printf("%d\n", aS); 
    // printf("%d %d\n", tab[A][B], (int)stoi[A][B]); 
    // printf("\n");

    if(!tab[A][B] && !stoi[A][B]){ 
        if(aH < H && hetman(A, B)){
            mark_hetman(A, B, 1); 
            stoi[A][B] = 'H';  
            aH++; 
            rekur(wyw[A][B].st, wyw[A][B].nd); 
            aH--; 
            stoi[A][B] = 0; 
            mark_hetman(A, B, -1); 
        } 
        if(aW < W && wieza(A, B)){ 
            mark_wieza(A, B, 1); 
            stoi[A][B] = 'W'; 
            aW++; 
            rekur(wyw[A][B].st, wyw[A][B].nd); 
            aW--; 
            stoi[A][B] = 0; 
            mark_wieza(A, B, -1); 
        }  
        if(aG < G && goniec(A, B)){ 
            mark_goniec(A, B, 1); 
            stoi[A][B] = 'G'; 
            aG++; 
            rekur(wyw[A][B].st, wyw[A][B].nd); 
            aG--; 
            stoi[A][B] = 0; 
            mark_goniec(A, B, -1); 
        } 
        if(aS < S && skoczek(A, B)){ 
            mark_skoczek(A, B, 1); 
            stoi[A][B] = 'S'; 
            aS++; 
            rekur(wyw[A][B].st, wyw[A][B].nd);  
            aS--; 
            stoi[A][B] = 0; 
            mark_skoczek(A, B, -1); 
        } 
    } 
}
int main(){   

    if(scanf("%d %d", &N, &M)!= 2) return 0;
    if(scanf("%d %d %d %d", &H, &W, &G, &S)!= 4) return 0; 
    for(int i= 0; i < 10; i++){ 
        for(int j =0; j < 10; j++){ 
            tab[i][j] = 0;  
            stoi[i][j] = 0; 
        }
    }   
    int wsk = 0; 
    for(int i = 0; i < N; i++){ 
        for(int j = 0; j < M-1; j++){ 
            //wyw[i][j] = {i, j+1};  
            wyw[i][j].st = i; 
            wyw[i][j].nd = j+1;  
            zost[i][j] = wsk++; 
        } 
        //wyw[i][m-1] = {i+1, 0};  
        wyw[i][M-1].st = i+1; 
        wyw[i][M-1].nd = 0;   
        zost[i][M-1] = wsk++;
    }  
    for(int i = 0;i < N; i++){ 
        for(int j = 0;  j < M; j++){ 
            zost[i][j] = N*M-zost[i][j]; 
        }
    }
    //wyw[n-1][m-1] = {n, m}; 
    wyw[N-1][M-1].st = N; 
    wyw[N-1][M-1].nd = M;  
    rekur(0, 0); 
    printf("%d", wynik); 
}   