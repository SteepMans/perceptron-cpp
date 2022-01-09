#include <iostream>
#include "matrix.h"
#include "ActivationFunction.h"
#include "Network.h"
#include "Dataset.h"

int main()
{
    Dataset mnist = Dataset();
    mnist.load(std::string("dataset/mnist_10k.txt"));

    size_t size_layer = 4;
    int* layer = new int[size_layer] {784, 20, 15, 10};

    Network net = Network(layer, size_layer, SIGMOID, mnist.getData());
    net.printConfig();

    Matrix value = net.feedForward(5);
    int max_index = net.getMaxIndexValue(value);

    std::cout << "answer " << max_index << " digit " << mnist.getData()[5].digit << std::endl;
    value.print();
}