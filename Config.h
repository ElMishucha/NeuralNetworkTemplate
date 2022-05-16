#pragma once
#include <vector>
#include <nlohmann/json.hpp>

class Config
{
public:
	Config() = default;

	void from_json(nlohmann::json& j);

	std::vector<int> layerSizes;
	int fieldsCount;
	int gensCount;
	int initialSegmentsCount;
	int fieldWidth;
	int fieldHeight;
	int entitiesPerFieldCount;
};
