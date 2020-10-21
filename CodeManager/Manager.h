#pragma once
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <iostream>
#include <algorithm>
#include <vector>
#include <direct.h>
#include <exception>

class Manager
{
private:
	std::unordered_map<std::string, std::set<std::string>>problemList;
	std::unordered_map<std::string, void(Manager::*)(void)> functionMap;
	std::string fileDirection;

	const std::string ss = "%%$$%%$$%%$$";
	const char magicNumber = '%' - '^';
	static std::streambuf* cinPointer;

	void OutputProblemListByCatalogue(const std::set<std::string>& s, int& count);
	void OutputProblemListByName(const std::set<std::string>& s, int& count);

	void initFunctionMap();

	void AddProblem();
	void QueryProblem();
	void QueryCatelogue();
	void Query();
	void ListProblem();
	void ListCatelogue();
	void List();
	void Clear();
	void SaveProblemList();
	void DeleteProblem();
	void DeleteCatelogue();
	void Delete();
	void OpenFileInVSCode();
	void LoadCommandFile();
	void CallFunction(const std::string& operation);
	void RunScript();

public:
	Manager();
	void Run();
	void Run(const std::string& script);
};
