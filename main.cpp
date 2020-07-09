#include "fns.hpp"
#include <iostream>

using namespace std;

int main()
{
	cout << "\e[1;1H\e[2J" << "This program allows you to play the following game:\n\n";
	printrules();
	bool two_players = !(ask("Play against the computer"));
	if (two_players)
	{
		std::string p1_name;
		std::string p2_name;
		std::cout << "Player 1 name: ";
		std::cin >> p1_name;
		std::cout << "Player 2 name: ";
		std::cin >> p2_name;
		playgame(&usermove, &usermove, p1_name.c_str(), p2_name.c_str());
	}
	else
	{
		std::string p_name;
		std::cout << "Player name: ";
		std::cin >> p_name;
		bool user_first = ask("Do you want to go first");
		if (user_first)
			playgame(&usermove, &compmove, p_name.c_str(), "Computer");
		else
			playgame(&compmove, &usermove, "Computer", p_name.c_str());
	}
	cout << "\e[1;1H\e[2J";
	return 0;
}