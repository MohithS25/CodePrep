
#include <iostream>

int add(int a, int b){
    return a+b;
}

int multiply(int a, int b){
    return a*b;
}

//int(*fp)(int, int) = add;


using BinaryOp = int(*)(int, int);

int apply(BinaryOp op, int a, int b) {
    return op(a, b);
}


int main(){
    /*int result = fp(3,5);
    std::cout << "Result: " << result << '\n';
    
    BinaryOp addfn = add;
    BinaryOp mulfn = multiply;
    */

    BinaryOp op[] = {add , multiply};

    int result = apply(add,3,5);
    std::cout << "Result: " << result << '\n';

    int result2 = op[1](4,3);
    std::cout << "Result: " << result2 << '\n';

    int result1 = apply(multiply,3,5);
    std::cout << "Result: " << result1 << '\n';

    return 0;
}
