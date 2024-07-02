#include<stdio.h> 
typedef long long ll; 

int main(void){ 
    ll x, buf, cnt;  
    scanf("%lld", &x); 
    ll max_result = 0, max_mn = 0, max_dx = 0, value; 
    for(ll mn = 1; mn <= 10; mn++){ 
        buf = x * mn; 
        for(ll dx = 0; dx <= 1000; dx++){ 
            buf = x * mn + dx; 
            cnt  = 0;  

            while(buf){ 
                if(buf%10 == 7) 
                    cnt++; 
                buf /= 10; 
            } 
            if(cnt > max_result){ 
                max_result = cnt;  
                value = x*mn + dx; 
                max_mn = mn; 
                max_dx = dx; 
            }
        }
    } 
    printf("Najwiecej siodemek - %lld zawiera liczba %lld powstala z pomnozenia x przez %lld a nastepnie dodania %lld",max_result, value, max_mn, max_dx); 
}