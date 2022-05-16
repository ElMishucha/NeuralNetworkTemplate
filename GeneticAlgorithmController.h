#pragma once

class NeuralNetwork;
class Config;

class GeneticAlgorithmController
{
public:

	static void Mutate(NeuralNetwork& a, Config& config_);

	static NeuralNetwork* Cross(NeuralNetwork& a, NeuralNetwork& b, Config& config_);
};

