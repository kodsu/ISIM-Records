#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 

int next[256]; int N, last, start; 
int prev[256]; 
void process_config(){ 
    FILE *plik;  
    for(int i = 0; i < 256; i++)
        next[i] = prev[i] = 0; 
    plik = fopen("config.bin", "r"); 
    if(plik == NULL){ 
        fprintf(stderr, "Blad odczytu z config.bin\n"); 
        exit(1); 
    }
    unsigned char bajt; 
    if( fread(&bajt, sizeof(unsigned char), 1, plik) != 1){ 
        fprintf(stderr, "Blad odczytu z config.bin\n"); 
        exit(1); 
    }  
    N = bajt; 
    if( fread(&bajt, sizeof(unsigned char), 1, plik) != 1){ 
        fprintf(stderr, "Blad odczytu z config.bin\n"); 
        exit(1); 
    }  
    last = bajt; 
    if( fread(&bajt, sizeof(unsigned char), 1, plik) != 1){ 
        fprintf(stderr, "Blad odczytu z config.bin\n"); 
        exit(1); 
    }   
    start = bajt; 
    // printf("%d %d %d\n", N, last, start); 
    for(int i = 1; i <= N; i++){ 
        if( fread(&bajt, sizeof(unsigned char), 1, plik) != 1){ 
            fprintf(stderr, "Blad odczytu z config.bin\n"); 
            exit(1); 
        }   
        next[i] = bajt; 
    }
    fclose(plik);  
    // tutaj potrzebujemy sobie zbudowac tablice prev; 
    char pre[256][2]; 
    for(int i = 0; i < 256; i++){ 
        pre[i][0] = pre[i][1] = 0; 
    } 
    for(int i = 1; i <= N; i++){ 
        if(next[i]){ 
            if(!pre[next[i]][0]) 
                pre[next[i]][0] = i; 
            else 
                pre[next[i]][1] = i; 
        }
    } 
    // teraz trzeba zdecydowac dla ziomkow o finalnym wygladzie prev 
    for(int i = 1; i <= N; i++){ 
        if(!pre[i][1]){ 
            prev[i] = pre[i][0]; 
            continue;
        }
        if(next[i] == pre[i][0]){
            prev[i] = pre[i][1];  
            continue; 
        } 
        if(next[i] == pre[i][1]){ 
            prev[i] = pre[i][0];  
            continue; 
        } 
        prev[i] = 0; 
    } 
}

void print_chapter(int id){ 
    char bufor[4];  
    sprintf(bufor, "%03d", id); 
    char nazwa[] = "chapt000.txt";
    for(int i = 0; i < 3; i++) 
        nazwa[i+5] = bufor[i]; 
    FILE *wczyt = fopen(nazwa, "r"); 
    if(wczyt == NULL){ 
        fprintf(stderr, "Blad odczytu zadanego rozdzialu\n"); 
        return;
    }  
    int val; 
    while((val = fgetc(wczyt)) != EOF) 
        putchar((char)val); 
    fclose(wczyt);  
}

void run(int pocz){ 
    fprintf(stderr, "Jestes w przegladarce rozdzialow ksiazki, mozesz otworzyc dowolny dostepny rozdzial za pomoca komendy: \nopen [numer rozdzialu]\n mozesz w 'zwyklej' kolejnosci otworzyc nastepny/poprzedni rozdzial komendami: \nnext \nprev \n oraz w nastepny/poprzendni rozdzial w kolejnosci zdefiniowanej w pliku config.bin: \nnext_hop \nprev_hop \n zakonczenie programu: \nquit \n\n");
    int aktuid = pocz;  
    char komenda[100];  
    bool done = 1; int c; int liczba; 
    while(1){  
        if(done){
            print_chapter(aktuid); 
            putchar('\n'); 
        }  
         done = 0; 
        if (scanf("%s", komenda) != 1) {
            // Blad wczytywania polecenia
            fprintf(stderr, "Blad wczytywania polecenia\n"); 
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        if (strcmp(komenda, "next") == 0) { 
            // zwykly nastepnik
            if(aktuid >= last){ 
                fprintf(stderr, "Brak dostepu do nastepnego rozdzialu\n"); 
                continue;
            } 
            else 
            aktuid++; 
            done = 1; 
            continue; 
        }
        if (strcmp(komenda, "prev") == 0) {
            // zwykly poprzednik
            if(aktuid == 1 || aktuid > last+1){ 
                fprintf(stderr, "Brak dostepu do poprzedniego rozdzialu\n"); 
                continue;; 
            } 
            else 
            aktuid--; 
            done = 1; 
            continue;
        }  
        if (strcmp(komenda, "next_hop") == 0) { 
            // nastepnik z config 
            if(next[aktuid] == 0){ 
                fprintf(stderr, "Brak dostepu do nastepnego rozdzialu\n"); 
                continue;
            } 
            else 
            aktuid = next[aktuid]; 
            done = 1; 
            continue; 
        }
        if (strcmp(komenda, "prev_hop") == 0) {
            // poprzednik z hop 
            if(prev[aktuid] == 0){ 
                fprintf(stderr, "Brak dostepu do poprzedniego rozdzialu\n"); 
                continue;; 
            } 
            else 
            aktuid = prev[aktuid]; 
            done = 1; 
            continue;
        }  
        if (strcmp(komenda, "open") == 0) {
            if (scanf("%d", &liczba) != 1) {
                while ((c = getchar()) != '\n' && c != EOF);
                fprintf(stderr, "Blad wczytywania numeru rozdzialu\n");
                continue;
            } 
            if(liczba <= 0 || liczba > N){ 
                fprintf(stderr, "Niewlasciwy numer rozdzialu\n");
                continue;
            } 
            print_chapter(liczba);  
            aktuid = liczba; 
            putchar('\n');   
            continue;
        } 
        if(strcmp(komenda, "quit") == 0) {
            fprintf(stderr, "Zakonczenie dzialania programu\n"); 
            exit(0); 
        } 
        else 
        { 
            fprintf(stderr, "Wczytano nieznana komemde\n");  
            continue;
        }
    }
}
int main(int argc, char* argv[]){   
    if(argc > 3){ 
        fprintf(stderr, "Zbyt wiele argumentow wywolania\n"); 
        return 1; 
    }
    if(argc == 1){ 
        process_config();
        run(1); 
    } 
    if(argc == 2){ 
        if(strcmp(argv[1], "-hopscotch") != 0){ 
            fprintf(stderr, "Nieprawidlowy argument wywolania\n"); 
            return 1; 
        }
        process_config(); 
        run(start); 
    }  
    if(argc == 3){
        process_config();  
        if(strcmp(argv[1], "-chapter") != 0){ 
            fprintf(stderr, "Nieprawidlowy argument wywolania\n"); 
            return 1; 
        } 
        int liczba = atoi(argv[2]);  
        if(liczba == 0){ 
            fprintf(stderr, "Nieprawidlowa postac numeru rozdzialu\n"); 
            return 1; 
        } 
        if(liczba <1 || liczba > N){ 
            fprintf(stderr, "Nieprawidlowa wartosc numeru rozdzialu\n"); 
            return 1; 
        }  
        run( liczba); 
    }
    exit(0); 
}