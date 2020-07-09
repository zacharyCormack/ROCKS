#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Board
{
	vector < vector < char > > rocks;
public:
	void print();
	unsigned get_size();
	bool isover();
	void toggle_r(unsigned, unsigned);
	void clear_r();
	bool check_r(unsigned, unsigned);
	bool validate(bool);
	Board(unsigned);
};