#pragma once
#include <vector>

#include "Point.h"


class NeuralNetwork;
class Config;
class Point;
class Field;

class Entity
{
public:
	
//  ↓                    ↓
//  ↓     ALL CUSTOM     ↓
//  ↓                    ↓

	Entity(Config& config, Point& position, Field& f);	// some special your arguments in constructor

	std::vector<Point> segments;			// for snake	(c) sssssssssss

	std::vector<float> getInputs();			// you must calculate INPUT LAYER

	bool Move();							// alive?

	bool wallColide(Point p);

	int foodColide(Point p);

	bool segmentColide(Point p);


	int foodEaten = 0;
	int stepsTaken = 0;
	int stepsLeft = 500;

	Point dir;

//  ↑                    ↑
//  ↑     ALL CUSTOM     ↑
//  ↑                    ↑

	void copyWeightsFromNNParent(const NeuralNetwork& parent);

	float getScore();

	NeuralNetwork* nn_;

private:

	Config& config_;
	Field& field_;

};
