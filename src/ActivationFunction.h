#pragma once

#include <iostream>
#include <vector>

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
	ActivationFunction(FUNCTION_ACTIVATE activate);
	void getName();
	double use(double value);
	FUNCTION_ACTIVATE getType();
};

