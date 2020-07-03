#include "fns.hpp"
#include <string>

const char* rules =
"Lorem Ipsum dolor sit amet,\n"
"Consectutur adsciping elit...";

bool ask(char* q)
{
	std::cout << q << "? y/n:";
	string ans;
	std::cin >> ans;
	if (ans == "y")
		return true;
	else if (ans == "n")
		return false;
	return ask(q);
}

void usermove()
{

}

void compmove()
{

}

void playgame()
{

}