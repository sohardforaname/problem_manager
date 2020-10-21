#include "Manager.h"

std::streambuf* cinPointer = std::cin.rdbuf();

std::string decrypt(const std::string& str, char magicNumber);

int ReadInt(std::istream& is)
{
	int tmp;
	if (!(is >> tmp))
		throw std::invalid_argument("stream comes to the end");
	return tmp;
}

std::string ReadString(std::istream& is)
{
	std::string tmp;
	if (!(is >> tmp))
		throw std::invalid_argument("stream comes to the end");
	return tmp;
}

std::set<std::string> FindIntersection
(
	const std::set<std::string>& firstSet, 
	const std::set<std::string>& secondSet
)
{
	auto it1 = firstSet.begin(), it2 = secondSet.begin();
	std::set<std::string> s;
	while (it1 != firstSet.end() && it2 != secondSet.end())
	{
		if (*it1 < *it2)
			++it1;
		else if (*it1 > * it2)
			++it2;
		else
		{
			s.insert(*it1);
			++it1;
			++it2;
		}
	}
	return s;
}

void ProblemList(const std::pair<std::string, std::set<std::string>>& p, int& count)
{
	++count;
	std::cout << p.first << "\ntag:";
	for (auto& sstr : p.second)
		if (sstr[0] > 0)
			std::cout << " " << sstr;
	std::cout << "\n";
}

void Manager::OutputProblemListByCatalogue
(
	const std::set<std::string>& s, 
	int& count
)
{
	for (auto& str : problemList)
		if (FindIntersection(s, str.second).size())
			ProblemList(str, count);
}

void Manager::OutputProblemListByName
(
	const std::set<std::string>& s,
	int& count
)
{
	for (auto& str : s)
	{
		auto it = problemList.find(str);
		if (it != problemList.end())
			ProblemList(*it, count);
	}
}

