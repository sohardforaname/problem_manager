#include "Manager.h"
int main()
{
	Manager manager;
	std::string operation;
	while (operation != "-e")
	{
		std::cout << ">>> ";
		std::cin >> operation;
		manager.CallFunction(operation);
	}
	return 0;
}