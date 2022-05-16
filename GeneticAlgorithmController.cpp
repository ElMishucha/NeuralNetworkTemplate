#include <ctime>

#include "GeneticAlgorithmController.h"
#include "Layer.h"
#include "NeuralNetwork.h"
#include "Config.h"

void GeneticAlgorithmController::Mutate(NeuralNetwork& a, Config& config_)
{
	//srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < a.layers.size(); i++)
	{
		for (int j = 0; j < a.layers[i]->weights.size(); j++)
		{
			for (int k = 0; k < a.layers[i]->weights[j].size(); k += 2)
			{
				if ((rand() % 100) <= 10) {
					int multiplier;
					switch (rand() % 5) {
					case 0:
						multiplier = 0.8;
						break;
					case 1:
						multiplier = -0.6;
						break;
					case 2:
						multiplier = 0.1;
						break;
					case 3:
						multiplier = -0.5;
						break;
					case 4:
						multiplier = 0.7;
						break;
					}
					a.layers[i]->weights[j][k] *= multiplier;
				}
			}
		}
	}
}

NeuralNetwork* GeneticAlgorithmController::Cross(NeuralNetwork& a, NeuralNetwork& b, Config& config_)
{
	auto c = new NeuralNetwork(config_.layerSizes);

	for (int i = 0; i < a.layers.size(); i++)
	{
		int size = a.layers[i]->weights.size() * a.layers[i]->weights[0].size();
		int counter = 0;
		for (int j = 0; j < a.layers[i]->weights.size(); j++)
		{
			for (int k = 0; k < a.layers[i]->weights[j].size(); k++)
			{
				if (counter < size / 2)
				{
					c->layers[i]->weights[j][k] = a.layers[i]->weights[j][k];
				}
				else
				{
					c->layers[i]->weights[j][k] = b.layers[i]->weights[j][k];
				}
				counter++;
			}
		}
	}

	return c;
}
