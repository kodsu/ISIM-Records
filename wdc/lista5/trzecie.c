#include<stdio.h>   
#include<math.h> 
#include <stdlib.h>
#include<stdbool.h>  
#include<ctype.h>  
#include<assert.h>
typedef long long ll; 
 

int d, n, m; 
ll potega(ll a, ll b){ // zwraca a ^ b
    ll res = 1; 
    for(int i = 0; i < b; i++) 
        res *= a; 
    return res; 
}

int pv[31];  
char c[13]; 
void buildp3(){ 
    for(ll i = 0; i < 13; i++) 
        pv[i] = potega(3, i); 
}
char znak(int x, int y, int p){   
    if(x==0&&y==0)
        return c[0];
    p--;
    if(x/pv[p]==1&&y/pv[p]==1)
        return c[p+1];
    return znak(x%pv[p],y%pv[p],p);
}

void read(){ 
    scanf("%d", &d);  
    char znak;    
    znak = getchar();  
    while(isspace(znak)) 
        znak = getchar(); 
    for(int i = 0; i <= d; i++){  
        c[i] = znak; 
        znak = getchar(); 
    }
    scanf("%d %d", &n, &m);   
    //printf("%d %d\n", n, m); 
}

void spiralka(){ 
    ll as = 0, bs = 0;   
    char acc = znak(as, bs, d); ll ile = 1; char aktu; 
    ll lim = potega(3,d)-1;  
    ll upmade = 0, downmade = lim +1, 
    leftmade = -1, rightmade = lim+1; 
    //printf("roz %d\n", lim); 
    for(ll i =lim ; i> 0; i--){ 
        // prawo i-1
        //dol i-1
        // lewo i-1 
        // dol i-2 
        while(bs +1 < rightmade){ 
            bs+=1; 
            aktu = znak(as, bs, d);  
            if(aktu == acc){ 
                ile++; 
            } 
            else{ 
                if(ile != 0)
                    printf("%lld %c ",ile, acc); 
                acc = aktu; 
                ile = 1; 
            }     
            
        } 
        rightmade = bs;  
        while(as+1 < downmade){
            as+=1; 
            aktu = znak(as, bs, d);  
            if(aktu == acc){ 
                ile++; 
            } 
            else{ 
                if(ile != 0)
                    printf("%lld %c ",ile, acc); 
                acc = aktu; 
                ile = 1; 
            }    
        }  
        downmade = as; 
        while(leftmade < bs -1){
            bs-=1; 
            aktu = znak(as, bs, d);  
            if(aktu == acc){ 
                ile++; 
            } 
            else{ 
                if(ile != 0)
                    printf("%lld %c ",ile, acc); 
                acc = aktu; 
                ile = 1; 
            }    
        }   
        leftmade = bs;  
        while(as-1 > upmade){ 
            as-=1; 
            aktu = znak(as, bs, d);  
            if(aktu == acc){ 
                ile++; 
            } 
            else{ 
                if(ile != 0)
                    printf("%lld %c ",ile, acc); 
                acc = aktu; 
                ile = 1; 
            }    
        }  
        upmade = as; 
    }  
    if(ile > 0)
        printf("%lld %c ",ile, acc);
}
 
//int tab[1000][1000];  

void jazda(){ 
    if(n == 0 ){ 
        spiralka(); 
        return; 
    } 
    ll lim = potega(3, d); 
    ll as = 0, bs = 0;    
    char acc = znak(0, 0, d); int ile = 1;     
    char aktu = 0;   
    //int licz = 1; 
    //tab[as][bs] = licz++; 
    for(int i = 0; i < lim; i++){   
        if(i){ 
            as = (as+1)%lim; bs = (bs)%lim;
            //tab[as][bs] = licz++;  
            aktu = znak(as, bs, d);  
            if(aktu == acc){ 
                ile++; 
            } 
            else{ 
                if(ile != 0)
                    printf("%d %c ",ile, acc); 
                acc = aktu; 
                ile = 1; 
            }    
        }
        for(int j = 1; j < lim; j++){
            as = (as+m)%lim; bs =(bs+n)%lim;  
            aktu = znak(as, bs, d);
            //tab[as][bs] = licz++; 
            if(aktu == acc){ 
                ile++; 
            } 
            else{  
                if(ile != 0)
                    printf("%d %c ",ile, acc); 
                acc = aktu; 
                ile = 1;     
            } 
        } 
    }  
    if(ile > 0)
        printf("%d %c ",ile, acc);      
    //printf("\n"); 
    //for(int i = 0;  i < lim; i++){ 
    //   for(int j = 0; j < lim; j++) 
    //       printf("%d ", tab[i][j]); 
    //   printf("\n"); 
    //}
}
int main(){ 
    read();   
    buildp3(); 
    //printf("%c \n", znak(1,1)); 
    //printf("%c \n", znak(9, 9));
    //printf("%c \n", znak(12, 12));
    //printf("%c \n", znak(13, 13));   
    jazda(); 
}