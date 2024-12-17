// Plan:
// -------------------------------------------------------------------------------
//     - Create a visited locations set which includes each location's coordinate and direction
//     - Find default position, change positions to include direction
//     - Loop through each visited location, and place a '#' to act as an obstacle
//         (-) Make sure each loop uses a copy of the original grid, with only the # as a change
//     - Count only iterations that result in a loop
//         (-) Check for this by making a local visited locations set including coordinates and directions,
//             and compare current location of each update to every item on local set.
//                  - If the tuple at the current location is equal to a tuple in the set, then there's a loop,
//                    so return function and add to a counter
//
// IMPORTANT:
// -------------------------------------------------------------------------------
//     - PRESERVE GRID BY USING COPY FOR EACH ITERATION
//     - PRESERVE DEFAULT CURRENTPOSITION VALUE BY USING COPY FOR EACH ITERATION
//     - MODULARIZE CODE TO MAKE EASY TO READ
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <unordered_set>

struct custom_hash {
    std::size_t operator()(const std::tuple<int, int, int>& t) const {
        auto [a, b, c] = t;
        std::size_t h1 = std::hash<int>{}(a);
        std::size_t h2 = std::hash<int>{}(b);
        std::size_t h3 = std::hash<int>{}(c);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

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

bool firstRun = true;

int checkGuardFacing(int y, int x, std::vector<std::vector<char>> grid) {
    int direction = 0;
    
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

    return direction;
}

std::tuple<int, int, int> getDefaultPosition(std::vector<std::vector<char>>& grid, int rowCount, int columnCount) {
    std::tuple<int, int, int> defaultPosition;

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < columnCount; j++) {
            if (std::find(guardFaces.begin(), guardFaces.end(), grid[i][j]) != guardFaces.end()) {
                std::get<0>(defaultPosition) = i;
                std::get<1>(defaultPosition) = j;
                std::get<2>(defaultPosition) = checkGuardFacing(i, j, grid);

                std::cout << i << std::endl;
                std::cout << j << std::endl;


                grid[i][j] = '.';
            }
        }
    }

    return defaultPosition;
}

void updateGuard(std::vector<std::vector<char>>& grid, std::unordered_set<std::tuple<int, int, int>, custom_hash>& visitedPositionsSet, std::tuple<int, int, int>& currentPosition, int rowCount, int columnCount, bool& endFlag, bool&loopFlag) {
    int y = std::get<0>(currentPosition);
    int x = std::get<1>(currentPosition);
    int direction = std::get<2>(currentPosition);
    
    int newy = y + directions[direction].first;
    int newx = x + directions[direction].second;

    grid[y][x] = 'X';
    
    if (newx < 0 || newy < 0 || newy >= rowCount || newx >= columnCount) {
        endFlag = true;
        return;
    }

    if (grid[newy][newx] == '.' || grid[newy][newx] == 'X') {
        grid[y][x] = 'X';
        std::get<0>(currentPosition) = newy;
        std::get<1>(currentPosition) = newx;

        //std::cout << "New position: (" << newx << ", "<< newy << ")" << grid[newy][newx] << grid[y][x] << std::endl; 

        if (!firstRun && visitedPositionsSet.count(currentPosition)) {
            loopFlag = true;
            return;
        }
        return;
    }

    else if (grid[newy][newx] == '#') {
        grid[y][x] = 'X';
        //std::cout << "Obstacle Encountered at (" << x << ", "<< y << ") For direction: " << guardFaces[direction] << " ! Rotating." << std::endl;

        direction = (direction + 1) % 4;
        newy = y + directions[direction].first;
        newx = x + directions[direction].second;
        

        if (newx < 0 || newy < 0 || newy >= rowCount || newx >= columnCount) {
            endFlag = true;
            return;
        }

        //std::cout << "New position: (" << newx << ", "<< newy << ") -> " << grid[newy][newx] << grid[y][x] << std::endl; 
        
        std::get<0>(currentPosition) = newy;
        std::get<1>(currentPosition) = newx;
        std::get<2>(currentPosition) = direction;

        grid[y][x] = 'X';

        if (!firstRun && visitedPositionsSet.count(currentPosition)) {
            loopFlag = true;
            return;
        }

        return;
    }

    else {
        std::cout << " Simulation encountered an error! Coords: "  << grid[newy][newx] << " (" << newx << ", " << newy << ") " << grid[y][x] << std::endl;
        return;
    }
}

