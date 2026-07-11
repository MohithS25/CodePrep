/* Exercise 3. Write int count_words(const char* s) that counts words in a string where words are separated by spaces (assume no leading/trailing spaces, single spaces only). 
Example: "hello world foo" → 3. Do not use strtok.
*/

#include <stdio.h>
#include <stdlib.h>

int count_words(const char* s){
    if(*s == '\0'){
        return 0;
    }
    int count = 1;
    while(*s != '\0'){
        if (*s == ' '){
            count++;
        }
        s++;
    }
    return count;
}


int main(){
    char str[] = "hello world foo";
    printf("%d\n", count_words(str));
    char str2[] = "";
    printf("%d", count_words(str2));
}