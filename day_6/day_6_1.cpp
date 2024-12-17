#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// Directions global variable
std::vector<std::pair<int, int>> directions = {
    {-1, 0}, // Up 
    {0, 1},  // Right
    {1, 0},  // Down 
    {0, -1}, // Left 
};

// Guardfaces global variable
std::vector<char> guardFaces = {
        '^',
        '>',
        'v',
        '<'
};

void defaultPosition(std::pair<int, int>& currentPosition, const std::vector<std::vector<char>>& grid) {
    int rowCount = grid.size();
    int columnCount = grid[0].size();

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < columnCount; j++) {
            if (std::find(guardFaces.begin(), guardFaces.end(), grid[i][j]) != guardFaces.end()) {
                currentPosition.first = i;
                currentPosition.second = j;
                return;
            }
        }
    }
}

// Read's file from puzzle and puts it into grid
std::vector<std::vector<char>> readPuzzle(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::vector<std::vector<char>> grid;

    std::string line; 
    while(std::getline(inputFile, line)) {
        std::vector<char> row(line.begin(), line.end()); // Creates row vector of each character
        grid.push_back(row); // pushes row to row in 2D vector
    }

    inputFile.close();
    return grid;
}

void updateGuard(std::vector<std::vector<char>>& grid, bool& endFlag, int rowCount, int columnCount, std::pair<int, int>& currentPosition) {
    int direction = 0;
    int y = currentPosition.first;
    int x = currentPosition.second;
    int newy = 0;
    int newx = 0;

    if (grid[y][x] == guardFaces[0]) { // ^
        direction = 0;
    }
    else if (grid[y][x] == guardFaces[1]) { // >
        direction = 1;
    }
    else if (grid[y][x] == guardFaces[2]) { // v
        direction = 2; 
    }
    else if (grid[y][x] == guardFaces[3]) { // <
        direction = 3;
    }

    newy = y + directions[direction].first;
    newx = x + directions[direction].second;

    if (newx < 0 || newy < 0 || newy >= rowCount || newx >= columnCount) {
        endFlag = true;
        grid[y][x] = 'X';
        return;
    }

    // No obstacle
    if (grid[newy][newx] == '.' || grid[newy][newx] == 'X') {
        grid[newy][newx] = guardFaces[direction];
        grid[y][x] = 'X';
        std::cout << "Guard position after move: (" << newx << ", " << newy << ") Direction: " << guardFaces[direction] << std::endl;
        currentPosition = {newy, newx};
    }

    // Obstacle
    else if (grid[newy][newx] == '#') {
        std::cout << "Guard at (" << x << ", " << y << ") encountered obstacle, rotating to " << guardFaces[(direction + 1) % 4] << std::endl;

        newy = y + directions[(direction + 1) % 4].first;
        newx = x + directions[(direction + 1) % 4].second;

        if (newx < 0 || newy < 0 || newy >= rowCount || newx >= columnCount) {
            endFlag = true;
            grid[y][x] = 'X';
            return;
        }
        grid[newy][newx] = guardFaces[(direction + 1) % 4];
        grid[y][x] = 'X';
        std::cout << "Guard at (" << x << ", " << y << ") rotated and moved to (" << newx << ", " << newy << ")\n";
        currentPosition = {newy, newx};
    }
}

void runSimulation(std::vector<std::vector<char>>& grid, bool& endFlag, std::pair<int, int> currentPosition) {
    int rowCount = grid.size();
    int columnCount = grid[0].size();
    std::cout << "\nTotal size:" << rowCount << " x " << columnCount << std::endl;

    while(!endFlag) {
        updateGuard(grid, endFlag, rowCount, columnCount, currentPosition);
        //std::cout << "Successful tick." << std::endl;
    }
    return;
}

int countVisited(const std::vector<std::vector<char>>& grid) {
    int count = 0;
    for (const auto& row : grid) {
        count += std::count(row.begin(), row.end(), 'X');
    }
    return count;
}

int main() {
    std::cout << "Starting" << std::endl;
    std::vector<std::vector<char>> grid = readPuzzle("input.txt");
    
    std::pair<int, int> currentPosition = {0, 0};
    defaultPosition(currentPosition, grid);
    grid[currentPosition.first][currentPosition.second] = 'X';

    bool endFlag = false;
    int iterationCount;

    runSimulation(grid, endFlag, currentPosition);

    std::cout << "Number of spaces guard visited: " << countVisited(grid) << std::endl;
}