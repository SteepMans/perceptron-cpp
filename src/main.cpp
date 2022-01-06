#include <iostream>
#include "matrix.h"

int main()
{
    Matrix matrix = Matrix(3, 5, 1.2);
    matrix.randomValue();
    matrix.print();

    std::cout << "=========" << std::endl;
    
    Matrix matrix_two = Matrix(5, 3, 1.2);
    matrix_two.randomValue();
    matrix_two.print();

    std::cout << "=========" << std::endl;

    Matrix matrix_multipiller = matrix * matrix_two;
    matrix_multipiller.print();

    std::cout << "=========" << std::endl;
    matrix_multipiller.transpose().print();
}