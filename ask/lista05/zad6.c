#include<inttypes.h> 
#include <stdio.h>
#include <assert.h>

long puzzle4(long*a, long v, uint64_t s, uint64_t e){// rdi, rsi, rdx, rcx
    uint64_t ind = e-s; 
    ind >>= 1; 
    ind += s; // ind = (e-s)/2 + s;
    if(s > e) return -1; 
    long val = *(a + ind); 
    if(val == v) return ind; 
    if(v > val){ 
        e = ind -1; 
        return puzzle4(a, v, s, e);
    }  
    s = ind+1;
    return puzzle4(a, v, s, e);
} 

    // Works correctly with arrays of size 1
void test_array_size_1() {
    long arr[] = {1};
    long v = 1;
    uint64_t s = 0;
    uint64_t e = sizeof(arr)/sizeof(arr[0]) ;
    long result = puzzle4(arr, v, s, e);
    assert(result == 0);
}
    // Works correctly with arrays of size 2
void test_array_size_2() {
    long arr[] = {1, 2};
    long v = 2;
    uint64_t s = 0;
    uint64_t e = sizeof(arr)/sizeof(arr[0]);
    long result = puzzle4(arr, v, s, e);
    assert(result == 1);
}
    // Works correctly with arrays of size 1000
void test_array_size_1000() {
    long arr[1000];
    for (int i = 0; i < 1000; i++) {
        arr[i] = i;
    }
    long v = 500;
    uint64_t s = 0;
    uint64_t e = sizeof(arr)/sizeof(arr[0]);
    long result = puzzle4(arr, v, s, e);
    assert(result == 500);
}
    // Works correctly with the largest possible array
void test_largest_possible_array() {
    long arr[1000000];
    for (int i = 0; i < 1000000; i++) {
        arr[i] = i;
    }
    long v = 500000;
    uint64_t s = 1;
    uint64_t e = sizeof(arr)/sizeof(arr[0]);
    long result = puzzle4(arr, v, s, e);
    assert(result == 500000);
}
void test_found_first_element() {
    long arr[] = {1, 2, 3, 4, 5};
    long v = 1;
    uint64_t s = 0;
    uint64_t e = sizeof(arr)/sizeof(arr[0]);
    long result = puzzle4(arr, v, s, e);
    assert(result == 0);
}

int main(){  
    test_array_size_1();  
    test_array_size_2(); 
    test_array_size_1000();  
    test_largest_possible_array();  
    test_found_first_element(); 
} 

  