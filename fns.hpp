#pragma once
#include "Board.hpp"
#include <curses.h>

bool ask(char*);
void usermove(Board*);
void compmove(Board*);
void playgame(void(*)(Board*), void(*)(Board*));