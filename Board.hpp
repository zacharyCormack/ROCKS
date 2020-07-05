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
	int move(unsigned, unsigned);
	void toggle_r(unsigned, unsigned);
	void clear_r();
	bool validate();
	Board(unsigned);
};