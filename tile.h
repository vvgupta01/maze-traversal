/**
 * @file tile.h
 * Definition of tile class.
 */

/**
 * Tile representing a single square unit in a maze. Each
 * tile contains a top and left wall (ignoring maze borders).
 * @author Vaibhav Gupta
 */
class Tile {
    public:
        /**
         * Constructor to create a tile.
         * @param x X-coordinate of tile.
         * @param y Y-coordinate of tile.
         * @param id Unique ID of tile.
         */
        Tile(unsigned x, unsigned y, unsigned id);

        /**
         * Removes either the top or left wall.
         * @param dir Direction to remove wall (0 = top, 1 = left).
         */
        void remove_wall(unsigned dir);

        /**
         * Returns whether a wall exists or not.
         * @param dir Direction of wall (0 = top, 1 = left).
         * @returns Boolean representing if the wall exists or not.
         */
        bool has_wall(unsigned dir);

        unsigned x, y, id;

    private:
        bool walls[2] = {true, true};
};