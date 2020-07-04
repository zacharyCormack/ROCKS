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

unsigned usermove_select_col(Board board, unsigned col_num)
{
	cout << "\033[H" << "\n\nSelecing outer rock:\n";
	unsigned i;
	switch ((int)(col_num/board.get_size()))
	{
	case 0:
		i = col_num-board.get_size();
		do
			cout << "  ";
		while (i-->0);
		board.print(-1);
		break;
	case 1:
		board.print(-1);
		break;
	case 2:
		board.print(-1);
		break;
	case 3:
		board.print(col_num-board.get_size()*3);
		break;
	default:
		exit(-4);
	}
	if (col_num < board.get_size()*3)
	{
		board.print(-1);
		cout << "\033[H" << "\n\n\n\n";
		unsigned i = col_num-board.get_size()*3;
		do
			cout << "\n";
		while (i-->0);
		cout << " >";
	}
	else
		board.print(col_num-board.get_size()*3);
	cout << "Use a and d arrow keys to move counterclockwise and clockwise, respectively, press return to select.";
	char key;
	do
		cin.get(key);
	while (key != 'a' && key != 'd' && key != '\n');
	switch (key == '\n' ? ((key == 'a' ^ col_num % board.get_size()*2 < board.get_size()) ? 1 : 0) : 2)
	{
	case 0:
		switch ((col_num+1) % board.get_size() == 0 ? (col_num+1)/board.get_size() : 0)
		{
		case 0:
			col_num++;
			break;
		case 1:
			col_num = board.get_size()*3;
			break;
		case 2:
			col_num = board.get_size()*4-1;
			break;
		case 3:
			col_num = board.get_size();
			break;
		case 4:
			col_num = board.get_size()*2-1;
			break;
		default:
			exit(-6);
		}
		break;
	case 1:
		switch ((col_num-1) % board.get_size() == 0 ? (col_num-1)/board.get_size()+1 : 0)
		{
		case 0:
			col_num--;
			break;
		case 1:
			col_num = board.get_size()*2;
			break;
		case 2:
			col_num = board.get_size()*3-1;
			break;
		case 3:
			col_num = 0;
			break;
		case 4:
			col_num = board.get_size()-1;
			break;
		default:
			exit(-6);
		}
		break;
	case 2:
		return col_num;
	default:
		exit(-5);
	}
	return usermove_select_col(board, col_num);
}

unsigned usermove_select_num(Board board, unsigned r_num)
{

}

bool usermove_selected()
{

}

bool usermove_validate(unsigned col_num, unsigned r_num)
{
	
}

void usermove(Board board)
{
	cout << "\e[1;1H\e[2J";
	cout << "Human move\n\n\n";
	board.print(-1);
	unsigned col = 0;
	unsigned num = 1;
	do
		do
		{
			col = usermove_select_col(board, col);
			if (usermove_selected())
				break;
			num = usermove_select_num(board, num);
		}
		while (usermove_selected());
	while (usermove_validate(col, num));
}

void compmove(Board board)
{
	cout << "Computer move\n\n\n";
	board.print(-1);
}

void playgame(void(*p1)(Board), void(*p2)(Board))
{
	cout << "Game size: ";
	unsigned size;
	cin >> size;
	Board board(size);
	bool p2win = true;
	do
	{
		cout << "Player 1: ";
		(*p1)(board);
		if (board.isover())
		{
			cout << "Player 1 wins!\n";
			p2win = false;
			break;
		}
		cout << "Player 2: ";
		(*p2)(board);
	}
	while (!board.isover());
	if (p2win)
		cout << "Player 2 wins!\n";
	bool play_again = ask("Play again");
	if (play_again)
		playgame(p1, p2);
}