#include "Config.h"

void Config::from_json(nlohmann::json& j)
{
	layerSizes = j.at("layerSizes").get<std::vector<int>>();
	fieldsCount = j.at("fieldsCount").get<int>();
	gensCount = j.at("gensCount").get<int>();
	initialSegmentsCount = j.at("initialSegmentsCount").get<int>();
	fieldWidth = j.at("fieldWidth").get<int>();
	fieldHeight = j.at("fieldHeight").get<int>();
	entitiesPerFieldCount = j.at("entitiesPerFieldCount").get<int>();
}
