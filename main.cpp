#include "fns.hpp"
#include <iostream>
using namespace std;

const char* rules =
"Lorem Ipsum dolor sit amet,\n"
"Consectutur adsciping elit...\n";

int main()
{
	// char test[1];
	// cin.get(test, 1);
	cout << rules;
	bool two_players = ask("Play against the computer");
	if (two_players)
		playgame(&usermove, &usermove);
	bool user_first = ask("Do you want to go first");
	if (user_first)
		playgame(&usermove, &compmove);
	playgame(&compmove, &usermove);
}