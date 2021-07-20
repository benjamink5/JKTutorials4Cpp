#pragma once

#include <string>

namespace ExerciseNielsLohmannJson
{
	class JsonLoader
	{
	protected:
		const std::string _strURL;
		std::string _jsonData;

	public:
		JsonLoader(std::string& strURL);
		virtual ~JsonLoader();

		std::string GetJsonData() const { return _jsonData; }
		void SetJsonData(std::string jsonData) { _jsonData = jsonData;  }

		virtual void LoadData() = 0;
		virtual void UnloadData() = 0;
	};
}

