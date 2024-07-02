#include <stdio.h> 
#include <stdint.h>   
#include <inttypes.h> 

uint32_t puzzle3(uint32_t n, uint32_t d); 

uint32_t puzzle3_bad(uint64_t n, uint64_t d){ // rdi, rsi 
    // zerujemy 
    n = n & UINT32_MAX;
    d <<= 32; 
    //uint32_t edx = 32; // rdx 
    uint32_t ecx = 0x80000000; //(INT_MIN) 100... 0
    uint32_t res = 0; // eax, interesuje nas tylko dolna polowa ze wzgledu na typ wynikowy funkcji 
    for(int edx = 32; edx; edx--){
        n = n+n;  
        uint64_t r8 = n - d;  
        if( r8 < ( (uint64_t)1 << 63) ){ // r8 >= 0 
            res |= ecx;  
            n = r8; 
        } 
        ecx >>= 1; ecx &= 0x7FFFFFFF; 
    } 
    return res; 
}

uint32_t puzzle3_glupio(uint64_t n, uint64_t d){ // rdi, rsi 
    // zerujemy 
    n = n & UINT32_MAX; 
    d  = (d <<= 32);  
    uint32_t edx = 32; // rdx 
    uint32_t ecx = 0x80000000; //(INT_MIN)
    uint32_t res = 0; // eax, interesuje nas tylko dolna polowa ze wzgledu na typ wynikowy funkcji 
    L3: 
        n = n+n; // rdi 
        uint64_t r8 = n; 
        r8 = r8 - d; 
        //printf("d, n, r8: %lu %lu %lu \n", d, n, r8); 
        if( r8 >= ((uint64_t)1 << 63) ) goto L2; 
        res |= ecx;  
        n = r8; 
    L2: 
        ecx >>= 1;
        ecx &= 0x7FFFFFFF;       
        edx -= 1; 
        if(edx != 0) goto L3;  
    return res; 
}


int main(){
    uint32_t a, b;  
    while(1){ 
        scanf("%u%u", &a, &b);   
        printf("%u\n", puzzle3(a, b));
        printf("%u\n", puzzle3_bad(a, b)); 
    } 
}


