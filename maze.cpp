/**
 * @file maze.cpp
 * Implementation of maze class.
 */

#include <queue>
#include <stack>
#include <random>
#include <algorithm>
#include <chrono>

#include "maze.h"

Maze::Maze(unsigned width, unsigned height) {
    this -> width = width;
    this -> height = height;

    auto start = chrono::steady_clock::now();
    int num_walls = generate();
    draw_maze();

    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    unsigned total_walls = 2 * width * height - width - height;
    cout << endl << "Generated " << width << "x" << height << " maze (" << num_walls 
        << "/" << total_walls << " walls) in " << time << "ms" << endl << endl << flush;
}

Maze::~Maze() {
    for (unsigned x = 0; x < width; x++) {
        for (unsigned y = 0; y < height; y++) {
            delete maze[x][y];
        }
    }
}

unsigned Maze::generate() {
    maze.resize(width, vector<Tile*>(height, NULL));
    for (unsigned x = 0; x < width; x++) {
        for (unsigned y = 0; y < height; y++) {
            maze[x][y] = new Tile(x, y, x + y * width);
            if (y == 0) {
                maze[x][y] -> remove_wall(0);
            }

            if (x == 0) {
                maze[x][y] -> remove_wall(1);
            }
        }
    }

    DisjointSets sets(width * height);
    vector<pair<Tile*, Tile*>> walls = generate_walls();

    unsigned num_walls = walls.size();
    for (auto wall : walls) {
        if (!sets.is_cycle(wall.first -> id, wall.second -> id)) {
            sets.set_union(wall.first -> id, wall.second -> id);

            unsigned dir = wall.first -> x - wall.second -> x;
            maze[wall.first -> x][wall.first -> y] -> remove_wall(dir);
            num_walls--;
        }
    }
    return num_walls;
}

vector<pair<Tile*, Tile*>> Maze::generate_walls() const {
    vector<pair<Tile*, Tile*>> walls;
    for (unsigned x = 0; x < width; x++) {
        for (unsigned y = 0; y < height; y++) {
            if (x > 0) {
                walls.push_back(pair<Tile*, Tile*>(maze[x][y], maze[x - 1][y]));
            }

            if (y > 0) {
                walls.push_back(pair<Tile*, Tile*>(maze[x][y], maze[x][y - 1]));
            }
        }
    }

    auto random = std::default_random_engine { std::random_device{}() };
    std::shuffle(walls.begin(), walls.end(), random);
    return walls;
}

vector<Tile*> Maze::bfs(vector<Tile*> &search, int type) const {
    auto start = chrono::steady_clock::now();
    pair<int, int> adj[4] = {pair<int, int>(0, -1), pair<int, int>(-1, 0), 
        pair<int, int>(0, 1), pair<int, int>(1, 0)};

    queue<Tile*> bfs_queue;
    vector<vector<Tile*>> predecessor(width, vector<Tile*>(height, NULL));

    bfs_queue.push(maze[0][0]);
    predecessor[0][0] = maze[0][0];

    unsigned exits = 0;
    Tile *current = maze[0][0];
    while ((type == 1 && exits < 1) || (type == 2 && current -> id != width * height - 1) || 
        (type == 3 && exits < width)) {
        current = bfs_queue.front();
        bfs_queue.pop();
        search.push_back(current);

        if (current -> y == height - 1) {
            exits++;
        }

        for (unsigned i = 0; i < 4; i++) {
            int to_x = current -> x + adj[i].first;
            int to_y = current -> y + adj[i].second;
            if (can_traverse(current, to_x, to_y) && predecessor[to_x][to_y] == NULL) {
                bfs_queue.push(maze[to_x][to_y]);
                predecessor[to_x][to_y] = current;
            }
        }
    }

    vector<Tile*> path;
    while (current -> id != 0) {
        path.push_back(current);
        current = predecessor[current -> x][current -> y];
    }
    path.push_back(maze[0][0]);
    std::reverse(path.begin(), path.end());

    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    float coverage = 100.0 * search.size() / (width * height);
    string type_str = type == 1 ? "Shortest-Path" : "Set-Path";
    type_str = type == 2 ? "Set-Path" : "Longest-Path";
    cout << "Completed " << type_str << " BFS in " << time << "ms" << endl;
    cout << "Path Length: " << path.size() << "  Search Coverage: " << coverage 
        << "%" << endl << flush;
    return path;
}

