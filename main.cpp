#include "fns.hpp"
#include <iostream>

using namespace std;

const char* rules =
"Lorem Ipsum dolor sit amet,\n"
"Consectutur adsciping elit...\n";

int main()
{
	cout << "\e[1;1H\e[2J" << rules;
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
}