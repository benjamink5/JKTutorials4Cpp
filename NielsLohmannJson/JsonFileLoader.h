#pragma once

#include "JsonLoader.h"

namespace ExerciseNielsLohmannJson
{
	class JsonFileLoader : public JsonLoader
	{
	public:
		JsonFileLoader(std::string& strURL);
		~JsonFileLoader();

		void LoadData();
		void UnloadData();
	};
}

