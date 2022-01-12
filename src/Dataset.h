#pragma once
#include <string>
#include <chrono>
#include <fstream>

struct DatasetData 
{
	double* pixels;
	int digit;
};

class Dataset
{
private:
	int examples;

public:
	DatasetData* data;
	void load(std::string path, int input_layer_count_neyron = 784);
	DatasetData* getData();
	int getExamples();
};

