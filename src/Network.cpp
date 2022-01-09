#include "Network.h"

Network::Network(int* layer, size_t size, FUNCTION_ACTIVATE activ_funx, DatasetData* data)
{
	this->layer = layer;
	this->size = size;
	this->weights = new Matrix[size - 1];
	this->bios = new double* [size - 1];
	this->active_function = ActivationFunction(activ_funx);
	this->dataset = data;

	for (int idx = 0; idx < this->size - 1; idx++)
	{
		this->weights[idx].init(layer[idx + 1], layer[idx], 0);
		this->bios[idx] = new double[layer[idx + 1]];

		this->weights[idx].randomValue();

		for (int j = 0; j < layer[idx + 1]; j++) 
			this->bios[idx][j] = ((rand() % 50)) * 0.06 / (layer[idx] + 15);
	}
}

Matrix Network::feedForward(int dataset_index)
{
	Matrix neurons_value = Matrix(this->dataset[dataset_index].pixels, this->layer[0]);

	for (int idx = 1; idx < this->size; idx++)
	{
		neurons_value = this->weights[idx - 1] * neurons_value;
		neurons_value.sumVector(this->bios[idx - 1]);
		neurons_value = this->active_function.use(neurons_value);
	}

	return neurons_value;
}

void Network::printConfig()
{
	std::cout << "==============================" << std::endl;
	std::cout << "Netwrok config:" << std::endl;
	std::cout << "Hidden Layer count " << this->size << std::endl;

	for (int idx = 0; idx < this->size; idx++)
		std::cout << "Layer " << idx + 1 << " count neyron " << this->layer[idx] << std::endl;

	std::cout << "==============================" << std::endl;
}

Network::~Network()
{
	//delete this->bios;
	//delete this->weights;
}

int Network::getMaxIndexValue(Matrix vector)
{
	int max_index = 0;

	for (int idx = 0; idx < vector.getRows(); idx++)
	{
		if (vector(idx, 0) > vector(max_index, 0))
			max_index = idx;
	}

	return max_index;
}