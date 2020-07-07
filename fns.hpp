#pragma once
#include "Board.hpp"

bool ask(char*);
void printrules();
void usermove(Board*);
void compmove(Board*);
void playgame(void(*)(Board*), void(*)(Board*));