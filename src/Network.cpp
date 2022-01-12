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
		
		neurons_value = new double* [this->size]; 
		neurons_error = new double* [this->size];
		
		for (int i = 0; i < this->size; i++) 
		{
			neurons_value[i] = new double[this->layer[i]]; 
			neurons_error[i] = new double[this->layer[i]];
		}
	}
}

double* Network::feedForward(int dataset_index)
{
	for (int idx = 0; idx < this->layer[0]; idx++)
		this->neurons_value[0][idx] = this->dataset[dataset_index].pixels[idx];

	for (int idx = 1; idx < this->size; idx++)
	{
		this->neurons_value[idx] = this->weights[idx - 1].dot(this->neurons_value[idx - 1], this->layer[idx - 1]);
		
		for(int i = 0; i < this->layer[idx]; i++)
			this->neurons_value[idx][i] += this->bios[idx - 1][i];
		
		this->neurons_value[idx] = this->active_function.use(this->neurons_value[idx], this->layer[idx]);
	}

	return this->neurons_value[this->size -1];
}

void Network::backPropogation(int dataset_index, int epoch)
{
	neurons_error[this->size - 1] = this->neurons_value[this->size - 1];

	for (int i = 0; i < this->layer[this->size - 1]; i++)
	{
		if (i == this->dataset[dataset_index].digit)
		{
			neurons_error[this->size - 1][i] = 1 - neurons_error[this->size - 1][i] *
				this->active_function.derivative(neurons_error[this->size - 1][i]);
		}
		else
		{
			neurons_error[this->size - 1][i] = -neurons_error[this->size - 1][i] *
				this->active_function.derivative(neurons_error[this->size - 1][i]);
		}
	}

	// neurons_error[this->size - 1] = neurons_error[this->size - 1] * this->active_function.derivative(neurons_err[this->size - 1]);

	for (int i = this->size - 2; i > 0; i--)
	{
		this->weights[i].dotTranspose(neurons_error[i + 1], this->layer[i + 1], neurons_error[i]);
		this->active_function.derivative(neurons_error[i], this->layer[i]);
	}

	for (int i = 0; i < this->size - 1; i++)
	{
		for (int j = 0; j < this->layer[i + 1]; j++)
		{
			for (int k = 0; k < this->layer[i]; k++)
				this->weights[i](j, k) += neurons_value[i][k] * neurons_error[i + 1][j]
						* 0.15 * exp(-epoch / 20.);
		}	
	}

	for (int i = 0; i < this->size - 1; i++)
	{
		for (int j = 0; j < this->layer[i + 1]; j++)
			this->bios[i][j] += neurons_error[i + 1][j] * 0.15 * exp(-epoch / 20.);
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

void Network::readWeights(std::string path)
{
	std::ifstream file_w;
	file_w.open(path);
	
	if (!file_w.is_open()) 
	{
		std::cout << "Error reading the file";
		system("pause");
	}
	
	for (int i = 0; i < this->size - 1; ++i) 
	{
		file_w >> weights[i];
	}

	for (int i = 0; i < this->size - 1; ++i)
	{
		for (int j = 0; j < this->layer[i + 1]; ++j) 
		{
			file_w >> bios[i][j];
		}
	}

	std::cout << "Weights readed \n";
	file_w.close();
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

int Network::getMaxIndexValue(double* vector, int vector_size)
{
	int max_index = 0;

	for (int idx = 0; idx < vector_size; idx++)
	{
		if (vector[idx] > vector[max_index])
			max_index = idx;
	}

	return max_index;
}

void Network::saveWeights(std::string path)
{
	std::ofstream file_weight;
	file_weight.open(path);

	if (!file_weight.is_open())
	{
		std::cout << "[net] Error reading the file";
		system("pause");
	}
	for (int i = 0; i < this->size - 1; ++i)
		file_weight << weights[i] << " ";

	for (int i = 0; i < this->size - 1; ++i) {
		for (int j = 0; j < this->layer[i + 1]; ++j) {
			file_weight << bios[i][j] << " ";
		}
	}

	std::cout << "[net] Weights saved" << std::endl;
	file_weight.close();
}