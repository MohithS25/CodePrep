#include<iostream>
#include <string>
using namespace std;

int main(){
    int x = 40;
    string s = "mohith";
    cout<<x<<"\t"<<&x<<endl;       //prints val of x and addr of x
    cout<<s<<"\t"<<&s<<endl;

    int* a =&x;
    string* c = &s;

    cout<<a<<"\t"<<*a<<"\t"<<&a<<endl;      //prints value at a = addr of x, dereference -> value in x = 40, addr of a 
    cout<<c<<"\t"<<*c<<"\t"<<&c<<endl;

    *a = 100;                 //changing the value at x;
    *c = "kaushik";           //c= "kaushik" -> won't work -> can make it point elsewhere but can't change the address directly

    cout<<a<<"\t"<<*a<<"\t"<<&a<<endl;      
    cout<<c<<"\t"<<*c<<"\t"<<&c<<endl;

    string p = "pramila";
    c = &p;
    cout<<*c<<endl;  // should print pramila and not kaushik
    
    return 0;
}