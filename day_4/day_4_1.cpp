#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

std::vector<std::pair<int, int>> directions = {
    {0, 1},  // Right
    {0, -1}, // Left
    {1, 0},  // Down
    {-1, 0}, // Up
    {1, 1},  // Diagonal down-right
    {1, -1}, // Diagonal down-left
    {-1, 1}, // Diagonal up-right
    {-1, -1} // Diagonal up-left
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

bool validityCheck (int x, int y, int dx, int dy, const std::string& target, const std::vector<std::vector<char>>& puzzle) {
    int rowCount = puzzle.size();
    int columnCount = puzzle[0].size();

    for (int i = 0; i < target.size(); i++) {
        int newx = x + i * dx;
        int newy = y + i * dy;

        if (newx < 0 || newy < 0 || newx >= rowCount || newy >= columnCount || puzzle[newx][newy] != target[i]) {
            return false;
        }
    }

    return true;
}

int countOccurences (const std::string& target, const std::vector<std::vector<char>>& puzzle) {
    int rowCount = puzzle.size();
    int columnCount = puzzle[0].size();
    int count = 0;

    for(int x = 0; x < rowCount; x++) {
        for(int y = 0; y < columnCount; y++) {
            for(const auto& [dx, dy] : directions) {
                if (validityCheck(x, y, dx, dy, target, puzzle)) {
                    count++;
                }
            }
        }
    }

    return count;
}

int main() {

    std::vector<std::vector<char>> puzzle = readPuzzle("input.txt"); // Read puzzle from file and assign it to a 2D vector grid.
    std::string target = "XMAS";

    std::cout << "\nNumber of occurences: " << countOccurences(target, puzzle) << std::endl;
    return 0;
}