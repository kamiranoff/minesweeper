#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

#define BOMB  " * ";
#define UNDISCOVERED_CELL " + ";
#define FREE_CELL "   ";
#define UP 'w';
#define DOWN 's';
#define LEFT 'a';
#define RIGHT 'd';
#define USER_POSITION " + ";
#define PRESS 'p';

using namespace std;

int lines = 9, columns = 9, bombs = 10;
int is_game_finished = 0;
string board[100][100];
string user_board[100][100];
int user_line = 0;
int user_col = 0;

int compute_neighbours(int line, int col);


bool is_bomb(int line, int col) {
    return board[line][col] == BOMB;
}


bool is_inside_field(int line, int col) {
    return line >= 0 && line < lines && col >= 0 && col < columns;
}

void place_bombs() {
    vector<pair<int, int>> positions;
    for (int line = 0; line < lines; ++line) {
        for (int col = 0; col < columns; ++col) {
            positions.emplace_back(make_pair(line, col));
        }
    }
    std::random_device randomDevice;
    std::mt19937 rng(randomDevice());
    std::shuffle(positions.begin(), positions.end(), rng);

    for (int bomb = 0; bomb < bombs; ++bomb) {
        board[positions[bomb].first][positions[bomb].second] = BOMB;
    }
}

string get_neighbour_bomb_count(int line, int col) {
    int num_bombs = 0;

    for (int line_offset = -1; line_offset <= 1; ++line_offset) {
        for (int col_offset = -1; col_offset <= 1; ++col_offset) {
            bool isBomb = is_bomb(line + line_offset, col + col_offset);
            int next_line = line + line_offset;
            int next_column = col + col_offset;

            if (isBomb && is_inside_field(next_line, next_column)) {
                ++num_bombs;
            }
        }
    }

    return " " + to_string(num_bombs) + " ";
}

void init_board() {
    for (int line = 0; line < lines; ++line) {
        for (int col = 0; col < columns; ++col) {
            board[line][col] = user_board[line][col] = UNDISCOVERED_CELL;
        }
    }
    place_bombs();

    for (int line = 0; line < lines; ++line) {
        for (int col = 0; col < columns; ++col) {
            bool isBomb = is_bomb(line, col);
            if (!isBomb) {
                board[line][col] = get_neighbour_bomb_count(line, col);
            }
        }
    }
}

void print_board() {
    for (int line = 0; line < lines; ++line) {
        for (int col = 0; col < columns; ++col) {
            cout << user_board[line][col];
        }
        cout << '\n';
    }
}

void trigger_press(int line, int col) {
    char press = PRESS;
    string bomb = BOMB;
    string p(1, press);
    if (user_board[line][col] == p) {
        return;
    }

    if (board[line][col] == bomb) {
        is_game_finished = 1;
        cout << "GAME OVER!\n";
        for (int line = 0; line < lines; ++line) {
            for (int col = 0; col < columns; ++col) {
                if (board[line][col] == bomb) {
                    cout << bomb;
                }
            }
        }
    } else if (board[line][col] == " 0 ") {
        user_board[line][col] = FREE_CELL;
    } else {
        user_board[line][col] = board[line][col];
    }
    cout << '\n';
}

void process_command(char command) {
    char up = UP;
    char down = DOWN;
    char left = LEFT;
    char right = RIGHT;
    char press = PRESS;
    string user_position = USER_POSITION;

    int next_line = user_line;
    int next_col = user_col;

    if (command == up) {
        --next_line;
    } else if (command == down) {
        ++next_line;
    } else if (command == left) {
        --next_col;
    } else if (command == right) {
        ++next_col;
    }

    if (!is_inside_field(next_line, next_col)) {
        return;
    }

    if (user_board[user_line][user_col] == user_position) {
        user_board[user_line][user_col] = UNDISCOVERED_CELL;
    }
    user_line = next_line;
    user_col = next_col;
    user_board[next_line][next_col] = USER_POSITION;

    if (command == press) {
        trigger_press(user_line, user_col);
    }
}

void start_game() {
    user_line = user_col = 0;
    is_game_finished = 0;
    init_board();
    user_board[user_line][user_col] = USER_POSITION;

}

void start() {
    srand(time(nullptr));
    start_game();
    while (!is_game_finished) {
        print_board();
        char command;
        cout << "Input command: ";
        cin >> command;
        process_command(command);
    }
}
