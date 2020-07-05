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

bool usermove_validate(Board board)
{
	
}

void usermove_select(Board &board, unsigned x, unsigned y)
{
	cout << "\033[H" << "\n\nSelecing outer rock:\n";
	board.print();
	cout << "\n\nUse wasd to move cursor, q to toggle whether rock is set to be removed, and e to do move when VALID appears.\n";
	cout << "\e[" << 7 + y << ";" << 3 + 2*x << "H";
	char key;
	key = getchar();
	do
		key = getchar();
	while ((key != 'w') && (key != 'a') && (key != 's') && (key != 'd') && (key != 'q') && (key != 'e'));
	switch (key)
	{
	case 'a':
		if (x != 0)
		{
			x--;
		}
		break;
	case 'w':
		if (y != 0)
		{
			y--;
		}
		break;
	case 'd':
		if (x+1 < board.get_size())
		{
			x++;
		}
		break;
	case 's':
		if (y+1 < board.get_size())
		{
			y++;
		}
		break;
	case 'q':
		board.toggle_r(x, y);
		break;
	case 'e':
		if (usermove_validate(board))
			return;
		break;
	default:
		break;
	}
	if (usermove_validate(board))
		cout << "VALID";
	else
		cout << "     ";
	usermove_select(board, x, y);
}

void usermove(Board* board)
{
	cout << "\e[1;1H\e[2J";
	cout << "Human move\n\n\n";
	board->print();
	cout << "\e[H";
	unsigned x = 0;
	unsigned y = 0;
	usermove_select(*board, x, y);
	board->clear_r();
}

void compmove(Board* board)
{
	cout << "Computer move\n\n\n";
	board->print();
}

void playgame(void(*p1)(Board*), void(*p2)(Board*))
{
	cout << "Game size: ";
	unsigned size;
	cin >> size;
	Board board(size);
	bool p2win = true;
	do
	{
		cout << "Player 1: ";
		(*p1)(&board);
		if (board.isover())
		{
			cout << "Player 1 wins!\n";
			p2win = false;
			break;
		}
		cout << "Player 2: ";
		(*p2)(&board);
	}
	while (!board.isover());
	if (p2win)
		cout << "Player 2 wins!\n";
	bool play_again = ask("Play again");
	if (play_again)
		playgame(p1, p2);
}