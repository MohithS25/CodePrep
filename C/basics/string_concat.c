#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* string_concat(const char* a, const char* b){
    int lena = strlen(a);
    int lenb = strlen(b);

    char* str =  malloc (lena + lenb + 1);
    
    int i = 0;
    while(a[i] != '\0'){
        str[i] = a[i];
        i++;
    }

    int j = 0;
    while(b[j] != '\0'){
        str[i] = b[j];
        j++;
        i++;
    }

    str[i] = '\0';

    return str;
}


int main(){
    char* a = "moh";
    char* b = "kau";
    char* str = string_concat(a, b);
    printf("%s", str);
    //free(str);

}