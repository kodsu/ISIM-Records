#include<stdio.h>  
#include<string.h> 
#include<ctype.h>  
#include<stdbool.h> 
#include<stdlib.h>
#include<time.h>
#include<assert.h>
typedef  long long ll; 


struct node{ 
    struct node* prev; ll val; struct node* next; 
};  

struct list{ 
    struct node* begin; struct node* end; 
    ll sum; //int len; 
};  

void memory_error(){  
    assert(1 == 0); 
    fprintf(stderr, "Błąd alokacji pamięci.\n");
    exit(1);  // Zwracamy 1, aby oznaczyć błąd
}

void size_error(){  
    assert(1 == 0); 
    fprintf(stderr, "Błąd rozmiaru/indeksowania listy\n");
    exit(2);  // Zwracamy 1, aby oznaczyć błąd
}

struct node* new_Node(){ 
    struct node* ans = (struct node*)malloc(sizeof(struct node)); 
    if(ans == NULL) 
        memory_error(); 
    return ans; 
}
int M, Q; 
struct list* magazyn; 
void read_data(){   
    int buf; 
    struct node* stary; struct node* nowy; 
    magazyn = (struct list*)malloc((M+1)*sizeof(struct list)); 
    if(magazyn == NULL){ 
        memory_error(); 
    } 
    int t; 
    for(int i = 1; i <= M; i++){ 
        if(scanf("%d", &t) != 1) 
            assert(1 == 0); 
        magazyn[i].begin = new_Node();   
        magazyn[i].sum = 0;  
        //magazyn[i].len = t; 
        // tutaj dodajemy begin node
        stary = magazyn[i].begin;  
        magazyn[i].begin->prev = NULL; 
        magazyn[i].begin->val = 0;   
         
        // stary ma pozostac wskaznikiem na ostatnia komorke listy
        for(int j = 0; j < t; j++){ 
            nowy = new_Node(); 
            stary->next= nowy; 
            nowy->prev = stary; 
            if(scanf("%d", &buf) != 1)  
                assert(1 == 0); 
            nowy->val = buf;  
            magazyn[i].sum += nowy->val; 
            stary = nowy; 
        } 
        // tutaj dodajemy endnode 
        nowy = new_Node(); 
        stary->next = nowy; 
        nowy->prev = stary;  
        nowy->val = 0; 
        magazyn[i].end = nowy; 
        nowy->next = NULL; 
    } 
    // i tutaj powinna byc zainicjowana tablica list
} 

void wypisz_liste(struct list* A){ 
    struct node* buf = A->begin; 
    buf = buf->next; 
    while(1){ 
        if(buf->next != NULL){ 
            printf("%lld ", buf->val);  
            buf = buf->next; 
        } 
        else  
            break; 
    } 
    printf("\n"); 
    return; 
} 
 
void remove_r(struct node* A){ 
    if(A->next == NULL){
        free(A); 
        return; 
    } 
    remove_r(A->next); 
    free(A); 
}

void remove_list(struct list* A){ 
    remove_r(A->begin); 
} 

void remove_all(){ 
    for(int i = 1; i <= M; i++){ 
        remove_list(&magazyn[i]); 
    }
    free(magazyn); 
}
 
void kontrola(){ 
    for(int i = 1; i <= M; i++){ 
        printf("%lld ", magazyn[i].sum); 
        //wypisz_liste(&magazyn[i]); 
    } 
    printf("\n");  
} 

ll aktusum = 0; struct node* ans; 
struct node* element(struct list* L, int id, bool wlacz){   
    aktusum = 0; 
    if(id >= 0){  
        ans = L->begin; 
        while(id){ 
            id--;  
            aktusum += ans->val; 
            ans = ans->next;  
            if(ans->next == NULL){ 
                size_error(); 
            }
        }   
        if(wlacz) 
            aktusum += ans->val; 
        return ans; 

    } 
    else {  
       ans = L->end;  
       while(id < 0){ 
            aktusum += ans->val; 
            id++; 
            ans = ans->prev; 
            if(ans->prev == NULL) 
                size_error(); 
       }  
       if(wlacz) 
            aktusum += ans->val; 
       return ans; 
    } 
    // memory_error(); 
    // return NULL; 
} 

struct node* poprz; struct node* r_ind; struct node* l_ind;  
struct node* nast; // = r_ind->next; 

void pref_elem(struct list* L, int l, int r){ 
    aktusum = L->sum; 
    ans = L->begin; 
    for(int id = 1; id <= r; id++){  
        if(ans == NULL) 
            size_error(); 
        ans = ans->next; 
        if(l <= id && id <= r) 
            aktusum -= ans->val; 
        if(id == l)     
            l_ind = ans; 
        if(id == r) 
            r_ind = ans; 
    }
} 

void suf_elem(struct list* L, int l, int r){ 
    aktusum = L->sum; 
    ans = L->end; 
    for(int id = -1; id >= l; id--){  
        if(ans == NULL) 
            size_error(); 
        ans = ans->prev; 
        if(l <= id && id <= r) 
            aktusum -= ans->val; 
        if(id == l) 
            l_ind = ans; 
        if(id == r) 
            r_ind = ans; 
    }
}

void realokacja(struct list* origin, struct list* destiny, int l, int r){  
    // trzeba jeszcze zadbac o modyfikacje sumy  
    // if(l < 0 && r < 0){ 
    // if(l < -1) l++; 
    // if(r < -1) r++; }
    ll nowasuma = 0;   
    if(l > 0 && r < 0){  
        l_ind = element(origin, l, 0);   
        nowasuma += aktusum; 
        r_ind = element(origin, r, 0);   
        nowasuma += aktusum; // nie moga najsc na siebie, jest dobrze 
    } 
    if(l < 0 && r > 0){   
        assert(1 == 0); 
    }
    if(l > 0 && r > 0){ 
        pref_elem(origin, l, r); 
        nowasuma = aktusum;  
        //origin->len -= (r-l+1);  
        //destiny->len += (r-l+1); 
    }  
    if(l < 0 && r < 0){ 
        suf_elem(origin, l, r); 
        nowasuma = aktusum;  // na przykład -5 -3
        //origin->len -= ((r - l) +1);  
        //destiny->len += ((r-l)+1); 
    }  
    poprz = l_ind->prev;  
    nast = r_ind->next; 
    poprz->next = nast; 
    nast->prev = poprz; // stara lista jest sklejona 
    // tutaj trzeba dokleic wspomniandy przedzial do nowej listy 
    poprz = destiny->end->prev; 
    poprz->next = l_ind; 
    l_ind->prev = poprz;  
    r_ind->next = destiny->end; 
    destiny->end->prev = r_ind;  
    destiny->sum += (origin->sum - nowasuma); 
    origin->sum = nowasuma; 
}

int main(){    
    
    if(scanf("%d%d", &M, &Q) != 2)  
        assert(1 == 0); 
    read_data();  
    // tutaj wlasciwa czesc tego co chcemy robic  
    char type;
    int from, to, l, r;  
    for(int i = 0; i < Q; i++){  
        type = 'A';  
        while(type != 'K' && type != 'R') 
            type = getchar(); 
        //printf("%c\n", type); 
        if(type == 'K'){ 
            kontrola(); 
        } 
        if(type == 'R'){ 
            if(scanf("%d %d %d %d\n",&from, &to, &l, &r) != 4) 
                assert(1 == 0);  
            realokacja(&magazyn[from], &magazyn[to], l, r); 
        }
    }
    //remove_all(); 
}   