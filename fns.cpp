#include "fns.hpp"

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
	bool valid = board.validate(true);
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
			x--;
		break;
	case 'w':
		if (y != 0)
			y--;
		break;
	case 'd':
		if (x+1 < board.get_size())
			x++;
		break;
	case 's':
		if (y+1 < board.get_size())
			y++;
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
	bool resign = usermove_core(*board, 0, 0);
	board->clear_r();
	return resign;
}

bool compmove(Board* board)
{
	cout << "\e[H\n";
	board->print();
	cout << "\e[H\n";
	board->print();
	usleep(1275000);
	for (size_t i = 0; i < board->get_size(); i++)
		for (size_t j = 0; j < board->get_size(); j++)
			if (board->check_r(i, j))
				board->toggle_r(board->get_size()-i-1, board->get_size()-j-1);
	if (board->validate(false))
		goto end;
	do
		board->toggle_r(rand() % board->get_size(), rand() % board->get_size());
	while (!(board->validate(false)));
	end:
	cout << "\e[H\n";
	board->print();
	usleep(1500000);
	board->clear_r();
	cout << "\e[H\n";
	board->print();
	usleep(1275000);
	return false;
}

void playgame(bool(*p1_move)(Board*), bool(*p2_move)(Board*), const char* p1_name, const char* p2_name)
{
	cout << "Game size: ";
	unsigned size;
	cin >> size;
	Board board(size);
	bool p2win = true;
	do
	{
		cout << "\e[1;1H\e[2J" << p1_name;
		usleep(750000);
		if ((*p1_move)(&board))
		{
			cout << "\e[1;1H\e[2J\n\n" << p1_name << " has resigned!\n\n";
			usleep(1250000);
			break;
		}
		if (board.isover())
		{
			p2win = false;
			break;
		}
		cout << "\e[1;1H\e[2J" << p2_name;
		usleep(750000);
		if ((*p2_move)(&board))
		{
			p2win = false;
			cout << "\e[1;1H\e[2J\n\n" << p2_name << " has resigned!\n\n";
			usleep(1250000);
			break;
		}
	}
	while (!board.isover());
	if (p2win)
		cout << "\e[1;1H\e[2J\n\n" << p2_name << " wins!\n\n";
	else
		cout << "\e[1;1H\e[2J\n\n" << p1_name << " wins!\n\n";
	usleep(1750000);
	bool play_again = ask("Play again");
	if (play_again)
		playgame(p1_move, p2_move, p1_name, p2_name);
}