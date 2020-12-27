
#include <iostream>

#include "maze.h"

int get_input(const string &prompt) {
    string input;
    cout << prompt << ": ";
    std::getline(cin, input);
    return std::stoi(input);
}

unsigned get_dimension(const string &prompt) {
    int dim = get_input(prompt);
    while (dim < 2 || dim > 1000) {
        cout << "Invalid Dimension" << endl;
        dim = get_input(prompt); 
    }
    return dim;
}

void run(unsigned width, unsigned height, int type) {
    if (width < 2 || width > 1000 || height < 2 || 
        height > 1000 || type < 1 || type > 3) {
        cout << "Invalid Parameter" << endl;
        exit(0);
    }

    Maze maze(width, height);

    vector<Tile*> bfs_search;
    vector<Tile*> dfs_search;

    vector<Tile*> bfs_path = maze.bfs(bfs_search, type);
    vector<Tile*> dfs_path = maze.dfs(dfs_search, type);

    cout << endl;
    cout << "Visualizing BFS Search..." << flush;
    maze.visualize(bfs_search, bfs_path, "bfs");
    cout << "Done" << endl;

    cout << "Visualizing DFS Search..." << flush;
    maze.visualize(dfs_search, dfs_path, "dfs");
    cout << "Done" << endl;
}

int main(int argc, char** argv) {
    if (argc == 1) {
        cout << "[1] Shortest-Path BFS/DFS" << endl << "[2] Set-Path BFS/DFS" << 
            endl << "[3] Longest-Path BFS/DFS" << endl;
        int type = get_input("Select Type");
        while (type < 1 || type > 3) {
            cout << "Invalid Type" << endl;
            type = get_input("Select Type");
        }

        cout << endl;
        unsigned width = get_dimension("Enter Width (2-1000)");
        unsigned height = get_dimension("Enter Height (2-1000)");
        run(width, height, type);
    } else {
        run(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]));
    }
}