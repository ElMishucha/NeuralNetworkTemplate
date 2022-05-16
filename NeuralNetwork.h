#pragma once
#include <iostream>
#include <memory>
#include <vector>

class Layer;

class NeuralNetwork
{
public:
	NeuralNetwork(std::vector<int> layerSizes); // init (generate random weights)

	NeuralNetwork(const NeuralNetwork& parent); // copy ready network

	std::vector<float> CalculateOutputs(std::vector<float> inputs);

	std::vector<Layer*> layers;

	void PrintWeights();
};	

