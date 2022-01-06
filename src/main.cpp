#include <iostream>
#include "matrix.h"
#include "ActivationFunction.h"

int main()
{
    auto funx_activated = ActivationFunction(LUCKY_RELU);
    funx_activated.getName();

    std::cout << funx_activated.use(-2.0) << std::endl;
}