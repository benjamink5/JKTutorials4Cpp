#include "pch.h"
#include "JsonFileLoader.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace ExerciseNielsLohmannJson
{
	JsonFileLoader::JsonFileLoader(std::string& strURL)
		: JsonLoader(strURL)
	{
	}


	JsonFileLoader::~JsonFileLoader()
	{
	}

	void JsonFileLoader::LoadData()
	{
		_jsonData.clear();

		string line;
		ifstream myfile(_strURL);
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				_jsonData.append(line);
			}
			myfile.close();
		}
	}

	void JsonFileLoader::UnloadData()
	{

	}

}