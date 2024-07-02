// glowny plik z funkcja main  
// to ma miec argument wywoolania jako n - dlugosc boku planszy 

#include<stdio.h>   
#include<math.h> 
#include<stdlib.h>
#include<stdbool.h>
#include<string.h> 
#include<ctype.h>  
#include<time.h> 
typedef long long ll; 
#define MAKS_SIZE 50

#include"plansza.h" 
#include"gracz_losowy.h" 
#include"gracz_ze_strategia.h" 



int main(int argc, char *argv[]){  
    srand(time(NULL)); 
    int N = 3; 
    if(argc > 2){ 
        printf("Nieprawidlowa liczba arumentow wywoalnia\n"); 
        return 1; 
    }   
    if(argc == 2){
        int amo = atoi(argv[1]);  
        if(amo < 1 || amo > MAKS_SIZE){
            printf("Nieprawidlowy argument wywolania\n"); 
            return 2; 
        } 
        N = amo;  
    }
    char plansza[N][N]; 
    for(int i = 0; i < N; i++){ 
        for(int j = 0; j < N; j++) 
            plansza[i][j] = 0; 
    }  
    // tutaj będziemy wywolywac odpowiednie funkcje 
    // wypisujemy sobie po prostu plansze po kolei 
    int start = los(0,1); int lim = N*N+start; 
    char Gracz[2] = {'O', 'X'}; int par;  
    if(los(0,1)){ 
        Gracz[0] = 'X'; 
        Gracz[1] = 'O'; 
    } 
    char* move; char gr;  
    //wypisz_plansze(N, plansza);  
    char c; 
    for(int i = start; i < lim; i++){    
        c = getchar(); 
        while(c != '\n') 
            c = getchar(); 
        par = i%2;  
        gr = Gracz[par];  
        if(i&1){ 
            // wykonujemy ruch losowego 
            move = ruch_losowego(par, N, plansza);   
            *(move) = gr; 
            //plansza[move.st][move.nd] = gr; 
            if(czy_wygral(gr, N, plansza)){ 
                wypisz_plansze(N, plansza);
                printf("WYGRAL GRACZ %c\n", gr);
                exit(0); 
            }
        } 
        else 
        { 
            move = ruch_deter(par, N, plansza);  
            *(move) = gr; 
            if(czy_wygral(gr, N, plansza)){
                wypisz_plansze(N, plansza); 
                printf("WYGRAL GRACZ %c\n", gr); 
                exit(0); 
            }
        } 
        wypisz_plansze(N, plansza); 
    } 
    printf("REMIS!\n"); 
}