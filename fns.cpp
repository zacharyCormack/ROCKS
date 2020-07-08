#include "fns.hpp"
#include <string>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <unistd.h>

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

bool usermove_core(Board &board, unsigned x, unsigned y)
{
	cout << "\e[H\n                                ";
	board.print();
	cout << "\n\n";
	bool valid = board.validate();
	cout <<
	(valid ? "\e[5;32mVALID\e[0m" : "     ") <<
	"\n\nUse wasd to move cursor, q to select rock, e to remove all selected rocks, and r to resign.\n"
	"Rules marked by \e[5;32m*\e[0m are followed, rules marked by \e[5;31m*\e[0m are not.\n";
	cout << "\e[" << 5 + y << ";" << 3 + 2*x << "H";
	char key = '.';
	do
		key = mygetch();
	while ((key != 'w') && (key != 'a') && (key != 's') && (key != 'd') && (key != 'q') && (key != 'e') && (key != 'r'));
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
		if (valid)
			if (ask("\e[2;0HConfirm move"))
				return false;
			else
				break;
		cout << '\a';
		break;
	case 'r':
		if (ask("\e[2;0HConfirm resignation"))
			return true;
	default:
		break;
	}
	return usermove_core(board, x, y);
}

bool usermove(Board* board)
{
	cout << "Human move";
	bool resign = usermove_core(*board, 0, 0);
	board->clear_r();
	return resign;
}



bool compmove(Board* board)
{
	cout << "Computer move\n";
	mv:
	usleep(1250000);
	unsigned a = rand() % board->get_size();
	unsigned b = rand() % board->get_size();
	unsigned c = rand() % 4;
	for (size_t i = 0; i < a; i++)
	{
		board->toggle_r(c < 2 ? b : (c == 1 ? i : board->get_size()-1), c > 1 ? b : (c == 2 ? i : board->get_size()-1));
	}
	cout << "\e[H\n";
	board->print();
	cout << "\n\n";
	if (!board->validate())
		goto mv;
	usleep(475000);
	board->clear_r();
	return false;
}

void playgame(bool(*p1)(Board*), bool(*p2)(Board*))
{
	cout << "Game size: ";
	unsigned size;
	cin >> size;
	Board board(size);
	bool p2win = true;
	do
	{
		cout << "\e[1;1H\e[2J" << "Player 1: ";
		if ((*p1)(&board))
			break;
		if (board.isover())
		{
			p2win = false;
			break;
		}
		cout << "\e[1;1H\e[2J" << "Player 2: ";
		if ((*p2)(&board))
		{
			p2win = false;
			break;
		}
	}
	while (!board.isover());
	if (p2win)
		cout << "\e[1;1H\e[2J" << "Player 2 wins!\n";
	else
		cout << "\e[1;1H\e[2J" << "Player 1 wins!\n";
	bool play_again = ask("Play again");
	if (play_again)
		playgame(p1, p2);
}