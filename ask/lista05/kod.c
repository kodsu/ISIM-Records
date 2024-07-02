#include <stdio.h> 
#include <stdint.h>  

int puzzle_glupio(long x, unsigned n){//esi, edi n <= 64   
    int res; 
    if(n&n == 0) goto Kon;  
    int a = 0, b = 0; // edx, eax
    LOOP: 
        int tym = x; // ecx
        tym = tym & 1; 
        b += tym; 
        x >>= 1; 
        a++; 
        // esi - edx 
        if(n-a) goto LOOP; 
    Kon: 
        b = x; 
        return b;  
}

int puzzle_madrze(long x, unsigned n){ // liczba zapalonych n najmniej znaczacych bitow x 
    if(n == 0) return 0; 
    /*int a =0, b = 0;
    while(x -a){ 
        b += n &1;  
        n = (n >> 1);
        a++;  
    }
    return b; */ 
    int b = 0;
    for(int a = 0; n-a; a++){ 
        b += x&1; 
        x = (x >> 1); 
    }  
    return b; 
}


long puzzle2(char*s, char*d){ // rdi, rsi 
    long res = s; // rax  
    long r9; long r8, dx;  
    char cl; // cl
    L3:  
        r9 = *((long*)(uintptr_t)res); //  r8b
        r8 = res + 1; // %r8 
        dx = d; 
    L2: 
        cl = *((long*)(uintptr_t)dx);; 
        dx++; 
        if(cl == 0) goto L4; 
        if((char)r9 - cl) goto L2; 
        res = r8; 
        goto L3; 
    L4: 
        res -= (unsigned)s; 
        return res;  

    return 0; 

}  
// co to robi? 
long puzzle2(char*s, char*d){ // rdi, rsi 
    //long res = s; // rax  
    long r9; long r8, dx;  
    char cl; // cl 
    // Ladnie: 
    char znak; char aktu; 
    for(char* res = s; 1; res++){  // numer pierwszego znaku w s, który nie występuje w d 
        znak = *(res); 
        for(char* pt = d;  pt == d || (aktu != znak); pt++){ 
            aktu = *pt;
            if(aktu == 0){ 
                return res -s;  
            } 
        }

    } 
    // petlowo - srednio
    long res; 
    while(1){
        r9 = *((long*)(uintptr_t)res); //  r8b
        r8 = res + 1; // %r8 
        dx = d; 
        do{
            cl = *((long*)(uintptr_t)dx);; 
            dx++; 
            if(cl == 0){ // L4 
                res -= (unsigned)s; 
                return res; // tutaj jest jedyne zakonczenie 
            }  
        } while((char)r9 - cl);   
        res = r8;   
    }  
    return 0; 
}  

uint32_t puzzle3_glupio(uint64_t n, uint64_t d){ // rdi, rsi 
    // zerujemy 
    n = n & UINT32_MAX;
    d <<= 32; 
    uint32_t edx = 32; // rdx 
    uint32_t ecx = 0x80000000; //(INT_MIN)
    uint32_t res = 0; // eax, interesuje nas tylko dolna polowa ze wzgledu na typ wynikowy funkcji 
    L3: 
        n += n; // rdi 
        uint64_t r8 = n; 
        r8 -= d; 
        if((1 << 63) & r8) goto L2; 
        res |= ecx;  
        n = r8; 
    L2: 
        ecx >>= 1; 
        edx -= 1; 
        if(edx) goto L3; 
        return res; 
}


uint32_t puzzle3(uint64_t n, uint64_t d){ // rdi, rsi 
    // zerujemy 
    n = n & UINT32_MAX;
    d <<= 32; 
    //uint32_t edx = 32; // rdx 
    uint32_t ecx = 0x80000000; //(INT_MIN) 100... 0
    uint32_t res = 0; // eax, interesuje nas tylko dolna polowa ze wzgledu na typ wynikowy funkcji 
    for(int edx = 32; edx; edx--){
        n <<= 1; 
        uint64_t r8 = n - d;  
        if(( (uint64_t)1 << 63) & r8 == 0){ // r8 >= 0 
            res |= ecx;  
            n = r8; 
        } 
        // przesuniecie takie sus
        ecx >>= 1; ecx &= (1 << 31)-1; 
    } 
    return res; 
}



int main(){ 
    return 0; 
}


