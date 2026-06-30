#include <iostream>

int main()
{
    int rows=3, columns=4;

    int** matrix = new int*[rows];                    //array of pointers for rows
    for (int i = 0; i < rows; i++) {
      matrix[i] = new int[columns];                   //creating row elements for each row
    }

    for(int i=0;i<rows;i++){
        for(int j=0; j<columns; j++){
            matrix[i][j] = (i*columns)+j;                   
        }
    }

    for(int i=0;i<rows;i++){
        for(int j=0; j<columns; j++){
            std::cout<< matrix[i][j] << "\t";
        }
        std::cout<<"\n";
    }

    for (int i = 0; i < rows; i++) {
      delete[] matrix[i];   // free each row first
    }
    delete[] matrix;          // then free the array of pointers

  //  std::cout<<*(*(matrix+1)+2);       will cause segfault 
    return 0;
}