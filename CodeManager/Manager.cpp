#include "Manager.h"

bool find_com(std::set<std::string>& firstSet, std::set<std::string>& secondSet)
{
	auto it1 = firstSet.begin(), it2 = secondSet.begin();
	while (it1 != firstSet.end() && it2 != secondSet.end())
	{
		if (*it1 < *it2)
			++it1;
		else if (*it1 > * it2)
			++it2;
		else
			return true;
	}
	return false;
}

void Manager::AddProblem()
{
	std::string problem, tagList;
	int catalogueCounter;
	while (std::cin >> problem && problem != "end")
	{
		std::cin >> catalogueCounter;
		problemList[problem] = std::set<std::string>();
		while (catalogueCounter--)
		{
			std::cin >> tagList;
			problemList[problem].insert(tagList);
		}
	}
}

void Manager::QueryProblem()
{
	std::string tmpProblemName;
	std::set<std::string> tmpProblemList;
	while (std::cin >> tmpProblemName && tmpProblemName != "end")
		tmpProblemList.insert(tmpProblemName);
	std::cout << "searching...\n";
	int findCounter = 0;
	for (auto& str : tmpProblemList)
	{
		auto it = problemList.find(str);
		if (it != problemList.end())
		{
			++findCounter;
			std::cout << (*it).first << "\ntag:";
			for (auto& sstr : (*it).second)
				std::cout << " " << sstr;
			std::cout << "\n";
		}
	}
	std::cout << "total items: " << findCounter << "\n";
}

void Manager::QueryCatelogue()
{
	int findCounter = 0;
	std::string tmpTag;
	std::set<std::string> tmpTagList; 
	while (std::cin >> tmpTag && tmpTag != "end")
		tmpTagList.insert(tmpTag);
	std::cout << "searching...\n";
	for (auto& str : problemList)
		if (find_com(tmpTagList, str.second))
		{
			std::cout << str.first << "\ntag:";
			for (auto& sstr : str.second)
				std::cout << " " << sstr;
			std::cout << "\n";
			++findCounter;
		}
	std::cout << "total items: " << findCounter << "\n";
}

void Manager::Query()
{
	std::string operation;
	std::cin >> operation;
	if (operation == "-p")
		QueryProblem();
	else if (operation == "-c")
		QueryCatelogue();
}

void Manager::ListProblem()
{
	int findCounter= 0;
	for (auto& str : problemList)
	{
		std::cout << str.first << "\ntag:";
		for (auto& sstr : str.second)
		{
			std::cout << " " << sstr;
			++findCounter;
		}
		std::cout << "\n";
	}
	std::cout << "total items: " << findCounter << "\n";
}

void Manager::listCatelogue()
{
	std::unordered_map<std::string, std::set<std::string>>tmpProblemList;
	for (auto &dat : problemList)
		for (auto& str : dat.second)
			tmpProblemList[str].insert(dat.first);
	for (auto& dat : tmpProblemList)
	{
		std::cout << dat.first << "\n";
		for (auto& str : dat.second)
			std::cout << "\t" << str << "\n";
		std::cout << "total items: " << dat.second.size() << "\n";
	}	
}

void Manager::List()
{
	std::string operation;
	std::cin >> operation;
	if (operation == "-p")
		ListProblem();
	else if (operation == "-c")
		listCatelogue();
}

void Manager::Clear()
{
	std::string operationCheck;
	std::cout << "please check y/n: ";
	std::cin >> operationCheck;
	if (operationCheck == "y")
	{
		problemList.clear();
		std::cout << "cleared\n";
	}
}

void Manager::SaveProblemList()
{
	std::fstream filePointer("D:\\problemdata\\problemdata.txt", std::ios::out);
	for (auto& str : problemList)
	{
		filePointer << str.first;
		filePointer << " " << str.second.size();
		for (auto& sstr : str.second)
			filePointer << " " << sstr;
		filePointer << "\n";
	}
	filePointer.close();
	std::cout << "save ok!\n";
}

void Manager::DeleteProblem()
{
	int findCounter = 0;
	std::string tmpProblemName;
	std::set<std::string> tmpProblemList;
	while (std::cin >> tmpProblemName && tmpProblemName != "end")
		tmpProblemList.insert(tmpProblemName);
	for (auto& str : tmpProblemList)
		if (problemList.find(str) != problemList.end())
		{
			problemList.erase(str);
			++findCounter;
		}
	std::cout << "total items: " << findCounter << "\n";
}

void Manager::DeleteCatelogue()
{
	std::string tmpTag;
	std::set<std::string>tmpTagList;
	while (std::cin >> tmpTag && tmpTag != "end")
		tmpTagList.insert(tmpTag);
	std::vector<std::string>tmpDeleteVector;
	for (auto& str : problemList)
		if (find_com(tmpTagList, str.second))
		tmpDeleteVector.push_back(str.first);
	std::cout << "total items: " << tmpDeleteVector.size() << "\n";
	for (auto& str : tmpDeleteVector)
		problemList.erase(str);
}

void Manager::Delete()
{
	std::string operation;
	std::cin >> operation;
	if (operation == "-p")
		DeleteProblem();
	else if (operation == "-c")
		DeleteCatelogue( );
}

void Manager::initFunctionMap()
{
	std::fstream filePointer("D:\\problemdata\\problemdata.txt", std::ios::in);
	if (!filePointer)
	{
		std::cout << "Can't open file\n";
		std::exit(0);
	}
	std::cout << "Initializing\n";
	std::string tmpProblemName, tmpTagList;
	int catelogueCounter;
	while (filePointer >> tmpProblemName)
	{
		filePointer >> catelogueCounter;
		while (catelogueCounter--)
		{
			filePointer >> tmpTagList;
			problemList[tmpProblemName].insert(tmpTagList);
		}
	}
	std::cout << "Initialized\n";
	filePointer.close();
}

Manager::Manager()
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	initFunctionMap();
	functionMap["-a"] = &Manager::AddProblem;
	functionMap["-q"] = &Manager::Query;
	functionMap["-d"] = &Manager::Delete;
	functionMap["-l"] = &Manager::List;
	functionMap["-c"] = &Manager::Clear;
	functionMap["-s"] = &Manager::SaveProblemList;
}
void Manager::CallFunction(std::string& op)
{

	auto it = functionMap.find(op);
	if (it != functionMap.end())
		(this->*(*it).second)();
	else if (op != "-e")
		std::cout << "Error Command!\n";
}
