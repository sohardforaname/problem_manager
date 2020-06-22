#pragma once
#include <unordered_map>
#include <fstream>
#include <string>
#include <set>
#include <iostream>
#include <algorithm>
#include <vector>

class Manager
{
private:
	std::unordered_map<std::string, std::set<std::string>>problemList;
	std::unordered_map<std::string, void(Manager::*)(void)> functionMap;
	void initFunctionMap();
	void AddProblem();
	void QueryProblem();
	void QueryCatelogue();
	void Query();
	void ListProblem();
	void listCatelogue();
	void List();
	void Clear();
	void SaveProblemList();
	void DeleteProblem();
	void DeleteCatelogue();
	void Delete();

public:
	Manager();
	void CallFunction(std::string& operation);
};