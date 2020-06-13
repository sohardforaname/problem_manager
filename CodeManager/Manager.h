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
	std::unordered_map<std::string, std::set<std::string>>mp;
	std::unordered_map<std::string, void(Manager::*)(void)> func_mp;
	void init_mp();
	void add_pro();
	void query_pro();
	void query_cata();
	void query();
	void list_pro();
	void list_cata();
	void list();
	void clear();
	void save_pro();
	void del_pro();
	void del_cata();
	void del();

public:
	Manager();
	void call_func(std::string& op);
};