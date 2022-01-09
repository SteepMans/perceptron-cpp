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

    Network net = Network(layer, size_layer, 0.1, SIGMOID, mnist.getData());
    net.printConfig();

    int epoch = 5;

    for (int idx = 0; idx < epoch; idx++)
    {
        int correct_answer = 0;
        for (int i = 0; i < mnist.getExamples(); i++)
        {
            net.backPropogation(i);
            
            Matrix prediction = net.feedForward(i);
            //std::cout << net.getMaxIndexValue(prediction) << " " << mnist.getData()[i].digit << std::endl;
            if (mnist.getData()[i].digit == net.getMaxIndexValue(prediction))
                correct_answer++;
        }

        std::cout << "epoch " << idx << " acu: " << correct_answer << std::endl;
    }
}