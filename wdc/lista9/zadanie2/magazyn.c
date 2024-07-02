#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 




struct node{ 
    struct node* next; struct node* prev; 
    ll value;  
}; 

struct node* new_node(){ 
    struct node* nowy_node = (struct node*)malloc(sizeof(struct node));
    if (nowy_node == NULL) {
        assert(1 == 3); 
    }
    return nowy_node;
}
struct list{ 
    struct node* begin; struct node* end;  
    ll sum; 
}; 

bool empty(struct list* L){ 
    return (L->begin == NULL && L->end == NULL); 
}

struct node* pref_element(struct list* L, int k, ll* sum){ // modyfikuje wartosc 
    struct node* ans = L->begin; 
    *sum = ans->value; 
    while(--k){ 
        if(ans->next == NULL) 
            assert(1 == 2); 
        ans = ans->next;  
        *sum+= ans->value; 
    }
    return ans; 
}

struct node* suf_element(struct list* L, int k, ll* sum){ // modyfikuje wartosc 
    struct node* ans = L->end;  
    assert(k > 0); 
    *sum = ans->value; 
    while(--k){ 
        if(ans->prev == NULL) 
            assert(1 == 2); 
        ans = ans->prev;  
        *sum += (ans->value); 
    }
    return ans; 
}

struct node MEM[3000005];  
struct list magazyn[100005]; 
int m, q; int ind = 0; 

void read_data(){ 
    int n;  
    struct node* last; 
    for(int i = 1; i <= m; i++){ 
        if(scanf("%d", &n) != 1)  
            exit(0); 
            //assert(2 == 6);   
        //printf("%d\n", n); 
        magazyn[i].sum = 0;

        if(n == 0){ 
            magazyn[i].begin = NULL; 
            magazyn[i].end = NULL;  
            continue; 
        }
        magazyn[i].begin = &(MEM[ind++]);  
        last = magazyn[i].begin; 
        if(scanf("%lld", &(last->value)) != 1) 
            assert(2 == 7);  
        magazyn[i].sum += last->value; 
        //printf("%lld ", magazyn[i].sum);
        last->prev = NULL; 
        for(int j = 2; j <=n; j++){ 
            last->next =&(MEM[ind]); 
            MEM[ind].prev = last; 
            if(scanf("%lld", &(MEM[ind].value) ) != 1)  
                exit(0); 
                //assert(2 == 7);
            last = last->next;   
            magazyn[i].sum += MEM[ind].value;  
            //printf("%lld ", MEM[ind].value);
            ind++;
        }
        last->next = NULL; 
        magazyn[i].end = last;  
        //printf("\n"); 
    }
}

void wypisz_liste(struct list* L){ 
    struct  node* m = L->begin; 
    while(m != NULL){ 
        printf("%lld ", m->value);  
        m = m->next; 
    } 
    printf("\n"); 
    
}

void kontrola(){ 
    for(int i = 1; i <= m; i++){ 
        printf("%lld ", magazyn[i].sum);  
        //wypisz_liste(&magazyn[i]); 

    } 
    printf("\n"); 
}

void realokacja(int from, int to, int a, int b){ 
    ll diff = 0; ll buf=0; 
    struct node* left = NULL; struct node* right = NULL; 
    if(a > 0 && b > 0){ 
        left = pref_element(&magazyn[from], a, &buf);  
        diff -= buf; 
        diff += left->value;  
        right = pref_element(&magazyn[from], b, &buf); 
        diff += buf; 
    }
    if(a < 0 && b < 0){ 
        left = suf_element(&magazyn[from], -a, &buf);  
        diff += buf;   
        right = suf_element(&magazyn[from], -b, &buf); 
        diff -= buf;
        diff += right->value; 
    }  
    if(a > 0 && b < 0){ 
        diff = magazyn[from].sum; 
        left = pref_element(&magazyn[from], a,&buf); 
        diff -= buf; diff += left->value; 
        right = suf_element(&magazyn[from], -b, &buf); 
        diff -= buf; diff += right->value; 
    }
    //assert(!(a <0 && b > 0));
    assert(left != NULL && right != NULL);  
    // tutaj przepinamy sobie  
    magazyn[from].sum -= diff; 
    magazyn[to].sum += diff;  
    if((left == magazyn[from].begin && right == magazyn[from].end)||(left->prev == NULL && right->next == NULL)){ 
        magazyn[from].begin = NULL; 
        magazyn[from].end = NULL; 
    }  
    else 
    {  
        assert(!(left->prev == NULL && right->next == NULL)); 
        if(left == magazyn[from].begin){  
            assert(right->next != NULL); 
            magazyn[from].begin = right->next;    
            if(magazyn[from].begin == NULL) 
                magazyn[from].end = NULL; 
            (right->next)->prev = NULL; 
        }
        else{ 
            if(right == magazyn[from].end){  
                assert(left->prev != NULL); 
                magazyn[from].end = left->prev;   
                if(magazyn[from].end == NULL) 
                    magazyn[from].begin = NULL; 
                (left->prev)->next = NULL; 
            } 
            else {  
                assert(right->next != NULL); 
                assert(left->prev != NULL); 
                (left->prev)->next = right->next; 
                (right->next)->prev = left->prev; 
            }
        }
    } 
    assert(!((magazyn[to].begin == NULL && magazyn[to].end != NULL) || (magazyn[to].begin != NULL && magazyn[to].end == NULL))); 
    if(empty(&magazyn[to])){ 
        magazyn[to].begin = left; 
        magazyn[to].end = right;  
        left->prev = NULL; 
        right->next = NULL; 
    } 
    else 
    {   
        assert(magazyn[to].begin != NULL); 
        assert(magazyn[to].end != NULL); 
        magazyn[to].end->next = left;  
        left->prev = magazyn[to].end;  
        right->next = NULL; 
    }
}

int main(){  
    if(scanf("%d %d", &m, &q) != 2)  
        exit(0); 
        //assert(2 == -1);  
    read_data(); 
    exit(0);  
    //kontrola();   
    //printf("\n"); 
    char sign;  
    int from, to, a, b; 
    for(int i = 0; i < q; i++){ 
        if(scanf("%c", &sign) != 1)  
            exit(0); 
            //assert(2 == 3); 
        while(sign != 'K' && sign != 'R'){ 
            if(scanf("%c", &sign)!= 1)  
                exit(0);
                //assert(2 == 4); 
        }

        if(sign == 'K') 
            kontrola(); 
        if(sign == 'R'){ 
            if(scanf("%d%d%d%d", &from, &to, &a, &b) != 4)  
                exit(0);
                //assert(2 == 5); 
            realokacja(from, to, a, b); 
        }

    }
}   