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

// Function to find the meet-in-the-middle point
pair<int, int> meetInTheMiddle(vector<vector<int>> fidpDist, vector<vector<int>> bidpDist) {
    int rows = fidpDist.size();
    int cols = fidpDist[0].size();
    int minSum = numeric_limits<int>::max();
    pair<int, int> meetPoint = {-1, -1};

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int sum = fidpDist[i][j] + bidpDist[i][j] - fidpDist[0][0];
            if (sum < minSum) {
                minSum = sum;
                meetPoint = {i, j};
            }
        }
    }

    return meetPoint;
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

        // BIDP
        vector<vector<int>> bidpDist = bidp(grid);
        cout << "BIDP Shortest distances:" << endl;
        printGrid(bidpDist);

        // Meet-in-the-middle
        pair<int, int> meetPoint = meetInTheMiddle(fidpDist, bidpDist);
        cout << "Meet-in-the-middle point: (" << meetPoint.first << ", " << meetPoint.second << ")" << endl;

        // Print shortest distance
        int shortestDistance = fidpDist[meetPoint.first][meetPoint.second] + bidpDist[meetPoint.first][meetPoint.second] - grid[meetPoint.first][meetPoint.second];
 //     cout <<"fidp - "<<fidpDist[meetPoint.first][meetPoint.second]<<endl;
 //     cout <<"bidp -"<<bidpDist[meetPoint.first][meetPoint.second]<<endl;
 //     cout <<"Grid - "<<grid[meetPoint.first][meetPoint.second]<<endl;
        cout << "Shortest distance: " << shortestDistance << endl;

        i++;
    }

    return 0;
}