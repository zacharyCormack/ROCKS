#pragma once
#include "Board.hpp"
#include <string>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <unistd.h>

bool ask(char*);
void printrules();
bool usermove(Board*);
bool compmove(Board*);
void playgame(bool(*)(Board*), bool(*)(Board*), const char*, const char*);