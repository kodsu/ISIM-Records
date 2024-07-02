#include<stdio.h> 
typedef long long ll; 

#define MAKS_N 105 

char tablica[MAKS_N][MAKS_N]; 
char pom[MAKS_N][MAKS_N];  
char buf[2*MAKS_N]; 
const char FREE = '.', WHITE = 'b', BLACK = 'c'; 
int n;  

void wypisz(){ 
    for(int i = 0; i < n; i++){ 
        for(int j = 0; j < n; j++) 
            printf("%c", tablica[i][j]);  
        printf("\n"); 
    } 
    //printf(" \n"); 
} 

void rotation_left(){ 
    for(int i = 0; i < n; i++){ 
        for(int j = 0; j < n; j++) 
            pom[n-1-j][i] = tablica[i][j]; 
    } 
    for(int i = 0; i < n; i++) 
        for(int j = 0; j < n; j++) 
            tablica[i][j] = pom[i][j]; 
}

void push_down(){  
    int ind; 
    for(int j = 0; j < n; j++){  
        ind = 0; 
        for(int i = n-1; i > -1; i--){  
            if(tablica[i][j] != FREE)
                buf[ind++] = tablica[i][j];  
        } 
        for(int k = 0; k < ind; k++){ 
            tablica[n-1-k][j] = buf[k];  
        } 
        for(int k = ind; k < n; k++) 
            tablica[n-1-k][j] = FREE;  
        ind = 0; 
    }
} 

void rotation_right(){ 
    for(int i = 0; i < n; i++){ 
        for(int j = 0; j < n; j++) 
            pom[j][n-1-i] = tablica[i][j]; 
    } 
    for(int i = 0; i < n; i++) 
        for(int j = 0; j < n; j++) 
            tablica[i][j] = pom[i][j]; 
} 
 

int main(){  
    scanf("%d", &n); 
    for(int i = 0; i < n; i++){ 
        for(int j = 0; j < n; j++){ 
            do {
                tablica[i][j] = getchar();
            } while (tablica[i][j] == '\n'); 
        }
    }  
     //wypisz();  

    int operacja; 
    while((operacja = getchar()) != EOF){  
        if(!(operacja == 'L' || operacja == 'R')) 
            continue; 
        //printf("%c\n", (char)operacja); 
        if(operacja == 'R'){
            rotation_right();
            push_down();    
        }
        if(operacja == 'L'){ 
            rotation_left(); 
            push_down(); 
        }  
        //wypisz(); 
    }
    wypisz();  
}