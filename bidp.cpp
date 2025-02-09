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

// Function to implement BIDP
vector<vector<int>> bidp(vector<vector<int>> grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Initialize distance matrix
    vector<vector<int>> dist(rows, vector<int>(cols, numeric_limits<int>::max()));
    dist[rows - 1][cols - 1] = grid[rows - 1][cols - 1];

    // Backward iteration
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = cols - 1; j >= 0; j--) {
            if (i < rows - 1) {
                dist[i][j] = min(dist[i][j], dist[i + 1][j] + grid[i][j]);
            }
            if (j < cols - 1) {
                dist[i][j] = min(dist[i][j], dist[i][j + 1] + grid[i][j]);
            }
        }
    }

    return dist;
}

// Function to construct the previous cell matrix for BIDP
vector<vector<pair<int, int>>> constructBIDPPrevMatrix(vector<vector<int>> dist, vector<vector<int>> grid) {
    int rows = dist.size();
    int cols = dist[0].size();

    vector<vector<pair<int, int>>> prev(rows, vector<pair<int, int>>(cols, {-1, -1}));
    for (int x = rows - 1; x >= 0; x--) {
        for (int y = cols - 1; y >= 0; y--) {
            if (x < rows - 1) {
                if (dist[x][y] == dist[x + 1][y] + grid[x][y]) {
                    prev[x][y] = {x + 1, y};
                }
            }
            if (y < cols - 1) {
                if (dist[x][y] == dist[x][y + 1] + grid[x][y]) {
                    prev[x][y] = {x, y + 1};
                }
            }
        }
    }

    return prev;
}

// Function to print the BIDP path
void printBIDPPath(vector<vector<pair<int, int>>> prev, int rows, int cols) {
    int x = 0;
    int y = 0;
    cout << "(" << x << ", " << y << ")";
    while (x < rows && y < cols) {
        pair<int, int> next = prev[x][y];
        if (next.first == -1 && next.second == -1) {
            break;
        }
        x = next.first;
        y = next.second;
        cout << " -> (" << x << ", " << y << ")";
    }
    cout << endl;
}

int main() {
    int i = 1;

    while (i < 2) {
        int rows = (int)(pow(2, i));
        int cols = (int)(pow(2, i));

        vector<vector<int>> grid = buildGrid(rows, cols);
        cout << "Grid:" << rows << "x" << cols << endl;
        printGrid(grid);

        // BIDP
        vector<vector<int>> bidpDist = bidp(grid);
        cout << "BIDP Shortest distances:" << endl;
        printGrid(bidpDist);

        int totalShortestDistanceBIDP = bidpDist[0][0];
        cout << "Total shortest distance (BIDP): " << totalShortestDistanceBIDP << endl;

        vector<vector<pair<int, int>>> bidpPrev = constructBIDPPrevMatrix(bidpDist, grid);
        cout << "BIDP Path: ";
        printBIDPPath(bidpPrev, rows, cols);

        i++;
    }

    return 0;
}