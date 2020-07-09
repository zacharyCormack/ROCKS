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
		break;
	case (char)0:
		rocks[y][x] = (char)2;
		break;
	default:
		rocks[y][x] = (char)0;
		break;
	}
}

bool Board::check_r(unsigned x, unsigned y)
{
	if (rocks[y][x] == (char)0)
		return false;
	return true;
}

bool rules_message(bool r_one, bool r_two, bool r_three, bool r_four)
{
	cout <<
		"\n\e[5;3" << (r_one ? '2' : '1') << "m"
		" *\e[0m at least one rock on the perimeter of the grid is removed\n"
		"\e[5;3" << (r_two ? '2' : '1') << "m"
		" *\e[0m if any rocks removed on the perimeter are adjacent, then a rock must be removed from a corner\n"
		"\e[5;3" << (r_three ? '2' : '1') << "m"
		" *\e[0m all the rocks removed are in a straight line\n"
		"\e[5;3" << (r_four ? '2' : '1') << "m"
		" *\e[0m no two rocks removed have a space between them\n\n";
	return r_one && r_two && r_three && r_four;
	return false;
}

bool Board::validate(bool message)
{
	unsigned first_x = -1;
	unsigned first_y = -1;
	unsigned last_x = -1;
	unsigned last_y = -1;
	int num_dots = 0;
	bool rule_one = false;
	bool rule_two = true;
	bool rule_three = true;
	bool rule_four = true;
	for (unsigned i = 0; i < rocks.size(); i++)
		for (unsigned j = 0; j < rocks.size(); j++)
			if (rocks[i][j]==(char)2)
				if (i == 0 || i == rocks.size()-1 || j == 0 || j == rocks.size()-1)
					if (first_x >= rocks.size())
					{
						first_x = j;
						first_y = i;
						 last_x = j;
						 last_y = i;
						 num_dots++;
						 rule_one = true;
					}
					else
					{
						last_x = j;
						last_y = i;
						num_dots++;
						rule_one = true;
					}
				else if (first_x >= rocks.size())
				{
					first_x = j;
					first_y = i;
					 last_x = j;
					 last_y = i;
					 num_dots++;
				}
				else
				{
					last_x = j;
					last_y = i;
					num_dots++;
				}
	if (first_x >= rocks.size())
		return message ? rules_message(false, false, false, false) : false;
	if (first_x == last_x)
	{
		if (first_y != 0 && last_y != rocks.size()-1 && num_dots > 1)
			rule_two = false;
		if (last_y - first_y < num_dots-1)
			rule_three = false;
		else if (last_y - first_y >= num_dots)
			rule_four = false;
		for (unsigned i = first_y; i < last_y; ++i)
			if (rocks[i][first_x] != (char)2)
				rule_four = false;
	}
	else if (first_y == last_y)
	{
		if (first_x != 0 && last_x != rocks.size()-1 && num_dots > 1)
			rule_two = false;
		if (last_x - first_x < num_dots-1)
			rule_three = false;
		else if (last_x - first_x >= num_dots)
			rule_four = false;
		for (unsigned i = first_x; i < last_x; ++i)
			if (rocks[first_y][i] != (char)2)
				rule_four = false;
	}
	else
		rule_three = rule_four = false;
	return message ? rules_message(rule_one, rule_two, rule_three, rule_four) : rule_one && rule_two && rule_three && rule_four;
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
				cout << "\e[5;35m *\e[0m";
	}
}