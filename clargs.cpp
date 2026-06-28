/* 
#include <iostream>

int main(int argc, char* argv[]){
    std::cout << "Arguments provided: " << argc << std::endl;
    std::cout << "Program name: " << argv[0] << std::endl;
    for(int i=1;i<argc;i++){
        std::cout<<"Arg "<<i<<":"<<argv[i]<<std::endl;
    }
    return 0;
}

 my command line: ./clargs mohith kaushik pramila dvs
output: Arguments provided: 4
Program name: ./clargs
Arg 1: mohith
Arg 2: kaushik
Arg 3: pramila
Arg 4: dvs

*/
/*
#include <iostream>

int main(int argc, char* argv[]){
    if(argc!=3){
        return 1;
    }

    int x = std::stoi(*(argv + 1));
    int y = std::stoi(argv[2]);
    int sum = x+y;
    std::cout<<sum<<std::endl;
    return 0;
}

*/

#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
    cout << argv[1] << endl;      
    cout << argv[1][0] << endl;   
    cout << argv[1][1] << endl;  
    cout << *(argv + 1)<< endl;
    cout<< *(argv + 2)<<endl;
    cout << *(*(argv + 1))<<endl; 
    cout << *(*(argv + 2) + 1)<<endl;
}