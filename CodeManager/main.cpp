#include "Manager.h"
int main()
{
	Manager m;
	std::string op;
	while (op != "-e")
	{
		std::cout << ">>> ";
		std::cin >> op;
		m.call_func(op);
	}
	return 0;
}