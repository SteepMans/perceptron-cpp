#include "Network.h"

Network::Network(int* layer, size_t size, FUNCTION_ACTIVATE activ_funx)
{
	this->layer = layer;
	this->size = size;
	this->weights = new Matrix[size - 1];
	this->bios = new double* [size - 1];
	this->active_function = ActivationFunction(activ_funx);

	for (int i = 0; i < size - 1; i++)
	{
		this->weights[i].init(layer[i + 1], layer[i], 0);
		this->bios[i] = new double[layer[i + 1]];

		this->weights[i].randomValue();

		for (int j = 0; j < layer[i + 1]; j++) 
			bios[i][j] = ((rand() % 50)) * 0.06 / (layer[i] + 15);
	}
}

Network::~Network()
{
	//delete this->bios;
	//delete this->weights;
}