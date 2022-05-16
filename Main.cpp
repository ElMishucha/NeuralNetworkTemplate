#include "Config.h"
#include "nlohmann/json.hpp"

#include <fstream>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <algorithm>

#include "Entity.h"
#include "Field.h"
#include "GeneticAlgorithmController.h"
#include "NeuralNetwork.h"

using namespace std;



void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 2;
	Rect.Right = Width - 1;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(handle, coord);
	SetConsoleWindowInfo(handle, TRUE, &Rect);
}


void readConfig(Config& config, string path)
{
	ifstream i(path);
	nlohmann::json j;
	i >> j;
	config.from_json(j);
}

bool fitness(Entity* a, Entity* b)
{
	return a->getScore() > b->getScore();
}

signed main() {
	Config config;
	readConfig(config, "config.json");
	cout.tie(nullptr);
	ios_base::sync_with_stdio(false);
	//SetWindow(50, config.fieldHeight);
	srand (static_cast<unsigned int>(time(0)));

	vector<Entity*> topEntities;

	// ===== gen 1
	for (int f = 0; f < config.fieldsCount; f++)
	{
		auto field = new Field(config);
		field->simulate(topEntities);
		cout << f << " init " << topEntities.size() << "\n";
	}
	// =====

	/*for (int i = 0;i < 2;i++)
	{
		topEntities[i]->nn_->PrintWeights();
	}*/

	sort(topEntities.begin(), topEntities.end(), fitness);

	vector<Entity*> prevTop = topEntities;
	for (int gen = 1; gen < config.gensCount; gen++) {
		vector<Entity*> localTop_;
		for (int f = 0; f < config.fieldsCount; f++)
		{
			auto field = new Field(config, prevTop);
			field->simulate(localTop_);
			cout << f << " field " << localTop_.size() << "\n";
		}

		sort(localTop_.begin(), localTop_.end(), fitness);
		prevTop.clear();
		for (int i = 0;i < 10;i++)
		{
			prevTop.push_back(localTop_[i]);
		}
	}
}