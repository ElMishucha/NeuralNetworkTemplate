#include "NeuralNetwork.h"
#include "Layer.h"

NeuralNetwork::NeuralNetwork(std::vector<int> layerSizes)
{
	for (int i = 0;i < layerSizes.size() - 1;i++)
	{
		auto layer = new Layer(layerSizes[i], layerSizes[i + 1]);
		layers.push_back(layer);
	}
	// output layer
	auto outputLayer = new Layer(layerSizes[layerSizes.size() - 1], 0);
	layers.push_back(outputLayer);
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& parent) : layers(parent.layers)
{
}

std::vector<float> NeuralNetwork::CalculateOutputs(std::vector<float> inputs)
{
	layers[0]->neurons = inputs;

	for (int i = 1;i < layers.size();i++) // идем по слоям
	{
		float minValue = 0;
		if (i == layers.size() - 1) minValue = -1;
		Layer* a = layers[i - 1];
		Layer* b = layers[i];
		for (int j = 0;j < b->neurons.size();j++)
		{
			b->neurons[j] = 0;
			for (int k = 0;k < a->neurons.size();k++)
			{
				b->neurons[j] += a->neurons[k] * a->weights[k][j];
			}
			b->neurons[j] = std::min(float(1), std::max(minValue, b->neurons[j]));
		}
	}
	return layers[layers.size() - 1]->neurons;
}

void NeuralNetwork::PrintWeights()
{
	for (int i = 0;i < layers.size();i++)
	{
		for (int j = 0;j < layers[i]->weights.size();j++)
		{
			for (int k = 0;k < layers[i]->weights[j].size();k++)
			{
				std::cout << layers[i]->weights[j][k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}