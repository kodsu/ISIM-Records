#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 

#define INF 1000000001
#define MEM_S 500000
// Aby program dobrze dzialal powinno zachodzic:  
// MEM_S >= 2*Najluzsze slowo 
// MEM_S >= W + Najlduzsze slowo
void memory_error(){ 
    assert(1 == 0); 
    return; 
}

char MEM[MEM_S];
int END[MEM_S];  
int W = 72;  
FILE *strumien; 

int enter_cnt = 0; 
int words_amo = 0; 
int len = 0; int newlen; 
bool aktukier, change;  

bool read_white(){  
    enter_cnt = 0; 
    int znak;  int stat; 
    while ( (stat = (znak = fgetc(strumien))) != EOF && isspace(znak)) {
        if(znak == '\n') 
            enter_cnt++; 
    }  
    if(stat == EOF){ 
        return 0; 
    }
    else{ 
        ungetc(znak, strumien); 
        return 1; 
    } 
}

bool read_nonwhite(){ 
    int znak;  newlen = 0;  
    int stat; 
    while ( (stat = (znak = fgetc(strumien))) != EOF && !isspace(znak)) {
        MEM[len++] = znak;
        newlen++;  
    }  
    END[words_amo++] = len; 
    if(stat == EOF){ 
       return 0; 
    }
    else{
        ungetc(znak, strumien);
        return 1; 
    }  
}

void shift_last(int a, int b){ 
    for(int i = 0; i < b-a+1; i++){ 
        MEM[i] = MEM[i+a]; 
    }
    for(int i = b-a+1; i <= b; i++) 
        MEM[i] = 0; 
    int ind = 0; 
    while(END[ind] != -1){ 
        END[ind] = -1; 
    }
    END[0] = b-a+1; 
    len = b-a+1;  
    words_amo = 1; 
} 

void clear_structures(){ 
    for(int i = len-1; i>-1; i--) 
        MEM[i] = 0; 
    for(int i = words_amo-1; i > -1; i--) 
        END[i] = -1; 
    len = 0; 
    words_amo = 0; 
    return; 
}
// -l long -> short 0 
// -r short -> long 1  
void put_row(){ 
    if(words_amo == 1){ 
        for(int i = 0 ;i < len; i++){ 
            putchar(MEM[i]); 
        } 
        putchar('\n'); 
        return; 
    }

    aktukier^= change;  
    bool kier = aktukier;  
    int krotkie = (W-len)/(words_amo-1); 
    int dlugie = krotkie +1 ;  
    int dl_amo = (W-len)%(words_amo-1); 
    int kr_amo = (words_amo-1)-dl_amo; 
    int eind = 0;  
    // defaultowo robimy dlugie -> krotkie 
    if(kier){  
        int buf; 
        //swap(dlugie, krotkie);  
        buf = krotkie; krotkie = dlugie; 
        dlugie = buf; 
        //swap(dl_amo, kr_amo);  
        buf = kr_amo; 
        kr_amo = dl_amo; 
        dl_amo = buf; 
    } 
    int buf=-1;
    if(dl_amo != 0){ 
        for(int i= 0; i < len; i++){ 
            if(i != END[eind]){ 
                putchar(MEM[i]); 
            } 
            else 
            { 
                for(int j = 0; j < dlugie; j++) 
                    putchar(' '); 
                putchar(MEM[i]); 
                eind++; 
                if(eind == dl_amo){
                    buf = i;  
                    break; 
                }
            }
        } 
    }
    for(int i = buf+1; i <len; i++){ 
        if(END[eind] != i){ 
            putchar(MEM[i]); 
        } 
        else{ 
            for(int j = 0; j < krotkie; j++) 
                putchar(' ');  
            eind++; 
            putchar(MEM[i]); 
        }
    }
    putchar('\n'); 
}

void run(){  
    int stat, znak;  
    len = 0; words_amo =0; 
    stat = (znak= fgetc(strumien));   
    if(stat == EOF){
        exit(0); 
    }
    ungetc(znak, strumien); 
    if(isspace(znak)){ 
        read_white(); 
    } 
    int justput = 0; 
    while(1){  
        justput = 0; 
        if(!read_nonwhite()){ 
            if(len + words_amo-1 <= W){ 
                put_row();  
                exit(0); 
            }
            else{ 
                words_amo--; 
                len -= newlen; 
                put_row(); 
                shift_last(len, len+newlen-1); // <- ta funkcja zawiera customowe czyszczenie struktur
                put_row(); 
                exit(0); 

            }
        }
        // tutaj jesli czytanie sie udalo, bardzo podobnie ale inaczej
        //if(len + words_amo-1 <= W) <- w takim case nic nie musimy robic
        if(len + words_amo-1 > W){ 
            words_amo--; 
            len -= newlen; 
            put_row(); 
            shift_last(len, len+newlen-1); // <- ta funkcja zawiera customowe czyszczenie struktur
            justput = 1; 
        }
        if(!read_white()){  
            put_row();  
            exit(0); 
        } 
        // tutaj wczytanie bialych sie udalo 
        if(enter_cnt > 1){ 
            put_row(); 
            clear_structures(); 
            while(justput <2){ 
                justput++; 
                putchar('\n');
            }
        }
    }
}