void runSimulation(std::vector<std::vector<char>>& grid, std::unordered_set<std::tuple<int, int, int>, custom_hash> visitedPositionsSet, std::tuple<int, int, int> defaultPosition, int rowCount, int columnCount, bool&loopFlag) {
    int y = std::get<0>(defaultPosition);
    int x = std::get<1>(defaultPosition);
    int direction = std::get<2>(defaultPosition);
    bool endFlag = false;

    std::tuple<int, int, int> currentPosition = {y, x, direction};

    while(!endFlag && !loopFlag) {
        updateGuard(grid, visitedPositionsSet, currentPosition, rowCount, columnCount, endFlag, loopFlag);
        if (!visitedPositionsSet.count(currentPosition)) {
            visitedPositionsSet.insert(currentPosition);
        }
        if (loopFlag) {
            std::cout << "Looping Coords: " << std::get<0>(currentPosition) << std::get<1>(currentPosition) << std::endl; 
            return;
        }
    }
    return;
}

std::unordered_set<std::tuple<int, int, int>, custom_hash> getVisitedPositionsSet(std::vector<std::vector<char>> grid, std::tuple<int, int, int> defaultPosition, int rowCount, int columnCount) {
    int y = std::get<0>(defaultPosition);
    int x = std::get<1>(defaultPosition);
    int direction = std::get<2>(defaultPosition);
    bool endFlag = false;
    bool loopFlag = false;

    std::tuple<int, int, int> currentPosition = {y, x, direction};
    std::unordered_set<std::tuple<int, int, int>, custom_hash> visitedPositionsSet;

    while(!endFlag) {
        if (!visitedPositionsSet.count(currentPosition)) {
            visitedPositionsSet.insert(currentPosition);
        }
        updateGuard(grid, visitedPositionsSet, currentPosition, rowCount, columnCount, endFlag, loopFlag);
    }

    firstRun = false;
    return visitedPositionsSet;
}

bool doesObstacleSimulationLoop(std::vector<std::vector<char>> &grid, std::tuple<int, int, int> defaultPosition, int rowCount, int columnCount) {
    bool loopFlag = false;
    std::unordered_set<std::tuple<int, int, int>, custom_hash> localVisitedPositionsSet;
    localVisitedPositionsSet.insert(defaultPosition);

    runSimulation(grid, localVisitedPositionsSet, defaultPosition, rowCount, columnCount, loopFlag);
    return loopFlag;
}

int doObstacleSimulations (std::vector<std::vector<char>> grid, std::unordered_set<std::tuple<int, int, int>, custom_hash> visitedPositionsSet, std::tuple<int, int, int> defaultPosition, int rowCount, int columnCount) {
    int loopCount = 0;
    int iterationCount = 0;
    
    for (const auto& state : visitedPositionsSet) {
        iterationCount++;
        std::cout << "Begin Iteration: " << iterationCount << std::endl;
        int y = std::get<0>(state), x = std::get<1>(state);

        if (y == std::get<0>(defaultPosition) && x == std::get<1>(defaultPosition)) {
            continue;
        }

        char& gridOriginal = grid[y][x];
        char previousValue = gridOriginal;
        gridOriginal = '#';
        if (doesObstacleSimulationLoop(grid, defaultPosition, rowCount, columnCount)) {
            loopCount++;
        }
        gridOriginal = previousValue;

        std::cout << loopCount << std::endl;
    }

    return loopCount;
}

int main() {
    std::vector<std::vector<char>> grid = readPuzzle("input.txt");
    int rowCount = grid.size();
    int columnCount = grid[0].size();

    std::tuple<int, int, int> defaultPosition = getDefaultPosition(grid, rowCount, columnCount);
    std::unordered_set<std::tuple<int, int, int>, custom_hash> visitedPositionsSet = getVisitedPositionsSet(grid, defaultPosition, rowCount, columnCount);

    visitedPositionsSet.insert(defaultPosition);

    int loopCount = doObstacleSimulations(grid, visitedPositionsSet, defaultPosition, rowCount, columnCount);
    std::cout << "Number of obstacles that cause loops: " << loopCount << std::endl;
}