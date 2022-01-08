#pragma once

#include "ActivationFunction.h";
#include "matrix.h";

class Network
{
private:
	int* layer;
	size_t size;
	ActivationFunction active_function;
	Matrix* weights;
	double** bios;
	double** neurons_value, ** neurons_error;

public:
	Network(int* layer, size_t size, FUNCTION_ACTIVATE activ_funx);
	~Network();
};

