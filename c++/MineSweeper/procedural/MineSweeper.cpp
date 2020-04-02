#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

#define BOMB  " * ";
#define UNDISCOVERED_CELL "⬜";
#define FREE_CELL "   ";

using namespace std;

int lines = 9, columns = 9, bombs = 10;

string board[100][100];
string user_board[100][100];

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
            cout << board[line][col];
        }
        cout << '\n';
    }
}

void start() {
    srand(time(nullptr));
    init_board();
    print_board();
}
