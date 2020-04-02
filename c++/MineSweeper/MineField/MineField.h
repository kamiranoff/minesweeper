//
// Created by Kevin Amiranoff on 01/04/2020.
//

#ifndef MINESWEEPER_MINEFIELD_H
#define MINESWEEPER_MINEFIELD_H


class MineField {
private:
    class Tile {
    public:
        enum class State {
            Hidden,
            Flagged,
            Revealed
        };
    public:
        void SpawnMine();

        bool HasMine() const;

    private:
        State state = State::Hidden;
        bool hasMine = false;
    };


public:
    MineField(int nMines);

private:
    static constexpr int width = 20;
    static constexpr int height = 16;
    Tile field[width * height];
};


#endif //MINESWEEPER_MINEFIELD_H
