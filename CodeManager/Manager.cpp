#include "Manager.h"
void Manager::add_pro()
{
	std::string pro, lst;
	int cata_cnt;
	while (std::cin >> pro && pro != "end")
	{
		std::cin >> cata_cnt;
		mp[pro] = std::set<std::string>();
		while (cata_cnt--)
		{
			std::cin >> lst;
			mp[pro].insert(lst);
		}
	}
}
void Manager::query_pro()
{
	std::string lst, tmp;
	std::set<std::string> pro_lst;
	while (std::cin >> lst && lst != "end")
		pro_lst.insert(lst);
	std::cout << "searching...\n";
	for (auto& str : pro_lst)
	{
		auto it = mp.find(str);
		if (it != mp.end())
		{
			std::cout << (*it).first << "\ntag:";
			for (auto& sstr : (*it).second)
				std::cout << " " << sstr;
			std::cout << "\n";
		}
	}
}

bool find_com(std::set<std::string>& a, std::set<std::string>& b)
{
	auto it1 = a.begin(), it2 = b.begin();
	while (it1 != a.end() && it2 != b.end())
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
void Manager::query_cata()
{
	int cnt = 0;
	std::string lst;
	std::set<std::string>tag_lst;
	while (std::cin >> lst && lst != "end")
		tag_lst.insert(lst);
	std::cout << "searching...\n";
	for (auto& str : mp)
		if (find_com(tag_lst, str.second))
		{
			std::cout << str.first << "\ntag:";
			for (auto& sstr : str.second)
				std::cout << " " << sstr;
			std::cout << "\n";
			++cnt;
		}
	std::cout << "total items: " << cnt << "\n";
}
void Manager::query()
{
	std::string op;
	std::cin >> op;
	if (op == "-p")
		query_pro();
	else if (op == "-c")
		query_cata();
}
void Manager::list_pro()
{
	for (auto& str : mp)
	{
		std::cout << str.first << "\nkind:";
		for (auto& sstr : str.second)
			std::cout << " " << sstr;
		std::cout << "\n";
	}
}
void Manager::clear()
{
	std::string pro;
	std::cout << "please check y/n: ";
	std::cin >> pro;
	if (pro == "y")
	{
		mp.clear();
		std::cout << "cleared\n";
	}
}
void Manager::save_pro()
{
	std::fstream file_ptr("D:\\problemdata\\problemdata.txt", std::ios::out);
	for (auto& str : mp)
	{
		file_ptr << str.first;
		file_ptr << " " << str.second.size();
		for (auto& sstr : str.second)
			file_ptr << " " << sstr;
		file_ptr << "\n";
	}
	file_ptr.close();
	std::cout << "save ok!\n";
}
void Manager::del_pro()
{
	std::string lst;
	std::set<std::string> pro_lst;
	while (std::cin >> lst && lst != "end")
		pro_lst.insert(lst);
	for (auto& str : pro_lst)
		if (mp.find(str) != mp.end())
			mp.erase(str);
}
void Manager::del_cata()
{
	std::string lst;
	std::set<std::string>tag_lst;
	while (std::cin >> lst && lst != "end")
		tag_lst.insert(lst);
	std::vector<std::string>tmp;
	for (auto& str : mp)
		if (find_com(tag_lst, str.second))
			tmp.push_back(str.first);
	std::cout << "total items: " << tmp.size() << "\n";
	for (auto& str : tmp)
		mp.erase(str);
}
void Manager::del()
{
	std::string op;
	std::cin >> op;
	if (op == "-p")
		del_pro();
	else if (op == "-c")
		del_cata();
}
void Manager::init_mp()
{
	std::fstream file_ptr("D:\\problemdata\\problemdata.txt", std::ios::in);
	if (!file_ptr)
	{
		std::cout << "Can't open file\n";
		std::exit(0);
	}
	std::cout << "Initializing\n";
	std::string pro, lst;
	int cata_cnt;
	while (file_ptr >> pro)
	{
		file_ptr >> cata_cnt;
		while (cata_cnt--)
		{
			file_ptr >> lst;
			mp[pro].insert(lst);
		}
	}
	std::cout << "Initialized\n";
	file_ptr.close();
}
Manager::Manager()
{
	init_mp();
	func_mp["-a"] = &Manager::add_pro;
	func_mp["-q"] = &Manager::query;
	func_mp["-d"] = &Manager::del;
	func_mp["-l"] = &Manager::list_pro;
	func_mp["-c"] = &Manager::clear;
	func_mp["-s"] = &Manager::save_pro;
}
void Manager::call_func(std::string& op)
{

	auto it = func_mp.find(op);
	if (it != func_mp.end())
		(this->*(*it).second)();
	else if (op != "-e")
		std::cout << "Error Command!\n";
}
