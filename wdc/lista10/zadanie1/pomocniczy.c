#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 

#define val_A 10
#define val_Z 5
#define MAX_STEP 10
#define MIN_STEP 0
#define plik_wejsciowy article
void memory_error(){ 
    assert(1 == 0); 
    return; 
}

ll los(ll a, ll b){ 
   ll t = rand(); 
    t <<= 31; 
    t += rand(); 
    return a + t %(b - a + 1); 
}
bool konczy(char a){ 
    return (a == '.' || a == '?' || a == '!'); 
}
FILE* wczyt;   
char plik_wejsciowy[] = "article"; // Plik article to fragment "Quo Vadis" Henryka Sienkiewicza
void renew_wczyt(){ 
    fclose(wczyt); 
    wczyt = fopen(plik_wejsciowy, "r"); 
    if(wczyt == NULL){ 
        fprintf(stderr, "Blad odczytu z tekstu zrodlowego\n"); 
        exit(1);
    }
}
void skip_sentence(){ 
    int status; int val; 
    bool done = 0; 
    while(!done){ 
        while((status =(val = fgetc(wczyt))) != EOF && !konczy(val)) 
            continue; 
        if(status == EOF) 
            renew_wczyt(); 
        else 
            done = 1; 
    } 
}

void print_sentence(FILE *plik){ // '\n' -> ' ' 
    int status; int val; 
    bool done = 0; 
    while(!done){ 
        while((status =(val = fgetc(wczyt)))!=EOF && !konczy(val)){ 
            if(isspace(val)) 
                val = ' '; 
            putc(val, plik); 
        }       
        if(status == EOF) 
            renew_wczyt(); 
        else{ 
            done = 1; 
            putc((char)val, plik); 
        } 
    } 
}

void generate_content(FILE *plik){ 
    int liczba_akapitow = los(1, val_A);  
    wczyt = fopen(plik_wejsciowy, "r");
    if(wczyt == NULL){ 
        fprintf(stderr, "Blad odczytu z tekstu zrodlowego\n"); 
        exit(1); 
    }
    int zdan; int k;  
    for(int i = 0; i < liczba_akapitow; i++){ 
        zdan = los(1, val_Z); 
        for(int j = 0; j < zdan; j++){ 
            k = los(MIN_STEP, MAX_STEP); 
            for(int w = 0; w < k; w++) 
                skip_sentence(); 
            print_sentence(plik); 
        }
        fputc('\n', plik);fputc('\n', plik); 
    }

    fclose(wczyt); 
}

int main(int argc, char* argv[]){  
    srand(time(NULL)); 
    if(argc != 2){ 
        fprintf(stderr, "Nieprawidlowa liczba argumentow wywolania\n"); 
        return 1; 
    } 
    int liczba;  
    liczba = atoi(argv[1]); 
    if (!(liczba != 0 ) ) {
        fprintf(stderr, "Nieprawidlowa wartosc wywolania\n"); 
        return 1; 
    }  
    if(liczba <= 0 || liczba >=256 ){ 
        fprintf(stderr, "Argument wywolania nie miesci sie w zakresie [1, 255] \n");  
        return 1; 
    }  
    char bufor[4]; 
    FILE *plik; 
    char napis[] = "chapt000.txt";  
    // const char* content[] = "ROZDZIAL "; 
    for(int ind = 1; ind <= liczba; ind++){ 
        sprintf(bufor, "%03d", ind); 
        //  printf("%ld %ld", strlen(napis), strlen(bufor)); 
        for(int i = 0; i < 3; i++) 
        //printf("%s\n", napis); 
            napis[i+5] = bufor[i]; 
        plik = fopen(napis, "w"); 
        if (plik == NULL) {
            fprintf(stderr, "Blad tworzenia pliku \n");
            return 1;  
        } 
        fprintf(plik, "ROZDZIAL ");  
        sprintf(bufor, "%d", ind); 
        fprintf(plik, "%s" , bufor); fprintf(plik, "\n");  
        generate_content(plik); 
        fclose(plik); 
    } 
}