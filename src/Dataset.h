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
	DatasetData* data;
	int examples;

public:
	void load(std::string path, int input_layer_count_neyron = 784);
	DatasetData* getData();
	int getExamples();
};

