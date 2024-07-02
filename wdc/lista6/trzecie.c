#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 

typedef struct{ll st; ll nd;} pair; 

#define B 262144 
#define MTS 524411 

ll tree[MTS]; 

ll sum_on_seg(int a, int b){ 
    a += B, b += B; 
    ll res = 0; 
    while(a < b){ 
         if(a&1){ res += tree[a]; a++; } 
         if(!(b&1)){ res += tree[b]; b--; }
         a >>=1, b >>= 1; 
    } 
    if(a == b) 
        res += tree[a]; 
    return res; 
} 

void setval(int pos, ll val){ 
    pos += B; 
    tree[pos] = val; 
    pos >>= 1; 
    while(pos){ 
        tree[pos] = tree[(pos<<1)] + tree[(pos<<1)+1];  
        pos >>=1; 
    } 
}
int main(){   
    //printf("%ld %ld\n", strlen(argv[1]), strlen(argv[2]));   
    //printf("%d\n", argc); 
    int n, m; 
    scanf("%d %d", &n, &m);  
   //printf("%d %d\n", n, m); 
   for(int i = 0; i < n; i++){ 
       scanf("%lld", &tree[B+i]); 
   } 
   // for(int i = 0; i < m; i++){ 
   //     printf("%lld ", tree[B+i]); 
   // }  
   // printf("\n"); 
    for(int i = B+m; i < (B<<1); i++) 
        tree[i] = 0; 
    for(int i = B-1; i; i--) 
        tree[i] = tree[(i<<1)] + tree[(i<<1)+1]; 
    char type; int a, b;  
    for(int i = 0; i < m; i++){  
        //type = 0; 
        //while(type != 'U' || type != 'Q')
        scanf("\n%c", &type);  
        //printf("%c\n", type); 
        if(type == 'Q'){ 
            scanf("%d %d", &a, &b);  
          //  printf("%d %d\n", a, b); 
            printf("%lld\n", sum_on_seg(a, b)); 
        } 
        if(type == 'U'){ 
            scanf("%d %d", &a, &b); 
          //  printf("%d %d\n", a, b); 
            setval(a, b); 
        }
    }
}