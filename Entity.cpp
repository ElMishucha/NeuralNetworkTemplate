#include "Entity.h"
#include "NeuralNetwork.h"
#include "Config.h"
#include "Point.h"
#include "Field.h"

std::vector<float> Entity::getInputs()
{
	std::vector<float> inputs(24, 0);

	std::vector<Point> directions =
	{ {-1, 0}, {-1, 1},
	 {0, 1}, {1, 1},
	 {1, 0}, {1, -1},
	 {0, -1}, {-1, -1} };

	for (int i = 0; i < directions.size(); i++)
	{
		int dist = 1;
		while (true) {
			Point currDir{(directions[i] * dist)};
			auto p = (segments[0] + currDir);
			// looking for segments
			bool self = true;
			for (auto entity : field_.entities_)
			{
				for (auto s : entity->segments)
				{
					if (self)
					{
						self = false;
						continue;
					}
					if (p == s)
					{
						inputs[i] = 0.5;
					}
				}
			}

			// looking for food
			for (auto foodpos : field_.foodPositions_)
			{
				if (p == *foodpos)
				{
					inputs[8 + i] = 1;
				}
			}

			// looking for wall
			if (wallColide(p)) {
				inputs[16 + i] = 0.5;
				break;
			}

			dist++;
		}

		return inputs;
	}
}

bool Entity::Move()
{
	auto outputs = nn_->CalculateOutputs(getInputs());
	auto maxEl = int(std::max_element(outputs.begin(), outputs.end()) - outputs.begin());

	switch (maxEl)
	{
	case 0:
		// up
		dir = { -1, 0 };
		break;
	case 1:
		// right
		dir = { 0, 1 };
		break;
	case 2:
		// down
		dir = { 1, 0 };
		break;
	case 3:
		// left
		dir = { 0, -1 };
		break;
	}

 	for (int s = segments.size() - 1; s >= 1; s--)
	{
		segments[s] = segments[s - 1];
	}
	segments[0] += dir;

	stepsTaken++;
	stepsLeft--;

	if (stepsLeft <= 0)
		return false;

	if (wallColide(segments[0]))
		return false;

	int foodId = foodColide(segments[0]);
	if (foodId != -1)
	{
		foodEaten++;
		stepsLeft = 500;
		field_.respawnFood(foodId);
	}

	if (segmentColide(segments[0]))
		return false;

	return true;
}



bool Entity::wallColide(Point p)
{
	return p.row < 0 || p.row >= config_.fieldWidth || p.column < 0 || p.column >= config_.fieldHeight;
}

int Entity::foodColide(Point p)
{
	int id = 0;
	for (auto foodpos : field_.foodPositions_)
	{
		if (p == *foodpos)
		{
			return id;
		}
		id++;
	}
	return -1;
}

bool Entity::segmentColide(Point p)
{
	bool self = true;
	for (auto entity : field_.entities_)
	{
		for (auto s : entity->segments)
		{
			if (p == s)
			{
				if (self)
				{
					self = false;
					continue;
				}
				return true;
			}
		}
	}
	return false;
}

void Entity::copyWeightsFromNNParent(const NeuralNetwork& parent)
{
	nn_ = new NeuralNetwork(parent);
}

float Entity::getScore()
{
	return foodEaten * 10 + stepsTaken;
}

Entity::Entity(Config& config, Point& position, Field& f) : config_(config), field_(f)
{
	dir = { -1, 0 };
	nn_ = new NeuralNetwork(config_.layerSizes);
	for (int i = 1; i <= config_.initialSegmentsCount; i++)
	{
		Point pos;
		pos.row = position.row + i;
		pos.column = position.column;
		segments.push_back(pos);
	}
}
