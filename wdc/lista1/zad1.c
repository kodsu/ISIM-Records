#include<stdlib.h> 
#include<stdio.h> 
#include<stdbool.h> 
#include<time.h> 

int main(void){ 
    srand(time(NULL)); 
    int liczba = rand() % 101; 
    printf("Program wylosowal pewna liczbe, twoim zadaniem jest jej odganiecie!\n"); 
    printf("Twoim zadaniem jest podawanie liczb calkowitych, gdy odganiesz prawidlowa liczbe, gra sie konczy\nW przeciwnym razie program Ci powie czy podana liczba jest za duza czy tez za mala\n"); 
    bool skonczone = 0;  
    int strzal; 
    while(!skonczone){ 
        printf("\nPodaj liczbe calkowita: "); 
        while(scanf("%d", &strzal) < 1 ){ 
                while(getchar() != '\n') continue; 
                printf("\n Nieporawne wejscie - podaj liczbe ponownie: "); 
        }         
        if(strzal == liczba) 
            skonczone = 1; 
        if(strzal < liczba) 
            printf("Za malo!\n"); 
        if(strzal > liczba) 
            printf("Za duzo!\n");    
    } 
    printf("\nBrawo, udalo sie Tobie!\n"); 

}
