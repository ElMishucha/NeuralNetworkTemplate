#pragma once
#include <vector>

class Layer
{
public:
	Layer(int size, int nextSize);
	std::vector<float> neurons;
	std::vector<std::vector<float>> weights; 
};