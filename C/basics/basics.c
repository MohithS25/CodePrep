#include <stdio.h>

struct Point { int x; int y; };

void translate(struct Point* p, int x, int y) {
    p->x += x;
    p->y += y;
}

void print_point(struct Point* p){
    printf("(%d, %d)", p->x, p->y);
}

int main() {
    char* a = "cat";
    char b[] = "cat";
    b[0] = 'b';
    printf("%s %s\n", a, b);
}

