#include<stdint.h> 
#include<stdio.h> 
int main() {
    int value = 42;
    int *ptr = &value;

    uintptr_t ptr_value = (uintptr_t)ptr;

    printf("Value of the pointer: %lu\n", ptr_value);

    return 0;
}