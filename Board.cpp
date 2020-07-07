#include "Board.hpp"
using namespace std;

Board::Board(unsigned n)
{
	for (size_t i = 0; i < n; i++)
	{
		std::vector<char> new_row;
		for (size_t j = 0; j < n; j++)
			new_row.push_back((char)0);
		rocks.push_back(new_row);
	}
};

unsigned Board::get_size()
{
	return rocks.size();
}

int Board::move(unsigned col_or_row_num, unsigned num_rocks)
{
	if (col_or_row_num >= rocks.size()*4)
		return -1;
	switch ((int)(col_or_row_num/rocks.size()))
	{
	case 0:
		for (size_t i = 0; i < num_rocks; i++)
			if (rocks[col_or_row_num][i]==(char)1)
				return -3;
		for (size_t i = 0; i < num_rocks; i++)
			rocks[col_or_row_num][i] = (char)1;
		break;
	case 1:
		for (size_t i = 0; i < num_rocks+1; ++i)
			if (rocks[col_or_row_num-rocks.size()][rocks.size()-i]==(char)1)
				return -3;
		for (size_t i = 0; i < num_rocks+1; ++i)
			rocks[col_or_row_num-rocks.size()][rocks.size()-i] = (char)1;
		break;
	case 2:
		for (size_t i = 0; i < num_rocks; i++)
			if (rocks[i][col_or_row_num-rocks.size()*2]==(char)1)
				return -3;
		for (size_t i = 0; i < num_rocks; i++)
			rocks[i][col_or_row_num-rocks.size()*2] = (char)1;
		break;
	case 3:
		for (size_t i = 0; i < num_rocks+1; ++i)
			if (rocks[rocks.size()-i][col_or_row_num-rocks.size()*3]==(char)1)
				return -3;
		for (size_t i = 0; i < num_rocks+1; ++i)
			rocks[rocks.size()-i][col_or_row_num-rocks.size()*3] = (char)1;
		break;
	default:
		return -2;
	}
	return 0;
}

bool Board::isover()
{
	for (size_t i = 0; i < rocks.size(); i++)
		if (!(rocks[0][i]==(char)1 && rocks[i][0]==(char)1 && rocks[rocks.size()-1][i]==(char)1 && rocks[i][rocks.size()-1]==(char)1))
			return false;
	return true;
}

void Board::toggle_r(unsigned x, unsigned y)
{
	switch (rocks[y][x])
	{
	case (char)1:
		cout << '\a';
		break;
	case (char)0:
		rocks[y][x] = (char)2;
		break;
	default:
		rocks[y][x] = (char)0;
		break;
	}
}

bool rules_violation_one()
{
	cout <<
		"\e[5;31m"
		" * at least one rock is on the perimeter of the grid is removed\n"
		" * if any rocks removed on the perimeter are adjacent, then a rock must be removed from a corner\n"
		" * all the rocks removed are in a straight line\n"
		" * no two rocks removed have a space between them\n"
		"\e[0m";
	return false;
}

bool rules_violation_two()
{
	cout <<
		"\e[5;32m"
		" * at least one rock is on the perimeter of the grid is removed\n"
		"\e[5;31m"
		" * if any rocks removed on the perimeter are adjacent, then a rock must be removed from a corner\n"
		" * all the rocks removed are in a straight line\n"
		" * no two rocks removed have a space between them\n"
		"\e[0m";
	return false;
}

bool rules_violation_three()
{
	cout <<
		"\e[5;32m"
		" * at least one rock is on the perimeter of the grid is removed\n"
		" * if any rocks removed on the perimeter are adjacent, then a rock must be removed from a corner\n"
		"\e[5;31m"
		" * all the rocks removed are in a straight line\n"
		" * no two rocks removed have a space between them\n"
		"\e[0m";
	return false;
}

bool rules_violation_four()
{
	cout <<
		"\e[5;32m"
		" * at least one rock is on the perimeter of the grid is removed\n"
		" * if any rocks removed on the perimeter are adjacent, then a rock must be removed from a corner\n"
		" * all the rocks removed are in a straight line\n"
		"\e[5;31m"
		" * no two rocks removed have a space between them\n"
		"\e[0m";
	return false;
}

bool rules_followed()
{
	cout <<
		"\e[5;32m"
		" * at least one rock is on the perimeter of the grid is removed\n"
		" * if any rocks removed on the perimeter are adjacent, then a rock must be removed from a corner\n"
		" * all the rocks removed are in a straight line\n"
		" * no two rocks removed have a space between them\n"
		"\e[0m";
	return true;
}

bool Board::validate()
{
	unsigned first_x = -1;
	unsigned first_y = -1;
	bool no_second = true;
	bool second_down;
	for (unsigned i = 0; i < rocks.size(); i++)
		for (unsigned j = 0; j < rocks.size(); j++)
			if (rocks[i][j]==(char)2)
				if (first_x >= rocks.size())
				{
					first_x = j;
					first_y = i;
				}
	if (first_x >= rocks.size())
		return rules_violation_one();
	return rules_followed();
}

void Board::clear_r()
{
	for (size_t i = 0; i < rocks.size(); i++)
		for (size_t j = 0; j < rocks.size(); j++)
			rocks[i][j] = ((rocks[i][j] == (char)0) ? (char)0 : (char)1);
}

void Board::print()
{
	cout << "\nThe board is:\n";
	for (size_t i = 0; i < rocks.size(); i++)
	{
		cout << "\n ";
		for (size_t j = 0; j < rocks.size(); j++)
			if (rocks[i][j]==(char)0)
				cout << " o";
			else if (rocks[i][j]==(char)1)
				cout << "  ";
			else
				cout << "\e[5;31m *\e[0m";
	}
}