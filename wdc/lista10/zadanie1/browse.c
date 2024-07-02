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
char plik_wejsciowy[] = "article"; 
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

int next[256]; int N, last, start; 
int prev[256]; 
void process_config(){ 
    FILE *plik; 
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
    // for(int i = 1; i <= N; i++){ 
    //     printf("%d ", next[i]); 
    // } 
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
    // for(int i = 1; i <= N; i++){ 
    //     printf("%d %d %d\n", i, next[i], prev[i]); 
    // }
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
void run_simple(){ 
    // obslugujemy next i previous 
    fprintf(stderr, "Jestes w generycznym trybie, mozesz po kolei przelaczac sie pomiedzy rozdzialami komendami:\nprev\nnext\n\n");   
    int aktuid = 1;  
    char komenda[20];  
    bool done = 1; 
    int c;  
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
            if(aktuid == last){ 
                fprintf(stderr, "Brak dostepu do nastepnego rozdzialu\n"); 
                continue;
            } 
            else 
            aktuid++; 
            done = 1; 
            continue; 
        }
        else if (strcmp(komenda, "prev") == 0) {
            // Wykonaj operację dla polecenia "prev"
            if(aktuid == 1){ 
                fprintf(stderr, "Brak dostepu do poprzedniego rozdzialu\n"); 
                continue;; 
            } 
            else 
            aktuid--; 
            done = 1; 
            continue;
        }  
        else 
        { 
            fprintf(stderr, "Wczytano nieznana komemde\n");  
            continue;
        }
    }

}

void run_hopscotch(){ 
    fprintf(stderr, "Jestes w trybie przygody, mozesz przegladac rozdzialy w nieznanej dla Ciebie kolejnosci zdefiniowanej w config.bin za pomoca komend:\nprev\nnext\n\n"); 
    int aktuid = start;  
    char komenda[100];  
    bool done = 1; int c; 
    while(1){  
        if(done){
            print_chapter(aktuid); 
            putchar('\n'); 
        }  
        done = 0; 
        if (scanf("%s", komenda) != 1) {
            // Blad wczytywania polecenia
            while ((c = getchar()) != '\n' && c != EOF);
            fprintf(stderr, "Blad wczytywania polecenia\n");
            continue;
        }
        if (strcmp(komenda, "next") == 0) {
            if(next[aktuid] == 0){ 
                fprintf(stderr, "Brak dostepu do nastepnego rozdzialu\n"); 
                continue;
            } 
            else 
            aktuid = next[aktuid]; 
            done = 1; 
            continue; 
        }
        else if (strcmp(komenda, "prev") == 0) {
            // Wykonaj operację dla polecenia "prev"
            if(prev[aktuid] == 0){ 
                fprintf(stderr, "Brak dostepu do poprzedniego rozdzialu\n"); 
                continue;; 
            } 
            else 
            aktuid = prev[aktuid]; 
            done = 1; 
            continue;
        }  
        else 
        { 
            fprintf(stderr, "Wczytano nieznana komemde\n");  
            continue;
        }
    }
} 

void run_manual(int val){ 
    fprintf(stderr, "Jestes w trybie manualnym, mozesz otworzyc dowolny dostepny rozdzial za pomoca komendy: \n open [numer rozdzialu]\n\n");
    print_chapter(val); 
    char komenda[100];  
    int liczba; int c; 
    while(1){   
        if (scanf("%s", komenda) != 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            fprintf(stderr, "Blad wczytywania polecenia\n");
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
            putchar('\n');  
        } 
        else 
        { 
            fprintf(stderr, "Wczytano nieznane polecenie\n");
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
        run_simple(); 
    } 
    if(argc == 2){ 
        if(strcmp(argv[1], "-hopscotch") != 0){ 
            fprintf(stderr, "Nieprawidlowy argument wywolania\n"); 
            return 1; 
        }
        process_config(); 
        run_hopscotch(); 
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
        run_manual( liczba); 
    }
    exit(0); 
   
}