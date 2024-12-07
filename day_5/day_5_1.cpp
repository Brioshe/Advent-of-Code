#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

// Rules and updates vectors to be used post separation
std::vector<std::pair<int, int>> rules; 
std::vector<std::vector<int>> updates;

// Function to check validity of update
bool isUpdateValid (const std::vector<int>& update) {
    for (const auto& rule : rules) { // Loop through each element of rules vector and separate into vars x and y
        int x = rule.first, y = rule.second;

        // Find if each part of rule exists in update
        auto itX = std::find(update.begin(), update.end(), x);
        auto itY = std::find(update.begin(), update.end(), y);

        if (itX != update.end() && itY != update.end()) { // Check if std::find returns update.end for either variable (iterator that's returned only if element isn't in list)
            if (itX > itY) { // Check if X comes after Y (invalid)
                return false;
            }
        }
    }
    return true;
}

// Function to get and return the middle page of valid updates
int getMiddlePage(const std::vector<int>& update) {
    int middleIndex = update.size() / 2;
    return update[middleIndex];
}

// Function to sum up all middle values 
int sumMiddlePages() {
    int total = 0;
    for (const auto& update: updates) { // Go through each update
        if (isUpdateValid(update)) { // Check validity
            total+= getMiddlePage(update); // Return and add middle page to total
        }
    }
    return total;
}

int main() {
    std::ifstream infile("input.txt");
    std::string line;

    bool readingUpdates = false;

    while (std::getline(infile, line)) {
        // Check if we're transitioning from rules to updates
        if (line.empty()) {
            readingUpdates = true;
            continue;
        }

        if (!readingUpdates) {
            // Parse rules in the format "X|Y"
            std::replace(line.begin(), line.end(), '|', ' ');
            std::istringstream ruleStream(line);
            int x, y;
            ruleStream >> x >> y;
            rules.emplace_back(x, y);
        } else {
            // Parse updates in the format "X,Y,Z,..."
            std::vector<int> update;
            std::replace(line.begin(), line.end(), ',', ' ');
            std::istringstream updateStream(line);
            int page;
            while (updateStream >> page) {
                update.push_back(page);
            }
            updates.push_back(update);
        }
    }

    // Debug output to confirm parsing
    std::cout << "Rules:" << std::endl;
    for (const auto& rule : rules) {
        std::cout << rule.first << " must be before " << rule.second << std::endl;
    }

    std::cout << "\nUpdates:" << std::endl;
    for (const auto& update : updates) {
        for (int page : update) {
            std::cout << page << " ";
        }
        std::cout << std::endl;
    }

    int result = sumMiddlePages();
    std::cout << "Total sum of middle pages from valid updates: " << result << std::endl;

    return 0;
}
