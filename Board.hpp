#pragma once
#include "Rock.hpp"
#include <iostream>
#include <vector>
using namespace std;

class Board
{
	vector < vector < Rock > > rocks;
public:
	void print();
	int move(unsigned, unsigned);
	Board(unsigned);
};