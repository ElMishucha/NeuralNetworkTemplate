#include "Field.h"

#include <iostream>

#include "Config.h"
#include "Entity.h"
#include "Point.h"
#include "GeneticAlgorithmController.h"
#include "NeuralNetwork.h"
#include <Windows.h>
#include <ctime>

Field::Field(Config& config) : config_(config), positions_(generatePositions())
{
	generateFoodPositions();
	for (auto pos : positions_) {
		auto entity = new Entity(config, *pos, *this);
		entities_.push_back(entity);
	}
}

Field::Field(Config& config, std::vector<Entity*>& best) : config_(config), positions_(generatePositions())
{
	generateFoodPositions();
	//srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < config_.entitiesPerFieldCount; i++)
	{
		int a = rand() % best.size();
		int b = (a + rand() % (best.size() - 1) + 1) % best.size();

		NeuralNetwork* childNetwork = GeneticAlgorithmController::Cross(*best[a]->nn_, *best[b]->nn_, config_);
		GeneticAlgorithmController::Mutate(*childNetwork, config_);

		auto entity = new Entity(config_, *positions_[i], *this);
		entity->copyWeightsFromNNParent(*childNetwork);
		entities_.push_back(entity);
	}
}


bool Field::intersect(Point* p)
{
	for (auto entity : entities_)
	{
		for (auto segment : entity->segments)
		{
			if (*p == segment)
				return true;
		}
	}
	for (auto pos : foodPositions_)
	{
		if (p == pos)
			return true;
	}
	return false;
}

bool Field::step(std::vector<Entity*>& topEntities)
{
	for (auto entity : entities_)
	{
		bool alive = entity->Move();
		if (!alive)
		{
			topEntities.push_back(entity);
			entities_.erase(find(entities_.begin(), entities_.end(), entity));
		}
	}

	return entities_.size() != 0;
}

void Field::generateFoodPositions()
{
	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < config_.entitiesPerFieldCount; i++)
	{
		Point* p = new Point();
		do {
			p->row = rand() % config_.fieldWidth;
			p->column = rand() % config_.fieldHeight;
		} while (intersect(p));
		foodPositions_.push_back(p);
	}
}



std::vector<Point*> Field::generatePositions()
{
	std::vector<Point*> positions;
	for (int i = 1; i <= config_.entitiesPerFieldCount; i++) {
		auto pos = new Point();
		pos->row = config_.fieldWidth / (config_.entitiesPerFieldCount + 1) * i;
		pos->column = config_.fieldHeight / 2 - 1;
		positions.push_back(pos);
	}
	return positions;
}

void Field::simulate(std::vector<Entity*>& topEntities)
{
	bool allEntitiesAlive = true;
	while (allEntitiesAlive)
	{
		allEntitiesAlive = step(topEntities);
		/*print();
		Sleep(100);*/
	}
}

void Field::respawnFood(int id)
{
	do {
		foodPositions_[id]->row = rand() % config_.fieldWidth;
		foodPositions_[id]->column = rand() % config_.fieldHeight;
	} while (intersect(foodPositions_[id]));
}

void Field::print()
{
	std::vector<std::vector<char>> field(config_.fieldHeight, std::vector<char>(config_.fieldWidth, '-'));
	for (auto entity : entities_)
	{
		for (auto segment : entity->segments) {
			field[segment.row][segment.column] = '#';
		}
	}
	for (auto food : foodPositions_)
	{
		field[food->row][food->column] = '@';
	}

	for (auto a : field)
	{
		for (auto b : a)
		{
			std::cout << b << " ";
		}
		std::cout << std::endl;
	}
}
