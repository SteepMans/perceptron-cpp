#include "Dataset.h"
#include <iostream>
#include <uchar.h>
using namespace std;

void Dataset::load(std::string path, int input_layer_count_neyron)
{
	std::cout << "[dataset] Load " << path << std::endl;

	std::ifstream file_path;
	file_path.open(path);

	if (!file_path.is_open()) 
	{
		std::cout << "[dataset] Error reading the file " << path << std::endl;
		system("pause");
	}

	std::string data = "";
	file_path >> data;

	if (data == "Examples")
	{
		file_path >> this->examples;
		this->data = new DatasetData[this->examples];

		for (int idx = 0; idx < examples; idx++)
			this->data[idx].pixels = new double[input_layer_count_neyron];

		for (int i = 0; i < examples; i++) 
		{
			file_path >> this->data[i].digit;

			for (int j = 0; j < input_layer_count_neyron; j++)
				file_path >> this->data[i].pixels[j];
		}

		file_path.close();
	}
	else
	{
		std::cout << "[dataset] Error reading examples" << std::endl;
		system("pause");
	}
}

int Dataset::getExamples()
{
	return this->examples;
}

DatasetData* Dataset::getData()
{
	return this->data;
}