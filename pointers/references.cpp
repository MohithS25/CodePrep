#include <iostream>

int main(){
    int x = 40;
    int y = 30;

    int& ref = x;

    ref = y;   // changes value at x directly

    std::cout<<x<<std::endl;
    std::cout<<ref<<std::endl;

    return 0;
}