void Manager::AddProblem()
{
	std::string problem, pathCommand;
	int catalogueCounter;
	while (std::cin >> problem && problem != "end")
	{
		bool isWithPath = 1;
		std::cin >> pathCommand;
		if (pathCommand == "-f")
		{
			isWithPath = 0;
			std::cin >> catalogueCounter;
		}
		else if (isdigit(pathCommand[0]))
			catalogueCounter = atoi(pathCommand.c_str());
		else
			return void(puts("Not -f or digit, function Terminated!"));
		problemList[problem] = std::set<std::string>();
		while (catalogueCounter--)
			problemList[problem].insert(ReadString(std::cin));
		if (isWithPath)
			problemList[problem].insert(decrypt(ss, magicNumber) + ReadString(std::cin));
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
	OutputProblemListByName(tmpProblemList, findCounter);
	std::cout << "total items: " << findCounter << "\n";
}

void Manager::QueryCatelogue()
{
	std::string tmpTag;
	std::set<std::string> tmpTagList; 
	while (std::cin >> tmpTag && tmpTag != "end")
		tmpTagList.insert(tmpTag);
	std::cout << "searching...\n";
	int findCounter = 0;
	OutputProblemListByCatalogue(tmpTagList, findCounter);
	std::cout << "total items: " << findCounter << "\n";
}

void Manager::Query()
{
	std::string operation = ReadString(std::cin);
	if (operation == "-p")
		QueryProblem();
	else if (operation == "-c")
		QueryCatelogue();
}

void Manager::ListProblem()
{
	int findCounter= 0;
	for (auto& str : problemList)
		ProblemList(str, findCounter);
	std::cout << "total items: " << findCounter << "\n";
}

void Manager::ListCatelogue()
{
	std::unordered_map<std::string, std::set<std::string>>tmpProblemList;
	for (auto& dat : problemList)
		for (auto& str : dat.second)
			if (str[0] > 0)
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
	std::string operation = ReadString(std::cin);
	if (operation == "-p")
		ListProblem();
	else if (operation == "-c")
		ListCatelogue();
}

void Manager::Clear()
{
	std::cout << "please check y/n: ";
	std::string operationCheck = ReadString(std::cin);
	if (operationCheck == "n")
		return;
	problemList.clear();
	std::cout << "cleared\n";
}

void Manager::SaveProblemList()
{
	std::fstream filePointer("D:\\problemdata\\problemdata", std::ios::out);
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
		if (FindIntersection(tmpTagList, str.second).size())
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
	std::fstream configFilePointer("D:\\problemdata\\config", std::ios::in);
	if (!configFilePointer)
	{
		std::cout << "New User\n";
		_mkdir("D:\\problemdata");
		std::cout << "Input the direction that contain your code:\n";
		std::cin >> fileDirection;
		std::fstream newConfigFilePointer = std::fstream("D:\\problemdata\\config", std::ios::out);
		newConfigFilePointer << fileDirection << '\n';
		newConfigFilePointer.close();
	}
	else
	{
		configFilePointer >> fileDirection;
		configFilePointer.close();
	}
	std::fstream filePointer("D:\\problemdata\\problemdata", std::ios::in);
	if (!filePointer)
	{
		std::fstream newFilePointer = std::fstream("D:\\problemdata\\problemdata", std::ios::out);
		newFilePointer.close();
		std::cout << "problem file initialized\n";
		return;
	}
	std::cout << "Initializing\n";
	std::string tmpProblemName, tmpTagList;
	int catelogueCounter;
	while (filePointer >> tmpProblemName)
	{
		filePointer >> catelogueCounter;
		while (catelogueCounter--)
			problemList[tmpProblemName].insert(ReadString(filePointer));
	}
	std::cout << "Initialized\n";
	filePointer.close();
}


std::string decrypt(const std::string& str, char magicNumber)
{
	std::string res(str);
	for (auto& ch : res)
		ch ^= magicNumber;
	return res;
}
void Manager::OpenFileInVSCode()
{
	std::string targetFile;
	while (std::cin >> targetFile && targetFile != "end")
	{
		auto pset = problemList.find(targetFile);
		if (pset == problemList.end())
		{
			std::cout << "problem: " << targetFile << " not found\n";
			continue;
		}
		for (auto& iter : (*pset).second)
			if (iter.size() > 12 && decrypt(iter.substr(0, 12), magicNumber) == ss)
			{
				system((std::string("code ") + fileDirection + '\\' + iter.substr(12)).c_str());
				break;
			}
	}
}

void Manager::RunScript()
{
	std::string str;
	bool isComment = 0;
	while (std::cin >> str)
	{
		if (str[0] == '#')
		{
			isComment ^= 1;
			continue;
		}
		if (isComment)
			continue;
		try {
			CallFunction(str);
		}
		catch (const std::string& exceptionStr) {
			throw exceptionStr;
		}
	}
}

void Manager::LoadCommandFile()
{
	std::string filePath = ReadString(std::cin);
	std::ifstream filePointer(filePath.c_str(), std::ios::in);
	if(!filePointer)
		return void(puts("Can't open command file"));
	auto ptr = std::cin.rdbuf(filePointer.rdbuf());
	try {
		RunScript();
	}
	catch (const std::string& exceptionStr) {
		std::cin.rdbuf(ptr);
		filePointer.close();
		std::cout << "found \"-e\" in script file: " << filePath << "\n";
		throw exceptionStr;
	}
	std::cout << "Run script file: " << filePath << " ok!\n";
	std::cin.rdbuf(ptr);
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
	functionMap["-o"] = &Manager::OpenFileInVSCode;
	functionMap["-lc"] = &Manager::LoadCommandFile;
}

void Manager::CallFunction(const std::string& op)
{
	if (op == "-e")
		throw op;
	auto it = functionMap.find(op);
	if (it == functionMap.end())
		throw op;
	try {
		(this->*(*it).second)();
	}
	catch (const std::string& exceptionStr) {
		throw exceptionStr;
	}
}

void Manager::Run(const std::string& script)
{
	std::stringstream sstr;
	sstr << script;
	auto ptr = std::cin.rdbuf(sstr.rdbuf());
	std::string op;
	while (std::cin >> op)
	{
		try {
			CallFunction(op);
		}
		catch (const std::string& exceptionStr) {
			if (exceptionStr == "-e")
				break;
		}
	}
	std::cin.rdbuf(ptr);
	std::cout << "Run script string ok!\n";
}

void Manager::Run()
{
	while (1)
	{
		std::cout << ">>> ";
		try {
			CallFunction(ReadString(std::cin));
		}
		catch (const std::string& exceptionStr) {
			if (exceptionStr == "-e")
				break;
		}
	}
}
