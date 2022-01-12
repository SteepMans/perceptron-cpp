#pragma once

#include <iostream>
#include <vector>
#include "matrix.h"

enum FUNCTION_ACTIVATE
{
	SIGMOID = 0,
	LUCKY_RELU = 1
};

class ActivationFunction
{
private:
	FUNCTION_ACTIVATE activate = FUNCTION_ACTIVATE::SIGMOID;

public:
	ActivationFunction();
	ActivationFunction(FUNCTION_ACTIVATE activate);
	void getName();
	Matrix derivative(Matrix value);
	double derivative(double value);
	void derivative(double* vector, int vector_size);
	double use(double value);
	double* use(double* vector, int vector_size);
	FUNCTION_ACTIVATE getType();
};

