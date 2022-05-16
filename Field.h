#pragma once
#include <vector>

class Config;
class Entity;
class Point;
class NeuralNetwork;

class Field
{
public:
	Field(Config& config);

	Field(Config& config, std::vector<Entity*>& best);


	std::vector<Point*> generatePositions();

	void simulate(std::vector<Entity*>& topEntities);

	void respawnFood(int id);

	void print();

	std::vector<Entity*> entities_;

	std::vector<Point*> foodPositions_;
private:
	Config& config_;

	bool intersect(Point* p);

	bool step(std::vector<Entity*>& topEntities);

	void generateFoodPositions();

	std::vector<Point*> positions_;


};

