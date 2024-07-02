// tutaj sa naglowki funkcji do planszy 
#include<stdio.h>   
#include<math.h> 
#include <stdlib.h>
#include<stdbool.h> 
typedef long long ll; 
#define MAKS_SIZE 50
 
char plansza[MAKS_SIZE][MAKS_SIZE]; 

bool czy_wygral(char gracz, int n, char tab[n][n]);

void wypisz_plansze(int n, char tab[n][n]);



