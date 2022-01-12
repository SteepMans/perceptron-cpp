#include <iostream>
#include "matrix.h"
#include "ActivationFunction.h"
#include "Network.h"
#include "Dataset.h"

int main()
{
    Dataset mnist = Dataset();
    mnist.load(std::string("dataset/mnist.txt"));

    size_t size_layer = 3;
    int* layer = new int[size_layer] {784, 256, 10};

    Network net = Network(layer, size_layer, 0.1, SIGMOID, mnist.data);
    net.printConfig();
    /*net.readWeights("weights/Weights.txt");
    int correct_answer = 0;
    for (int i = 0; i < mnist.getExamples(); i++)
    {
        double* prediction = net.feedForward(i);
        std::cout << i << " " << correct_answer << " correct answer " << mnist.getData()[i].digit << " nn " << net.getMaxIndexValue(prediction, 10) << std::endl;
        if (mnist.getData()[i].digit == net.getMaxIndexValue(prediction, 10))
        {
            correct_answer++;
        }
    }*/

    int epoch = 10;

    for (int idx = 0; idx < epoch; idx++)
    {
        time_t start_time = 0, end_time = 0;
        time(&start_time);

        int correct_answer = 0;
        for (int i = 0; i < mnist.getExamples(); i++)
        {
            double* prediction = net.feedForward(i);
            if (mnist.getData()[i].digit == net.getMaxIndexValue(prediction, 10))
                correct_answer++;

            net.feedForward(i);
            net.backPropogation(i, idx);            
        }

        time(&end_time);

        std::cout << "epoch " << idx << " acu: " << correct_answer << " time: " <<  end_time - start_time << std::endl;
    }

    net.saveWeights("weights/Weights.txt");
}