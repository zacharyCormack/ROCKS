#include "fns.hpp"
#include <string>

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

void usermove(Board board)
{

}

void compmove(Board board)
{

}

void playgame(void(*p1)(Board), void(*p2)(Board))
{
	cout << "Game size: ";
	unsigned size;
	cin >> size;
	Board board(size);
	turn:
	cout << "Player 1: ";
	(*p1)(board);
	if (board.isover())
	{
		cout << "Player 1 wins!\n";
		goto end;
	}
	cout << "Player 2: ";
	(*p2)(board);
	if (board.isover())
	{
		cout << "Player 2 wins!\n";
		goto end;
	}
	end:
	bool play_again = ask("Play again");
	if (play_again)
		playgame(p1, p2);
	exit(0);
}