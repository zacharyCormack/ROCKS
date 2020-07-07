#include "fns.hpp"
#include <iostream>

using namespace std;

int main()
{
	cout << "\e[1;1H\e[2J" << "This program allows you to play the following game:\n\n";
	printrules();
	bool two_players = !(ask("Play against the computer"));
	if (two_players)
		playgame(&usermove, &usermove);
	else
	{
		bool user_first = ask("Do you want to go first");
		if (user_first)
			playgame(&usermove, &compmove);
		else
			playgame(&compmove, &usermove);
	}
	cout << "\e[1;1H\e[2J";
	return 0;
}