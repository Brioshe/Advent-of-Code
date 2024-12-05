#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

std::vector<std::pair<int, int>> directions = {
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

bool validityCheck (int x, int y, int dx, int dy, const std::vector<std::vector<char>>& puzzle) {
    int rowCount = puzzle.size();
    int columnCount = puzzle[0].size();
    int newx = x + dx;
    int newy = y + dy;

    if (newx < 0 || newx >= rowCount || newy < 0 || newy >= columnCount) {
        return false;
    }

    if (puzzle[newx][newy] == 'S' || puzzle[newx][newy] == 'M') {
        int newerx = x + (dx * -1);
        int newery = y + (dy * -1);

        if (newerx < 0 || newerx >= rowCount || newery < 0 || newery >= columnCount) {
        return false;
        }

        if (puzzle[newx][newy] == 'S' && puzzle[newerx][newery] == 'M') {
            return true;
        }
        if (puzzle[newx][newy] == 'M' && puzzle[newerx][newery] == 'S') {
            return true;
        }
        return false;
    }
    return false;
}

int countOccurences (const std::string&, const std::vector<std::vector<char>>& puzzle) {
    int rowCount = puzzle.size();
    int columnCount = puzzle[0].size();
    int count = 0;

    for(int x = 0; x < rowCount; x++) {
        for(int y = 0; y < columnCount; y++) {
            if (puzzle[x][y] == 'A') {
                if(validityCheck(x, y, -1, -1, puzzle) && validityCheck(x, y, -1, 1, puzzle)) {
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