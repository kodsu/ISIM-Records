#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 

typedef struct{ll st; ll nd;} pair; 

#define MAKS_N 1000

//ll pref[MAKS_N][MAKS_N]; 
//ll val[MAKS_N][MAKS_N]; 

int los(ll a, ll b){ 
    ll t = rand(); 
    t <<= 31; 
    return a + t %(b-a+1); 
}


void fill(int n, int m, int T[n][m]){ 
    int a = los(1, 996), b = los(1, 996); 
    for(int i = 0; i < n; i++){ 
        for(int j = 0; j < m; j++){ 
            T[i][j] = (a * (j+i*m)+b)%997; 
        }
    }
}

void wypisz(int a){ 
    if(a >= 100){
        printf("%d", a); 
        return; 
    } 
    if(a >= 10){ 
        printf(" %d", a); 
        return; 
    } 
    printf("  %d", a); 
}
 
void wizualizacja(int n, int m, int T[n][m], int x0, int y0, int x1, int y1){ 
    for(int i = 0; i < n; i++){
        if(x0 <= i && i <= x1){ 
            for(int j = 0; j < m; j++){ 
                if(j == y0 || j == y1+1)
                    printf("| "); 
                wypisz(T[i][j]);  
                printf(" "); 
            } 
            if(y1 == m-1) 
                printf("| ");
            printf("\n"); 
        } 
        else 
        { 
            for(int j = 0; j < m; j++){ 
                if(j == y0 || j == y1+1)
                    printf("  "); 
                wypisz(T[i][j]);  
                printf(" "); 
            }
            if(y1 == m-1) 
                printf("  ");
            printf("\n"); 
        }
    }
}
int main(int argc, char *argv[]){  
    srand(time(NULL)); 
    if(argc != 3){ 
        fprintf(stderr, "%s", "Nieprawidlowa liczba argumentow wywolania\n"); 
        return 1;       
    }    
    int n, m;  
    if(argc == 3){ 
        char *endptr; 
        n = strtol(argv[1], &endptr, 10); 
        if(*endptr != '\0'){ 
            fprintf(stderr, "Niepoprawny format liczby z wywolania\n");  
            return 1; 
        }
        m = strtol(argv[2], &endptr, 10); 
        if(*endptr != '\0'){ 
            fprintf(stderr, "Niepoprawny format liczby z wywolania\n");  
            return 1; 
        } 
        if(n < 1 || m < 1){ 
            fprintf(stderr, "Niepoprawna wartosc argumentu wywolania\n");  
            return 1; 
        }
    } 
     
    int T[n][m];  
    int pref[n+1][m+1]; 
    fill(n, m, T); 
    for(int i = 0; i <= n; i++) 
        pref[i][0] = 0; 
    for(int i = 0; i <= m; i++) 
        pref[0][i] = 0;
    ll aktuval; 
    for(int i = 1; i <= n; i++){ 
        aktuval = 0; 
        for(int j = 1; j <= m; j++){ 
            aktuval += T[i-1][j-1]; 
            pref[i][j] = pref[i-1][j] + aktuval; 
        }
    }   
    int x0, y0, x1, y1; 
    while(1){ 
        if(!scanf("%d %d %d %d", &x0, &y0, &x1, &y1)){ 
            fprintf(stderr, "Niepoprawna wartosc na wejsciu\n");  
            continue; 
        } 
        if(x0 == -1){ 
            exit(0); 
        } 
        if(x0 < 0 || x0 >= n || x0 > x1 || x1 <0 || x1 >= n 
        || y0 < 0 || y0 >= m || y0 > y1 || y1 <0 || y1 >= m){ 
            fprintf(stderr, "Niepoprawne dane na wejsciu\n");  
            continue;
        }
        printf("%d\n", pref[x1+1][y1+1]-pref[x1+1][y0]-pref[x0][y1+1] + pref[x0][y0]); 
        // tutaj wypisac wizualizacje  
        wizualizacja(n, m, T, x0, y0, x1, y1); 
    }
}