int nalezy(const char *szukanyNapis, int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) { 
        if(argv[i] == NULL) 
            continue;
        if (strcmp(szukanyNapis, argv[i]) == 0) {
            return 1;  // Znaleziono napis w tablicy
        }
    }
    return 0;  // Nie znaleziono napisu w tablicy
}  

int ile_wyst(const char *szukanyNapis, int argc, char *argv[]) {
    int ans = 0; 
    for (int i = 0; i < argc; ++i) {
        if (strcmp(szukanyNapis, argv[i]) == 0) {
            ans++; 
        }
    }
    return ans; 
}  

int pozycja(const char *szukanyNapis, int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        if (strcmp(szukanyNapis, argv[i]) == 0) {
            return i;  
        }
    }
    return -11; 
}  
int main(int argc, char* argv[]){  
    
    if(argc > 6){ 
        fprintf(stderr, "Zbyt wiele argumentow wywolania\n");
        return 1; 
    } 
    bool known[argc+1]; 
    for(int i = 0; i <= argc; i++) 
        known[i] = 0;   
    char* specjalne[] = {"-l", "-r", "-w", "-i"}; 
    bool lewy =0, prawy =0; 
    if(nalezy("-l",argc,  argv)){ 
        if(ile_wyst("-l", argc,  argv) > 1){ 
            fprintf(stderr, "Powtorzona nazwa specjalna w wywolaniu\n"); 
            return 1; 
        }
        lewy = 1; 
        known[pozycja("-l",argc, argv)] = 1; 
    } 
    if(nalezy("-r", argc,  argv)){ 
        if(ile_wyst("-r",argc,  argv) > 1){ 
            fprintf(stderr, "Powtorzona nazwa specjalna w wywolaniu\n"); 
            return 1; 
        }
        prawy = 1; 
        known[pozycja("-r",argc, argv)] = 1;
    } 
    if(lewy && prawy){ 
        fprintf(stderr, "Proba jednoczesnego uzycia -l oraz -r\n");
        return 1;
    }
    if(nalezy("-i",argc,  argv)){  
        if(ile_wyst("-i", argc, argv) > 1){ 
            fprintf(stderr, "Powtorzona nazwa specjalna w wywolaniu\n"); 
            return 1; 
        }
        int pos = pozycja("-i",argc,  argv); 
        if(pos >= argc-1){
            fprintf(stderr, "Brak prawidlowego argumentu dla flagi -i\n");
            return 1;
        }
        if(nalezy(argv[pos+1], 4,  specjalne)){ 
            fprintf(stderr, "Nieprawidlowa nazwa pliku - nastepnik jest nazwa specjalna \n");
            return 1;
        }
        known[pos] = 1; 
        known[pos+1] = 1; 
        strumien = fopen(argv[pos+1], "r");
        if (strumien == NULL) {
            fprintf(stderr, "Błąd otwarcia pliku\n");
            return 1; 
        }
    }  
    else 
    { 
        strumien = stdin; 
    }

    if(nalezy("-w", argc,  argv)){ 
        if(ile_wyst("-w", argc,argv) > 1){ 
            fprintf(stderr, "Powtorzona nazwa specjalna w wywolaniu\n"); 
            return 1; 
        }
        int pos = pozycja("-w",argc, argv); 
        if(pos == argc-1){
            fprintf(stderr, "Brak prawidlowego argumentu dla flagi -w\n");
            return 1;
        }
        if(nalezy(argv[pos+1], 4, specjalne)){ 
            fprintf(stderr, "Nieprawidlowa szerokosc wiersza- nastepnik jest nazwa specjalna \n");
            return 1;
        }
        known[pos] = 1; 
        known[pos+1] = 1; 
        int liczba = atoi(argv[pos+1]);  

        if (!(liczba != 0 ) ) {
            fprintf(stderr, "Nieprawidlowa wartosc po '-w' w wywolaniu\n"); 
            return 1; 
        }  
        if(liczba <= 0 || liczba >= MEM_S/2){ 
            fprintf(stderr, "Nieprawidlowa szerokosci wiersza, niedodatnia lub przekraczajaca mozliwosci programu\n");  
            return 1; 
        }
        W = liczba; 
    }  
    else 
    { 
        W = 72; 
    }
    for(int i = 1; i < argc; i++){ 
        if(!known[i]){ 
            fprintf(stderr, "Niezdefiniowana wartosc jako argument wywolania\n");  
            return 1; 
        }
    } 
    if(lewy){ 
        aktukier = 0; change = 0;
    } 
    if(prawy){ 
        aktukier = 1; change = 0; 
    } 
    if(!lewy && !prawy){ 
        aktukier = 0; change = 1; 
    }
    run();  
    if(strumien != stdin)
        fclose(strumien); 
}
