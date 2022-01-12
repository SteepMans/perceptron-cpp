#include "ActivationFunction.h"
#include "matrix.h"

void ActivationFunction::getName()
{
	std::cout << "ActivationFunction name: ";

	switch (this->activate)
	{
	case SIGMOID:
		std::cout << "SIGMOID" << std::endl;
		break;

	case LUCKY_RELU:
		std::cout << "RELU" << std::endl;
		break;

	default:
		std::cout << "NaN" << std::endl;
		break;
	}

}

FUNCTION_ACTIVATE ActivationFunction::getType()
{
	return this->activate;
}

ActivationFunction::ActivationFunction(FUNCTION_ACTIVATE activate)
{
	this->activate = activate;
}

ActivationFunction::ActivationFunction()
{
	this->activate = SIGMOID;
}

Matrix ActivationFunction::derivative(Matrix matrix)
{
	if (matrix.getCols() == 1)
	{
		Matrix finish = Matrix(matrix);

		for (int idx = 0; idx < finish.getRows(); idx++)
		{
			switch (ActivationFunction::getType())
			{
			case SIGMOID:
				finish(idx, 0) = matrix(idx, 0) * (1 - matrix(idx, 0));
				break;

			case LUCKY_RELU:
				if (matrix(idx, 0) < 0 || matrix(idx, 0) > 1) finish(idx, 0) = 0.01;
				else finish(idx, 0) = 1;
				break;

			default:
				throw std::runtime_error("Error type activationFunction");
				break;
			}
		}

		return finish;
	}
	else
	{
		throw std::runtime_error("not vector");
	}
}

double ActivationFunction::derivative(double value)
{
	double finish = 0.0;

	switch (ActivationFunction::getType())
	{
	case SIGMOID:
		finish = value * (1 - value);
		break;

	case LUCKY_RELU:
		if (value < 0 || value > 1) finish = 0.01;
		else finish = 1;
		break;

	default:
		throw std::runtime_error("Error type activationFunction");
		break;
	}

	return finish;
}

void ActivationFunction::derivative(double* vector, int vector_size)
{
	double* finish = new double[vector_size];

	for (int idx = 0; idx < vector_size; idx++)
	{
		switch (ActivationFunction::getType())
		{
		case SIGMOID:
			finish[idx] = vector[idx] * (1 - vector[idx]);
			break;

		case LUCKY_RELU:
			if (vector[idx] < 0 || vector[idx] > 1) finish[idx] = 0.01;
			else finish[idx] = 1;
			break;

		default:
			throw std::runtime_error("Error type activationFunction");
			break;
		}	
	}
}

double* ActivationFunction::use(double* vector, int vector_size)
{
	for (int idx = 0; idx < vector_size; idx++)
	{
		switch (ActivationFunction::getType())
		{
		case SIGMOID:
			vector[idx] = 1. / (1. + exp(-vector[idx]));
			break;

		case LUCKY_RELU:
			if (vector[idx] < 0) vector[idx] = vector[idx] * 0.01;
			else if (vector[idx] > 1) vector[idx] = 1. + 0.01 * (vector[idx] - 1.);
			break;

		default:
			throw std::runtime_error("Error type activationFunction");
			break;
		}
	}

	return vector;
}

double ActivationFunction::use(double value)
{
	double finish_value = 0.0;

	switch (ActivationFunction::getType())
	{
	case SIGMOID:
		finish_value = 1. / (1. + exp(-value));
		break;

	case LUCKY_RELU:
		if (value < 0) finish_value = value * 0.01;
		else if (value > 1) finish_value = 1. + 0.01 * (value - 1.);
		break;

	default:
		throw std::runtime_error("Error type activationFunction");
		break;
	}

	return finish_value;
}