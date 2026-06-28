#include <iostream>
using namespace std;

int main(){
    int arr[3] = {10, 20,30};
    int* p = arr;
    cout<<*p<<"\t"<<&p<<"\t"<<p<<endl;                   //print -> arr[0] -> 10
    cout<<*(p+1)<<"\t"<<(p+1)<<endl;               //print -> arr[1] -> 20 -> (p+1) = p + 4 bytes
    cout<<*(p+2)<<"\t"<<(p+2)<<endl;
    cout<<*(p+4)<<endl;             // prints garbage or any number stored at location (p+4) -> Undefined Behaviour

    double arr1[3] = {23.3,32.4,21.0};
    double* p1 = arr1;
    cout<<*p1<<"\t"<<&p1<<"\t"<<p1<<endl;                  
    cout<<*(p1+1)<<"\t"<<(p1+1)<<endl;               //since p1 -> double , (p1 + 1) -> move ahead by 8 bytes
    cout<<*(p1+2)<<"\t"<<(p1+2)<<endl;

    return 0;

}