/*
Exercise 1 — Calculator with dispatch table

  Write a calculator that takes an operator character (+, -, *, /) and two integers, and dispatches to the correct function using a dispatch table (array of function pointers). No if/else or switch in the dispatch
  path — index directly into the table.
  
  Write the four operation functions, the dispatch table, and a calculate(char op, int a, int b) function that looks up and calls the right one. Handle unknown operators by returning 0.
*/

#include <iostream>

int add(int a, int b){
    return a + b ;
}

int sub(int a, int b){
    return a - b ;
}

int mul(int a, int b){
    return a * b ;
}

int divide(int a, int b){
    if(b == 0){ return 0;}
    return a / b ;
}

using BinaryOp = int(*)(int,int);

BinaryOp table[] =
{
    add,
    sub,
    mul,
    divide
};

int calculate(char op, int a, int b){
    const std::string ops = "+-*/";
    size_t index = ops.find(op);
    return table[index](a, b);
}

int main(){
    std::cout << calculate('+', 10, 5) << '\n';
    std::cout << calculate('-', 10, 5) << '\n';
    std::cout << calculate('*', 10, 5) << '\n';
    std::cout << calculate('/', 10, 5) << '\n';

    return 0;
}

