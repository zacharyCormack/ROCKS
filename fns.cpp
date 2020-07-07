#include "fns.hpp"
#include <string>

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

void usermove_select(Board &board, unsigned x, unsigned y)
{
	printf("\e[H\n\n\n");
	board.print();
	printf("\n%s %s", (board.validate() ? "VALID" : "     "), "\n\nUse wasd to move cursor, q to toggle whether rock is set to be removed, and e to do move when VALID appears.\n");
	printf("\e[%d %c %d %c", 7 + y, ';', 3 + 2*x, 'H');
	char key;
	
	noecho();
	key = getch();
	do
		key = getch();
	while ((key != 'w') && (key != 'a') && (key != 's') && (key != 'd') && (key != 'q') && (key != 'e'));
	echo();
	endwin();
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
		printf("\a");
		break;
	default:
		break;
	}
	usermove_select(board, x, y);
}

void usermove(Board* board)
{
	printf("Human move\n\n\n");
	board->print();
	printf("\e[H");
	unsigned x = 0;
	unsigned y = 0;
	usermove_select(*board, x, y);
	board->clear_r();
}

void compmove(Board* board)
{
	printf("Computer move\n\n\n");
	board->print();
}

void playgame(void(*p1)(Board*), void(*p2)(Board*))
{
	printf("Game size: ");
	unsigned size;
	cin >> size;
	Board board(size);
	bool p2win = true;
	initscr();
	do
	{
		printf("\e[1;1H\e[2JPlayer 1: ");
		(*p1)(&board);
		if (board.isover())
		{
			printf("Player 1 wins!\n");
			p2win = false;
			break;
		}
		printf("\e[1;1H\e[2JPlayer 2: ");
		(*p2)(&board);
	}
	while (!board.isover());
	endwin();
	if (p2win)
		printf("Player 2 wins!\n");
	bool play_again = ask("Play again");
	if (play_again)
		playgame(p1, p2);
}