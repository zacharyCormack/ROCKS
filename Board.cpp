#include "Board.hpp"
using namespace std;

Board::Board(unsigned n)
{
	for (size_t i = 0; i < n; i++)
	{
		std::vector<Rock> new_row;
		for (size_t j = 0; j < n; j++)
			new_row.push_back(Rock());
		rocks.push_back(new_row);
	}
};

int Board::move(unsigned col_or_row_num, unsigned num_rocks)
{
	if (col_or_row_num >= rocks.size()*4)
		return -1;
	if (col_or_row_num < rocks.size())
	{
		for (size_t i = 0; i < num_rocks; i++)
			if (rocks[col_or_row_num][i].down)
				return -3;
		for (size_t i = 0; i < num_rocks; i++)
			rocks[col_or_row_num][i].down = true;
	}
	else if (col_or_row_num < rocks.size()*2)
	{
		for (size_t i = 0; i < num_rocks+1; ++i)
			if (rocks[col_or_row_num-rocks.size()][rocks.size()-i].down)
				return -3;
		for (size_t i = 0; i < num_rocks+1; ++i)
			rocks[col_or_row_num-rocks.size()][rocks.size()-i].down = true;
	}
	else if (col_or_row_num < rocks.size()*3)
	{
		for (size_t i = 0; i < num_rocks; i++)
			if (rocks[i][col_or_row_num-rocks.size()*2].down)
				return -3;
		for (size_t i = 0; i < num_rocks; i++)
			rocks[i][col_or_row_num-rocks.size()*2].down = true;
	}
	else if (col_or_row_num < rocks.size()*4)
	{
		for (size_t i = 0; i < num_rocks+1; ++i)
			if (rocks[rocks.size()-i][col_or_row_num-rocks.size()*3].down)
				return -3;
		for (size_t i = 0; i < num_rocks+1; ++i)
			rocks[rocks.size()-i][col_or_row_num-rocks.size()*3].down = true;
	}
	else
		return -2;
	return 0;
}

void Board::print()
{
	cout << "The board is:\n\n";
	for (size_t i = 0; i < rocks.size(); i++)
	{
		cout << "\n  ";
		for (size_t j = 0; j < rocks.size(); j++)
			if (rocks[i][j].down)
				cout << " *";
			else
			{
				cout << "  ";
			}
	}
}