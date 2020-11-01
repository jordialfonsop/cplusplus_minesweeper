#include "Minesweeper_functions.h"

int lines, columns, bombs;
bool is_game_finished = false;
char board[100][100], user_board[100][100];
int user_line, user_column;

bool is_inside(int line, int column) {
	return 0 <= line && line < lines && 0 <= column && column < columns;
}

void print_board(int lines, int columns)
{
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << user_board[i][j] << " ";
		}
		cout << "" << endl;
	}
	cout << "\n" << endl;
}

void place_bombs()
{
	vector<pair<int, int>> positions;
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			positions.push_back(make_pair(i, j));
		}
		random_shuffle(positions.begin(), positions.end());
	}
	for (int idx = 0; idx < bombs; idx++) {
		board[positions[idx].first][positions[idx].second] = BOMB;
	}
}

int compute_neighbours(int line, int column) {
	int count = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int future_line = line + i;
			int future_column = column + j;
			if ((is_inside(future_line, future_column) == true) && (board[future_line][future_column] == BOMB)) {
				count++;
			}
		}
	}
	return count;
}

void init_board()
{
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			board[i][j] = user_board[i][j] = FREE_CELL;
		}
	}
	place_bombs();
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (board[i][j] != BOMB) {
				board[i][j] = compute_neighbours(i, j) + '0';
			}
		}
	}

}

void trigger_press(int line, int column) {
	switch (board[line][column]) {
	case BOMB:
		is_game_finished = true;
		cout << "\n GAME OVER \n" << endl;

		for (int i = 0; i < lines; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (board[i][j] == BOMB) {
					cout << BOMB << " ";
				}
				else {
					cout << user_board[i][j] << " ";
				}
			}
			cout << endl;
		}

		break;
	case not FREE_CELL:
		return;
	default:
		user_board[line][column] = board[line][column];
		//empty_space_recursion(line, column);
		if (user_board[line][column] == '0') {
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int next_line = line + i, next_column = column + j;
					if (is_inside(next_line, next_column) == true) {
						user_board[next_line][next_column] = board[next_line][next_column];
					}

				}
			}
		}
		break;
	}
}

void process_command(char command) {
	int next_line = user_line, next_column = user_column;
	switch (command) {
	case UP:
		--next_line;
		break;
	case DOWN:
		++next_line;
		break;
	case LEFT:
		--next_column;
		break;
	case RIGHT:
		++next_column;
		break;
	default:
		break;
	}

	if (is_inside(next_line, next_column) == false) {
		return;
	}
	if (user_board[user_line][user_column] == USER_POS)
	{
		user_board[user_line][user_column] = FREE_CELL;
	}
	user_line = next_line;
	user_column = next_column;
	if (user_board[user_line][user_column] == FREE_CELL) {
		user_board[user_line][user_column] = USER_POS;
	}


	if (command == PRESS_COMMAND) {
		trigger_press(user_line, user_column);
	}
	if (command == FLAG_COMMAND) {
		if (user_board[user_line][user_column] == FLAG)
		{
			user_board[user_line][user_column] = USER_POS;
		}
		else {
			user_board[user_line][user_column] = FLAG;
		}

	}

}

void start_game() {
	user_line = user_column = 0;
	is_game_finished = false;
	init_board();
	user_board[user_line][user_column] = USER_POS;
}

bool check_win(int lines, int columns, int bombs) {
	int count = 0;
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (board[i][j] == user_board[i][j]) {
				count++;
			}
		}
	}
	if (count == ((lines * columns) - bombs)) {
		return true;
	}
	else {
		return false;
	}
}

void game() {
	int difficulty;
	bool quit = false;
	while (quit == false)
	{
		cout << "\n WELCOME TO MINESWEEPER, 1 FOR EASY, 2 FOR MEDIUM, 3 FOR HARD, 4 TO QUIT: ";
		cin >> difficulty;

		switch (difficulty) {
		case 1:

			srand(time(0));
			lines = 9;
			columns = 9;
			bombs = 10;

			start_game();

			while (is_game_finished == false) {
				print_board(lines, columns);
				char command;
				cout << "\n Input command (WASD to MOVE, P to select, F for flag): ";
				cin >> command;
				process_command(command);
				if (is_game_finished != true)
				{
					is_game_finished = check_win(lines, columns, bombs);
					if (is_game_finished == true) {
						cout << "\n CONGRATULATIONS!!! YOU WON!!! \n";
					}
				}

			}
			break;
		case 2:

			srand(time(0));
			lines = 16;
			columns = 16;
			bombs = 40;

			start_game();

			while (is_game_finished == false) {
				print_board(lines, columns);
				char command;
				cout << "Input command (WASD to MOVE, P to select, F for flag): ";
				cin >> command;
				process_command(command);
				if (is_game_finished != true)
				{
					is_game_finished = check_win(lines, columns, bombs);
					if (is_game_finished == true) {
						cout << "\n CONGRATULATIONS!!! YOU WON!!! \n";
					}
				}
			}
			break;
		case 3:

			srand(time(0));
			lines = 16;
			columns = 30;
			bombs = 99;

			start_game();

			while (is_game_finished == false) {
				print_board(lines, columns);
				char command;
				cout << "Input command (WASD to MOVE, P to select, F for flag): ";
				cin >> command;
				process_command(command);
				if (is_game_finished != true)
				{
					is_game_finished = check_win(lines, columns, bombs);
					if (is_game_finished == true) {
						cout << "\n CONGRATULATIONS!!! YOU WON!!! \n";
					}
				}
			}
			break;
		case 4:
			quit = true;
			break;
		default:
			cout << "\n Incorrect Input.";
			break;
		}
	}


}


