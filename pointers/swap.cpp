#include <iostream>
using namespace std;
/*
void swap(int* a, int* b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}
*/
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    int a = 10;
    int b = 30;
    swap(&a,&b);
    cout<< a << endl;
    cout << b <<endl;

    return 0;
}