#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef unsigned long long ull; 


void wypisz_najmlosze_bity(int n, ull m){ 
    for(int i = n-1; i > -1; i--){ 
        printf((m & ((ull)1 << i)) ? "1": "0"); 
    }
}

int wczytaj_bitowo(ull *x){ 
    char buf; 
    int valid = (buf= getchar());   
    if(valid == EOF) 
        return EOF;   
    while(isspace(buf)){
        valid = (buf= getchar()); 
        if(valid == EOF)    
            return EOF; 
    }
    bool fir = 0; 
    while(buf == '1' || buf == '0'){ 
        if(!fir){ 
            fir = 1; 
            *x = 0; 
        }
        *x = (*x)<<1; 
        if(buf == '1') 
            *x +=1; 
        valid = (buf = getchar()); 
            if(valid == EOF) 
                return 1; 
    }  
    ungetc(buf, stdin);  
    if(!fir) 
        return EOF; 
    return 1; 
}   

ull los_val(int len){ 
    ull res = 0; 
    for(int i = len-1; i > -1; i--){ 
        res <<= 1;  
        if(rand() &1) 
            res += 1;  
    } 
    return res; 
}  

int los_zakr(int a, int b){  
    assert(a<= b); 
    return (rand()%(b-a+1))+ a; 
}
ull bit_and(ull a, ull b){ 
    return (a&b); 
} 
ull bit_or(ull a, ull b){ 
    return (a|b); 
} 
ull bit_xor(ull a, ull b){ 
    return (a^b); 
} 
ull bit_left_shift(ull a, ull b){ 
    return (a << b); 
} 
ull bit_right_shift(ull a, ull b){ 
    return (a >> b); 
}  
ull (*operatory[5])(ull,ull) = {bit_and, bit_or, bit_xor, bit_left_shift, bit_right_shift};  
const char *nazwa_operator[] = {"&", "||", "^", "<<", ">>"};

int N;  
ull normalize(ull res, int len){ 
    ull clean = 0; 
    for(int i = len-1; i > -1; i--){ 
        clean <<= 1; 
        clean +=1; 
    } 
    return res&clean; 
}

int query(){ 
    int ind = los_zakr(0, 4); 
    ull fir = los_val(N); 
    ull sec;  
    if(ind < 3) 
        sec = los_val(N); 
    else 
        sec = los_zakr(0, N-1);   
    wypisz_najmlosze_bity(N, fir); printf(" %llu ", fir); printf("  <- argument 1\n");  
    wypisz_najmlosze_bity(N, sec); printf(" %llu ", sec); printf("  <- argument 2\n");  
    printf("operacja: %s \n", nazwa_operator[ind]);    
    ull ans; 
    int valid = wczytaj_bitowo(&ans);   
    if(valid != 1){ 
        printf("Nieprawidlowy format odpowiedzi\n"); 
        exit(1); 
    } 
    ull res = normalize(operatory[ind](fir, sec), N);  
    while(ans != res){ 
        printf("Niepoprawna odpowiedz. Sproboj jeszcze raz!\n");  
        valid = wczytaj_bitowo(&ans);   
        if(valid != 1){ 
            printf("Nieprawidlowy format odpowiedzi\n"); 
            exit(1); 
        } 
    } 
    printf("Brawo! Podales dobry wynik.\n"); 
    return 0; 
}

int main(int argc, char *argv[]){  
    if(argc > 2){ 
        printf("Nieprawidlowa liczba arumentow wywoalnia\n"); 
        return 1; 
    }   
    if(argc == 2){
        int amo = atoi(argv[1]); 
        ull example =0; 
        if(amo < 1 || amo > (int)sizeof(example)*__CHAR_BIT__){
            printf("Nieprawidlowy argument wywolania\n"); 
            return 2; 
        } 
        N = amo;  
    } 
    else 
        N = 8; 
    srand(time(NULL));  
    while(1){ 
        query();  
    }
}