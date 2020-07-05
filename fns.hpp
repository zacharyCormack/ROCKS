#pragma once
#include "Board.hpp"
#include <cstdio>

bool ask(char*);
void usermove(Board*);
void compmove(Board*);
void playgame(void(*)(Board*), void(*)(Board*));