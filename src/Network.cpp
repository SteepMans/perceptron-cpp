#include "Network.h"

Network::Network(int* layer, size_t size, int learning_rate, FUNCTION_ACTIVATE activ_funx, DatasetData* data)
{
	this->layer = layer;
	this->size = size;
	this->weights = new Matrix[size - 1];
	this->bios = new double* [size - 1];
	this->active_function = ActivationFunction(activ_funx);
	this->dataset = data;
	this->learning_rate = learning_rate;

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
		neurons_value = this->weights[idx - 1].dot(neurons_value);
		neurons_value.sumVector(this->bios[idx - 1]);
		neurons_value = this->active_function.use(neurons_value);
	}

	return neurons_value;
}

void Network::backPropogation(int dataset_index)
{
	Matrix* neurons_err = new Matrix[this->size];
	neurons_err[this->size - 1] = this->feedForward(dataset_index);

	for (int i = 0; i < neurons_err[this->size - 1].getRows(); i++)
	{
		if (i == this->dataset[dataset_index].digit)
		{
			neurons_err[this->size - 1](i, 0) = 1 - neurons_err[this->size - 1](i, 0);
		}
		else
		{
			neurons_err[this->size - 1](i, 0) = -neurons_err[this->size - 1](i, 0);
		}
	}

	Matrix error_end_layer = neurons_err[this->size - 1] * this->active_function.use(neurons_err[this->size - 1]);

	for (int i = this->size - 2; i > 0; i--)
	{
		neurons_err[i] = this->weights[i].transpose().dot(neurons_err[i + 1]);
		neurons_err[i] = neurons_err[i] * this->active_function.use(neurons_err[i]);
	}

	Matrix* neurons_value_list = new Matrix[this->size];
	Matrix neurons_value = Matrix(this->dataset[dataset_index].pixels, this->layer[0]);
	neurons_value_list[0] = neurons_value;

	for (int idx = 1; idx < this->size; idx++)
	{
		neurons_value = this->weights[idx - 1].dot(neurons_value);
		neurons_value.sumVector(this->bios[idx - 1]);
		neurons_value = this->active_function.use(neurons_value);

		neurons_value_list[idx] = neurons_value;
	}

	for (int i = 0; i < this->size - 1; i++)
	{
		for (int j = 0; j < this->layer[i + 1]; j++)
		{
			for (int k = 0; k < this->layer[i]; k++)
				this->weights[i](j, k) += neurons_value_list[i](k, 0) * neurons_err[i + 1](j, 0) * this->learning_rate;
		}	

		if (i == 0)
		{
			this->weights[i].print();
			std::cout << i << std::endl;
		}
	}

	for (int i = 0; i < this->size - 1; i++)
	{
		for (int j = 0; j < this->layer[i + 1]; j++)
			this->bios[i][j] = neurons_err[i + 1](j, 0) * this->learning_rate;
	}
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