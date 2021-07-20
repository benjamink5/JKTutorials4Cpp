#include "pch.h"
#include "WriteJsonTestDriver.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

namespace ExerciseNielsLohmannJson
{
	WriteJsonTestDriver::WriteJsonTestDriver()
	{
	}


	WriteJsonTestDriver::~WriteJsonTestDriver()
	{
	}

	void WriteJsonTestDriver::Execute()
	{
		json j_root = json::object();

		j_root["pi"] = 3.141;
		j_root["happy"] = true;
		j_root["name"] = "Niels";
		j_root["nothing"] = nullptr;

		json j_answer = json::object();
		j_answer["everything"] = 42;
		j_root["answer"] = j_answer;

		vector<int> vec = { 1, 0, 2 };
		json j_list = json::array();
		for (auto it = vec.begin(); it != vec.end(); ++it)
			j_list.push_back(*it);
		j_root["list"] = j_list;

		json j_object = json::object();
		j_object["currency"] = "USD";
		j_object["value"] = 42.99;
		j_root["object"] = j_object;

		cout << j_root.dump() << endl;

	}
}