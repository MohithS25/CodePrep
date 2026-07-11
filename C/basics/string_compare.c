#include <stdio.h>

int string_compare(const char* a, const char* b){
    while (*a != '\0' && *b != '\0') {
        if (*a != *b) {
            return *a - *b;
        }
        a++;
        b++;
    }

    // Handles cases where one string ends before the other
    return *a - *b;
}

int main(){
    char a[] = "moh";
    char b[] = "moh";
    char c[] = "kau";
    printf("%d", string_compare(c , b));

}