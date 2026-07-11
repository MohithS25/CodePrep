#include <stdio.h>

int string_length(const char* s){
    int length = 0;
    while(s[length] != '\0'){
        length++;
    }

    return length;
}

void string_copy(char* dst, const char* src){
    while (*src != '\0') {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
}

int main(){
    const char* original = "Hello, World!";
    char copy[50];

    string_copy(copy, original);

    printf("Original string: %s\n", original);
    printf("Copied string: %s\n", copy);
    printf("Length of original string: %d\n", string_length(original));

    return 0;
}
