#include <stdio.h>



int main(){

    char* a = "hello";
    a[0] = 'H';
    printf("%s", a);

    char b[] = "hello";
    b[0] = 'H';
    printf("%s", b);
}