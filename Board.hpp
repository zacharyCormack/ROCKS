#pragma once
#include "Rock.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Board
{
	vector < vector < Rock > > rocks;
public:
	void print(unsigned);
	unsigned get_size();
	bool isover();
	int move(unsigned, unsigned);
	Board(unsigned);
};