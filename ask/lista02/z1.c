#include <stdio.h> 
#include <limits.h> 
void a_test(int x){ 
    //printf("%d\n",  (x-1)  ); 
    printf("%d\n",  ((x - 1 < 0) ));   
    printf("%d\n",  (x> 0) ); 
    printf("%d\n", ((x > 0) || ( x - 1 < 0) ) );  
    printf("koniec wywolania\n"); 
} 
void test_c(){ 
    int x = 65436; 
    printf("%d\n", x*x); 
}
int main(){   

    test_c(); 
    /*
    a_test(INT_MIN);  
    printf("%d\n",  (INT_MIN -1)  ); 
    printf("%d\n",  ((INT_MIN - 1 < 0) ));   
    printf("%d\n",  (INT_MIN > 0) ); 
    printf("%d\n" ,  ((INT_MIN > 0) || (INT_MIN-1 < 0) )  ); */ 

}