vector<Tile*> Maze::dfs(vector<Tile*> &search, int type) const {
    auto start = chrono::steady_clock::now();
    pair<int, int> adj[4] = {pair<int, int>(0, -1), pair<int, int>(-1, 0), 
        pair<int, int>(0, 1), pair<int, int>(1, 0)};

    stack<Tile*> dfs_stack;
    vector<vector<Tile*>> predecessor(width, vector<Tile*>(height, NULL));
    vector<vector<bool>> is_visited(width, vector<bool>(height, false));
    dfs_stack.push(maze[0][0]);
    
    unsigned exits = 0;
    Tile *current = maze[0][0];
    while ((type == 1 && exits < 1) || (type == 2 && current -> id != width * height - 1) || 
        (type == 3 && exits < width)) {
        current = dfs_stack.top();
        dfs_stack.pop();

        if (!is_visited[current -> x][current -> y]) {
            is_visited[current -> x][current -> y] = true;
            search.push_back(current);
            if (current -> y == height - 1) {
                exits++;
            }

            for (int i = 0; i < 4; i++) {
                int to_x = current -> x + adj[i].first;
                int to_y = current -> y + adj[i].second;
                if (can_traverse(current, to_x, to_y) && !is_visited[to_x][to_y]) {
                    dfs_stack.push(maze[to_x][to_y]);
                    predecessor[to_x][to_y] = current;
                }
            }
        }
    }

    vector<Tile*> path;
    while (current -> id != 0) {
        path.push_back(current);
        current = predecessor[current -> x][current -> y];
    }
    path.push_back(maze[0][0]);
    std::reverse(path.begin(), path.end());

    auto end = chrono::steady_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    float coverage = 100.0 * search.size() / (width * height);
    string type_str = type == 1 ? "Shortest-Path" : "Set-Path";
    type_str = type == 2 ? "Set-Path" : "Longest-Path";
    cout << "Completed " << type_str << " DFS in " << time << "ms" << endl;
    cout << "Path Length: " << path.size() << "  Search Coverage: " << coverage 
        << "%" << endl << flush;
    return path;
}

bool Maze::can_traverse(Tile * tile, int to_x, int to_y) const {
    if (to_x < 0 || to_x >= width || to_y < 0 || to_y >= height) {
        return false;
    }

    if (tile -> y - to_y == 1) {
        return !tile -> has_wall(0);
    } else if (tile -> x - to_x == 1) {
        return !tile -> has_wall(1);
    } else if (to_y - tile -> y == 1) {
        return !maze[to_x][to_y] -> has_wall(0);
    } 
    return !maze[to_x][to_y] -> has_wall(1);
}

void Maze::draw_maze() {
    png.resize(width * 10 + 1, height * 10 + 1);
    HSLAPixel black = HSLAPixel(0, 0, 0);

    for (unsigned x = 0; x < png.width(); x++) {
        png.getPixel(x, png.height() - 1) = black;
        if (x >= 10) {
            png.getPixel(x, 0) = black;
        }
    }

    for (unsigned y = 0; y < png.height(); y++) {
        png.getPixel(0, y) = black;
        png.getPixel(png.width() - 1, y) = black;
    }

    for (unsigned x = 0; x < width; x++) {
        for (unsigned y = 0; y < height; y++) {
            if (maze[x][y] -> has_wall(0)) {
                for (unsigned k = 0; k <= 10; k++) {
                    png.getPixel(x * 10 + k, y * 10) = black;
                }
            }

            if (maze[x][y] -> has_wall(1)) {
                for (unsigned k = 0; k <= 10; k++) {
                    png.getPixel(x * 10, y * 10 + k) = black;
                }
            }
        }
    }
}

void Maze::visualize(const vector<Tile*> &search, vector<Tile*> &path, const string &filename) const {
    const static string dir = "visualization/";
    const static int threshold = 10000;

    PNG maze_png(png);
    HSLAPixel red(0, 1, 0.5), green(120, 1, 0.5);

    std::reverse(path.begin(), path.end());
    Tile *dest = path.back();
    for (int k = 0; k < 10; k++) {  
        maze_png.getPixel(10 * dest -> x + k, 10 * dest -> y + 10) = HSLAPixel();
    }

    if (width * height > threshold) {
        draw_tiles(maze_png, search, red);
        draw_tiles(maze_png, path, green);
    } else {
        Animation animation;
        animate_tiles(maze_png, animation, search, red);
        animate_tiles(maze_png, animation, path, green);
        animation.write(dir + filename + "-search.gif");
    }
    maze_png.writeToFile(dir + filename + "-path.png");
}

void Maze::draw_tiles(PNG &png, const vector<Tile*> &tiles, const HSLAPixel &color) const {
    for (Tile *tile : tiles) {
        for (unsigned x = 1; x < 10; x++) {
            for (unsigned y = 1; y < 10; y++) {
                png.getPixel(10 * tile -> x + x, 10 * tile -> y + y) = color;
            }
        }
    }
}

void Maze::animate_tiles(PNG &png, Animation &animation, const vector<Tile*> &tiles,
    const HSLAPixel &color) const {
    int tpf = ceil(tiles.size() / 50 + 0.5);
    for (unsigned long i = 0; i < tiles.size(); i++) {
        for (unsigned x = 1; x < 10; x++) {
            for (unsigned y = 1; y < 10; y++) {
                png.getPixel(10 * tiles[i] -> x + x, 10 * tiles[i] -> y + y) = color;
            }
        }

        if (i % tpf == 0) {
            animation.addFrame(png);
        }
    }

    if (tiles.size() % tpf != 0) {
        animation.addFrame(png);
    }
}