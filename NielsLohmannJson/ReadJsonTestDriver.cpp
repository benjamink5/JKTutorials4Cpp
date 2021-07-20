#include "pch.h"
#include "ReadJsonTestDriver.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

namespace ExerciseNielsLohmannJson
{
	ReadJsonTestDriver::ReadJsonTestDriver()
	{
	}


	ReadJsonTestDriver::~ReadJsonTestDriver()
	{
	}

	void ReadJsonTestDriver::Execute()
	{
		runTestCase01();
	}

	void ReadJsonTestDriver::runTestCase01()
	{
		string inputFileName = "sample-random.json";

		// Start up
		JsonLoader* pJsonLoader = NULL;

		// Read a json file
		pJsonLoader = new JsonFileLoader(inputFileName);
		pJsonLoader->LoadData();

		// Execute
		string jsonTestData = pJsonLoader->GetJsonData();

		json j_root = json::parse(jsonTestData);
		if (!j_root["pi"].is_null() && j_root["pi"].is_number_float())
		{
			cout << "pi = " << j_root["pi"].get<float>() << endl;
		}
		
		if (!j_root["happy"].is_null() && j_root["happy"].is_boolean())
		{
			cout << "happy = " << j_root["happy"].get<bool>() << endl;
		}
		
		if (!j_root["name"].is_null() && j_root["name"].is_string())
		{
			cout << "name = " << j_root["name"].get<string>() << endl;
		}
		
		if (j_root["nothing"].is_null())
		{
			cout << "nothing is null" << endl;
		}

		if (!j_root["answer"].is_null() && j_root["answer"].is_object())
		{
			cout << "answer: { " << endl;
			json j_answer = j_root["answer"];
			if (!j_answer["everything"].is_null() && j_answer["everything"].is_number_integer())
			{
				cout << "\teverything = " << j_answer["everything"].get<int>() << endl;
			}
			cout << "}" << endl;
		}

		if (!j_root["list"].is_null() && j_root["list"].is_array())
		{
			cout << "list: [ ";
			json j_list = j_root["list"];
			for (auto it = j_list.begin(); it != j_list.end(); ++it)
			{
				if (it->is_number_integer())
				{
					cout << it->get<int>();
				}

				if (it != j_list.end() - 1)
				{
					cout << ", ";
				}
			}
			cout << " ]" << endl;
		}

		if (!j_root["object"].is_null() && j_root["object"].is_object())
		{
			cout << "object: {" << endl;
			json j_object = j_root["object"];
			if (!j_object["currency"].is_null() && j_object["currency"].is_string())
			{
				cout << "\tcurrency = " << j_object["currency"].get<string>() << endl;
			}

			if (!j_object["value"].is_null() && j_object["value"].is_number_float())
			{
				cout << "\tvalue = " << j_object["value"].get<float>() << endl;
			}
			cout << "}" << endl;
		}

		// Clean up
		if (pJsonLoader != NULL)
		{
			pJsonLoader->UnloadData();
			delete pJsonLoader;
			pJsonLoader = NULL;
		}
	}
}
