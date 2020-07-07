#include "fns.hpp"
#include <string>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

bool ask(char* q)
{
	std::cout << q << "? y/n: ";
	string ans;
	std::cin >> ans;
	if (ans == "y")
		return true;
	else if (ans == "n")
		return false;
	return ask(q);
}

int mygetch()
{
	int ch;
	struct termios t_old, t_new;

	tcgetattr(STDIN_FILENO, &t_old);
	t_new = t_old;
	t_new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
	return ch;
}

void printrules()
{
	cout <<
		" Begin with a grid of \"rocks\" with side length n.\n"
		" Two players take turns removing groups of rocks in the following manner:\n"
		" \n"
		" * at least one rock is on the perimeter of the grid is removed\n"
		" * if any rocks removed on the perimeter are adjacent, then a rock must be removed from a corner\n"
		" * all the rocks removed are in a straight line\n"
		" * no two rocks removed have a space between them\n"
		" \n"
		" If, on your turn, you cannot remove rocks in this manner, you lose.\n\n";
}

void usermove_select(Board &board, unsigned x, unsigned y)
{
	cout << "\e[H\n\n\n";
	board.print();
	cout << '\n' << (board.validate() ? "\e[5;32mVALID  \e[0m" : "\e[5;31mINVALID\e[0m") << "\n\nUse wasd to move cursor, q to toggle whether rock is set to be removed, and e to do move when VALID appears.\n";
	cout << "\e[" << 7 + y << ";" << 3 + 2*x << "H";
	char key;
	key = mygetch();
	do
		key = mygetch();
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
		if (board.validate())
			return;
		cout << '\a';
		break;
	default:
		break;
	}
	usermove_select(board, x, y);
}

void usermove(Board* board)
{
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
		cout << "\e[1;1H\e[2J" << "Player 1: ";
		(*p1)(&board);
		if (board.isover())
		{
			cout << "\e[1;1H\e[2J" << "Player 1 wins!\n";
			p2win = false;
			break;
		}
		cout << "\e[1;1H\e[2J" << "Player 2: ";
		(*p2)(&board);
	}
	while (!board.isover());
	if (p2win)
		cout << "\e[1;1H\e[2J" << "Player 2 wins!\n";
	bool play_again = ask("Play again");
	if (play_again)
		playgame(p1, p2);
}