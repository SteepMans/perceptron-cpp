#include "ActivationFunction.h"

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