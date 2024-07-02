#include<stdio.h> 
typedef long long ll; 

struct pair{ 
    int st, nd; 
};  

void deb(int k){ 
    return; 
    printf("debug help#%d\n", k); 
}
void wyp(const char *napis, int liczba) {
    return; 
    printf("%s %d\n", napis, liczba);
}
#define MAKS_L 1005 
#define MAKS_S 1005
int S, M; ll P; // liczba stacji, miejsc, 'kroków' 
struct pair kolejka[MAKS_S][MAKS_L];   // {licznosc, cel podrozy} 
int kol_len[MAKS_S]; 
int kol_wsk[MAKS_S] = {0}; 
int wagonik[MAKS_S] = {0}; 
ll przejechalo= 0, chetnych = 0; 

void read(){ 
    scanf("%d%d%lld", &S, &M, &P );  
    for(int i = 0; i < S; i++){ 
        scanf("%d", &kol_len[i]); 
        for(int j = 0; j < kol_len[i]; j++){ 
            scanf("%d%d", &kolejka[i][j].st, &kolejka[i][j].nd);  
            chetnych += kolejka[i][j].st; 
        }
    } 
    deb(1); 
} 

void run(){ 
    int stacja = 0;  
    int wolne_miejsca = M;  
    wyp("M = ", M);   
    // for(int i = 0; i < S; i++){  
    //     wagonik[i] = 0; 
    //     printf("%d ", wagonik[i]); 
    // }
    
    wyp("chetnych = ", chetnych); 
    for(int i = 0; i < P+1; i++){  
        wyp("i = ", i); 
        if(przejechalo == chetnych) 
            break; 
        wolne_miejsca += wagonik[stacja];  
        przejechalo += wagonik[stacja]; 
        wagonik[stacja] = 0;  
        //deb(2);  
        while(wolne_miejsca!=0 && kol_wsk[stacja] < kol_len[stacja]){ 
            if(kolejka[stacja][kol_wsk[stacja]].st <= wolne_miejsca){ 
                wolne_miejsca -= kolejka[stacja][kol_wsk[stacja]].st;  
                wagonik[kolejka[stacja][kol_wsk[stacja]].nd] += kolejka[stacja][kol_wsk[stacja]].st; 
                kolejka[stacja][kol_wsk[stacja]].st = 0;  
                kol_wsk[stacja]++; 
            } 
            else 
            { 
                kolejka[stacja][kol_wsk[stacja]].st -= wolne_miejsca; 
                wagonik[kolejka[stacja][kol_wsk[stacja]].nd] += wolne_miejsca;
                wolne_miejsca = 0;  
            } 
            //deb(3); 
        } 
        stacja = (stacja+1)%S; 
    } 
    printf("%lld", przejechalo); 
}

int main(void){ 
    read();  
    run(); 
}