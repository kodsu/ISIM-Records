#include<stdio.h>   
#include<math.h> 
#include <stdlib.h>
#include<stdbool.h>  
#include<assert.h> 
typedef long long ll; 
#define MAKS_SIZE 50
 
char* buf[MAKS_SIZE * MAKS_SIZE]; 
int los(int a, int b); 
char* ruch_losowego(char gracz, int n, char tab[n][n]); 