#pragma once
#include "Board.hpp"

bool ask(char*);
void printrules();
bool usermove(Board*);
bool compmove(Board*);
void playgame(bool(*)(Board*), bool(*)(Board*));