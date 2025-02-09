#include <iostream>
#include <vector>
#include <limits>
#include <math.h>
#include <cstdlib>

using namespace std;

// Function to build the grid
vector<vector<int>> buildGrid(int rows, int cols) {
    int r = 0;
    vector<vector<int>> v(rows, vector<int>(cols, 0));
    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            r = rand() % 9 + 1;
            v[i][j] = r;
        }
    }
    return v;
}

// Function to print the grid
void printGrid(vector<vector<int>> grid) {
    for (vector<int> row : grid) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Function to implement FIDP
vector<vector<int>> fidp(vector<vector<int>> grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Initialize distance matrix
    vector<vector<int>> dist(rows, vector<int>(cols, numeric_limits<int>::max()));
    dist[0][0] = grid[0][0];

    // Forward iteration
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i > 0) {
                dist[i][j] = min(dist[i][j], dist[i - 1][j] + grid[i][j]);
            }
            if (j > 0) {
                dist[i][j] = min(dist[i][j], dist[i][j - 1] + grid[i][j]);
            }
        }
    }

    return dist;
}


// Function to construct the previous cell matrix
vector<vector<pair<int, int>>> constructPrevMatrix(vector<vector<int>> dist, vector<vector<int>> grid) {
    int rows = dist.size();
    int cols = dist[0].size();

    vector<vector<pair<int, int>>> prev(rows, vector<pair<int, int>>(cols, {-1, -1}));
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            if (x > 0) {
                if (dist[x][y] == dist[x - 1][y] + grid[x][y]) {
                    prev[x][y] = {x - 1, y};
                }
            }
            if (y > 0) {
                if (dist[x][y] == dist[x][y - 1] + grid[x][y]) {
                    prev[x][y] = {x, y - 1};
                }
            }
        }
    }

    return prev;
}


// Function to print the FIDP path
void printPath(vector<vector<pair<int, int>>> prev, int i, int j) {
    if (prev[i][j] == pair<int, int>{-1, -1}) {
        cout << "(" << i << ", " << j << ")";
    } else {
        printPath(prev, prev[i][j].first, prev[i][j].second);
        cout << " -> (" << i << ", " << j << ")";
    }
}


int main() {
    int i = 1;

    while (i < 2) {
        int rows = (int)(pow(2, i));
        int cols = (int)(pow(2, i));

        vector<vector<int>> grid = buildGrid(rows, cols);
        cout << "Grid:" << rows << "x" << cols << endl;
        printGrid(grid);

        // FIDP
        vector<vector<int>> fidpDist = fidp(grid);
        cout << "FIDP Shortest distances:" << endl;
        printGrid(fidpDist);

        int totalShortestDistanceFIDP = fidpDist[rows - 1][cols - 1];
        cout << "Total shortest distance (FIDP): " << totalShortestDistanceFIDP << endl;

        vector<vector<pair<int, int>>> fidpPrev = constructPrevMatrix(fidpDist, grid);
        cout << "FIDP Paths:" << endl;
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < cols; y++) {
                cout << "Path to (" << x << ", " << y << "): ";
                printPath(fidpPrev, x, y);
                cout << endl;
            }
        }

        i++;
    }

    return 0;
}