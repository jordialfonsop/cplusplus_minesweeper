#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#define BOMB '*'
#define FREE_CELL 'X'
#define USER_POS '$'
#define FLAG '+'

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

#define PRESS_COMMAND 'p'
#define FLAG_COMMAND 'f'

using namespace std;

bool is_inside(int line, int column);
void print_board(int lines, int columns);
void place_bombs();
int compute_neighbours(int line, int column);
void init_board();
void trigger_press(int line, int column);
void process_command(char command);
void start_game();
bool check_win(int lines, int columns, int bombs);
void game();
