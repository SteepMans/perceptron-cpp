#include <iostream>
#include "matrix.h"
#include "ActivationFunction.h"
#include "Network.h"

int main()
{
    size_t size_layer = 2;
    int* layer = new int[size_layer] {736, 12, 9};

    Network net = Network(layer, size_layer, SIGMOID);
}