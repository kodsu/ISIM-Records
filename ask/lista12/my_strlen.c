 
#include <stddef.h>
#include <stdio.h> 
inline  size_t  my_strlen(const char *s){ 
    size_t i = 0; 
    while(*(s+i) != '\0') 
        i = i+1; 
    return i; 
}

const char *my_index(const char *s, char v) {
    for (size_t i = 0; i < my_strlen(s); i++)
    if (s[i] == v)
        return &s[i];
    return 0;
} 

int main() {
    const char *str = "Hello, world!";
    char ch = 'o';
    const char *result = my_index(str, ch);

    if (result != NULL) {
        // Wypisanie znalezionego znaku i jego pozycji
        printf("Character '%c' found at position %ld\n", ch, result - str);
    } else {
        // Informacja o braku znaku
        printf("Character '%c' not found\n", ch);
    }

    return 0;
}