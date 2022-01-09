#pragma once

#include "ActivationFunction.h";
#include "matrix.h";
#include "Dataset.h"

class Network
{
private:
	int* layer;
	size_t size;
	ActivationFunction active_function;
	DatasetData* dataset;
	Matrix* weights;
	double** bios;
	//double** neurons_value, ** neurons_error;

public:
	Network(int* layer, size_t size, FUNCTION_ACTIVATE activ_funx, DatasetData* dataset);
	void printConfig();
	Matrix feedForward(int dataset_index);
	~Network();
	int getMaxIndexValue(Matrix vector);
};

