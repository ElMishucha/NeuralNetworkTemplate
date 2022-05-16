#include <ctime>

#include "Layer.h"

#include <iostream>

Layer::Layer(int size, int nextSize)
{
	//srand(static_cast<unsigned int>(time(0)));

	neurons.resize(size);
	weights.resize(size, std::vector<float>(nextSize));
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < nextSize;j++)
		{
			weights[i][j] = float(rand() % 20000 - 10000) / 10000.0;
		}
	}
}
