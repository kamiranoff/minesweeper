//
// Created by Kevin Amiranoff on 01/04/2020.
//

#include "MineField.h"
#include <assert.h>
#include <random>

void MineField::Tile::SpawnMine() {
    assert(!hasMine);
    hasMine = true;
}

bool MineField::Tile::HasMine() const {
    return hasMine;
}

MineField::MineField(int nMines) {
    assert(nMines > 0 && nMines < width * height);
    std::random_device randomDevice;
    std::mt19937 rng(randomDevice());
    std::uniform_int_distribution<int> xDist(0, width - 1);
    std::uniform_int_distribution<int> yDist(0, height - 1);

    for (int nSpawned = 0; nSpawned < nMines; ++nSpawned) {

    }
}
