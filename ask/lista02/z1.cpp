#include <> 
#include <limits.h>
using namespace std; 

void a_test(int x){ 
    cout << ((x > 0) || (x -1 < 0) ) << endl ; 
 
}
int main(){ 
    a_test(INT_MIN);  
    cout << (INT_MIN -1) << endl;  
    cout << ((INT_MIN - 1 < 0) )<< endl;  
    cout << (INT_MIN > 0) << endl;  
    cout << ((INT_MIN > 0) || (INT_MIN-1 < 0) )  << endl; 
}