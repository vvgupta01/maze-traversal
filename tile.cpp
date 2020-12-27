/**
 * @file tile.cpp
 * Implementation of tile class.
 */ 

#include "tile.h"

Tile::Tile(unsigned x, unsigned y, unsigned id) {
    this -> x = x;
    this -> y = y;
    this -> id = id;
}

void Tile::remove_wall(unsigned dir) {
    walls[dir] = false; 
}

bool Tile::has_wall(unsigned dir) {
    return walls[dir];
}